/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_stm.c
  * @author  MCD Application Team
  * @brief   Custom Example Service.
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
#include "common_blesvc.h"
#include "custom_stm.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct{
  uint16_t  CustomDins_ServiceHdle;                /**< DINS_Service handle */
  uint16_t  CustomRead_FaultHdle;                  /**< READ_FAULT handle */
  uint16_t  CustomWrite_CommandHdle;               /**< WRITE_COMMAND handle */
  uint16_t  CustomRead_SpeedHdle;                  /**< READ_SPEED handle */
  uint16_t  CustomWrite_Distance_AxleHdle;         /**< WRITE_DISTANCE_AXLE handle */
  uint16_t  CustomRead_Distance_AxleHdle;          /**< READ_DISTANCE_AXLE handle */
  uint16_t  CustomWrite_Distance_BarrelHdle;       /**< WRITE_DISTANCE_BARREL handle */
  uint16_t  CustomRead_Distance_BarrelHdle;        /**< READ_DISTANCE_BARREL handle */
  uint16_t  CustomWrite_LiteraHdle;                /**< WRITE_LITERA handle */
  uint16_t  CustomRead_LiteraHdle;                 /**< READ_LITERA handle */
}CustomContext_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private defines -----------------------------------------------------------*/
#define UUID_128_SUPPORTED  1

#if (UUID_128_SUPPORTED == 1)
#define BM_UUID_LENGTH  UUID_TYPE_128
#else
#define BM_UUID_LENGTH  UUID_TYPE_16
#endif

#define BM_REQ_CHAR_SIZE    (3)

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros ------------------------------------------------------------*/
#define CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET         2
#define CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET              1
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
//uint8_t SizeSpeed = 4;
//uint8_t SizeFault = 1;
//uint8_t SizeCommand = 1;


uint8_t SizeRead_Fault = 1;
uint8_t SizeWrite_Command = 1;
uint8_t SizeRead_Speed = 4;
uint8_t SizeWrite_Distance_Axle = 4;
uint8_t SizeRead_Distance_Axle = 4;
uint8_t SizeWrite_Distance_Barrel = 4;
uint8_t SizeRead_Distance_Barrel = 4;
uint8_t SizeWrite_Litera = 1;
uint8_t SizeRead_Litera = 1;

/**
 * START of Section BLE_DRIVER_CONTEXT
 */
static CustomContext_t CustomContext;

/**
 * END of Section BLE_DRIVER_CONTEXT
 */

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static SVCCTL_EvtAckStatus_t Custom_STM_Event_Handler(void *pckt);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
/* USER CODE BEGIN PFD */

/* USER CODE END PFD */

/* Private functions ----------------------------------------------------------*/

#define COPY_UUID_128(uuid_struct, uuid_15, uuid_14, uuid_13, uuid_12, uuid_11, uuid_10, uuid_9, uuid_8, uuid_7, uuid_6, uuid_5, uuid_4, uuid_3, uuid_2, uuid_1, uuid_0) \
do {\
    uuid_struct[0] = uuid_0; uuid_struct[1] = uuid_1; uuid_struct[2] = uuid_2; uuid_struct[3] = uuid_3; \
    uuid_struct[4] = uuid_4; uuid_struct[5] = uuid_5; uuid_struct[6] = uuid_6; uuid_struct[7] = uuid_7; \
    uuid_struct[8] = uuid_8; uuid_struct[9] = uuid_9; uuid_struct[10] = uuid_10; uuid_struct[11] = uuid_11; \
    uuid_struct[12] = uuid_12; uuid_struct[13] = uuid_13; uuid_struct[14] = uuid_14; uuid_struct[15] = uuid_15; \
}while(0)

/* Hardware Characteristics Service */
/*
 The following 128bits UUIDs have been generated from the random UUID
 generator:
 D973F2E0-B19E-11E2-9E96-0800200C9A66: Service 128bits UUID
 D973F2E1-B19E-11E2-9E96-0800200C9A66: Characteristic_1 128bits UUID
 D973F2E2-B19E-11E2-9E96-0800200C9A66: Characteristic_2 128bits UUID
 */
