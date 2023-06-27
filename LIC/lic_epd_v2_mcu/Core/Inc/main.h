/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "lora_stuff.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* USER CODE BEGIN EFP */


#define FLASH_FIRM_START_BLOCK          64    
#define FLASH_FIRM_START_PAGE           FLASH_FIRM_START_BLOCK * 256
#define FLASH_FIRM_PARAM_SECTOR         (FLASH_FIRM_START_PAGE >> 8) - 1


#if defined(USER_VECT_TAB_ADDRESS) 
#define FLASH_START_ADDR (FLASH_BASE + 0x0000C000U)
#else
#define FLASH_START_ADDR FLASH_BASE
#endif /*USER_VECT_TAB_ADDRESS*/

#define FRM_VERSION_ADDR        FLASH_START_ADDR + 0x188
#define FRM_BUILD_NUM_ADDR      FRM_VERSION_ADDR + 4
#define FRM_TIMESTAMP_ADDR      FRM_BUILD_NUM_ADDR + 4
#define BOOT_VERSION_ADDR       0x08000000UL + 0x188

//#define DEVICE_DEBUG

#ifdef DEVICE_DEBUG
#define DIAG_MSG printf

#else  /* DEVICE_DEBUG */
#define DIAG_MSG(message, ...)
#endif /* DEVICE_DEBUG */



