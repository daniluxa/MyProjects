#include "main.h"
#include "string.h"
#include "timers.h"
#include "W25Qxx.h"
#include "sensors.h"
#include "eeprom_lib.h"
#include "sound.h"
#include "BQ25887.h"
#include "gps.h"
#include "some_stuff.h"
#include "zigbee.h"
#include "mqtt_stuff.h"

#define BYTE2FLOAT(X) ((uint32_t)X[1] | (uint32_t)X[0] << 8 | (uint32_t)X[3] << 16 | (uint32_t)X[2] << 24)

#define FW_CRC_RECEIVED     *((uint32_t*)&mqtt_rx_buffer[12])
#define FW_LEN              *((uint32_t*)&mqtt_rx_buffer[4])

typedef struct TxMQTT_Msg
{
  char     *pTopic;
  uint8_t  *pData;
  uint16_t  DataSize;

  struct TxMQTT_Msg *pNext;
} TxMQTT_Msg, *pTxMQTT_Msg;

typedef enum
{
  MQTT_FIRST_MSG        = 0,
  MQTT_ALL_MSGS         = 1
} mqtt_msg2kill;

typedef enum
{
  FB_OK = 0,
  FB_ERR,
  FB_INFO
} mqtt_fb;

typedef enum
{
  NO_VALID_CMD = 0,
  CMD_INFO,
  CMD_RESET,
  CMD_SYNC_TIME,
  CMD_ADD_SENS,
  CMD_DEL_SENS,
  CMD_PAUSE_SENS,
  CMD_RESTART_SENS,
  CMD_POWER,
  CMD_REBOOT,
  CMD_FIRMWARE,
  CMD_FWINFO,
  CMD_FLASHFLAG,
  CMD_RAWDATA,
  CMD_NETCFG,
  CMD_RSCFG
} topic_cmd;

typedef enum
{
  NO_INTERFACE = 0,
  iRS1,
  iRS2,
  iRS3,
  iCAN,
  iAN1,
  iAN2,
  UNKNOWN_CMD  
} act_interface;



extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim7;
extern RTC_HandleTypeDef hrtc;
extern bool Service_mode;

extern struct netif gnetif;

extern uint8_t flag_pub_busy;
extern uint8_t flag_conn_ack;
extern uint8_t flag_sub_ack;
extern char mqtt_last_topicname[256];
extern char mqtt_rx_buffer[512];
extern uint32_t reboot_cntr;
extern int8_t GPS_timezone_h;
extern int8_t GPS_timezone_m;
extern __IO uint8_t DHCP_state;
extern uint32_t status_reg;

mqtt_client_t mqtt_client_global;
struct mqtt_connect_client_info_t client_info;
pRSx_SensorsChain pRSx[3] = {&RS1_SensorsChain, &RS2_SensorsChain, &RS3_SensorsChain};
uint32_t status_update_timer = 0xFF;
uint8_t device_paused = 0;
uint8_t add_raw_data = 0;

pTxMQTT_Msg pFirstMQTTmsg = NULL;

int32_t mqtt_kill_msg(mqtt_msg2kill msg);
uint32_t SendViaMQTT(UART_HandleTypeDef* pHuart, pSensorElem pSensor, uint8_t *pBuff, uint32_t DataSize);
void MQTT_RSx_StatusUpdate(pRSx_SensorsChain pChain);
uint32_t SendMsg2MQTT(MSG_TypeDef msg, void *pbuf, uint32_t datasize);


/**
  * @brief  
  * @param  
  * @retval 
  */
void mqtt_init_user(void)
{
  static char mqtt_id[20];
   

  status_update_timer = get_timer();
  init_timer(status_update_timer, 10555);
  //gps_timer = get_timer();
  //init_timer(gps_timer, 10555-1000);  
  
  //HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
  
  SendMsg = SendMsg2MQTT;
  
  memset(&mqtt_client_global, 0, sizeof(mqtt_client_global));

  memset(&client_info, 0, sizeof(client_info));
  if ( strcmp("%sn", cfg_eth->MQTT_ID) == 0 ) 
  {
    sprintf(mqtt_id, "%lld", dev_info->Serial_num);
    client_info.client_id = mqtt_id;
  }
  else client_info.client_id = cfg_eth->MQTT_ID;
  client_info.client_user = cfg_eth->MQTT_user;
  client_info.client_pass = cfg_eth->MQTT_password;
  client_info.keep_alive = 60;
    /*client_info.will_msg = mqtt_user;
    client_info.will_qos = 1;
    client_info.will_retain = 0;
    client_info.will_topic = mqtt_user;*/
  
  InitRSSensorsChain(&RS1_SensorsChain, RS1, &RS1_huart, RS1_VCC_EN_GPIO_Port, RS1_VCC_EN_Pin, rs1_config->State, rs1_config->ErrorCnt, rs1_config->FirstReqDelay, MQTT_RSx_StatusUpdate);
  for ( int i = 0; i < rs1_sensors->NumOfSensors; i++ ) AddSensor2Chain(&RS1_SensorsChain, 
    AddSensor(rs1_sensors->Sensors[i].ID,   rs1_sensors->Sensors[i].Address, rs1_sensors->Sensors[i].Name, rs1_sensors->Sensors[i].PollPeriod*1000, RS_SensorRead, SendViaMQTT));
  
  InitRSSensorsChain(&RS2_SensorsChain, RS2, &RS2_huart, RS2_VCC_EN_GPIO_Port, RS2_VCC_EN_Pin, rs2_config->State, rs2_config->ErrorCnt, rs2_config->FirstReqDelay, MQTT_RSx_StatusUpdate);
  for ( int i = 0; i < rs2_sensors->NumOfSensors; i++ ) AddSensor2Chain(&RS2_SensorsChain, 
    AddSensor(rs2_sensors->Sensors[i].ID,   rs2_sensors->Sensors[i].Address, rs2_sensors->Sensors[i].Name, rs2_sensors->Sensors[i].PollPeriod*1000, RS_SensorRead, SendViaMQTT));

  InitRSSensorsChain(&RS3_SensorsChain, RS3, &RS3_huart, RS3_VCC_EN_GPIO_Port, RS3_VCC_EN_Pin, rs3_config->State, rs3_config->ErrorCnt, rs3_config->FirstReqDelay, MQTT_RSx_StatusUpdate);
  for ( int i = 0; i < rs3_sensors->NumOfSensors; i++ ) AddSensor2Chain(&RS3_SensorsChain, 
    AddSensor(rs3_sensors->Sensors[i].ID,   rs3_sensors->Sensors[i].Address, rs3_sensors->Sensors[i].Name, rs3_sensors->Sensors[i].PollPeriod*1000, RS_SensorRead, SendViaMQTT));



  SendMsg2MQTT(MSG_STARTUP, NULL, 0);
}