#define COPY_DINS_SERVICE_UUID(uuid_struct)              COPY_UUID_128(uuid_struct,0x77,0xb4,0x96,0x00,0x00,0x52,0x11,0xee,0xbe,0x56,0x02,0x42,0xac,0x12,0x00,0x02)
#define COPY_READ_FAULT_UUID(uuid_struct)                COPY_UUID_128(uuid_struct,0x77,0xb4,0x96,0x01,0x00,0x52,0x11,0xee,0xbe,0x56,0x02,0x42,0xac,0x12,0x00,0x02)
#define COPY_WRITE_COMMAND_UUID(uuid_struct)             COPY_UUID_128(uuid_struct,0x77,0xb4,0x96,0x02,0x00,0x52,0x11,0xee,0xbe,0x56,0x02,0x42,0xac,0x12,0x00,0x02)
#define COPY_READ_SPEED_UUID(uuid_struct)                COPY_UUID_128(uuid_struct,0x77,0xb4,0x96,0x03,0x00,0x52,0x11,0xee,0xbe,0x56,0x02,0x42,0xac,0x12,0x00,0x02)
#define COPY_WRITE_DISTANCE_AXLE_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0x77,0xb4,0x96,0x04,0x00,0x52,0x11,0xee,0xbe,0x56,0x02,0x42,0xac,0x12,0x00,0x02)
#define COPY_READ_DISTANCE_AXLE_UUID(uuid_struct)        COPY_UUID_128(uuid_struct,0x77,0xb4,0x96,0x05,0x00,0x52,0x11,0xee,0xbe,0x56,0x02,0x42,0xac,0x12,0x00,0x02)
#define COPY_WRITE_DISTANCE_BARREL_UUID(uuid_struct)     COPY_UUID_128(uuid_struct,0x77,0xb4,0x96,0x06,0x00,0x52,0x11,0xee,0xbe,0x56,0x02,0x42,0xac,0x12,0x00,0x02)
#define COPY_READ_DISTANCE_BARREL_UUID(uuid_struct)      COPY_UUID_128(uuid_struct,0x77,0xb4,0x96,0x07,0x00,0x52,0x11,0xee,0xbe,0x56,0x02,0x42,0xac,0x12,0x00,0x02)
#define COPY_WRITE_LITERA_UUID(uuid_struct)              COPY_UUID_128(uuid_struct,0x77,0xb4,0x96,0x08,0x00,0x52,0x11,0xee,0xbe,0x56,0x02,0x42,0xac,0x12,0x00,0x02)
#define COPY_READ_READ_LITERA_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x77,0xb4,0x96,0x09,0x00,0x52,0x11,0xee,0xbe,0x56,0x02,0x42,0xac,0x12,0x00,0x02)

/* USER CODE BEGIN PF */