/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ETH_3V3_En_Pin GPIO_PIN_3
#define ETH_3V3_En_GPIO_Port GPIOE
#define ETH_RXER_Pin GPIO_PIN_2
#define ETH_RXER_GPIO_Port GPIOE
#define LED_B_Pin GPIO_PIN_7
#define LED_B_GPIO_Port GPIOD
#define GPS_RES_Pin GPIO_PIN_15
#define GPS_RES_GPIO_Port GPIOA
#define ETH_NRST_Pin GPIO_PIN_6
#define ETH_NRST_GPIO_Port GPIOE
#define LED_G_Pin GPIO_PIN_12
#define LED_G_GPIO_Port GPIOG
#define LED_R_Pin GPIO_PIN_10
#define LED_R_GPIO_Port GPIOG
#define Periph_5V_En_Pin GPIO_PIN_7
#define Periph_5V_En_GPIO_Port GPIOI
#define GPS_INT_Pin GPIO_PIN_2
#define GPS_INT_GPIO_Port GPIOI
#define OPEN_1_Pin GPIO_PIN_13
#define OPEN_1_GPIO_Port GPIOC
#define RS1_TR_Pin GPIO_PIN_8
#define RS1_TR_GPIO_Port GPIOI
#define TPS1_PG_Pin GPIO_PIN_9                                                  //TPS25942x: PGOOD Active High. A high indicates PGTH has crossed the threshold value. It is an open drain output
#define TPS1_PG_GPIO_Port GPIOI
#define GPS_EN_Pin GPIO_PIN_1
#define GPS_EN_GPIO_Port GPIOI
#define SD_VCC_EN_Pin GPIO_PIN_10
#define SD_VCC_EN_GPIO_Port GPIOA
#define CH_PG_Pin GPIO_PIN_0                                                    // BQ25887: Open drain active low power good indicator 
#define CH_PG_GPIO_Port GPIOF
#define CH_STATUS_Pin GPIO_PIN_10                                               // BQ25887: Open drain charge status indicator
#define CH_STATUS_GPIO_Port GPIOI
#define RS_48V_EN_Pin GPIO_PIN_11
#define RS_48V_EN_GPIO_Port GPIOI
#define CH_CD_Pin GPIO_PIN_3                                                    // BQ25887: Active High Chip Disable Pin
#define CH_CD_GPIO_Port GPIOH
#define Periph_3V3_En_Pin GPIO_PIN_2
#define Periph_3V3_En_GPIO_Port GPIOF
#define CH_INT_Pin GPIO_PIN_1                                                   // BQ25887: Open drain active Interrupt Output
#define CH_INT_GPIO_Port GPIOF
#define KEY_FLT_RS1_Pin GPIO_PIN_3
#define KEY_FLT_RS1_GPIO_Port GPIOF
#define RS1_Connected_Pin GPIO_PIN_4
#define RS1_Connected_GPIO_Port GPIOF
#define RS1_VCC_EN_Pin GPIO_PIN_5
#define RS1_VCC_EN_GPIO_Port GPIOH
#define RS2_VCC_EN_Pin GPIO_PIN_7
#define RS2_VCC_EN_GPIO_Port GPIOF
#define KEY_FLT_RS2_Pin GPIO_PIN_6
#define KEY_FLT_RS2_GPIO_Port GPIOF
#define RS2_Connected_Pin GPIO_PIN_10
#define RS2_Connected_GPIO_Port GPIOF
#define RS2_TR_Pin GPIO_PIN_9
#define RS2_TR_GPIO_Port GPIOF
#define RS3_VCC_EN_Pin GPIO_PIN_8
#define RS3_VCC_EN_GPIO_Port GPIOF
#define Buzzer_Pin GPIO_PIN_10
#define Buzzer_GPIO_Port GPIOH
#define SDIO_CD_Pin GPIO_PIN_2
#define SDIO_CD_GPIO_Port GPIOG
#define KEY_FLT_RS3_Pin GPIO_PIN_0
#define KEY_FLT_RS3_GPIO_Port GPIOC
#define RS3_Connected_Pin GPIO_PIN_2
#define RS3_Connected_GPIO_Port GPIOC
#define LORA_Connected_Pin GPIO_PIN_3
#define LORA_Connected_GPIO_Port GPIOC
#define SIM_VCC_EN_Pin GPIO_PIN_2
#define SIM_VCC_EN_GPIO_Port GPIOB
#define SIM_Connected_Pin GPIO_PIN_1
#define SIM_Connected_GPIO_Port GPIOG
#define KEY_FLT_CAN_Pin GPIO_PIN_14
#define KEY_FLT_CAN_GPIO_Port GPIOD
#define CAN_Connected_Pin GPIO_PIN_13
#define CAN_Connected_GPIO_Port GPIOD
#define LORA_BUSY_Pin GPIO_PIN_4
#define LORA_BUSY_GPIO_Port GPIOA
#define SIM_RST_Pin GPIO_PIN_13
#define SIM_RST_GPIO_Port GPIOF
#define CS_FLASH_Pin GPIO_PIN_0
#define CS_FLASH_GPIO_Port GPIOG
#define KEY_FLT_AN1_Pin GPIO_PIN_7
#define KEY_FLT_AN1_GPIO_Port GPIOH
#define AN2_VCC_EN_Pin GPIO_PIN_12
#define AN2_VCC_EN_GPIO_Port GPIOD
#define AN2_Connected_Pin GPIO_PIN_11
#define AN2_Connected_GPIO_Port GPIOD
#define CAN_VCC_EN_Pin GPIO_PIN_10
#define CAN_VCC_EN_GPIO_Port GPIOD
#define RS3_TR_Pin GPIO_PIN_6
#define RS3_TR_GPIO_Port GPIOA
#define LORA_CS_Pin GPIO_PIN_5
#define LORA_CS_GPIO_Port GPIOA
#define LORA_LED2_Pin GPIO_PIN_12
#define LORA_LED2_GPIO_Port GPIOF
#define OPEN_2_Pin GPIO_PIN_15
#define OPEN_2_GPIO_Port GPIOF
#define ZB_Connected_Pin GPIO_PIN_8
#define ZB_Connected_GPIO_Port GPIOE
#define ZB_CS_Pin GPIO_PIN_9
#define ZB_CS_GPIO_Port GPIOE
#define ACC_INT1_Pin GPIO_PIN_11
#define ACC_INT1_GPIO_Port GPIOE
#define CS_ADC_Pin GPIO_PIN_14
#define CS_ADC_GPIO_Port GPIOE
#define ZB_LED2_Pin GPIO_PIN_12
#define ZB_LED2_GPIO_Port GPIOB
#define AN1_Connected_Pin GPIO_PIN_13
#define AN1_Connected_GPIO_Port GPIOB
#define RS1_PWR_DIS_Pin GPIO_PIN_3
#define RS1_PWR_DIS_GPIO_Port GPIOA
#define LORA_NRST_Pin GPIO_PIN_1
#define LORA_NRST_GPIO_Port GPIOB
#define LORA_DIO1_Pin GPIO_PIN_0
#define LORA_DIO1_GPIO_Port GPIOB
#define LORA_DIO1_EXTI_IRQn EXTI0_IRQn
#define LORA_LED1_Pin GPIO_PIN_11
#define LORA_LED1_GPIO_Port GPIOF
#define LORA_3V3_En_Pin GPIO_PIN_14
#define LORA_3V3_En_GPIO_Port GPIOF
#define ZB_3V3_En_Pin GPIO_PIN_7
#define ZB_3V3_En_GPIO_Port GPIOE
#define ZB_GPIO1_Pin GPIO_PIN_12
#define ZB_GPIO1_GPIO_Port GPIOE
#define ZB_GPIO1_EXTI_IRQn EXTI15_10_IRQn
#define ZB_LED1_Pin GPIO_PIN_10
#define ZB_LED1_GPIO_Port GPIOB
#define AN1_VCC_EN_Pin GPIO_PIN_11
#define AN1_VCC_EN_GPIO_Port GPIOB
#define ADC_CLK_Pin GPIO_PIN_14
#define ADC_CLK_GPIO_Port GPIOB
#define KEY_FLT_AN2_Pin GPIO_PIN_15
#define KEY_FLT_AN2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA

