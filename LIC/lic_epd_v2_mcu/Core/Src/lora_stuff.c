#include "main.h"
#include "hw.h"
#include "radio.h"
#include "lora.h"
#include "low_power_manager.h"
#include "string.h"
#include "sensors.h"
#include "timers.h"
#include "gps.h"
#include "BQ25887.h"
#include "eeprom_lib.h"
#include "some_stuff.h"
#include "timeServer.h"
#include "lora_stuff.h"
#include "at24mac402.h"

#define MAX_LORA_MSGS_BUFF_SIZE 32


#define BYTE2FLOAT(X) ((uint32_t)X[1] | (uint32_t)X[0] << 8 | (uint32_t)X[3] << 16 | (uint32_t)X[2] << 24)

//#define APP_TX_DUTYCYCLE                            5000/*dev_info->Poll_period_ms*/
#define LORAWAN_ADR_STATE                           cfg_lora->LoRa_Datarate&0x80 //LORAWAN_ADR_ON
#define LORAWAN_DEFAULT_DATA_RATE                   cfg_lora->LoRa_Datarate&0x7F //DR_0
#define LORAWAN_APP_PORT                            cfg_lora->LoRa_App_Port
#define LORAWAN_TEL_PORT                            cfg_lora->LoRa_App_Port + 1
#define LORAWAN_DEFAULT_CLASS                       CLASS_A
#define LORAWAN_DEFAULT_CONFIRM_MSG_STATE           cfg_lora->LoRa_Message_Type
#define LORAWAN_APP_DATA_BUFF_SIZE                  128

#define LORA_INFO_ADR    0x00
#define LORA_CONFIG_ADR  0x80

irq_handler_addr irq_handler_DIO1;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern bool Service_mode;
extern GPS_t GPS;
extern IWDG_HandleTypeDef hiwdg;
extern pRSx_SensorsChain pRSx[3];
extern uint32_t status_update_timer;
extern uint32_t status_reg;

void mqtt_init_user();

//void handleDIO1()
//{
//  irq_handler_DIO1();
//  return;
//}
//

//#define BATT_GPS_MSG 9

static uint8_t AppDataBuff[LORAWAN_APP_DATA_BUFF_SIZE];

lora_AppData_t AppData = { AppDataBuff,  0, 0 };

LoraFlagStatus LoraMacProcessRequest = LORA_RESET;
LoraFlagStatus AppProcessRequest = LORA_RESET;

LoRaConfig  lora_config = {0, {0x16,0x02,0x14,0x02,0x03,0x17,0xA9,0x19}, {0xDC,0xA6,0x32,0xFF,0xFE,0x40,0x9B,0x25}, 
                              {0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x22,0x08,0x01}, 2, 0x80, 1, 0, 0};

static LoRaParam_t LoRaParamInit;/* = {LORAWAN_ADR_STATE,
                                     LORAWAN_DEFAULT_DATA_RATE,
                                     LORAWAN_PUBLIC_NETWORK
                                    };*/

//
typedef struct LoraMsg
{      
  uint8_t         Port;
  uint8_t         DataSize;
  uint8_t*        pMsg;
  struct LoraMsg* pNext;
}LoraMsg, *pLoraMsg;

pLoraMsg pFirstLoraMsg = NULL;
uint32_t total_lora_msgs = 0;


static uint32_t CheckLoraBuff(void);
static uint32_t AddLoraMsg2Queue(uint8_t port, uint8_t* pBuff, uint32_t DataSize);
static void     KillLoraMsg(uint32_t num);
static uint32_t SendViaLoRa(UART_HandleTypeDef* pHuart, pSensorElem pSensor, uint8_t *pBuff, uint32_t DataSize);
static uint32_t MakeLoraPacket(uint8_t* data2send, uint8_t* port2send);
static uint32_t SendMsg2LoRa(MSG_TypeDef msg, void *pbuf, uint32_t datasize);