/**
  * @brief  
  * @param  
  * @retval 
  */
topic_cmd get_topic_cmd(char* pbuff, act_interface* iface)
{
  char *ptemp = pbuff;
  uint32_t len = 0;
  
  while ( *ptemp != '/' && *ptemp != 0 )
  {
    len++;
    ptemp++;
  }
   
  if ( *ptemp++ == '/' )
  {        
    if      ( strcmp(ptemp, "RS1") == 0 ) *iface = iRS1;
    else if ( strcmp(ptemp, "RS2") == 0 ) *iface = iRS2;
    else if ( strcmp(ptemp, "RS3") == 0 ) *iface = iRS3;
    else if ( strcmp(ptemp, "CAN") == 0 ) *iface = iCAN;
    else if ( strcmp(ptemp, "AN1") == 0 ) *iface = iAN1;
    else if ( strcmp(ptemp, "AN2") == 0 ) *iface = iAN2;
    else *iface = UNKNOWN_CMD;
   
    pbuff[len] = NULL;
  }
  else *iface = NO_INTERFACE;
  
  if ( strcmp(pbuff, "Time")      == 0 ) return CMD_SYNC_TIME;
  if ( strcmp(pbuff, "Info")      == 0 ) return CMD_INFO;
  if ( strcmp(pbuff, "Add")       == 0 ) return CMD_ADD_SENS;
  if ( strcmp(pbuff, "Del")       == 0 ) return CMD_DEL_SENS;
  if ( strcmp(pbuff, "Start")     == 0 ) return CMD_RESTART_SENS;
  if ( strcmp(pbuff, "Pause")     == 0 ) return CMD_PAUSE_SENS;
  if ( strcmp(pbuff, "Reset")     == 0 ) return CMD_RESET;
  if ( strcmp(pbuff, "Pwr")       == 0 ) return CMD_POWER;
  if ( strcmp(pbuff, "Reboot")    == 0 ) return CMD_REBOOT;
  if ( strcmp(pbuff, "Fw")        == 0 ) return CMD_FIRMWARE;
  if ( strcmp(pbuff, "Fwinfo")    == 0 ) return CMD_FWINFO;
  if ( strcmp(pbuff, "Flashflag") == 0 ) return CMD_FLASHFLAG;  
  if ( strcmp(pbuff, "Rawdata")   == 0 ) return CMD_RAWDATA;  
  if ( strcmp(pbuff, "Netconfig") == 0 ) return CMD_NETCFG;  
  if ( strcmp(pbuff, "Config")    == 0 ) return CMD_RSCFG;  

  return NO_VALID_CMD;
  
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t mqtt_send_feedback(mqtt_fb result, char* appendex, char* comment )
{
  char mqtt_topic[MAX_TOPIC_LEN];
  char* ptopic;
  char data[MAX_PAYLOAD_SIZE] = {0};
  
  if ( get_mqtt_topic(NULL, CTRL_OUT, mqtt_topic) != 0 ) return 1;
  ptopic = mqtt_topic+strlen(mqtt_topic);
  if ( appendex ) strcpy(ptopic, appendex);
  if ( result != FB_INFO )
    strcpy(data, result ? "ERR" : "OK");  
  if ( comment ) strcat(data, comment);    
  
  mqtt_add2queue(mqtt_topic, (uint8_t*)data, strlen(data));
  
  return 0;
}

#define DEVICE_PAUSE  1
#define DEVICE_RESUME 0
/**
  * @brief  
  * @param  
  * @retval 
  */
void PauseDevice(uint32_t state)
{
  device_paused = state;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void mqtt_receive(uint32_t datasize)
{
    char buff[100];
    char apdx[20];
    uint32_t len, topic_len;
    act_interface iface;
    topic_cmd cmd;
    
    if ( mqtt_last_topicname[0] == 0 || datasize == 0 ) return;
    get_mqtt_topic(NULL, SUBSCRIBE, buff);
    len = strlen(buff);
    topic_len = strlen(mqtt_last_topicname);
    if ( len >= topic_len ) 
    {
      mqtt_send_feedback(FB_ERR, NULL, ": topic error");
      return;
    }
    strcpy(apdx, &mqtt_last_topicname[len-1]);    
    
    cmd = get_topic_cmd(&mqtt_last_topicname[len-1], &iface);
    if ( iface == UNKNOWN_CMD )
    {
      mqtt_send_feedback(FB_ERR, apdx, ": unknown interface");
      return;
    }
    
    switch (cmd)
    {
      /* Установка системного времени */
      case CMD_SYNC_TIME: { // читаем такой формат 2022-11-30T12:00:00+03:00 
        int32_t year, month, day;
        int32_t hours, minutes, seconds;
        int32_t timezone_h, timezone_m;
        int res;
        
        res = sscanf(mqtt_rx_buffer, "%d-%d-%dT%d:%d:%d%d:%d", &year, &month, &day, &hours, &minutes, &seconds, &timezone_h, &timezone_m);

        if ( res != 8 ) 
        {
          mqtt_send_feedback(FB_ERR, apdx, ": incorrect format");
          break;
        }
        
        if ( year >= 2022 && year < 2100 && month <= 12 && hours <= 23 && minutes <= 59 && seconds <= 59 && timezone_h >= -12 && timezone_h <= 14 && (timezone_m == 0 || timezone_m == 30 || timezone_m == 45) )
        {
          RTC_TimeTypeDef sTime = {0};
          RTC_DateTypeDef sDate = {0};
          
          /* Get the RTC current Time */
          HAL_RTC_GetTime(&hrtc, &sTime, FORMAT_BIN);
          /* Get the RTC current Date */
          HAL_RTC_GetDate(&hrtc, &sDate, FORMAT_BIN);        
      
          sDate.Year  = year-2000;
          sDate.Month = month;
          sDate.Date  = day;
          sTime.Hours   = hours;
          sTime.Minutes = minutes;
          sTime.Seconds = seconds;
          
          GPS_timezone_h = timezone_h;
          GPS_timezone_m = timezone_m;
    
          HAL_RTC_SetTime(&hrtc, &sTime, FORMAT_BIN);
          HAL_RTC_SetDate(&hrtc, &sDate, FORMAT_BIN);
          
          mqtt_send_feedback(FB_OK, apdx, NULL);  
        }          
        else mqtt_send_feedback(FB_ERR, apdx, ": incorrect values");  
        
      } break;
      
      /* Управление питанием на разъёмах датчиков */
      case CMD_POWER: {
        uint32_t pwr_switch = mqtt_rx_buffer[0] == '0' ? 0 : 1;
        uint32_t res = 1;
        
        switch (iface) {
          case iRS1: {
            res = RSSensorsChainPwrSwitch(&RS1_SensorsChain, pwr_switch);
          } break;
          case iRS2: {
            res = RSSensorsChainPwrSwitch(&RS2_SensorsChain, pwr_switch);
          } break;
          case iRS3: {
            res = RSSensorsChainPwrSwitch(&RS3_SensorsChain, pwr_switch);
          } break;
        }
        mqtt_send_feedback(res ? FB_ERR : FB_OK, apdx, NULL); 
        
      } break;

      /* Перезагрузка устройства */
      case CMD_REBOOT: {
        if ( mqtt_rx_buffer[0] == '1' )
        {
          mqtt_send_feedback(FB_OK, apdx, ": reboot in 5 sec...");         
          reboot_cntr = 5000;
          PauseDevice(DEVICE_PAUSE);
        }
        else mqtt_send_feedback(FB_ERR, apdx, ": WAT?");         
        
      } break;
      
      /* Обновление прошивки */
      case CMD_FIRMWARE: {
        uint16_t page_num  = *(uint16_t*)mqtt_rx_buffer;
        uint16_t data_size = *(uint16_t*)&mqtt_rx_buffer[2];
                
        if ( page_num == 0 )
        {
          HAL_GPIO_WritePin(ZB_LED2_GPIO_Port, ZB_LED2_Pin, GPIO_PIN_RESET);
          ZIGBEE_POWER_OFF();
          PauseDevice(DEVICE_PAUSE);
          // Erase flash for new firmware          
          HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
          for (uint8_t i = 0; i < 16; i++){
            W25qxx_EraseBlock(FLASH_FIRM_START_BLOCK + i);
          }              
          HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
        }
                
        if ( page_num >= 0xFFFE )
        {          
          char answ[60] = ": CRC verified!";        
          uint32_t fw_crc_calc = W25qxx_CRCFirmware(FW_LEN);
          
          if( FW_CRC_RECEIVED == fw_crc_calc ){
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
            W25qxx_EraseSector(FLASH_FIRM_PARAM_SECTOR);
            W25qxx_WriteSector((uint8_t*)&mqtt_rx_buffer[4], FLASH_FIRM_PARAM_SECTOR, 0, data_size);
            // set flag for bootloader
            W25qxx_SetFlagFirmware(true);
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
            if ( page_num == 0xFFFF ) 
            {
              reboot_cntr = 5000;
              strcat(answ, " Reboot in 5 sec...");
            }
            else PauseDevice(DEVICE_RESUME);
            mqtt_send_feedback(FB_OK, apdx, answ);  
          }
          else mqtt_send_feedback(FB_ERR, apdx, ": CRC error");         
          
        }
        else 
        {
          char answ[20];
          
          if ( page_num > 1300 )
            mqtt_send_feedback(FB_ERR, apdx, "Page number out of range");                
          else
          {
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
            W25qxx_WritePage((uint8_t*)&mqtt_rx_buffer[4], FLASH_FIRM_START_PAGE + page_num, 0, data_size);   
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
            sprintf(answ, ": page num #%d", page_num);
            mqtt_send_feedback(FB_OK, apdx, answ);    
          }
        }
      } break;
      
      /* Отправляем информацию о прошивке */
      case CMD_FWINFO: {
          char answ[60];        
          uint32_t firm_vers = *(uint32_t*)(FRM_VERSION_ADDR);         
          uint32_t firm_build = *(uint32_t*)(FRM_BUILD_NUM_ADDR);
          sprintf(answ, "FW v%d.%d.%d, build #%d", (firm_vers>>16)&0xFF, (firm_vers>>8)&0xFF, firm_vers&0xFF, firm_build);
          mqtt_send_feedback(FB_INFO, apdx, answ);                 
      } break;
      
      /* Выставляем флаг бутлодеру на перепрошивку (если она лежит во флэшке) */
      case CMD_FLASHFLAG: {
          if ( mqtt_rx_buffer[0] == '1' )
          {
            W25qxx_SetFlagFirmware(true);        
            mqtt_send_feedback(FB_OK, apdx, NULL);                 
          }
          else mqtt_send_feedback(FB_ERR, apdx, ": WAT?"); 
      } break;

      /* Включаем в выдачу сырые данные с датчиков */
      case CMD_RAWDATA: {
        if ( mqtt_rx_buffer[0] == '1' ) add_raw_data = 1;
        else if ( mqtt_rx_buffer[0] == '0' ) add_raw_data = 0;
        else 
        {
          mqtt_send_feedback(FB_ERR, apdx, NULL);  
          break;
        }
        mqtt_send_feedback(FB_OK, apdx, NULL);                 
      } break;
      
      /* Установка/запрос сетевых настроек */
      case CMD_NETCFG: {
        if ( mqtt_rx_buffer[0] == '?' ) 
        {
          char answ[MAX_PAYLOAD_SIZE]; 
          
          sprintf(answ, "{\"IP\":\"%hhu.%hhu.%hhu.%hhu\",\"Netmask\":\"%hhu.%hhu.%hhu.%hhu\",\"Gateway\":\"%hhu.%hhu.%hhu.%hhu\",\"MAC\":\"%02X-%02X-%02X-%02X-%02X-%02X\",\"DHCP\":%hhu}",
          /* IP Address */ (gnetif.ip_addr.addr)&0xFF, (gnetif.ip_addr.addr>>8)&0xFF, (gnetif.ip_addr.addr>>16)&0xFF, (gnetif.ip_addr.addr>>24)&0xFF, 
          /*   Netmask  */ (gnetif.netmask.addr)&0xFF, (gnetif.netmask.addr>>8)&0xFF, (gnetif.netmask.addr>>16)&0xFF, (gnetif.netmask.addr>>24)&0xFF, 
          /*   Gateway  */ (gnetif.gw.addr)&0xFF, (gnetif.gw.addr>>8)&0xFF, (gnetif.gw.addr>>16)&0xFF, (gnetif.gw.addr>>24)&0xFF,
          /*  MAC, DHCP */ gnetif.hwaddr[0], gnetif.hwaddr[1], gnetif.hwaddr[2], gnetif.hwaddr[3], gnetif.hwaddr[4], gnetif.hwaddr[5], DHCP_state);          
          mqtt_send_feedback(FB_INFO, apdx, answ);                           
        }
        else
        {
          char *pbuff = mqtt_rx_buffer;
          EthernetConfig ecfg = config.ethernet;
          int flag = 1;
          while ( *pbuff && flag )
          {
            if ( *pbuff == 0x0A || *pbuff == ' ' || *pbuff == ';' ) pbuff++;
            
            if ( memcmp(pbuff, "MAC", 3) == 0 ) {
              uint8_t HW_addr[6];  
              int res;
              
              res = sscanf(pbuff, "MAC %02hhX-%02hhX-%02hhX-%02hhX-%02hhX-%02hhX", &HW_addr[0], &HW_addr[1], &HW_addr[2], &HW_addr[3], &HW_addr[4], &HW_addr[5]);
              if ( res != 6 ) flag = 0;
              else memcpy(ecfg.HW_addr, HW_addr, 6);              
            }
            else if ( memcmp(pbuff, "IP", 2) == 0 ) {
              uint8_t Dev_IP[4];
              int res;
              
              res = sscanf(pbuff, "IP %hhu.%hhu.%hhu.%hhu", &Dev_IP[0], &Dev_IP[1], &Dev_IP[2], &Dev_IP[3]);
              if ( res != 4 ) flag = 0;
              else memcpy(ecfg.Dev_IP, Dev_IP, 4);              
            }            
            else if ( memcmp(pbuff, "MASK", 4) == 0 ) {
              uint8_t Net_mask[4];              
              int res;
              
              res = sscanf(pbuff, "MASK %hhu.%hhu.%hhu.%hhu", &Net_mask[0], &Net_mask[1], &Net_mask[2], &Net_mask[3]);
              if ( res != 4 ) flag = 0;
              else memcpy(ecfg.Net_mask, Net_mask, 4);              
            }
            else if ( memcmp(pbuff, "GW", 2) == 0 ) {
              uint8_t GW_IP[4];
              int res;
              
              res = sscanf(pbuff, "GW %hhu.%hhu.%hhu.%hhu", &GW_IP[0], &GW_IP[1], &GW_IP[2], &GW_IP[3]);
              if ( res != 4 ) flag = 0;
              else memcpy(ecfg.GW_IP, GW_IP, 4);              
            }
            else if ( memcmp(pbuff, "DHCP", 4) == 0 ) {
              uint8_t DHCP_flag;            
              int res;
              
              res = sscanf(pbuff, "DHCP %hhu", &DHCP_flag);
              if ( res != 1 ) flag = 0;
              else ecfg.DHCP_flag = DHCP_flag;
            }
            
            while ( *pbuff != 0x0A && *pbuff != ';' && *pbuff != NULL ) pbuff++;
          }
          
          if ( flag == 0 )
            mqtt_send_feedback(FB_ERR, apdx, ": format error"); 
          else
          {
            config.ethernet = ecfg;
            save_settings(PRIMARY_CONF_SECT);
            mqtt_send_feedback(FB_OK, apdx, NULL);                 
          }
        }
      } break;

      /* Добавление нового датчика */
      case CMD_ADD_SENS: {
        SensorsConfig  *rs_sensors;
        Cfg_Sensor *pNewSens;
        uint32_t address, type, poll_period;
        uint32_t res;
        char sens_name[16];
        char answ[30];
        RSx_SensorsChain *pChain = NULL;
        
                
        switch (iface) {
          case iRS1: pChain = &RS1_SensorsChain; rs_sensors = &config.sensors[0]; break;          
          case iRS2: pChain = &RS2_SensorsChain; rs_sensors = &config.sensors[1]; break;            
          case iRS3: pChain = &RS3_SensorsChain; rs_sensors = &config.sensors[2]; break;
          default: {
            mqtt_send_feedback(FB_ERR, apdx, ": inapplicable"); 
          } break;
        }                              
        
        if ( pChain )
        {
          res = sscanf(mqtt_rx_buffer, "%d %d %s %d", &address, &type, sens_name, &poll_period);
          if ( res != 4 ) 
          {
            mqtt_send_feedback(FB_ERR, apdx, ": format error");
            break;
          }
          if ( rs_sensors->NumOfSensors == 32 )
          {
            mqtt_send_feedback(FB_ERR, apdx, ": maximum number of sensors");
            break;
          }
          if ( type > MAX_SENSOR_ID )
          {
            mqtt_send_feedback(FB_ERR, apdx, ": unknown sensor type");
            break;
          }
            
          pNewSens = &rs_sensors->Sensors[rs_sensors->NumOfSensors++];
          pNewSens->Address = address;
          pNewSens->ID = type;
          pNewSens->PollPeriod = poll_period;
          strcpy(pNewSens->Name, sens_name);
          pNewSens->Status = 1;
          save_settings(PRIMARY_CONF_SECT);
          AddSensor2Chain(pChain, AddSensor(pNewSens->ID, pNewSens->Address, pNewSens->Name, pNewSens->PollPeriod*1000, RS_SensorRead, SendViaMQTT));        
          sprintf(answ, ": number of sensors #%d", rs_sensors->NumOfSensors);
          mqtt_send_feedback(FB_OK, apdx, answ);
          
        }        
      } break;

      /* Удаление, приостановка и возобновление опроса датчиков */
      case CMD_DEL_SENS:
      case CMD_RESTART_SENS:         
      case CMD_PAUSE_SENS: {
        SensorsConfig  *rs_sensors;
        Cfg_Sensor *pSens;
        RSx_SensorsChain *pChain = NULL;
        uint32_t address, type;
        uint32_t res;
        uint32_t num;
                
        switch (iface) {
          case iRS1: pChain = &RS1_SensorsChain; rs_sensors = &config.sensors[0]; break;          
          case iRS2: pChain = &RS2_SensorsChain; rs_sensors = &config.sensors[1]; break;            
          case iRS3: pChain = &RS3_SensorsChain; rs_sensors = &config.sensors[2]; break;
          default: {
            mqtt_send_feedback(FB_ERR, apdx, ": inapplicable"); 
          } break;
        }                              
        
        if ( pChain )
        {
          res = sscanf(mqtt_rx_buffer, "%d %d", &address, &type);
          if ( res != 2 ) 
          {
            /* Удаляем все датчики, если пришла '*' */
            if ( mqtt_rx_buffer[0] == '*' && cmd == CMD_DEL_SENS )
            {
              rs_sensors->NumOfSensors = 0;
              DelSensorFromChain(pChain, 0, 0);

              save_settings(PRIMARY_CONF_SECT);              
              mqtt_send_feedback(FB_OK, apdx, ": number of sensors #0");
              break;
            }
            
            mqtt_send_feedback(FB_ERR, apdx, ": format error");
            break;
          }
          
          if ( cmd == CMD_DEL_SENS ) 
            res = DelSensorFromChain(pChain, type, address);
          else
            res = RSSensorPause(pChain, address, type, (cmd == CMD_RESTART_SENS) ? 1:0); 
          
          if ( res ) mqtt_send_feedback(FB_ERR, apdx, ": sensor not found"); 
          else 
          {
            char answ[30] = {0};
            if ( cmd == CMD_DEL_SENS )
            {
              num = rs_sensors->NumOfSensors;
              if ( num > 1 )
              {
                uint32_t i;
                for ( i = 0; i < num; i++ )
                {
                  pSens = &rs_sensors->Sensors[i];
                  if ( (pSens->Address == address) && (pSens->ID == type) ) break;                    
                }
                
                /* Если удаляем не последний датчик в списке, то просто копируем на его место последний */
                if ( i < (num-1) )
                  rs_sensors->Sensors[i] = rs_sensors->Sensors[num-1];                
              }
              rs_sensors->NumOfSensors--;

              save_settings(PRIMARY_CONF_SECT);              
              sprintf(answ, ": number of sensors #%d", rs_sensors->NumOfSensors);
            }
            mqtt_send_feedback(FB_OK, apdx, answ);
          }
        }        
      } break;
      
      /* Запрос конфигурации датчиков, висящих на интерфейсе */
      case CMD_INFO: {
        RSx_SensorsChain *pChain = NULL;
        pSensorElem pSensor;
        char answ[MAX_PAYLOAD_SIZE] = {'1', '/', '1', ' '};
        char *pansw = &answ[4];
                
        if ( mqtt_rx_buffer[0] != '?' ) 
        {
          mqtt_send_feedback(FB_ERR, apdx, ": WAT?");
          break;
        }
        
        switch (iface) {
          case iRS1: pChain = &RS1_SensorsChain; break;          
          case iRS2: pChain = &RS2_SensorsChain; break;            
          case iRS3: pChain = &RS3_SensorsChain; break;
          default: {
            mqtt_send_feedback(FB_ERR, apdx, ": inapplicable"); 
          } break;
        }      
        
        if ( pChain->pSensorsChain == NULL )
        {
          answ[0] = '-';
          answ[1] = NULL;
        }
        else
        {
          pSensor = pChain->pSensorsChain;
          while ( pSensor )
          {
            pansw += sprintf(pansw, "%hhu %hu %s %d %hhu;", pSensor->DevAddr, pSensor->SensorType, pSensor->SensorName, pSensor->PollPeriod/1000, pSensor->SensorEnabled);
            /* Если приблизились к максимальному размеру посылки, то отправляем 2мя частями */
            if ( pansw + 50 > &answ[MAX_PAYLOAD_SIZE] )
            {
              if ( pSensor->pNext ) 
              {
                answ[2] = '2';
                pansw = &answ[4];
                mqtt_send_feedback(FB_INFO, apdx, answ);                           
                answ[0] = '2';
              }
            }
            pSensor = pSensor->pNext;
          }
        }
        mqtt_send_feedback(FB_INFO, apdx, answ);                           
      } break;
           
      /* Восстановление настроек из резервной копии */
      case CMD_RESET: {
        if ( mqtt_rx_buffer[0] != '1' ) mqtt_send_feedback(FB_ERR, apdx, ": WAT?"); 
        else
        {
          if ( read_cfg_eeprom(RESERV_CONF_SECT) == HAL_OK )
          {
            save_settings(PRIMARY_CONF_SECT);
            mqtt_send_feedback(FB_OK, apdx, NULL);
          }
          else mqtt_send_feedback(FB_ERR, apdx, ": no reserv configuration"); 
        }
        
      } break;

      /* Конфигурация RS-интерфейсов */
      case CMD_RSCFG: {
        char answ[50];
        RSConfig *rs_config = NULL;
                        
        switch (iface) {
          case iRS1: rs_config = rs1_config; break;          
          case iRS2: rs_config = rs2_config; break;            
          case iRS3: rs_config = rs3_config; break;
          default: {
            mqtt_send_feedback(FB_ERR, apdx, ": inapplicable"); 
          } break;
        }      
        
        if ( rs_config )
        {
          uint32_t br;
          uint8_t db, parity, sb, state;
          int res;
          
          /* Запрос параметров */
          if ( mqtt_rx_buffer[0] == '?' ) 
          {
            sprintf(answ, "%d %hhu %hhu %hhu %hhu", rs_config->BaudRate, rs_config->DataBits, rs_config->Parity, rs_config->StopBits, rs_config->State);
            mqtt_send_feedback(FB_INFO, apdx, answ);                           
            break;
          }
          
          /* Установка параметров */
          res = sscanf(mqtt_rx_buffer, "%d %hhu %hhu %hhu %hhu", &br, &db, &parity, &sb, &state);
                       
          if ( res != 5 ) 
          {
            mqtt_send_feedback(FB_ERR, apdx, ": incorrect format");
            break;
          }
          if ( br < 256000 ) 
            rs_config->BaudRate = br;
          if ( db < 2 )
            rs_config->DataBits = db;
          if ( parity < 3 )
            rs_config->Parity = parity;
          if ( sb < 2 )
            rs_config->StopBits = sb;
          if ( state < 2 )
            rs_config->State = state;          
          save_settings(PRIMARY_CONF_SECT);
          mqtt_send_feedback(FB_OK, apdx, NULL);
        }        
      } break;      
        
      default: {
        mqtt_send_feedback(FB_ERR, apdx, ": unknown command");         
      }

      
    }
}

/**
  * @brief  
  * @param  
  * @retval 
  */
err_t mqtt_connect(mqtt_client_t *client)
{
  err_t _err;

  ip_addr_t ipaddr;
  IP4_ADDR(&ipaddr, cfg_eth->Broker_addr[0],  cfg_eth->Broker_addr[1],  cfg_eth->Broker_addr[2],  cfg_eth->Broker_addr[3]);


  //flag_conn_ack = 0;
  _err = mqtt_client_connect(client, &ipaddr, cfg_eth->Broker_port, mqtt_connection_cb, NULL, &client_info);
  print_err(_err);

  /*if (timeout_wait(120, &flag_conn_ack, "Connection ack timeout!\n") == TIMEOUT_TRIGGERED)
  {
    mqtt_disconnect(client);
    _err = ERR_TIMEOUT;
  }*/


  return _err;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
err_t mqtt_sub(mqtt_client_t *client)
{
  err_t _err;
  char mqtt_topic[MAX_TOPIC_LEN];

  flag_sub_ack = 0;
  mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, NULL);
  get_mqtt_topic(NULL, SUBSCRIBE, mqtt_topic);
  _err = mqtt_subscribe(client, mqtt_topic, MQTT_QOS_AtMostOnce, mqtt_sub_request_cb, NULL);
  print_err(_err);

//  if (timeout_wait(200, &flag_sub_ack, "Subscription ack timeout!\n") == TIMEOUT_TRIGGERED)
//  {
//    _err = ERR_TIMEOUT;
//  }

  return _err;
}

err_t mqtt_send(mqtt_client_t *client, char *topicname, char *data, uint16_t data_len)
{
  err_t _err;

  
  _err = mqtt_publish(client, topicname, data, data_len, MQTT_QOS_AtLeastOnce, MQTT_NoRetain, mqtt_pub_request_cb, NULL);
  if ( _err == ERR_OK ) flag_pub_busy = 1;
  
  print_err(_err);

 /* if (timeout_wait(200, &flag_pub_ack, "Sending ack timeout!\n") == TIMEOUT_TRIGGERED || flag_pub_ack == 2)
  {
    _err = ERR_TIMEOUT;
  }
  else play_rt(rt_wdt, 0, 0);*/

  return _err;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
int32_t mqtt_add2queue(char *pTopicName, uint8_t *pData, uint16_t DataSize)
{    
  pTxMQTT_Msg pNewMsg, pTempMsg;
  uint32_t queue_len = 0;
  
  if ( ethernet_link_state == 0 ) return -4;
   
  if ( DataSize > MAX_PAYLOAD_SIZE) return -5;
  
  pNewMsg = malloc(sizeof(TxMQTT_Msg));
  if ( pNewMsg == NULL ) return -1;
  
  pNewMsg->pData = malloc(DataSize);
  if ( pNewMsg->pData == NULL ) 
  {
    free(pNewMsg);
    return -2;
  }
  memcpy(pNewMsg->pData, pData, DataSize);
  pNewMsg->DataSize = DataSize;
  
  pNewMsg->pTopic = malloc(strlen(pTopicName)+1);
  if ( pNewMsg->pTopic == NULL ) 
  {
    free(pNewMsg->pData);
    free(pNewMsg);
    return -3;
  }
  strcpy(pNewMsg->pTopic, pTopicName);
  
  pNewMsg->pNext = NULL;

  if ( pFirstMQTTmsg == NULL ) pFirstMQTTmsg = pNewMsg;
  else 
  {
    pTempMsg = pFirstMQTTmsg;
    while ( pTempMsg->pNext != NULL )
    {
      pTempMsg = pTempMsg->pNext;
      queue_len++;
    }
    pTempMsg->pNext = pNewMsg;
  }
  if ( queue_len == 64 ) mqtt_kill_msg(MQTT_FIRST_MSG);                         // слишком много скопилось. что-то не так.
  
  return 0;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
int32_t mqtt_kill_msg(mqtt_msg2kill msg)
{
  pTxMQTT_Msg pTempMsg;
    
  if ( pFirstMQTTmsg == NULL ) return -1;
  
  do {
    pTempMsg = pFirstMQTTmsg->pNext;
    
    free(pFirstMQTTmsg->pData);
    free(pFirstMQTTmsg->pTopic);
    free(pFirstMQTTmsg);
    pFirstMQTTmsg = pTempMsg;
  } while (pFirstMQTTmsg && (msg == MQTT_ALL_MSGS) );
  
  if ( msg == MQTT_ALL_MSGS ) flag_pub_busy = 0;
  
  return 0;
}



/**
  * @brief  
  * @param  
  * @retval 
  */
err_t mqtt_init_conn(mqtt_client_t *client)
{
  err_t _err;

  if (mqtt_client_is_connected(client))
    return ERR_OK;

  _err = mqtt_connect(client);
  print_err(_err);

  if (_err == ERR_OK)
  {
    _err = mqtt_sub(client);
    print_err(_err);
  }
  else mqtt_disconnect(client);

  return _err;
}


/**
  * @brief  
  * @param  
  * @retval 
  */
err_t mqtt_send_abstract(mqtt_client_t* mqtt_client, uint8_t* data, uint16_t datalen, char* topicname)
{
  err_t _err;

  DIAG_MSG("Data: %s\n", data);

  _err = mqtt_init_conn(mqtt_client);

  if (_err == ERR_OK)
  {
   
    _err = mqtt_send(mqtt_client, topicname, (char*)data, datalen);
    
    ///interface_mqtt_publish(mqtt_client, topicname, data, datalen);
  }
  //else mqtt_kill_msg(MQTT_ALL_MSGS);

  return _err;
}


/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t SendViaMQTT(UART_HandleTypeDef* pHuart, pSensorElem pSensor, uint8_t *pBuff, uint32_t DataSize)
{
  if(cfg_eth->mqtt_enabled){
    uint32_t len;
    char mqtt_payload[MAX_PAYLOAD_SIZE];
    char mqtt_topic[MAX_TOPIC_LEN];

    get_mqtt_topic(pHuart, pSensor->SensorType, mqtt_topic);
    len = get_sensor_data_string(pSensor, pBuff, mqtt_payload, DataSize);
    mqtt_add2queue(mqtt_topic, (uint8_t*)mqtt_payload, len);
  }
  return 0;
}


/**
  * @brief  
  * @param  
  * @retval 
  */
void MQTT_RSx_StatusUpdate(pRSx_SensorsChain pChain)
{
  uint32_t len;
  char mqtt_payload[MAX_PAYLOAD_SIZE];
  char mqtt_topic[MAX_TOPIC_LEN];

  if ( pChain->InterfaceID == RS1 )
  {
    /* Переключение транзистора, подающего 48В на разъём */
    HAL_GPIO_WritePin(RS_48V_EN_GPIO_Port, RS_48V_EN_Pin, pChain->Powered);   
    /* Переключение сигнала управляющего изолированным питанием на ADUM.*/
    HAL_GPIO_WritePin(RS1_PWR_DIS_GPIO_Port, RS1_PWR_DIS_Pin, (GPIO_PinState)!pChain->Powered); 
  }

  get_mqtt_topic(pChain->pHuart, RSxSTATUS, mqtt_topic);
  len = sprintf(mqtt_payload, "{\"Enabled\":%hd,\"Connected\":%hd,\"Powered\":%hd}",
                pChain->InterfaceEnabled, (uint8_t)pChain->Connected, (uint8_t)pChain->Powered);

  mqtt_add2queue(mqtt_topic, (uint8_t*)mqtt_payload, len);
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint8_t get_mqtt_topic(void* interface, uint16_t msg_type, char* buf)
{
  
  buf += sprintf(buf, "%s/%lld/", cfg_eth->MQTT_topic_data, dev_info->Serial_num);
     
  switch ( msg_type ) {
    case STATUS: strcat(buf, "STATE"); return 0;
    case MSG: strcat(buf, "MSG"); return 0;
    case SUBSCRIBE: strcat(buf, "CTRL/IN/#"); return 0;
    case CTRL_OUT: strcat(buf, "CTRL/OUT/"); return 0;
  }  

  strcat(buf, "DATA/");
  
  if(interface == &RS1_huart)
      strcat(buf, "RS1/");
  else if(interface == &RS2_huart)
      strcat(buf, "RS2/");
  else if(interface == &RS3_huart)
      strcat(buf, "RS3/");
  else if ( (uint32_t)interface == iZIGBEE )
      strcat(buf, "ZIGBEE/");
  else
      strcat(buf, "?/");
  
  if ( msg_type == RSxSTATUS ) 
  {
    strcat(buf, "STATE");
    return 0;
  }
  
  switch(msg_type){
    case MSU44RHTL:        strcat(buf, "MSU44RHTL");  break;
    case SEROV:            strcat(buf, "WIND");       break;
    case OXYGEN_SENS:      strcat(buf, "O2");         break;
    case EKSIK_TEMP:       strcat(buf, "TEMP");       break;
    case EKSIK_HUM:        strcat(buf, "HUM");        break;
    case EKSIK_PRES:       strcat(buf, "PRES");       break;
    case EKSIK_CH4:        strcat(buf, "CH4");        break;
    case EKSIK_O2:         strcat(buf, "O2");         break;
    case EKSIK_CO2:        strcat(buf, "CO2");        break;
    case EKSIK_NH3:        strcat(buf, "NH3");        break;
    case EKSIK_H2S:        strcat(buf, "H2S");        break;
    case EKSIK_CO:         strcat(buf, "CO");         break;
    case EKSIK_NO2:        strcat(buf, "NO2");        break;
    case EKSIK_SO2:        strcat(buf, "SO2");        break;
    case EKSIK_LIGHT:      strcat(buf, "LUM");        break;
    case EKSIK_DUST_PM10:  strcat(buf, "DUST_10");    break;
    case EKSIK_DUST_PM25:  strcat(buf, "DUST_2.5");   break;
    case ISA_LIC_v2:       strcat(buf, "ISA");        break;
    case AQARA:            strcat(buf, "AQARA");      break;
    default:               strcat(buf, "UNKNOWN"); 
  }    
  
  return 0;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
int32_t get_sensor_data_string(pSensorElem pSensor, uint8_t* data_in, char* data_out, uint32_t datasize)
{
  int32_t len = 0, tlen = 0;
  float eksik_res = -1;
            
  data_out += len = sprintf(data_out, "{\"Time\":\"20%02hhu-%02hhu-%02hhuT%02hhu:%02hhu:%02hhu\",", 
                                data_in[0], data_in[1], data_in[2], data_in[3], data_in[4], data_in[5]);
  
  if ( pSensor->SensorType != AQARA )
  {
     tlen = sprintf(data_out, "\"Addr\":%hd,\"Type\":\"%s\",", pSensor->DevAddr, pSensor->SensorName);
     data_out += tlen;
     len += tlen;
  }

  data_in += 6;
  if ( add_raw_data && datasize == 4 )
  {
    tlen = sprintf(data_out, "\"Raw [hex]\":\"%02X%02X%02X%02X\",", data_in[3], data_in[2], data_in[1], data_in[0]);
    data_out += tlen; 
    len += tlen;
  }
  
  tlen = 0;
  switch(pSensor->SensorType)
  {
    /*case MSU44RHTL:
      val1 = (float)(data[1]) + (float)(data[3]) * 0.1;
      val2 = (float)(data[5]) + (float)(data[7]) * 0.1;
      val4 = (int)(data[28] << 8) + (int)data[29];
      len = snprintf(data_out, sizeof(buf), "{\"device_id\":%lld,\"deviceType\":\"sensors\",\"sensor\":\"meteo\",\"data\":{\"Temp_C\":%f,\"Humidity\":%f,\"Light\":%d}}",
             dev_info->Serial_num, val1, val2, val4);
      break;
    case SEROV:
      val1 = (float) ((int16_t) ((data[1] << 8) | data[0])) / 1000.0;
      val2 = (float) ((int16_t) ((data[3] << 8) | data[2])) / 1000.0;
      val3 = ((data[5] << 8) | data[4]) / 10.0;
      val4 = ((data[7] & 0x07) << 8) | data[6];
      len = snprintf(data_out, sizeof(buf), "{\"device_id\":%lld,\"deviceType\":\"sensors\",\"sensor\":\"wind\",\"data\":{\"WindVelocityLongitudinal_mps\":%f,\"WindVelocityCross_mps\":%f,\"Temp_C\":%f,\"Pressure_mmHg\":%d}}",
             dev_info->Serial_num, val1, val2, val3, val4);
      break;
    case OXYGEN_SENS:
      *(uint32_t*)&val_oxy = (uint32_t)data_in[1] | (uint32_t)data_in[0]<< 8 | (uint32_t)data_in[3] << 16 | (uint32_t)data_in[2] << 24;
      len = snprintf(data_out, sizeof(buf), "{\"device_id\":%lld,\"deviceType\":\"sensors\",\"sensor\":\"oxygen\",\"data\":{\"Oxygen\":%f}}",
             dev_info->Serial_num, val_oxy);
      break;*/

    case EKSIK_TEMP:
      tlen = sprintf(data_out, "\"TEMP\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;
      
    case EKSIK_HUM:
      tlen = sprintf(data_out, "\"HUM\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;
      
    case EKSIK_PRES:
      tlen = sprintf(data_out, "\"PRES\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;
      
    case EKSIK_CH4:
      tlen = sprintf(data_out, "\"CH4 x10^6\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);
        len += sprintf(data_out, "%f}", eksik_res*1000000);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;
      
    case EKSIK_O2:
      tlen = sprintf(data_out, "\"O2\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;
      
    case EKSIK_CO2:
      tlen = sprintf(data_out, "\"CO2\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;
      
    case EKSIK_NH3:
      tlen = sprintf(data_out, "\"NH3\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;

    case EKSIK_H2S:
      tlen = sprintf(data_out, "\"H2S\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;

    case EKSIK_CO:
      tlen = sprintf(data_out, "\"CO\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;

    case EKSIK_NO2:
      tlen = sprintf(data_out, "\"NO2\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;

    case EKSIK_SO2:
      tlen = sprintf(data_out, "\"SO2\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);        
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;
      
    case EKSIK_LIGHT:
      tlen = sprintf(data_out, "\"LUM\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);        
        len += sprintf(data_out, "%f}", eksik_res);
      }
      break;
      
    case EKSIK_DUST_PM10:
      tlen = sprintf(data_out, "\"DUST\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);        
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;
      
    case EKSIK_DUST_PM25:
      tlen = sprintf(data_out, "\"DUST\":");
      data_out += tlen; 
      if ( datasize ) 
      {
        *(uint32_t*)&eksik_res = BYTE2FLOAT(data_in);        
        len += sprintf(data_out, "%f}", eksik_res);
      }
//      else len += sprintf(data_out, "\"N/A\"}");
      break;
      
    case AQARA:
      if ( datasize ) 
      {
        AqaraSensor* pSens = (AqaraSensor*)data_in;
        len += sprintf(data_out, "\"TEMP\":%.2f,\"PRES[kPa]\":%.1f,\"HUM\":%.2f,\"LQI\":%hhu,\"RSSI\":%hhd}",
                       (float)pSens->temp/100, (float)pSens->pressure/10, (float)pSens->humidity/100, pSens->LQI, pSens->RSSI);       
      }
      break;
      
    case ISA_LIC_v2:
      if ( datasize ) 
      {
        Isa_LIC* pISA_Data = (Isa_LIC*)data_in;
        
        len += sprintf(data_out, "\"WIND_L\":%.2f,\"WIND_T\":%.2f,\"WIND_ABS\":%.2f,\"WIND_DIR\":%.2f,\"TEMP\":%.2f,\"PRES[mm_hg]\":%.2f,\"PRES[gPa]\":%.2f,\"HUM\":%.2f,\"LIGHT\":%.2f,\"ANGLE_Z\":%.4f,\"ANGLE_A\":%.4f,\"NORTH_DIR\":%.4f,\"LAT\":%f,\"LONG\":%f,\"ALT\":%.2f}",
                      pISA_Data->Long_Comp_Speed_Wind, pISA_Data->Trans_Comp_Speed_Wind, pISA_Data->ABS_Speed_Wind, pISA_Data->Direct_Wind, pISA_Data->Temp_Air, pISA_Data->Air_pressure_mm_hg, pISA_Data->Air_pressure_gPa,
                      pISA_Data->Humidity, pISA_Data->Light, pISA_Data->Angle_Inclination_Zenith, pISA_Data->Angle_Inclination_Azimuth, pISA_Data->Direct_to_North, pISA_Data->Latitude, pISA_Data->Longitude, pISA_Data->Altitude);
      }
      else len += sprintf(data_out, "\"data\":\"N/A\"}");
      break;
  }
  
  if ( (datasize == 0) && (pSensor->SensorType != ISA_LIC_v2) ) len += sprintf(data_out, "\"N/A\"}");
  
  len += tlen;
  /* Это последний раз, когда мы отправляем сообщение по этому датчику из-за его отключения */
  if ( pSensor->SensorEnabled == 0 )     
  {
    while ( *(++data_out) != 0 );
    data_out--;
    len += sprintf(data_out, ",\"status\":\"disabled\"}") - 1;
  }

  return len;
  
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t SendMsg2MQTT(MSG_TypeDef msg, void *pbuf, uint32_t datasize)
{
  char mqtt_topic[MAX_TOPIC_LEN];
  char mqtt_payload[MAX_PAYLOAD_SIZE];
  uint8_t len;
  
  get_mqtt_topic(NULL, MSG, mqtt_topic);
  if ( msg == MSG_BAT_TAMPER_DET || msg == MSG_CASE_TAMPER_DET )    
    len = sprintf(mqtt_payload, (msg == MSG_CASE_TAMPER_DET) ? "{\"caseTamperState\":%d}" : "{\"batTamperState\":%d}", *(int*)pbuf);
  else if ( msg == MSG_STARTUP )
    len = sprintf(mqtt_payload, "Start");    
  else if ( msg == MSG_STATUS_CHANGED )
  {
    if ( check_timer(status_update_timer) > 1100 ) init_timer(status_update_timer, 1100);      
    return 0;
  }
    

  mqtt_add2queue(mqtt_topic, (uint8_t*)mqtt_payload, len);
  
  return 0;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void MQTT_Process(void)
{
  static uint8_t gps_flag = 1;  
  
  if ( pFirstMQTTmsg && flag_pub_busy == 0 ) 
  {
    act_led(LED_BLUE, 30);
    if ( gnetif.ip_addr.addr == 0 ) 
      act_led(LED_GREEN, 30);
    else
    {
      mqtt_send_abstract(&mqtt_client_global, pFirstMQTTmsg->pData, pFirstMQTTmsg->DataSize, pFirstMQTTmsg->pTopic);
      mqtt_kill_msg(MQTT_FIRST_MSG);
    }
  }
  
  if ( device_paused ) return;
  
  for ( int i = 0; i < 3; i++ )
    if ( SensorsChainProcess(pRSx[i]) == 0 ) break;
  
  if ( gps_flag && (check_timer(status_update_timer) < 1100) )
  {
    gps_flag = 0;
    PollGPSData();
  }
  
  if ( check_timer(status_update_timer) == 0 ) 
  {      
    char mqtt_payload[MAX_PAYLOAD_SIZE];
    char mqtt_topic[MAX_TOPIC_LEN];
    uint8_t ts_buff[6];
    float vbat;
    uint32_t len;
    
    init_timer(status_update_timer, 60000);  
    gps_flag = 1;
    
    vbat = ((float)BQ25887_Get_Vbat())/1000;
    
    GetGPSData();    
    
    SyncTimeGPS2RTC();
    get_mqtt_topic(NULL, STATUS, mqtt_topic);
    MakeTimeStamp(ts_buff);
    len = sprintf(mqtt_payload, "{\"Time\":\"20%02hhu-%02hhu-%02hhuT%02hhu:%02hhu:%02hhu\",\"BATT [V]\":%1.02f,\"STATUS\":\"0x%X\",\"GPS\":{\"Latitude\":\"%d.%u\",\"Longitude\":\"%d.%u\",\"Altitude [m]\":%hd,\"HorError [m]\":%hhu,\"Date\":\"%02hhu-%02hhu-%04hu\",\"Time\":\"%02hhu:%02hhu:%02hhu\",\"Flags\":\"0x%02X%02X\"}}",                  
    /*  Timestamp */ ts_buff[0], ts_buff[1], ts_buff[2], ts_buff[3], ts_buff[4], ts_buff[5], vbat, status_reg,
    /*     GPS    */ GPS.latitude/10000000, GPS.latitude%10000000U, GPS.longitude/10000000U, GPS.longitude%10000000U, GPS.altitude, GPS.horizontal_acc, GPS.day, GPS.month, GPS.year, GPS.hours, GPS.minutes, GPS.seconds, GPS.fix_type, GPS.valid_flags);
    mqtt_add2queue(mqtt_topic, (uint8_t*)mqtt_payload, len);
  }
    
}