#define PERIPH_5V_ON() HAL_GPIO_WritePin(Periph_5V_En_GPIO_Port, Periph_5V_En_Pin, GPIO_PIN_RESET)
#define PERIPH_5V_OFF() HAL_GPIO_WritePin(Periph_5V_En_GPIO_Port, Periph_5V_En_Pin, GPIO_PIN_SET)
#define PERIPH_3V3_ON() HAL_GPIO_WritePin(Periph_3V3_En_GPIO_Port, Periph_3V3_En_Pin, GPIO_PIN_RESET)
#define PERIPH_3V3_OFF() HAL_GPIO_WritePin(Periph_3V3_En_GPIO_Port, Periph_3V3_En_Pin, GPIO_PIN_SET)
#define LORA_POWER_ON() HAL_GPIO_WritePin(LORA_3V3_En_GPIO_Port, LORA_3V3_En_Pin, GPIO_PIN_RESET)
#define LORA_POWER_OFF() HAL_GPIO_WritePin(LORA_3V3_En_GPIO_Port, LORA_3V3_En_Pin, GPIO_PIN_SET)    
#define ZIGBEE_POWER_ON() HAL_GPIO_WritePin(ZB_3V3_En_GPIO_Port, ZB_3V3_En_Pin, GPIO_PIN_RESET)
#define ZIGBEE_POWER_OFF() HAL_GPIO_WritePin(ZB_3V3_En_GPIO_Port, ZB_3V3_En_Pin, GPIO_PIN_SET)    

#define LORA_CONNECTED !HAL_GPIO_ReadPin(LORA_Connected_GPIO_Port, LORA_Connected_Pin)
#define ZIGBEE_CONNECTED !HAL_GPIO_ReadPin(ZB_Connected_GPIO_Port, ZB_Connected_Pin)

#define SC_huart        hsc1  
#define RS1_huart       huart3        
#define RS2_huart       huart2
#define RS3_huart       huart4
#define GPS_huart       huart6
#define RtcHandle       hrtc
#define hspi            hspi1

//#define USE_GPS
//#define USE_LORA
//#define USE_ETHERNET
//#define USE_ACCELEROMETER
#define USE_ZIGBEE

typedef enum
{
  MSG_BAT_TAMPER_DET    = 0,
  MSG_CASE_TAMPER_DET   = 1,
  MSG_STARTUP           = 2,
  MSG_STATUS_CHANGED    = 3  
} MSG_TypeDef;



typedef enum
{
  LED_OFF       = 0,            // 000
  BLUE          = 1,            // 001
  GREEN         = 2,            // 010
  L_BLUE        = 3,            // 011
  RED           = 4,            // 100
  PURPLE        = 5,            // 101
  YELLOW        = 6,            // 110
  WHITE         = 7,            // 111  
} LED_COLORS;

enum timeout_wait_result
{
  TIMEOUT_OK = 0,
  TIMEOUT_TRIGGERED
};

typedef __packed struct
{
  uint8_t eth_enabled;
  uint8_t Dev_IP[4];
  uint8_t Net_mask[4];
  uint8_t GW_IP[4];
  uint8_t HW_addr[6];
  uint8_t DHCP_flag;
  uint8_t mqtt_enabled;
  uint8_t Broker_addr[32];
  uint8_t Broker_addr_dns_flag;
  uint16_t Broker_port;
  char MQTT_topic_data[32];
//  char MQTT_topic_poll_period[32];
  char MQTT_ID[32];
  char MQTT_user[32];
  char MQTT_password[32];
} EthernetConfig;

typedef __packed struct{
  uint8_t  enabled;
  uint64_t ZigBee_Dev_ID;  
} ZigBeeConfig;

typedef __packed struct{
  uint8_t  Build_date[3];
  uint64_t Serial_num;
  uint32_t CRC32;
//  uint32_t Poll_period_ms;
//  uint32_t Standby_time;
//  uint32_t Work_time;
} DeviceInfo;

typedef __packed struct{
  char     Name[16];
  uint16_t ID;
  uint8_t  Address;
  uint8_t  Status;
  uint16_t PollPeriod;
} Cfg_Sensor;

typedef __packed struct{
  Cfg_Sensor Sensors[32];
  uint8_t NumOfSensors;
} SensorsConfig;

typedef __packed struct{
  uint32_t BaudRate;
  uint8_t DataBits;
  uint8_t Parity;
  uint8_t StopBits;
  uint8_t State;
  uint8_t FirstReqDelay;
  uint8_t ErrorCnt;
} RSConfig;