static uint16_t HW_GetTemperatureLevel(void);
static uint8_t LORA_GetBatteryLevel(void);
static void LORA_TxNeeded(void);
static uint32_t HW_GetRandomSeed(void);
static void LORA_RxData(lora_AppData_t *AppData);
static void LORA_HasJoined(void);
static void LoraMacProcessNotify(void);
static void LORA_ConfirmClass(DeviceClass_t Class);

static LoRaMainCallback_t LoRaMainCallbacks = { LORA_GetBatteryLevel,
                                                HW_GetTemperatureLevel,
                                                HW_GetUniqueId,
                                                HW_GetRandomSeed,
                                                LORA_RxData,
                                                LORA_HasJoined,
                                                LORA_ConfirmClass,
                                                LORA_TxNeeded,
                                                LoraMacProcessNotify
                                              };




static void LoraMacProcessNotify(void)
{
  LoraMacProcessRequest = LORA_SET;
}


static void LORA_HasJoined(void)
{
  DIAG_MSG("JOINED\n\r");
  LORA_RequestClass(LORAWAN_DEFAULT_CLASS);
  HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);  
}

//void LORA_Do_Reset(void){
//  
//  // Wait 50 ms
//  HAL_Delay(200);
//
//  // Set RESET pin to 0
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  GPIO_InitStruct.Pin = LORA_NRST_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//  HAL_GPIO_Init(LORA_NRST_GPIO_Port, &GPIO_InitStruct);
//
//  HW_GPIO_Write(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_RESET);
//
//  // Wait 50 ms
//  HAL_Delay(50);
//
//  HW_GPIO_Write(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_SET);
//
//}


static void LORA_RxData(lora_AppData_t *AppData)
{
  DIAG_MSG("Packet received on port %d:\n\r", AppData->Port);
  DIAG_MSG((char*)AppData->Buff);
}

//static void OnTxTimerEvent(void *context)
//{
//  TimerStart(&TxTimer);
////  AppProcessRequest = LORA_SET;
////  if ( count == BATT_GPS_MSG-1 ){
////    GPS_req = get_timer();
////    init_timer(GPS_req, APP_TX_DUTYCYCLE-1000); 
////  }
//}

//static void LoraStartTx(TxEventType_t EventType)
//{
//  TimerInit(&TxTimer, OnTxTimerEvent);
//  TimerSetValue(&TxTimer,  APP_TX_DUTYCYCLE);
//  OnTxTimerEvent(NULL);
//}
/**
  * @brief  
  * @param  
  * @retval 
  */
static void LORA_ConfirmClass(DeviceClass_t Class)
{
  DIAG_MSG("Switch to class %c done\n\r", "ABC"[Class]);

  AppData.BuffSize = 0;
  AppData.Port = LORAWAN_APP_PORT;

  LORA_send(&AppData, LORAWAN_UNCONFIRMED_MSG);
}

/**
  * @brief  
  * @param  
  * @retval 
  */
static void LORA_TxNeeded(void)
{
  AppData.BuffSize = 0;
  AppData.Port = LORAWAN_APP_PORT;

  LORA_send(&AppData, LORAWAN_UNCONFIRMED_MSG);
}

static uint8_t LORA_GetBatteryLevel(void)
{
  return 0xAA;
}

