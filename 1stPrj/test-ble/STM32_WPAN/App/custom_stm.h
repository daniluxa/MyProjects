/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_stm.h
  * @author  MCD Application Team
  * @brief   Header for custom_stm.c module.
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
#ifndef CUSTOM_STM_H
#define CUSTOM_STM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ble_types.h"
#include "app_ble.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  /* DINS */
  CUSTOM_STM_READ_FAULT,
  CUSTOM_STM_WRITE_COMMAND,
  CUSTOM_STM_READ_SPEED,
  CUSTOM_STM_WRITE_DISTANCE_AXLE,
  CUSTOM_STM_READ_DISTANCE_AXLE,
  CUSTOM_STM_WRITE_DISTANCE_BARREL,
  CUSTOM_STM_READ_DISTANCE_BARREL,
  CUSTOM_STM_WRITE_LITERA,
  CUSTOM_STM_READ_LITERA,
} Custom_STM_Char_Opcode_t;

typedef enum
{
  /* READ_FAULT */
  CUSTOM_STM_READ_FAULT_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_READ_FAULT_NOTIFY_DISABLED_EVT,
  /* WRITE_COMMAND */
  CUSTOM_STM_WRITE_COMMAND_WRITE_NO_RESP_EVT,
  /* READ_SPEED */
  CUSTOM_STM_READ_SPEED_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_READ_SPEED_NOTIFY_DISABLED_EVT,
  /* WRITE_DISTANCE_AXLE */
  CUSTOM_STM_WRITE_DISTANCE_AXLE_WRITE_NO_RESP_EVT,
  /* READ_DISTANCE_AXLE */
  CUSTOM_STM_READ_DISTANCE_AXLE_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_READ_DISTANCE_AXLE_NOTIFY_DISABLED_EVT,
  /* WRITE_DISTANCE_BARREL */
  CUSTOM_STM_WRITE_DISTANCE_BARREL_WRITE_NO_RESP_EVT,
  /* READ_DISTANCE_BARREL */
  CUSTOM_STM_READ_DISTANCE_BARREL_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_READ_DISTANCE_BARREL_NOTIFY_DISABLED_EVT,
  /* WRITE_LITERA */
  CUSTOM_STM_WRITE_LITERA_WRITE_NO_RESP_EVT,
  /* READ_LITERA */
  CUSTOM_STM_READ_LITERA_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_READ_LITERA_NOTIFY_DISABLED_EVT,

  CUSTOM_STM_BOOT_REQUEST_EVT
} Custom_STM_Opcode_evt_t;

typedef struct
{
  uint8_t * pPayload;
  uint8_t   Length;
} Custom_STM_Data_t;

typedef struct
{
  Custom_STM_Opcode_evt_t       Custom_Evt_Opcode;
  Custom_STM_Data_t             DataTransfered;
  uint16_t                      ConnectionHandle;
  uint8_t                       ServiceInstance;
} Custom_STM_App_Notification_evt_t;

/* USER CODE BEGIN ET */
__packed typedef struct
{
  float      distance_axle;
  float      distance_barrel;
  uint32_t   litera;
} Config_t;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
extern uint8_t SizeRead_Fault;
extern uint8_t SizeWrite_Command;
extern uint8_t SizeRead_Speed;
extern uint8_t SizeWrite_Distance_Axle;
extern uint8_t SizeRead_Distance_Axle;
extern uint8_t SizeWrite_Distance_Barrel;
extern uint8_t SizeRead_Distance_Barrel;
extern uint8_t SizeWrite_Litera;
extern uint8_t SizeRead_Litera;

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macros -----------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions ------------------------------------------------------- */
void SVCCTL_InitCustomSvc(void);
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification);
tBleStatus Custom_STM_App_Update_Char(Custom_STM_Char_Opcode_t CharOpcode,  uint8_t *pPayload);
/* USER CODE BEGIN EF */

/* USER CODE END EF */

#ifdef __cplusplus
}
#endif

#endif /*CUSTOM_STM_H */