typedef __packed struct{  
  uint16_t       config_ver;
  //CommonConfig   common;
  EthernetConfig ethernet;
  //LoRaConfig     lora;
  ZigBeeConfig   zigbee;
  SensorsConfig  sensors[3];
  RSConfig       rs_config[3];
  uint32_t       CRC32;
} DeviceConfig;

/*typedef enum{
  Parity_None   = 0,
  Parity_Even   = 1,
  Parity_Odd    = 2,
}Isa_Parity;

typedef enum {
  Speed_9600   = 0,
  Speed_19200  = 1,
  Speed_38400  = 2,
  Speed_115200 = 4,
}Isa_Speed;

typedef enum {
  Stop_bits_2 = 0,
  Stop_bits_1 = 1,
}Isa_Stop_bits;

typedef struct{
  Isa_Parity parity;
  Isa_Speed speed;
  Isa_Stop_bits stop_bits;
}Isa_Settings;*/


typedef enum
{
  FIELD_BUILD_DATE             = 0xB2,
  FIELD_SERIAL_NUM             = 0xB3,
  FIELD_ETH_EN                 = 0xAA,
  FIELD_DEV_IP                 = 0xB4,
  FIELD_NET_MASK               = 0xB5,
  FIELD_GW_IP                  = 0xB6,
  FIELD_HW_ADDR                = 0xB7,
  FIELD_DHCP_FLAG              = 0xB8,
  FIELD_MQTT_EN                = 0xA6,
  FIELD_BROKER_ADDR            = 0xB9,
  FIELD_BROKER_ADDR_DNS_FLAG   = 0xB0,
  FIELD_STANDBY_TIME           = 0xBA,
  FIELD_WORK_TIME              = 0xBB,
  FIELD_FRM_VERSION            = 0xBC,
  FIELD_FRM_BUILD_NUM          = 0xBD,
  FIELD_FRM_TIMESTAMP          = 0xBE,
  FIELD_BOOT_VERSION           = 0xBF,
  FIELD_BROKER_PORT            = 0xC0,
  FIELD_MQTT_TOPIC_DATA        = 0xC1,
//  FIELD_MQTT_TOPIC_POLL_PERIOD = 0xC2,
  FIELD_MQTT_ID                = 0xC3,
  FIELD_MQTT_USER              = 0xC4,
  FIELD_MQTT_PASSWORD          = 0xC5,
  FIELD_POLL_PERIOD_MS         = 0xC6,
  
  FIELD_LORA_EN                 = 0xAF,
  FIELD_LORA_UID                = 0xC7,
  FIELD_LORA_DEV_EUI            = 0xC8,
  FIELD_LORA_APP_EUI            = 0xC9,
  FIELD_LORA_APP_KEY            = 0xCA,
  FIELD_LORA_APP_PORT           = 0xCB,
  FIELD_LORA_DATARATE           = 0xCC,
  FIELD_LORA_ADR                = 0xCD,
  FIELD_LORA_AUTO_DEV_EUI       = 0xCE,
  FIELD_LORA_MESSAGE_TYPE       = 0xCF,
  
  FIELD_ZIGBEE_EN               = 0xA2,
  FIELD_ZIGBEE_DEV_ID           = 0xD0,
  
  FIELD_SENSOR_RS1              = 0xE0,
  FIELD_SENSOR_RS2              = 0xE1,
  FIELD_SENSOR_RS3              = 0xE2,
   
} Cfg_fields;

typedef enum
{
  MODULE_ERROR    = 0,
  MODULE_LORA     = 1,
  MODULE_ZIGBEE   = 2,
  MODULE_ETHERNET = 3
} Module_type;

typedef enum{
  i_RS1     =   11,
  i_RS2     =   12,
  i_RS3     =   13,
  i_AN1     =   21,
  i_AS2     =   22,
  i_CAN     =   31,  
} Interfaces;

extern EthernetConfig *cfg_eth;
extern LoRaConfig     *cfg_lora;
extern ZigBeeConfig   *cfg_zigbee;
extern DeviceInfo     *dev_info;
extern SensorsConfig  *rs1_sensors;
extern SensorsConfig  *rs2_sensors;
extern SensorsConfig  *rs3_sensors;
extern RSConfig       *rs1_config;
extern RSConfig       *rs2_config;
extern RSConfig       *rs3_config;

extern DeviceConfig    config;

extern uint8_t RS1_sensor_type;
extern uint8_t RS2_sensor_type;
extern uint8_t RS3_sensor_type;

extern uint32_t (* SendMsg)(MSG_TypeDef msg, void *pbuf, uint32_t datasize);

typedef void (*irq_handler_addr)(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void Enter_Stand_By_Mode();
void Freq_Change(uint8_t Freq);
void USB_DP_PreInint();

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