/* USER CODE END PF */

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
static SVCCTL_EvtAckStatus_t Custom_STM_Event_Handler(void *Event)
{
  SVCCTL_EvtAckStatus_t return_value;
  hci_event_pckt *event_pckt;
  evt_blecore_aci *blecore_evt;
  aci_gatt_attribute_modified_event_rp0 *attribute_modified;
  Custom_STM_App_Notification_evt_t     Notification;
  /* USER CODE BEGIN Custom_STM_Event_Handler_1 */

  /* USER CODE END Custom_STM_Event_Handler_1 */

  return_value = SVCCTL_EvtNotAck;
  event_pckt = (hci_event_pckt *)(((hci_uart_pckt*)Event)->data);

  switch (event_pckt->evt)
  {
    case HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE:
      blecore_evt = (evt_blecore_aci*)event_pckt->data;
      switch (blecore_evt->ecode)
      {
        case ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE:
          /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */
          attribute_modified = (aci_gatt_attribute_modified_event_rp0*)blecore_evt->data;
          if (attribute_modified->Attr_Handle == (CustomContext.CustomRead_SpeedHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1 */

            /* USER CODE END CUSTOM_STM_Service_1_Char_1 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_1_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_READ_SPEED_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_READ_SPEED_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_default */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomRead_SpeedHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if (attribute_modified->Attr_Handle == (CustomContext.CustomRead_FaultHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2 */

            /* USER CODE END CUSTOM_STM_Service_1_Char_2 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_1_Char_2_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_1_Char_2_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_READ_FAULT_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_1_Char_2_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_1_Char_2_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_READ_FAULT_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_1_Char_2_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_default */

                /* USER CODE END CUSTOM_STM_Service_1_Char_2_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomRead_FaultHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if (attribute_modified->Attr_Handle == (CustomContext.CustomWrite_CommandHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            Notification.Custom_Evt_Opcode = CUSTOM_STM_WRITE_COMMAND_WRITE_NO_RESP_EVT;
            Notification.DataTransfered.Length=attribute_modified->Attr_Data_Length;
            Notification.DataTransfered.pPayload=attribute_modified->Attr_Data;
            Custom_STM_App_Notification(&Notification);
            /* USER CODE END CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if (attribute_modified->Attr_Handle == (CustomContext.CustomWrite_CommandHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          
          else if (attribute_modified->Attr_Handle == (CustomContext.CustomWrite_Distance_AxleHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            Notification.Custom_Evt_Opcode = CUSTOM_STM_WRITE_DISTANCE_AXLE_WRITE_NO_RESP_EVT;
            Notification.DataTransfered.Length=attribute_modified->Attr_Data_Length;
            Notification.DataTransfered.pPayload=attribute_modified->Attr_Data;
            Custom_STM_App_Notification(&Notification);
            /* USER CODE END CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if (attribute_modified->Attr_Handle == (CustomContext.CustomWrite_Distance_AxleHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          
          else if (attribute_modified->Attr_Handle == (CustomContext.CustomRead_Distance_AxleHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1 */

            /* USER CODE END CUSTOM_STM_Service_1_Char_1 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_1_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_READ_DISTANCE_AXLE_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_READ_DISTANCE_AXLE_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_default */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomRead_Distance_AxleHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/
          
          else if (attribute_modified->Attr_Handle == (CustomContext.CustomWrite_Distance_BarrelHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            Notification.Custom_Evt_Opcode = CUSTOM_STM_WRITE_DISTANCE_BARREL_WRITE_NO_RESP_EVT;
            Notification.DataTransfered.Length=attribute_modified->Attr_Data_Length;
            Notification.DataTransfered.pPayload=attribute_modified->Attr_Data;
            Custom_STM_App_Notification(&Notification);
            /* USER CODE END CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if (attribute_modified->Attr_Handle == (CustomContext.CustomWrite_Distance_BarrelHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          
          else if (attribute_modified->Attr_Handle == (CustomContext.CustomRead_Distance_BarrelHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1 */

            /* USER CODE END CUSTOM_STM_Service_1_Char_1 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_1_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_READ_DISTANCE_BARREL_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_READ_DISTANCE_BARREL_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_default */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomRead_Distance_BarrelHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/
          
          else if (attribute_modified->Attr_Handle == (CustomContext.CustomWrite_LiteraHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            Notification.Custom_Evt_Opcode = CUSTOM_STM_WRITE_LITERA_WRITE_NO_RESP_EVT;
            Notification.DataTransfered.Length=attribute_modified->Attr_Data_Length;
            Notification.DataTransfered.pPayload=attribute_modified->Attr_Data;
            Custom_STM_App_Notification(&Notification);
            /* USER CODE END CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if (attribute_modified->Attr_Handle == (CustomContext.CustomWrite_LiteraHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          
          else if (attribute_modified->Attr_Handle == (CustomContext.CustomRead_LiteraHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1 */

            /* USER CODE END CUSTOM_STM_Service_1_Char_1 */
            switch (attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_1_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_READ_LITERA_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_READ_LITERA_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_default */

                /* USER CODE END CUSTOM_STM_Service_1_Char_1_default */
              break;
            }
          }  /* if (attribute_modified->Attr_Handle == (CustomContext.CustomRead_LiteraHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/
          /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */

          /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */
          break;
          
        case ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE :
          /* USER CODE BEGIN EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN */
          /* USER CODE BEGIN EVT_BLUE_GATT_READ_PERMIT_REQ_END */

          /* USER CODE END EVT_BLUE_GATT_READ_PERMIT_REQ_END */
          break;

        case ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE:
          /* USER CODE BEGIN EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN */
          /* USER CODE BEGIN EVT_BLUE_GATT_WRITE_PERMIT_REQ_END */

          /* USER CODE END EVT_BLUE_GATT_WRITE_PERMIT_REQ_END */
          break;
        /* USER CODE BEGIN BLECORE_EVT */

        /* USER CODE END BLECORE_EVT */
        default:
          /* USER CODE BEGIN EVT_DEFAULT */

          /* USER CODE END EVT_DEFAULT */
          break;
      }
      /* USER CODE BEGIN EVT_VENDOR*/

      /* USER CODE END EVT_VENDOR*/
      break; /* HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE */

      /* USER CODE BEGIN EVENT_PCKT_CASES*/

      /* USER CODE END EVENT_PCKT_CASES*/

    default:
      /* USER CODE BEGIN EVENT_PCKT*/

      /* USER CODE END EVENT_PCKT*/
      break;
  }

  /* USER CODE BEGIN Custom_STM_Event_Handler_2 */

  /* USER CODE END Custom_STM_Event_Handler_2 */

  return(return_value);
}/* end Custom_STM_Event_Handler */

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void SVCCTL_InitCustomSvc(void)
{

  Char_UUID_t  uuid;
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN SVCCTL_InitCustomSvc_1 */

  /* USER CODE END SVCCTL_InitCustomSvc_1 */

  /**
   *  Register the event handler to the BLE controller
   */
  SVCCTL_RegisterSvcHandler(Custom_STM_Event_Handler);

  /**
   *          DINS
   *
   * Max_Attribute_Records = 1 + 2*3 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for DINS_Service +
   *                                2 for READ_FAULT +
   *                                2 for WRITE_COMMAND +
   *                                2 for READ_SPEED +
   *                                2 for WRITE_DISTANCE_AXLE +
   *                                2 for READ_DISTANCE_AXLE +
   *                                2 for WRITE_DISTANCE_BARREL +
   *                                2 for READ_DISTANCE_BARREL +
   *                                2 for WRITE_LITERA +
   *                                2 for READ_LITERA +
   *                                1 for READ_FAULT configuration descriptor +
   *                                1 for READ_SPEED configuration descriptor +
   *                                1 for READ_DISTANCE_AXLE configuration descriptor +
   *                                1 for READ_DISTANCE_BARREL configuration descriptor +
   *                                1 for READ_LITERA configuration descriptor +
   *                              = 24
   */

  COPY_DINS_SERVICE_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             24,
                             &(CustomContext.CustomDins_ServiceHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_service command: DINS, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_service command: DINS \n\r");
  }

  /**
   *  READ_SPEED
   */
  COPY_READ_SPEED_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomDins_ServiceHdle,
                          UUID_TYPE_128, &uuid,
                          SizeRead_Speed,
                          CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_AUTHEN_READ | ATTR_PERMISSION_AUTHEN_WRITE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_CONSTANT,
                          &(CustomContext.CustomRead_SpeedHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : READ SPEED, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : READ SPEED \n\r");
  }
  /**
   *  READ FAULT
   */
  COPY_READ_FAULT_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomDins_ServiceHdle,
                          UUID_TYPE_128, &uuid,
                          SizeRead_Fault,
                          CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_AUTHEN_READ | ATTR_PERMISSION_AUTHEN_WRITE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_CONSTANT,
                          &(CustomContext.CustomRead_FaultHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : READ FAULT, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : READ FAULT \n\r");
  }
  /**
   *  WRITE COMMAND
   */
  COPY_WRITE_COMMAND_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomDins_ServiceHdle,
                          UUID_TYPE_128, &uuid,
                          SizeWrite_Command,
                          CHAR_PROP_WRITE_WITHOUT_RESP,
                          ATTR_PERMISSION_AUTHEN_READ | ATTR_PERMISSION_AUTHOR_READ | ATTR_PERMISSION_ENCRY_READ | ATTR_PERMISSION_AUTHEN_WRITE | ATTR_PERMISSION_AUTHOR_WRITE | ATTR_PERMISSION_ENCRY_WRITE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_CONSTANT,
                          &(CustomContext.CustomWrite_CommandHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : COMMAND, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : COMMAND \n\r");
  }
  /**
   *  WRITE_DISTANCE_AXLE
   */
  COPY_WRITE_DISTANCE_AXLE_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomDins_ServiceHdle,
                          UUID_TYPE_128, &uuid,
                          SizeWrite_Distance_Axle,
                          CHAR_PROP_WRITE_WITHOUT_RESP,
                          ATTR_PERMISSION_AUTHEN_READ | ATTR_PERMISSION_AUTHOR_READ | ATTR_PERMISSION_ENCRY_READ | ATTR_PERMISSION_AUTHEN_WRITE | ATTR_PERMISSION_AUTHOR_WRITE | ATTR_PERMISSION_ENCRY_WRITE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_CONSTANT,
                          &(CustomContext.CustomWrite_Distance_AxleHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : WRITE_DISTANCE_AXLE, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : WRITE_DISTANCE_AXLE \n\r");
  }
  /**
   *  READ_DISTANCE_AXLE
   */
  COPY_READ_DISTANCE_AXLE_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomDins_ServiceHdle,
                          UUID_TYPE_128, &uuid,
                          SizeRead_Distance_Axle,
                          CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_AUTHEN_READ | ATTR_PERMISSION_AUTHEN_WRITE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_CONSTANT,
                          &(CustomContext.CustomRead_Distance_AxleHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : READ_DISTANCE_AXLE, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : READ_DISTANCE_AXLE \n\r");
  }
  /**
   *  WRITE_DISTANCE_BARREL
   */
  COPY_WRITE_DISTANCE_BARREL_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomDins_ServiceHdle,
                          UUID_TYPE_128, &uuid,
                          SizeWrite_Distance_Barrel,
                          CHAR_PROP_WRITE_WITHOUT_RESP,
                          ATTR_PERMISSION_AUTHEN_READ | ATTR_PERMISSION_AUTHOR_READ | ATTR_PERMISSION_ENCRY_READ | ATTR_PERMISSION_AUTHEN_WRITE | ATTR_PERMISSION_AUTHOR_WRITE | ATTR_PERMISSION_ENCRY_WRITE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_CONSTANT,
                          &(CustomContext.CustomWrite_Distance_BarrelHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : WRITE_DISTANCE_BARREL, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : WRITE_DISTANCE_BARREL \n\r");
  }
  /**
   *  READ_DISTANCE_BARREL
   */
  COPY_READ_DISTANCE_BARREL_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomDins_ServiceHdle,
                          UUID_TYPE_128, &uuid,
                          SizeRead_Distance_Barrel,
                          CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_AUTHEN_READ | ATTR_PERMISSION_AUTHEN_WRITE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_CONSTANT,
                          &(CustomContext.CustomRead_Distance_BarrelHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : READ_DISTANCE_BARREL, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : READ_DISTANCE_BARREL \n\r");
  }
    /**
   *  WRITE_LITERA
   */
  COPY_WRITE_LITERA_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomDins_ServiceHdle,
                          UUID_TYPE_128, &uuid,
                          SizeWrite_Litera,
                          CHAR_PROP_WRITE_WITHOUT_RESP,
                          ATTR_PERMISSION_AUTHEN_READ | ATTR_PERMISSION_AUTHOR_READ | ATTR_PERMISSION_ENCRY_READ | ATTR_PERMISSION_AUTHEN_WRITE | ATTR_PERMISSION_AUTHOR_WRITE | ATTR_PERMISSION_ENCRY_WRITE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_CONSTANT,
                          &(CustomContext.CustomWrite_LiteraHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : WRITE_LITERA, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : WRITE_LITERA \n\r");
  }
  /**
   *  READ_LITERA
   */
  COPY_READ_READ_LITERA_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CustomContext.CustomDins_ServiceHdle,
                          UUID_TYPE_128, &uuid,
                          SizeRead_Litera,
                          CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_AUTHEN_READ | ATTR_PERMISSION_AUTHEN_WRITE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_CONSTANT,
                          &(CustomContext.CustomRead_LiteraHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_add_char command   : READ_LITERA, error code: 0x%x \n\r", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_add_char command   : READ_LITERA \n\r");
  }

  /* USER CODE BEGIN SVCCTL_InitCustomSvc_2 */

  /* USER CODE END SVCCTL_InitCustomSvc_2 */

  return;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  Service_Instance: Instance of the service to which the characteristic belongs
 *
 */
tBleStatus Custom_STM_App_Update_Char(Custom_STM_Char_Opcode_t CharOpcode, uint8_t *pPayload)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Custom_STM_App_Update_Char_1 */
    if(APP_BLE_Get_Server_Connection_Status() != APP_BLE_CONNECTED_SERVER)return ret;
  /* USER CODE END Custom_STM_App_Update_Char_1 */

  switch (CharOpcode)
  {

    case CUSTOM_STM_READ_SPEED:
      ret = aci_gatt_update_char_value(CustomContext.CustomDins_ServiceHdle,
                                       CustomContext.CustomRead_SpeedHdle,
                                       0, /* charValOffset */
                                       SizeRead_Speed, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value READ_SPEED command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value READ_SPEED command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_1*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_1*/
      break;

    case CUSTOM_STM_READ_FAULT:
      ret = aci_gatt_update_char_value(CustomContext.CustomDins_ServiceHdle,
                                       CustomContext.CustomRead_FaultHdle,
                                       0, /* charValOffset */
                                       SizeRead_Fault, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value READ_FAULT command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value READ_FAULT command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_2*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_2*/
      break;

    case CUSTOM_STM_WRITE_COMMAND:
      ret = aci_gatt_update_char_value(CustomContext.CustomDins_ServiceHdle ,
                                       CustomContext.CustomWrite_CommandHdle,
                                       0, /* charValOffset */
                                       SizeWrite_Command, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value WRITE_COMMAND command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value WRITE_COMMAND command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_3*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_3*/
      break;
      
    case CUSTOM_STM_WRITE_DISTANCE_AXLE:
      ret = aci_gatt_update_char_value(CustomContext.CustomDins_ServiceHdle ,
                                       CustomContext.CustomWrite_Distance_AxleHdle,
                                       0, /* charValOffset */
                                       SizeWrite_Distance_Axle, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value WRITE_DISTANCE_AXLE command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value WRITE_DISTANCE_AXLE command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_3*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_3*/
      break;
      
    case CUSTOM_STM_READ_DISTANCE_AXLE:
      ret = aci_gatt_update_char_value(CustomContext.CustomDins_ServiceHdle,
                                       CustomContext.CustomRead_Distance_AxleHdle,
                                       0, /* charValOffset */
                                       SizeRead_Distance_Axle, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value READ_DISTANCE_AXLE command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value READ_DISTANCE_AXLE command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_2*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_2*/
      break;
      
    case CUSTOM_STM_WRITE_DISTANCE_BARREL:
      ret = aci_gatt_update_char_value(CustomContext.CustomDins_ServiceHdle ,
                                       CustomContext.CustomWrite_Distance_BarrelHdle,
                                       0, /* charValOffset */
                                       SizeWrite_Distance_Barrel, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value WRITE_DISTANCE_BARREL command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value WRITE_DISTANCE_BARREL command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_3*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_3*/
      break;
      
    case CUSTOM_STM_READ_DISTANCE_BARREL:
      ret = aci_gatt_update_char_value(CustomContext.CustomDins_ServiceHdle,
                                       CustomContext.CustomRead_Distance_BarrelHdle,
                                       0, /* charValOffset */
                                       SizeRead_Distance_Barrel, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value READ_DISTANCE_BARREL command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value READ_DISTANCE_BARREL command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_2*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_2*/
      break;
      
     case CUSTOM_STM_WRITE_LITERA:
      ret = aci_gatt_update_char_value(CustomContext.CustomDins_ServiceHdle ,
                                       CustomContext.CustomWrite_LiteraHdle,
                                       0, /* charValOffset */
                                       SizeWrite_Litera, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value WRITE_LITERA command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value WRITE_LITERA command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_3*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_3*/
      break;
      
    case CUSTOM_STM_READ_LITERA:
      ret = aci_gatt_update_char_value(CustomContext.CustomDins_ServiceHdle,
                                       CustomContext.CustomRead_LiteraHdle,
                                       0, /* charValOffset */
                                       SizeRead_Litera, /* charValueLen */
                                       (uint8_t *)  pPayload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_update_char_value READ_LITERA command, result : 0x%x \n\r", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_update_char_value READ_LITERA command\n\r");
      }
      /* USER CODE BEGIN CUSTOM_STM_App_Update_Service_1_Char_2*/

      /* USER CODE END CUSTOM_STM_App_Update_Service_1_Char_2*/
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Custom_STM_App_Update_Char_2 */

  /* USER CODE END Custom_STM_App_Update_Char_2 */

  return ret;
}
