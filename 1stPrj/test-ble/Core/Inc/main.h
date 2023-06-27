/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32wbxx_hal.h"
#include "app_conf.h"
#include "app_entry.h"
#include "app_common.h"
#include "custom_stm.h"
#include "custom_app.h"
#include "app_ble.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
  typedef enum{
    DIST_AXLE =   1,
    DIST_BARREL = 2,
    LITERA      = 3,    
  } ConfigReqFlagBits;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_LPUART1_UART_Init(void);
void MX_USART1_UART_Init(void);

/* USER CODE BEGIN EFP */
void saveConfigToFlash();
void getConfigFormFlash();
void getDistance(uint8_t * data, float dist);
uint32_t Flash_Write_Data (uint32_t StartPageAddress, uint32_t *Data, uint16_t numberofwords);
void Flash_Read_Data (uint32_t StartPageAddress, uint32_t *RxBuf, uint16_t numberofwords);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_BLUE_Pin GPIO_PIN_5
#define LED_BLUE_GPIO_Port GPIOB
#define ADDR_FLASH_PAGE_16    ((uint32_t)0x08010000) /* Base @ of Page 16, 4 Kbytes */
#define FLASH_USER_START_ADDR       ADDR_FLASH_PAGE_16   /* Start @ of user Flash area */
#define DATA_64                     ((uint64_t)0x1234567812345678)

/* USER CODE BEGIN Private defines */
#define ADDR_LITERA             0x08010000//FLASH_BASE + 0x13C
#define ADDR_DISTANCE_AXLE      ADDR_LITERA + 4
#define ADDR_DISTANCE_BARREL    ADDR_DISTANCE_AXLE + 4

#define CheckFlag(_var, _bit)        (_var & (1 << _bit) == (1 << _bit))
#define SetBit(_var, _bit)           _var |= (1 << _bit)
#define ResetBit(_var, _bit)         _var &= !(1 << _bit)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
