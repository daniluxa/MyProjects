/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
#include "sensors.h"
#include "SC_lib.h"
#include "magma.h"
#include "inputs.h"
#include "sound.h"
#include "init.h"
#include "zigbee.h"
#include "hw_gpio.h"
#include "lora_stuff.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */
extern irq_handler_addr irq_handler_DIO1;

/* USER CODE BEGIN PV */
uint8_t RS1_sensor_type = 0;
uint8_t RS2_sensor_type = 0;
uint8_t RS3_sensor_type = 0;
bool Service_mode = false;
//uint8_t AutoDevEUI[8];
uint8_t sensorsToSend[32][24];
uint8_t sensorsToSendCount = 0;
uint32_t reboot_cntr = 0;
uint32_t status_reg = 0;

/* USER CODE END PV */


/* USER CODE BEGIN PFP */

void handleDIO1();
uint8_t (* USB_SendMore)(uint32_t) = NULL;

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
DeviceConfig config = {
  /* Config V*/ 2,
  /* Ethernet*/ {1,{10,0,38,31}, {255,255,0,0}, {10,0,0,1}, {0xA0,0xB1,0xC5,0x22,0x08,0x00}, 0, 1, {10,0,38,32}, 1, 1883, "MIET/OU", "%sn", "user", "password"},
  /* Zigbee*/   {0, 0},
  /* Sensors*/  {{{0},0}, {{0},0}, {{0},0}},
  /* RS conf*/  {{115200,UART_WORDLENGTH_8B,UART_PARITY_NONE,UART_STOPBITS_1,0,10,20}, 
                 {115200,UART_WORDLENGTH_8B,UART_PARITY_NONE,UART_STOPBITS_1,0,10,20}, 
                 {115200,UART_WORDLENGTH_8B,UART_PARITY_NONE,UART_STOPBITS_1,0,10,20}},
  /* CRC32 */   0};

DeviceInfo   devinfo = {{30,8,22}, 2208000, 0};

DeviceInfo     *dev_info    = &devinfo;
EthernetConfig *cfg_eth     = &config.ethernet;
LoRaConfig     *cfg_lora    = &lora_config;
ZigBeeConfig   *cfg_zigbee  = &config.zigbee;
SensorsConfig  *rs1_sensors = &config.sensors[0];
SensorsConfig  *rs2_sensors = &config.sensors[1];
SensorsConfig  *rs3_sensors = &config.sensors[2];
RSConfig       *rs1_config  = &config.rs_config[0];
RSConfig       *rs2_config  = &config.rs_config[1];
RSConfig       *rs3_config  = &config.rs_config[2];

//Isa_Settings isa_set;
DG_struct dg_struct;

static uint8_t USB_config_send(uint32_t flag);
static uint8_t USB_sensors_send(uint32_t flag);
static uint32_t SendMsgDummy(MSG_TypeDef msg, void *pbuf, uint32_t datasize);
static void STMPS_SwitchOff(uint32_t switch_num);
uint32_t (* SendMsg)(MSG_TypeDef msg, void *pbuf, uint32_t datasize) = SendMsgDummy;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  Device_Init();
/* USER CODE BEGIN 2 */

  //Isa_Settings isa_set = {Parity_None, Speed_115200, Stop_bits_2};
