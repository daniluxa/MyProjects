/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_app.c
  * @author  MCD Application Team
  * @brief   Custom Example Application (Server)
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "custom_app.h"
#include "custom_stm.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  /* DINS_Service */
  uint8_t               Read_fault_Notification_Status;
  uint8_t               Read_speed_Notification_Status;
  uint8_t               Read_distance_axle_Notification_Status;
  uint8_t               Read_distance_barrel_Notification_Status;
  uint8_t               Read_distance_litera_Notification_Status;
  /* USER CODE BEGIN CUSTOM_APP_Context_t */

  /* USER CODE END CUSTOM_APP_Context_t */

  uint16_t              ConnectionHandle;
} Custom_App_Context_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */

static Custom_App_Context_t Custom_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

uint8_t UpdateCharData[247];
uint8_t NotifyCharData[247];

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* DINS */
static void Custom_Read_fault_Update_Char(void);
static void Custom_Read_fault_Send_Notification(void);
static void Custom_Read_speed_Update_Char(void);
static void Custom_Read_speed_Send_Notification(void);
static void Custom_Read_distance_axle_Update_Char(void);
static void Custom_Read_distance_axle_Send_Notification(void);
static void Custom_Read_distance_barrel_Update_Char(void);
static void Custom_Read_distance_barrel_Send_Notification(void);
static void Custom_Read_litera_Update_Char(void);
static void Custom_Read_litera_Send_Notification(void);
extern uint8_t flag_status;
extern uint8_t flag_speed;
extern Config_t config_t;
extern uint8_t updateConfigReq;

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_1 */

  /* USER CODE END CUSTOM_STM_App_Notification_1 */
  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* USER CODE END CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* DINS */
    case CUSTOM_STM_READ_SPEED_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_SPEED_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_SPEED_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_READ_SPEED_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_SPEED_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_SPEED_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_READ_FAULT_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_FAULT_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_FAULT_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_READ_FAULT_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_FAULT_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_FAULT_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_WRITE_COMMAND_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_COMMAND_WRITE_NO_RESP_EVT */
      if(pNotification->DataTransfered.pPayload[0] == 0xA5){
        //HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
        flag_speed = 1;
      }
      else if(pNotification->DataTransfered.pPayload[0] == 0x28){
        flag_status ^= 0x01;
      }
      else if(pNotification->DataTransfered.pPayload[0] == 0x34){
        updateConfigReq = 7;
      }
      /* USER CODE END CUSTOM_STM_COMMAND_WRITE_NO_RESP_EVT */
      break;
    case CUSTOM_STM_WRITE_DISTANCE_AXLE_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_WRITE_DISTANCE_AXLE_WRITE_NO_RESP_EVT */
      memcpy(&config_t.distance_axle, &(pNotification->DataTransfered.pPayload), sizeof(config_t.distance_axle));
      SetBit(updateConfigReq, DIST_AXLE);
      /* USER CODE END CUSTOM_STM_WRITE_DISTANCE_AXLE_WRITE_NO_RESP_EVT */
      break;

    case CUSTOM_STM_READ_DISTANCE_AXLE_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_READ_DISTANCE_AXLE_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_READ_DISTANCE_AXLE_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_READ_DISTANCE_AXLE_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_READ_DISTANCE_AXLE_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_READ_DISTANCE_AXLE_NOTIFY_DISABLED_EVT */
      break;
    
    case CUSTOM_STM_WRITE_DISTANCE_BARREL_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_WRITE_DISTANCE_BARREL_WRITE_NO_RESP_EVT */
      memcpy(&config_t.distance_barrel, pNotification->DataTransfered.pPayload, sizeof(config_t.distance_barrel));
      SetBit(updateConfigReq, DIST_BARREL);
      /* USER CODE END CUSTOM_STM_WRITE_DISTANCE_BARREL_WRITE_NO_RESP_EVT */
      break;
      
    case CUSTOM_STM_READ_DISTANCE_BARREL_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_READ_DISTANCE_BARREL_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_READ_DISTANCE_BARREL_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_READ_DISTANCE_BARREL_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_READ_DISTANCE_BARREL_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_READ_DISTANCE_BARREL_NOTIFY_DISABLED_EVT */
      break;
      
    case CUSTOM_STM_WRITE_LITERA_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_WRITE_LITERA_WRITE_NO_RESP_EVT */
      config_t.litera = pNotification->DataTransfered.pPayload[0];
      SetBit(updateConfigReq, LITERA);
      /* USER CODE END CUSTOM_STM_WRITE_LITERA_WRITE_NO_RESP_EVT */
      break;
      
    case CUSTOM_STM_READ_LITERA_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_READ_LITERA_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_READ_LITERA_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_READ_LITERA_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_READ_LITERA_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_READ_LITERA_NOTIFY_DISABLED_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_STM_App_Notification_default */

      /* USER CODE END CUSTOM_STM_App_Notification_default */
      break;
  }
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_2 */

  /* USER CODE END CUSTOM_STM_App_Notification_2 */
  return;
}