static uint16_t HW_GetTemperatureLevel(void)
{
  return 0x55;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void HW_GetUniqueId(uint8_t *id)
{
  uint32_t ID1 = HAL_GetUIDw0();
  uint32_t ID2 = HAL_GetUIDw1();
  uint32_t ID3 = HAL_GetUIDw2();

  id[7] = (ID1 + ID3) >> 24;
  id[6] = (ID1 + ID3) >> 16;
  id[5] = (ID1 + ID3) >> 8;
  id[4] = (ID1 + ID3);
  id[3] = ID2 >> 24;
  id[2] = ID2 >> 16;
  id[1] = ID2 >> 8;
  id[0] = ID2;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
static uint32_t HW_GetRandomSeed(void)
{
  uint32_t ID1 = HAL_GetUIDw0();
  uint32_t ID2 = HAL_GetUIDw1();
  uint32_t ID3 = HAL_GetUIDw2();
  return ID1 ^ ID2 ^ ID3;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void LoRa_RSx_StatusUpdate(pRSx_SensorsChain pChain)
{
  if ( pChain->InterfaceID == RS1 )
  {
    /* Переключение транзистора, подающего 48В на разъём */
    HAL_GPIO_WritePin(RS_48V_EN_GPIO_Port, RS_48V_EN_Pin, pChain->Powered);   
    /* Переключение сигнала управляющего изолированным питанием на ADUM.*/
    HAL_GPIO_WritePin(RS1_PWR_DIS_GPIO_Port, RS1_PWR_DIS_Pin, (GPIO_PinState)!pChain->Powered); 
  }
  
  SendMsg2LoRa(MSG_STATUS_CHANGED, NULL, 0);
}

uint8_t last_msg[55];
uint32_t last_msg_size;
uint32_t numofresets = 0;
/**
  * @brief  
  * @param  
  * @retval 
  */
void LORA_Process(void)
{
  static uint8_t gps_flag = 1; 
  static uint32_t last_tx_time = 0;
  
  
  if (LoraMacProcessRequest == LORA_SET)
  {
    LoraMacProcessRequest = LORA_RESET;
    LoRaMacProcess();
  }
  
  if ( CheckLoraBuff() )
  {
    if (LORA_JoinStatus() != LORA_SET)
    {
      static uint32_t last_try = 0;
      
      if ( HAL_GetTick() > (last_try+10000) )
      {
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
        LORA_Join();
        last_try = HAL_GetTick();
      }
      return;
    }
    else HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
    
    if ( LoRaMacIsBusy() == false )
    {
      last_msg_size = AppData.BuffSize = MakeLoraPacket(AppData.Buff, &AppData.Port);
      memcpy(last_msg, AppData.Buff, last_msg_size);
      if ( AppData.BuffSize == 0 ) return;
      if ( LORA_send(&AppData, (LoraConfirm_t)LORAWAN_DEFAULT_CONFIRM_MSG_STATE) ) 
        HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
      else
        HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);      
      act_led(LED_BLUE, 30);
      last_tx_time = HAL_GetTick();
    }
    else
    {
      if ( HAL_GetTick() > (last_tx_time + 20000)  )
      {
        HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
/*        LORA_POWER_OFF();
        HAL_Delay(50);
        LORA_POWER_ON();
        HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_RESET);
        HAL_Delay(20);
        HAL_GPIO_WritePin(LORA_NRST_GPIO_Port, LORA_NRST_Pin, GPIO_PIN_SET);
        HAL_Delay(50);*/
        LoraMacProcessRequest = LORA_RESET;
        AppProcessRequest = LORA_RESET;
        LORA_Init(&LoRaMainCallbacks, &LoRaParamInit);
        
        //LoRaMacStart();
        //LORA_Join();
        last_tx_time = HAL_GetTick();
        numofresets++;
      }
    }
    
  }
  
/*  if ( IS_TIMER_NOTFREE(send_timer) && (check_timer(send_timer) == 0) )
  {
    free_timer(&send_timer);
    
    if (LORA_JoinStatus() != LORA_SET)
    {
      HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
      LORA_Join();
      return;
    }
    else HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);

    AppData.BuffSize = tx_counter;
    tx_counter = 0;
    act_led(LED_BLUE, 30);
    AppData.Port = LORAWAN_APP_PORT;  
    if ( LORA_send(&AppData, LORAWAN_DEFAULT_CONFIRM_MSG_STATE) ) 
      HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
    else
      HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);

  }  */
    
  for ( int i = 0; i < 3; i++ )
    if ( SensorsChainProcess(pRSx[i]) == 0 ) break;

  if ( gps_flag && (check_timer(status_update_timer) < 1100) )
  {
    gps_flag = 0;
    PollGPSData();
  }
  
  if ( check_timer(status_update_timer) == 0 ) 
  {          
    uint16_t vbat;
    uint8_t tel[52];
    int i = 0;
    
    init_timer(status_update_timer, 60000);  
    gps_flag = 1;
    
    vbat = BQ25887_Get_Vbat();
    
    GetGPSData();    
    
    SyncTimeGPS2RTC();

    tel[i++] = (uint8_t)total_lora_msgs;
    CAST2U16(tel[i]) = vbat;
    i += 2;
    CAST2U32(tel[i]) = GPS.latitude;//  >> 24;
    i += 4;
    CAST2U32(tel[i]) = GPS.longitude;
    i += 4;
//    tel[i++] = GPS.latitude  >> 16;
//    tel[i++] = GPS.latitude  >> 8;
//    tel[i++] = GPS.latitude   & 0xFF;
//    tel[i++] = GPS.longitude >> 24;
//    tel[i++] = GPS.longitude >> 16;
//    tel[i++] = GPS.longitude >> 8;
//    tel[i++] = GPS.longitude  & 0xFF;
    CAST2U16(tel[i]) = GPS.altitude;
    i += 2;
//    tel[i++] = GPS.altitude  >> 8;
//    tel[i++] = GPS.altitude   & 0xFF;
    tel[i++] = GPS.horizontal_acc;
    tel[i++] = (uint8_t)(GPS.year-2000);
    tel[i++] = GPS.month;
    tel[i++] = GPS.day;
    tel[i++] = GPS.hours;
    tel[i++] = GPS.minutes;
    tel[i++] = GPS.seconds;
    tel[i++] = GPS.fix_type;
    tel[i++] = GPS.valid_flags;
    CAST2U32(tel[i]) = status_reg;
    i += 4;
    tel[i++] = numofresets;
    
    AddLoraMsg2Queue(LORAWAN_TEL_PORT, tel, i);
    
  }
//  if ((LoraMacProcessRequest != LORA_SET) && (AppProcessRequest != LORA_SET))
//  {
//    LPM_EnterLowPower();
//      HW_RTC_StopAlarm();
//      Eeprom_Write(100, new_count, 1);
//      if(count_stand_by > 1) Enter_Stand_By_Mode();
//  }
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t CheckLoraBuff(void)
{
  if ( pFirstLoraMsg ) return 1;
  else return 0;
}


/**
  * @brief  
  * @param  
  * @retval 
  */
void KillLoraMsg(uint32_t num)
{
  pLoraMsg pNextMsg, pTemp = pFirstLoraMsg;
  
  if (num == 0 ) num = 0xFFFFFFFF;
  
  for ( int i = 0; i < num; i++ )
  {
    if ( pTemp )
    {
      free(pTemp->pMsg);
      pNextMsg = pTemp->pNext;
      free(pTemp);
      pTemp = pNextMsg;    
      total_lora_msgs--;
    }
    else return;
  }
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t AddLoraMsg2Queue(uint8_t port, uint8_t* pBuff, uint32_t DataSize)
{
  pLoraMsg pNewMsg, pTemp;
  
  if ( total_lora_msgs > MAX_LORA_MSGS_BUFF_SIZE ) 
    KillLoraMsg(1);
  
  pNewMsg = malloc(sizeof(LoraMsg));
  if ( pNewMsg == NULL ) return 1;

  pNewMsg->Port = port;
  pNewMsg->pNext = NULL;
  if ( DataSize > 0 && DataSize <= 51 )
  {
    pNewMsg->pMsg = malloc(DataSize);
    if ( pNewMsg->pMsg == NULL ) return 1;
    pNewMsg->DataSize = DataSize;
    memcpy(pNewMsg->pMsg, pBuff, DataSize);
  }
  
  if ( pFirstLoraMsg ) 
  {
    pTemp = pFirstLoraMsg;
    while ( pTemp->pNext ) pTemp = pTemp->pNext;
    pTemp->pNext = pNewMsg;
  }
  else pFirstLoraMsg = pNewMsg;      
  total_lora_msgs++;
  
  return 0;
}  


/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t SendViaLoRa(UART_HandleTypeDef* pHuart, pSensorElem pSensor, uint8_t *pBuff, uint32_t DataSize)
{
   uint8_t payload[52];
   //float fvalue;
   //uint32_t value;
   
  //if ( tx_counter > 200 ) tx_counter = 0;

  //payload = &AppData.Buff[tx_counter];
  
  if(pHuart == &RS1_huart) payload[0] = 1;
  else if(pHuart == &RS2_huart) payload[0] = 2;
  else if(pHuart == &RS3_huart) payload[0] = 3;
  else payload[0] = 0;
    
  CAST2U16(payload[1]) = pSensor->SensorType;
  payload[3] = pSensor->DevAddr;
  //memcpy(&payload[4], pBuff, 6);
  uint32_t *ts = (uint32_t*)&payload[4];
  
  *ts = /*year*/(uint32_t)pBuff[0]<<26 | /*month*/(uint32_t)pBuff[1]<<22 | /*date*/(uint32_t)pBuff[2]<<17 | 
        /*hours*/(uint32_t)pBuff[3]<<12 | /*minutes*/(uint32_t)pBuff[4]<<6 | /*seconds*/(uint32_t)pBuff[5];
  
  payload[8] = (uint8_t)DataSize;   
  if (DataSize)
  {
    pBuff += 6;
    memcpy(&payload[9], pBuff, DataSize);
    
//    *(uint32_t*)&fvalue = BYTE2FLOAT(pBuff);
//    value = (uint32_t)(fvalue * 1000000);
//    memcpy(&payload[11], &value, 4);
  }
  AddLoraMsg2Queue(LORAWAN_APP_PORT, payload, DataSize+9);
  //*((uint32_t*)&payload[11]) = value;
  //tx_counter += 11+DataSize;
    
  //if ( IS_TIMER_FREE(send_timer ) )send_timer = get_timer();
  //init_timer(send_timer, 1000);

  return 0;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t MakeLoraPacket(uint8_t* data2send, uint8_t* port2send)
{
  pLoraMsg pTemp = pFirstLoraMsg, pNextMsg;
  uint8_t port;
  uint32_t pl = 0;
  
  if ( pTemp == NULL ) return 0;
  
  port = pTemp->Port;
  while ( pTemp ) 
  {
    if ( pTemp->Port != port ) break;
    if ( (pl + pTemp->DataSize) > 51 ) break;
    memcpy(data2send, pTemp->pMsg, pTemp->DataSize);
    pl += pTemp->DataSize;
    data2send += pTemp->DataSize;
    free(pTemp->pMsg);
    pNextMsg = pTemp->pNext;
    free(pTemp);
    pTemp = pNextMsg;
    total_lora_msgs--;
  }
  
  pFirstLoraMsg = pTemp;
  *port2send = port;
  
  return pl;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void LORA_Init_user(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  LPM_SetOffMode(LPM_APPLI_Id, LPM_Disable);
  HW_RTC_Init();
  LoRaParamInit.AdrEnable = LORAWAN_ADR_STATE;
  LoRaParamInit.EnablePublicNetwork = LORAWAN_PUBLIC_NETWORK;
  LoRaParamInit.TxDatarate = LORAWAN_DEFAULT_DATA_RATE;
  LORA_Init(&LoRaMainCallbacks, &LoRaParamInit);
  //LORA_Join();
  SendMsg = SendMsg2LoRa;
  //LoraStartTx(TX_ON_TIMER);
  
  /*Configure GPIO pin : LORA_DIO1_Pin */
  GPIO_InitStruct.Pin = LORA_DIO1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(LORA_DIO1_GPIO_Port, &GPIO_InitStruct);
  
  InitRSSensorsChain(&RS1_SensorsChain, RS1, &RS1_huart, RS1_VCC_EN_GPIO_Port, RS1_VCC_EN_Pin, rs1_config->State, rs1_config->ErrorCnt, rs1_config->FirstReqDelay, LoRa_RSx_StatusUpdate);
  for ( int i = 0; i < rs1_sensors->NumOfSensors; i++ ) AddSensor2Chain(&RS1_SensorsChain, 
    AddSensor(rs1_sensors->Sensors[i].ID,   rs1_sensors->Sensors[i].Address, rs1_sensors->Sensors[i].Name, rs1_sensors->Sensors[i].PollPeriod*1000, RS_SensorRead, SendViaLoRa));
  
  InitRSSensorsChain(&RS2_SensorsChain, RS2, &RS2_huart, RS2_VCC_EN_GPIO_Port, RS2_VCC_EN_Pin, rs2_config->State, rs2_config->ErrorCnt, rs2_config->FirstReqDelay, LoRa_RSx_StatusUpdate);
  for ( int i = 0; i < rs2_sensors->NumOfSensors; i++ ) AddSensor2Chain(&RS2_SensorsChain, 
    AddSensor(rs2_sensors->Sensors[i].ID,   rs2_sensors->Sensors[i].Address, rs2_sensors->Sensors[i].Name, rs2_sensors->Sensors[i].PollPeriod*1000, RS_SensorRead, SendViaLoRa));

  InitRSSensorsChain(&RS3_SensorsChain, RS3, &RS3_huart, RS3_VCC_EN_GPIO_Port, RS3_VCC_EN_Pin, rs3_config->State, rs3_config->ErrorCnt, rs3_config->FirstReqDelay, LoRa_RSx_StatusUpdate);
  for ( int i = 0; i < rs3_sensors->NumOfSensors; i++ ) AddSensor2Chain(&RS3_SensorsChain, 
    AddSensor(rs3_sensors->Sensors[i].ID,   rs3_sensors->Sensors[i].Address, rs3_sensors->Sensors[i].Name, rs3_sensors->Sensors[i].PollPeriod*1000, RS_SensorRead, SendViaLoRa));
  
  status_update_timer = get_timer();
  init_timer(status_update_timer, 10555);
}

/**
  * @brief  
  * @param  
  * @retval 
  */
static uint32_t SendMsg2LoRa(MSG_TypeDef msg, void *pbuf, uint32_t datasize)
{
//  if ( msg == MSG_STATUS_CHANGED )
//  {
    if ( check_timer(status_update_timer) > 1100 ) init_timer(status_update_timer, 1100);      
    return 0;
//  }

//  return 0;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void LORA_ReadConfig(void)
{
  LoRaConfig tempconfig;
  uint32_t crc32;
  
  if (LORA_CONNECTED)
  {
    at24_read_data(LORA_AT24_DEVICE_ADR, LORA_CONFIG_ADR, (uint8_t*)&tempconfig, sizeof(LoRaConfig));
    crc32 = crc32_byte(0, (uint8_t*)&tempconfig, sizeof(LoRaConfig) - sizeof(crc32));
    if ( crc32 == tempconfig.CRC32 ) 
      lora_config = tempconfig;
  }
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void LORA_SaveConfig(void)
{
  if (LORA_CONNECTED)
  {
    lora_config.CRC32 = crc32_byte(0, (uint8_t*)&lora_config, sizeof(LoRaConfig) - sizeof(lora_config.CRC32));
    at24_write_data(LORA_AT24_DEVICE_ADR, LORA_CONFIG_ADR, (uint8_t*)&lora_config, sizeof(LoRaConfig));
  }
}