//  isa_set.parity    = Parity_None;
//  isa_set.speed     = Speed_115200;
//  isa_set.stop_bits = Stop_bits_2;

  AddInputs(RS1_CONN, RS1_Connected_GPIO_Port, RS1_Connected_Pin, 20000);
  AddInputs(RS2_CONN, RS2_Connected_GPIO_Port, RS2_Connected_Pin, 20000);
  AddInputs(RS3_CONN, RS3_Connected_GPIO_Port, RS3_Connected_Pin, 20000);
  AddInputs(CAN_CONN, CAN_Connected_GPIO_Port, CAN_Connected_Pin, 20000);
  AddInputs(AN1_CONN, AN1_Connected_GPIO_Port, AN1_Connected_Pin, 20000);
  AddInputs(AN2_CONN, AN2_Connected_GPIO_Port, AN2_Connected_Pin, 20000);
  AddInputs(BAT_TAMPER_DET, OPEN_1_GPIO_Port, OPEN_1_Pin, 1000);
  AddInputs(CASE_TAMPER_DET, OPEN_2_GPIO_Port, OPEN_2_Pin, 1000);
  AddInputs(BQ25887_PG, CH_PG_GPIO_Port, CH_PG_Pin, 10);
  AddInputs(BQ25887_STATUS, CH_STATUS_GPIO_Port, CH_STATUS_Pin, 10);
  AddInputs(TPS25942x_PG, TPS1_PG_GPIO_Port, TPS1_PG_Pin, 10);
  AddInputs(OVL_RS1, KEY_FLT_RS1_GPIO_Port, KEY_FLT_RS1_Pin, 10);
  AddInputs(OVL_RS2, KEY_FLT_RS2_GPIO_Port, KEY_FLT_RS2_Pin, 10);
  AddInputs(OVL_RS3, KEY_FLT_RS3_GPIO_Port, KEY_FLT_RS3_Pin, 10);
  AddInputs(OVL_CAN, KEY_FLT_CAN_GPIO_Port, KEY_FLT_CAN_Pin, 10);
  AddInputs(OVL_AN1, KEY_FLT_AN1_GPIO_Port, KEY_FLT_AN1_Pin, 10);
  AddInputs(OVL_AN2, KEY_FLT_AN2_GPIO_Port, KEY_FLT_AN2_Pin, 10);
  
  act_led(LED_GREEN, 1000);
  act_led(LED_RED, 500);
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    HAL_IWDG_Refresh(&hiwdg);
    
    sound_processing();
    act_led(NO_LED, 0);
    
    /* USER CODE BEGIN 3 */
    
    if( reboot_cntr )
    {
      HAL_Delay(1);
      if ( (reboot_cntr % 250) == 0 ) 
      {
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);        
        HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);        
      }
      if ( reboot_cntr == 1000 ) 
      {
        Prepare4Reboot();
        Service_mode = 1;
      }
      if ( --reboot_cntr == 0 ) NVIC_SystemReset();
    }
    if(Service_mode) continue;
    
    if ( cfg_eth->eth_enabled ) MX_LWIP_Process();
    if ( cfg_lora->enabled ) LORA_Process();

    if ( PollInputs() )
    {
      DI_Event InpEvent;
            
      GetInputEvent(&InpEvent);
      switch ( InpEvent.input_id ) 
      {
        /* Концевик подключения внешнего разъёма RS1. 0 = подключен */
        case RS1_CONN: {                 
          if ( InpEvent.state ) CLEAR_BIT(status_reg, 1<<RS1_CONN);
          else SET_BIT(status_reg, 1<<RS1_CONN);
          RSSensorsChainPwrControl(&RS1_SensorsChain, (GPIO_PinState)!InpEvent.state);          
        } break;
        
        case RS2_CONN: {
          if ( InpEvent.state ) CLEAR_BIT(status_reg, 1<<RS2_CONN);
          else SET_BIT(status_reg, 1<<RS2_CONN);
          RSSensorsChainPwrControl(&RS2_SensorsChain, (GPIO_PinState)!InpEvent.state);          
        } break;
        
        case RS3_CONN: {
          if ( InpEvent.state ) CLEAR_BIT(status_reg, 1<<RS3_CONN);
          else SET_BIT(status_reg, 1<<RS3_CONN);
          RSSensorsChainPwrControl(&RS3_SensorsChain, (GPIO_PinState)!InpEvent.state);          
        } break;

        case CAN_CONN: {                 
          uint32_t data = (uint32_t)CAN_CONN;
          if ( InpEvent.state ) CLEAR_BIT(status_reg, 1<<CAN_CONN);
          else SET_BIT(status_reg, 1<<CAN_CONN);
          SendMsg(MSG_STATUS_CHANGED, &data, 4);          
        } break;
        
        case AN1_CONN: {                 
          uint32_t data = (uint32_t)AN1_CONN;
          if ( InpEvent.state ) CLEAR_BIT(status_reg, 1<<AN1_CONN);
          else SET_BIT(status_reg, 1<<AN1_CONN);
          SendMsg(MSG_STATUS_CHANGED, &data, 4);          
        } break;
        
        case AN2_CONN: {                 
          uint32_t data = (uint32_t)AN2_CONN;
          if ( InpEvent.state ) CLEAR_BIT(status_reg, 1<<AN2_CONN);
          else SET_BIT(status_reg, 1<<AN2_CONN);
          SendMsg(MSG_STATUS_CHANGED, &data, 4);          
        } break;
        
        case BAT_TAMPER_DET: {
          int data = (int)InpEvent.state;
          if ( InpEvent.state ) SET_BIT(status_reg, 1<<BAT_TAMPER_DET);
          else CLEAR_BIT(status_reg, 1<<BAT_TAMPER_DET);
          SendMsg(MSG_BAT_TAMPER_DET, &data, 4);
        } break;
        
        case CASE_TAMPER_DET: {
          int data = (int)InpEvent.state;
          if ( InpEvent.state ) SET_BIT(status_reg, 1<<CASE_TAMPER_DET);
          else CLEAR_BIT(status_reg, 1<<CASE_TAMPER_DET);
          SendMsg(MSG_CASE_TAMPER_DET, &data, 4);
        } break;
        
        case BQ25887_PG: {
          uint32_t data = (uint32_t)BQ25887_PG;
          if ( InpEvent.state ) SET_BIT(status_reg, 1<<BQ25887_PG);
          else CLEAR_BIT(status_reg, 1<<BQ25887_PG);
          SendMsg(MSG_STATUS_CHANGED, &data, 4);          
        } break;
        
        case BQ25887_STATUS: {
          uint32_t data = (uint32_t)BQ25887_STATUS;
          if ( InpEvent.state ) SET_BIT(status_reg, 1<<BQ25887_STATUS);
          else CLEAR_BIT(status_reg, 1<<BQ25887_STATUS);
          SendMsg(MSG_STATUS_CHANGED, &data, 4);          
        } break;
        
        /* Сигнал от мультиплексора питания. Сообщает о наличии/отсутствии стационарного питания */
        case TPS25942x_PG: {
          uint32_t data = (uint32_t)TPS25942x_PG;
          if ( InpEvent.state ) 
          {
            SET_BIT(status_reg, 1<<TPS25942x_PG);
            HAL_GPIO_WritePin(GPIOE, ETH_3V3_En_Pin, GPIO_PIN_RESET);
          }
          else 
          {
            CLEAR_BIT(status_reg, 1<<TPS25942x_PG);
            HAL_GPIO_WritePin(GPIOE, ETH_3V3_En_Pin, GPIO_PIN_SET);
          }
          SendMsg(MSG_STATUS_CHANGED, &data, 4);          
        } break;
        
        case OVL_CAN: 
        case OVL_AN1: 
        case OVL_AN2: 
        case OVL_RS1: 
        case OVL_RS2: 
        case OVL_RS3: {
          uint32_t data = (uint32_t)InpEvent.input_id;
          if ( InpEvent.state ) 
            CLEAR_BIT(status_reg, 1<<InpEvent.input_id);
          else 
          {
            STMPS_SwitchOff(InpEvent.input_id);
            SET_BIT(status_reg, 1<<InpEvent.input_id);
          }
          SendMsg(MSG_STATUS_CHANGED, &data, 4);          
        } break;
      }
    }
  }
  /* USER CODE END 3 */
}