void Custom_APP_Notification(Custom_App_ConnHandle_Not_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_APP_Notification_1 */

  /* USER CODE END CUSTOM_APP_Notification_1 */

  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_APP_Notification_Custom_Evt_Opcode */

    /* USER CODE END P2PS_CUSTOM_Notification_Custom_Evt_Opcode */
    case CUSTOM_CONN_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_CONN_HANDLE_EVT */

      /* USER CODE END CUSTOM_CONN_HANDLE_EVT */
      break;

    case CUSTOM_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_DISCON_HANDLE_EVT */

      /* USER CODE END CUSTOM_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_APP_Notification_default */

      /* USER CODE END CUSTOM_APP_Notification_default */
      break;
  }

  /* USER CODE BEGIN CUSTOM_APP_Notification_2 */

  /* USER CODE END CUSTOM_APP_Notification_2 */

  return;
}

void Custom_APP_Init(void)
{
  /* USER CODE BEGIN CUSTOM_APP_Init */

  /* USER CODE END CUSTOM_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

/* DINS */
void Custom_Read_speed_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Speed_UC_1*/

  /* USER CODE END Speed_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_READ_SPEED, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Speed_UC_Last*/

  /* USER CODE END Speed_UC_Last*/
  return;
}

void Custom_Read_speed_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Speed_NS_1*/

  /* USER CODE END Speed_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_READ_SPEED, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Speed_NS_Last*/

  /* USER CODE END Speed_NS_Last*/

  return;
}

void Custom_Read_fault_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Fault_UC_1*/

  /* USER CODE END Fault_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_READ_FAULT, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Fault_UC_Last*/

  /* USER CODE END Fault_UC_Last*/
  return;
}

void Custom_Read_fault_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Fault_NS_1*/

  /* USER CODE END Fault_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_READ_FAULT, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Fault_NS_Last*/

  /* USER CODE END Fault_NS_Last*/

  return;
}

void Custom_Read_distance_axle_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Read_distance_axle_UC_1*/

  /* USER CODE END Read_distance_axle_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_READ_DISTANCE_AXLE, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Read_distance_axle_UC_Last*/

  /* USER CODE END Read_distance_axle_UC_Last*/
  return;
}

void Custom_Read_distance_axle_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Read_distance_axle_NS_1*/

  /* USER CODE END Read_distance_axle_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_READ_DISTANCE_AXLE, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Read_distance_axle_NS_Last*/

  /* USER CODE END Read_distance_axle_NS_Last*/

  return;
}

void Custom_Read_distance_barrel_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Read_distance_barrel_UC_1*/

  /* USER CODE END Read_distance_barrel_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_READ_DISTANCE_BARREL, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Read_distance_barrel_UC_Last*/

  /* USER CODE END Read_distance_barrel_UC_Last*/
  return;
}

void Custom_Read_distance_barrel_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Read_distance_barrel_NS_1*/

  /* USER CODE END Read_distance_barrel_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_READ_DISTANCE_BARREL, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Read_distance_barrel_NS_Last*/

  /* USER CODE END Read_distance_barrel_NS_Last*/

  return;
}

void Custom_Read_litera_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Read_litera_UC_1*/

  /* USER CODE END Read_litera_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_READ_LITERA, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Read_litera_UC_Last*/

  /* USER CODE END Read_litera_UC_Last*/
  return;
}

void Custom_Read_litera_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Read_litera_NS_1*/

  /* USER CODE END Read_litera_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_READ_LITERA, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Read_litera_NS_Last*/

  /* USER CODE END Read_litera_NS_Last*/

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/

/* USER CODE END FD_LOCAL_FUNCTIONS*/