static void STMPS_SwitchOff(uint32_t switch_num)
{
  switch (switch_num)
  {
    case OVL_CAN: HAL_GPIO_WritePin(CAN_VCC_EN_GPIO_Port, CAN_VCC_EN_Pin, GPIO_PIN_RESET); break;
    case OVL_AN1: HAL_GPIO_WritePin(AN1_VCC_EN_GPIO_Port, AN1_VCC_EN_Pin, GPIO_PIN_RESET); break;
    case OVL_AN2: HAL_GPIO_WritePin(AN2_VCC_EN_GPIO_Port, AN2_VCC_EN_Pin, GPIO_PIN_RESET); break;
    case OVL_RS1: HAL_GPIO_WritePin(RS1_VCC_EN_GPIO_Port, RS1_VCC_EN_Pin, GPIO_PIN_RESET); break;
    case OVL_RS2: HAL_GPIO_WritePin(RS2_VCC_EN_GPIO_Port, RS2_VCC_EN_Pin, GPIO_PIN_RESET); break;
    case OVL_RS3: HAL_GPIO_WritePin(RS3_VCC_EN_GPIO_Port, RS3_VCC_EN_Pin, GPIO_PIN_RESET); break;   
  }  
}

void tim7_handle(void)
{
    HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
//  MX_LWIP_Process();
}


void VCOM_handle(uint8_t *buf, uint32_t len)
{
  uint8_t cmd = buf[0];
  uint8_t* cfg_field = 0;
  static uint8_t page_buff[256];
  static uint16_t page_pos = 0;
  static uint32_t page_num = 0;
  Cfg_fields field = (Cfg_fields)0;
  //uint16_t eeprom_addr_sector = 0;
  uint32_t size = 0;
  uint8_t ans[] = {0xA5, 0x5A};

  switch (cmd)
  {
    case 0xEE:
    {
      Service_mode = true;
      LED_set_color(WHITE);
      //HAL_TIM_Base_Start_IT(&htim7);      
      CDC_Transmit_FS(ans, 2);      
    } break;
      
    case 0x15:                  // write sensors
    {
      SensorsConfig * tmp;
      Cfg_Sensor * _sens;
      switch(buf[1]){
        case i_RS1: 
          tmp = rs1_sensors;
          break;
        case i_RS2: 
          tmp = rs2_sensors;
          break;
        case i_RS3: 
          tmp = rs3_sensors;
          break;
        default:
          CDC_Transmit_FS(ans, 2);
          return;
      }
      tmp->NumOfSensors = buf[2] + 1;   
      if ( tmp->NumOfSensors )
      {
        _sens = &(tmp->Sensors[buf[2]]);
        memcpy(_sens->Name, &buf[3], 16);
        _sens->ID = *((uint16_t*) &buf[19]);
        _sens->PollPeriod = *((uint16_t*) &buf[21]);
        _sens->Address = buf[23];  
        _sens->Status = 1;
      }
      CDC_Transmit_FS(ans, 2);
      break;
    }
    
    case 0x14:                  // read sensors
    {
      SensorsConfig * tmp;
      switch(buf[1]){
        case i_RS1: 
          tmp = rs1_sensors;
          break;
        case i_RS2: 
          tmp = rs2_sensors;
          break;
        case i_RS3: 
          tmp = rs3_sensors;
          break;
        default:
          CDC_Transmit_FS(ans, 2);
          return;
      }
      
      if ( tmp->NumOfSensors )
      {
        for (uint8_t i = 0; i <= tmp->NumOfSensors; i++){
          sensorsToSend[i][0] = 0x14;
          sensorsToSend[i][1] = buf[1];
          Cfg_Sensor * _sens = &(tmp->Sensors[i]);
          sensorsToSend[i][2] = i;
          memcpy(&sensorsToSend[i][3], _sens->Name, 16);
          *(uint16_t*)&sensorsToSend[i][19] = _sens->ID;
          *(uint16_t*)&sensorsToSend[i][21] = _sens->PollPeriod;
          sensorsToSend[i][23] = _sens->Address;
        }
        sensorsToSendCount = tmp->NumOfSensors;
        USB_sensors_send(0);
      }
      break;
    }
    
    case 0x25:                  // write port settings
    {
      RSConfig * tmp;
      switch(buf[1]){        
        case i_RS1: 
          tmp = rs1_config;
          break;
        case i_RS2: 
          tmp = rs2_config;
          break;
        case i_RS3: 
          tmp = rs3_config;
          break;
        default:
          CDC_Transmit_FS(ans, 2);
          return;
      }
      tmp->BaudRate = *((uint32_t*) &buf[2]);
      tmp->DataBits = buf[6];
      tmp->Parity = buf[7];
      tmp->StopBits = buf[8];
      tmp->State = buf[9];
      tmp->FirstReqDelay = buf[10];
      tmp->ErrorCnt = buf[11];
      CDC_Transmit_FS(ans, 2);
      break;
    }
    
    case 0x24:                  // read port settings
    {
      uint8_t sendBuff[12] = {0x24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      RSConfig * tmp;
      switch(buf[1]){        
        case i_RS1: 
          tmp = rs1_config;
          break;
        case i_RS2: 
          tmp = rs2_config;
          break;
        case i_RS3: 
          tmp = rs3_config;
          break;
        default:
          CDC_Transmit_FS(ans, 2);
          return;
      }      
      sendBuff[1] = buf[1];
      *(uint32_t*)&sendBuff[2] = tmp->BaudRate;
      sendBuff[6] = tmp->DataBits;
      sendBuff[7] = tmp->Parity;
      sendBuff[8] = tmp->StopBits;
      sendBuff[9] = tmp->State;
      sendBuff[10] = tmp->FirstReqDelay;
      sendBuff[11] = tmp->ErrorCnt;
      CDC_Transmit_FS(sendBuff, 12);
      break;
    }
    
    case 0x44:                  // config dump read
    {       
      USB_config_send(0);      
      break;
    }
    
    case 0x45:                  // config write
    {
      
      break;
    }
      
    case 0x34:                  // ZigBee 
    case 0x54:                  // firmware params
    { 
      uint16_t frm_len = *((uint16_t*) &buf[1]);
      // Erase flash for new firmware
      for (uint8_t i = 0; i < 16; i++){
        W25qxx_EraseBlock(FLASH_FIRM_START_BLOCK + i);
      }
      uint8_t* frm = &buf[3];
      W25qxx_EraseSector(FLASH_FIRM_PARAM_SECTOR);
      W25qxx_WriteSector(frm, FLASH_FIRM_PARAM_SECTOR, 0, frm_len);
      CDC_Transmit_FS(ans, 2);
      page_num = page_pos = 0;
      break;
    }
    
    case 0x35:                  // ZigBee
    case 0x55:                  // download firmware
    {
      uint16_t frm_len = *((uint16_t*) &buf[1]);
      //uint16_t numOfPacket = *((uint16_t*) &buf[3]);
      //uint8_t* frm = &buf[5];
      
      memcpy(&page_buff[page_pos], &buf[5], frm_len);
      page_pos += frm_len-2;
      if ( page_pos == 256 )
      {
        page_pos = 0;
        W25qxx_WritePage(page_buff, FLASH_FIRM_START_PAGE + page_num++, 0, 256);   
      }
      //W25qxx_WritePage(frm, FLASH_FIRM_START_PAGE + (numOfPacket / 8) , 32 * (numOfPacket % 8), frm_len - 2);   
      
      CDC_Transmit_FS(ans, 2);
      break;
    }
    
    case  0x36:                 // ZigBee
    case  0x56:
    {                           // check firmware and reboot
      uint8_t sendBuff[5];// = {0x65};
      uint8_t tmp_buff[32];
      
      if ( page_pos != 0 )
      {
        W25qxx_WritePage(page_buff, FLASH_FIRM_START_PAGE + page_num, 0, page_pos);
        page_pos = 0;
      }
      W25qxx_ReadSector(tmp_buff, FLASH_FIRM_PARAM_SECTOR, 0, 32);
      uint32_t frm_len = *((uint32_t*) tmp_buff);
      uint32_t frm_crc_read = *((uint32_t*) &tmp_buff[8]);
      uint32_t frm_crc_calc = W25qxx_CRCFirmware(frm_len);
      sendBuff[0] = (cmd == 0x36) ? 0x66 : 0x65;
      *(uint32_t*)&sendBuff[1] = frm_crc_calc;
      CDC_Transmit_FS(sendBuff, 5);
      if(frm_crc_read == frm_crc_calc)
      {
        if ( cmd == 0x36 )
        {
          
        }
        else
        {
          // set flag for bootloader
          W25qxx_SetFlagFirmware(true);
        }
      }
      break;
    }
    
    case 0x7A:
    {
      // set flag for reboot
      reboot_cntr = 3000;      
      break;
    }
    
    case 0xA0:
    {
      W25qxx_EraseSector(PRIMARY_CONF_SECT);
      W25qxx_EraseSector(RESERV_CONF_SECT);      
      CDC_Transmit_FS(ans, 2);    
    } break;
    
    /* Команда на сохранение параметров устройства */
    case 0xA6: {
      save_settings(PRIMARY_CONF_SECT);
      /* Резервная копия */
      save_settings(RESERV_CONF_SECT);
//      W25qxx_EraseSector(RESERV_CONF_SECT);
//      W25qxx_WriteSector((uint8_t*)&config, RESERV_CONF_SECT, 0, sizeof(config));
      CDC_Transmit_FS(ans, 2);      
    } break;
    
    /* Команда на сохранение параметров модуля LoRa */
    case 0xA7: {
      LORA_SaveConfig();
      CDC_Transmit_FS(ans, 2);      
    } break;
    
    case 0xA5:
    {
      field = (Cfg_fields) buf[2];
      
      set_param(field, &buf[3], buf[1] - 1);
      if ( field == FIELD_SERIAL_NUM ) 
        write_device_info();

      CDC_Transmit_FS(ans, 2);
      break;
    }
    
    case 0xA2:
    {
      cfg_zigbee->enabled = buf[1];
      CDC_Transmit_FS(ans, 2);
      break;
    }

    case 0xA4:
    {
      // read cfg
      uint8_t sendBuff[7] = {0xA4, 5, 0, 0, 0, 0, 0};
      sendBuff[2] = buf[1];
      switch(buf[1]){        
        case FIELD_FRM_VERSION:
        {
          uint32_t firm_vers = *(uint32_t*)(FRM_VERSION_ADDR);
          *(uint32_t*)&sendBuff[3] = firm_vers;
          CDC_Transmit_FS(sendBuff, 7);
          break;
        }
        case FIELD_FRM_BUILD_NUM:
        {
          uint32_t firm_build = *(uint32_t*)(FRM_BUILD_NUM_ADDR);
          *(uint32_t*)&sendBuff[3] = firm_build;
          CDC_Transmit_FS(sendBuff, 7);
          break;
        }
        case FIELD_FRM_TIMESTAMP:
        {
          uint32_t firm_timestamp = *(uint32_t*)(FRM_TIMESTAMP_ADDR);
          *(uint32_t*)&sendBuff[3] = firm_timestamp;
          CDC_Transmit_FS(sendBuff, 7);
          break;
        } 
        case FIELD_BOOT_VERSION:
        {
          uint32_t boot_version = *(uint32_t*)(BOOT_VERSION_ADDR);
          *(uint32_t*)&sendBuff[3] = boot_version;
          CDC_Transmit_FS(sendBuff, 7);
          break;
        }
      default:
        {
          if(buf[1] == FIELD_LORA_DEV_EUI && cfg_lora->LoRa_AUTO_Dev_EUI == 1){
            // get auto DEV_EUI that generated when LoRa init
            size = 8;
            uint8_t msg[35] = {0xA4, size + 1, FIELD_LORA_DEV_EUI};
            HW_GetUniqueId(&msg[3]);
            //memcpy(&msg[3], AutoDevEUI, size);
            CDC_Transmit_FS(msg, size + 3);
          }
          else{
            // read cfg
            field = (Cfg_fields) buf[1];
            cfg_field = get_param_ptr(field, &size);
            if ( cfg_field )
            {
              uint8_t msg[35] = {0xA4, size + 1, field};
              memcpy(&msg[3], cfg_field, size);
              CDC_Transmit_FS(msg, size + 3);
            }
          }
          break;
        }
      }      
      break;
    }
    
    case 0xFF:
    {
      reboot_cntr = 1000;
      break;
    }

  }
}

#define USB_MAX_BLOCK_SIZE 120

static uint8_t USB_config_send(uint32_t flag)
{
  static uint16_t pack_num;
  static uint16_t already_sent;
  uint8_t ret = 0;
  uint8_t data2send[USB_MAX_BLOCK_SIZE+10] = {0x44};
  
  if ( flag == 0 )
  {
    already_sent = 0;
    pack_num = 0;
    data2send[1] = 8;
    CAST2U16(data2send[2]) = pack_num++;
    CAST2U16(data2send[4]) = (uint16_t)sizeof(config);
    CAST2U32(data2send[6]) = config.CRC32;
    ret = CDC_Transmit_FS(data2send, 10);
    USB_SendMore = USB_config_send;
    return ret;
  }
  else if ( already_sent < sizeof(config) )
  {
    uint32_t payload = USB_MAX_BLOCK_SIZE;
    uint8_t* pcfg = (uint8_t*)&config + already_sent;
    if ( (already_sent + USB_MAX_BLOCK_SIZE) > sizeof(config) ) 
      payload = sizeof(config)-already_sent;    
    data2send[1] = payload+3;
    CAST2U16(data2send[2]) = pack_num++;
    memcpy(&data2send[4], pcfg, payload);
    already_sent += payload;
    ret = CDC_Transmit_FS(data2send, data2send[1]+1);
    USB_SendMore = USB_config_send;
    return ret;
  }
  USB_SendMore = NULL;
  return 0;
}

static uint8_t USB_sensors_send(uint32_t flag)
{
  static uint8_t sens_cnt;
  uint8_t ret = 0;
    
  if ( flag == 0 ) sens_cnt = 0;
  if ( sensorsToSendCount )
  {
    sensorsToSendCount--;    
    ret = CDC_Transmit_FS(sensorsToSend[sens_cnt++], 24);    
    USB_SendMore = USB_sensors_send;
    return ret;
  }
  
  USB_SendMore = NULL;
  return 0;
}

static uint32_t SendMsgDummy(MSG_TypeDef msg, void *pbuf, uint32_t datasize)
{
  return 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  HW_GPIO_IrqHandler(GPIO_Pin);

  if(Service_mode) return;
  
//  uint32_t adc_code = 0;
  if ( GPIO_Pin & LORA_DIO1_Pin )
  {
    irq_handler_DIO1();
  }
  if ( GPIO_Pin & OPEN_1_Pin )
  {
  }
  if ( GPIO_Pin & OPEN_2_Pin )
  {
  }
  if ( GPIO_Pin & ZB_GPIO1_Pin )
  {
    ZigBeeParse();
  }
//  switch(GPIO_Pin)
//  {
//    case LORA_DIO1_Pin:
//      handleDIO1();
//      break;
//    case OPEN_2_Pin:
////      open_handler();
//      break;
//    case OPEN_1_Pin:
////      open_handler();
//      break;
////    case RS1_CONNECTED_Pin:
////      rs_connected_handler();
////      break;
////    case RS2_CONNECTED_Pin:
////      rs_connected_handler();
////      break;
////    case ADC_READY_Pin:
////      adc_code = ads1220_read_data_cont();
////      adc_data = ADC_code_to_value(adc_code);
////      break;
//    case ZB_GPIO1_Pin:
//      ZigBeeParse();
//      break;
//    default:
//      break;
//  }
}


/* USER CODE BEGIN 4 */


//void Enter_Stand_By_Mode()
//{
//    HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);
//    HAL_RTCEx_DeactivateWakeUpTimer( &hrtc); 
//    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
//    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG( &hrtc, RTC_FLAG_WUTF);
//    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
//    if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, dev_info->Standby_time, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
//    {
//      Error_Handler();
//    }
//      HAL_PWR_EnterSTANDBYMode();
//}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim7)
    tim7_handle();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */