
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/app_zigbee.c
  * @author  MCD Application Team
  * @brief   Zigbee Application.
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
#include "app_common.h"
#include "app_entry.h"
#include "dbg_trace.h"
#include "app_zigbee.h"
#include "zigbee_interface.h"
#include "shci.h"
#include "stm_logging.h"
#include "app_conf.h"
#include "stm32wbxx_core_interface_def.h"
#include "zigbee_types.h"
#include "stm32_seq.h"

/* Private includes -----------------------------------------------------------*/
#include <assert.h>
#include "zcl/zcl.h"
#include "zcl/general/zcl.press.meas.h"
#include "zcl/general/zcl.temp.meas.h"
#include "zcl/general/zcl.wcm.h"

/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private defines -----------------------------------------------------------*/
#define APP_ZIGBEE_STARTUP_FAIL_DELAY               500U
#define CHANNEL                                     13

#define SW1_ENDPOINT                                1

/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macros ------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* External definition -------------------------------------------------------*/
enum ZbStatusCodeT ZbStartupWait(struct ZigBeeT *zb, struct ZbStartupT *config);

/* USER CODE BEGIN ED */
/* USER CODE END ED */

/* Private function prototypes -----------------------------------------------*/
static void APP_ZIGBEE_StackLayersInit(void);
static void APP_ZIGBEE_ConfigEndpoints(void);
static void APP_ZIGBEE_NwkForm(void);

static void APP_ZIGBEE_TraceError(const char *pMess, uint32_t ErrCode);
static void APP_ZIGBEE_CheckWirelessFirmwareInfo(void);

static void Wait_Getting_Ack_From_M0(void);
static void Receive_Ack_From_M0(void);
static void Receive_Notification_From_M0(void);

/* USER CODE BEGIN PFP */
static void zcl_press_meas_client_report(struct ZbZclClusterT *clusterPtr, struct ZbApsdeDataIndT *dataIndPtr, uint16_t attributeId,
    enum ZclDataTypeT dataType, const uint8_t *in_payload, uint16_t in_len);
static void zcl_temp_meas_client_report(struct ZbZclClusterT *clusterPtr, struct ZbApsdeDataIndT *dataIndPtr, uint16_t attributeId,
    enum ZclDataTypeT dataType, const uint8_t *in_payload, uint16_t in_len);
static void zcl_wc_meas_client_report(struct ZbZclClusterT *clusterPtr, struct ZbApsdeDataIndT *dataIndPtr, uint16_t attributeId,
    enum ZclDataTypeT dataType, const uint8_t *in_payload, uint16_t in_len);

static bool ZbNlmePermitJoin(uint8_t Duration);
static enum zb_msg_filter_rc app_nwk_msg_filter_cb(struct ZigBeeT *zb, uint32_t id, void *msg, void *arg);
static void Send_Data(void);
/* USER CODE END PFP */

/* Private variables ---------------------------------------------------------*/
static TL_CmdPacket_t *p_ZIGBEE_otcmdbuffer;
static TL_EvtPacket_t *p_ZIGBEE_notif_M0_to_M4;
static TL_EvtPacket_t *p_ZIGBEE_request_M0_to_M4;
static __IO uint32_t CptReceiveNotifyFromM0 = 0;
static __IO uint32_t CptReceiveRequestFromM0 = 0;

PLACE_IN_SECTION("MB_MEM1") ALIGN(4) static TL_ZIGBEE_Config_t ZigbeeConfigBuffer;
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static TL_CmdPacket_t ZigbeeOtCmdBuffer;
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static uint8_t ZigbeeNotifRspEvtBuffer[sizeof(TL_PacketHeader_t) + TL_EVT_HDR_SIZE + 255U];
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static uint8_t ZigbeeNotifRequestBuffer[sizeof(TL_PacketHeader_t) + TL_EVT_HDR_SIZE + 255U];

struct zigbee_app_info {
  bool has_init;
  struct ZigBeeT *zb;
  enum ZbStartType startupControl;
  enum ZbStatusCodeT join_status;
  uint32_t join_delay;

  struct ZbZclClusterT *pressure_meas_client_1;
  struct ZbZclClusterT *temperature_meas_client_1;
  struct ZbZclClusterT *water_content_client_1;
};
static struct zigbee_app_info zigbee_app_info;

/* USER CODE BEGIN PV */

zigbee_app_data_t zigbee_app_data;

/* USER CODE END PV */
/* Functions Definition ------------------------------------------------------*/

/**
 * @brief  Zigbee application initialization
 * @param  None
 * @retval None
 */
void APP_ZIGBEE_Init(void)
{
  SHCI_CmdStatus_t ZigbeeInitStatus;

  APP_DBG("APP_ZIGBEE_Init");

  /* Check the compatibility with the Coprocessor Wireless Firmware loaded */
  APP_ZIGBEE_CheckWirelessFirmwareInfo();

  /* Register cmdbuffer */
  APP_ZIGBEE_RegisterCmdBuffer(&ZigbeeOtCmdBuffer);

  /* Init config buffer and call TL_ZIGBEE_Init */
  APP_ZIGBEE_TL_INIT();

  /* Register task */
  /* Create the different tasks */

  UTIL_SEQ_RegTask(1U << (uint32_t)CFG_TASK_NOTIFY_FROM_M0_TO_M4, UTIL_SEQ_RFU, APP_ZIGBEE_ProcessNotifyM0ToM4);
  UTIL_SEQ_RegTask(1U << (uint32_t)CFG_TASK_REQUEST_FROM_M0_TO_M4, UTIL_SEQ_RFU, APP_ZIGBEE_ProcessRequestM0ToM4);

  /* Task associated with network creation process */
  UTIL_SEQ_RegTask(1U << CFG_TASK_ZIGBEE_NETWORK_FORM, UTIL_SEQ_RFU, APP_ZIGBEE_NwkForm);

  /* USER CODE BEGIN APP_ZIGBEE_INIT */
  UTIL_SEQ_RegTask(1U << CFG_TASK_SEND_NEW_DATA, UTIL_SEQ_RFU, Send_Data);
  /* USER CODE END APP_ZIGBEE_INIT */

  /* Start the Zigbee on the CPU2 side */
  ZigbeeInitStatus = SHCI_C2_ZIGBEE_Init();
  /* Prevent unused argument(s) compilation warning */
  UNUSED(ZigbeeInitStatus);

  /* Initialize Zigbee stack layers */
  APP_ZIGBEE_StackLayersInit();

} /* APP_ZIGBEE_Init */

/**
 * @brief  Initialize Zigbee stack layers
 * @param  None
 * @retval None
 */
static void APP_ZIGBEE_StackLayersInit(void)
{
  APP_DBG("APP_ZIGBEE_StackLayersInit");

  zigbee_app_info.zb = ZbInit(0U, NULL, NULL);
  assert(zigbee_app_info.zb != NULL);

  /* Create the endpoint and cluster(s) */
  APP_ZIGBEE_ConfigEndpoints();

  /* USER CODE BEGIN APP_ZIGBEE_StackLayersInit */
  memset(&zigbee_app_data, 0x00, sizeof(zigbee_app_data_t));
  /* USER CODE END APP_ZIGBEE_StackLayersInit */

  /* Configure the joining parameters */
  zigbee_app_info.join_status = (enum ZbStatusCodeT) 0x01; /* init to error status */
  zigbee_app_info.join_delay = HAL_GetTick(); /* now */
  zigbee_app_info.startupControl = ZbStartTypeForm;

  /* Initialization Complete */
  zigbee_app_info.has_init = true;

  /* run the task */
  UTIL_SEQ_SetTask(1U << CFG_TASK_ZIGBEE_NETWORK_FORM, CFG_SCH_PRIO_0);
} /* APP_ZIGBEE_StackLayersInit */

/**
 * @brief  Configure Zigbee application endpoints
 * @param  None
 * @retval None
 */
static void APP_ZIGBEE_ConfigEndpoints(void)
{
  struct ZbApsmeAddEndpointReqT req;
  struct ZbApsmeAddEndpointConfT conf;

  memset(&req, 0, sizeof(req));

  /* Endpoint: SW1_ENDPOINT */
  req.profileId = ZCL_PROFILE_HOME_AUTOMATION;
  req.deviceId = ZCL_DEVICE_COMBINED_INTERFACE;
  req.endpoint = SW1_ENDPOINT;
  ZbZclAddEndpoint(zigbee_app_info.zb, &req, &conf);
  assert(conf.status == ZB_STATUS_SUCCESS);

  /* Pressure meas client */
  zigbee_app_info.pressure_meas_client_1 = ZbZclPressMeasClientAlloc(zigbee_app_info.zb, SW1_ENDPOINT);
  assert(zigbee_app_info.pressure_meas_client_1 != NULL);
  zigbee_app_info.pressure_meas_client_1->report = &zcl_press_meas_client_report;
  ZbZclClusterEndpointRegister(zigbee_app_info.pressure_meas_client_1);

  /* Temperature meas client */
  zigbee_app_info.temperature_meas_client_1 = ZbZclTempMeasClientAlloc(zigbee_app_info.zb, SW1_ENDPOINT);
  assert(zigbee_app_info.temperature_meas_client_1 != NULL);
  zigbee_app_info.temperature_meas_client_1->report = &zcl_temp_meas_client_report;
  ZbZclClusterEndpointRegister(zigbee_app_info.temperature_meas_client_1);

  /* Water content client */
  zigbee_app_info.water_content_client_1 = ZbZclWaterContentMeasClientAlloc(zigbee_app_info.zb, SW1_ENDPOINT, ZCL_CLUSTER_MEAS_HUMIDITY);
  assert(zigbee_app_info.water_content_client_1 != NULL);
  zigbee_app_info.water_content_client_1->report = &zcl_wc_meas_client_report;
  ZbZclClusterEndpointRegister(zigbee_app_info.water_content_client_1);

  /* USER CODE BEGIN CONFIG_ENDPOINT */
  /* USER CODE END CONFIG_ENDPOINT */
} /* APP_ZIGBEE_ConfigEndpoints */


/* pressure report received from server*/
static void
zcl_press_meas_client_report(struct ZbZclClusterT *clusterPtr, struct ZbApsdeDataIndT *dataIndPtr, uint16_t attributeId,
    enum ZclDataTypeT dataType, const uint8_t *in_payload, uint16_t in_len)
{  
    int attrLen;
    int16_t attr_val;

    /* Verify the source of the reported attribute. */
    /*if(dataIndPtr->src.nwkAddr!=nwkAddr) 
    {
      APP_DBG("[PRESS MEAS] Report error wrong source addr");
        return;
    }*/
    if (dataIndPtr->src.endpoint!= SW1_ENDPOINT) 
    {
        APP_DBG("[PRESS MEAS] Report error wrong endpoint");
        return;
    }
    if (attributeId == ZCL_PRESS_MEAS_ATTR_MEAS_VAL)
    {

        APP_DBG("[PRESS MEAS] Received a report from Server");
        attrLen = ZbZclAttrParseLength(dataType, in_payload, dataIndPtr->asduLength, 0);
        if (attrLen < 0) {
            return;
        }
        if (attrLen > (int)in_len) {
           return;
        }
    
        attr_val= pletoh16(in_payload);
        
        for (int i = 0; i < MAX_SENSOR_COUNT; i++){
          if (dataIndPtr->src.nwkAddr == zigbee_app_data.AqaraSensor[i].address){
            zigbee_app_data.AqaraSensor[i].pressure = (int16_t)attr_val;
            zigbee_app_data.AqaraSensor[i].LQI = dataIndPtr->linkQuality;
            
            zigbee_app_data.AqaraSensor[i].pressure_new = true;
            if (zigbee_app_data.AqaraSensor[i].temperature_new == true &&
                zigbee_app_data.AqaraSensor[i].water_content_new == true){
                  zigbee_app_data.AqaraSensor[i].all_new = true;
                  UTIL_SEQ_SetTask(1U << CFG_TASK_SEND_NEW_DATA, CFG_SCH_PRIO_0);
                }
          }      
        }
    }
  
} /* zcl_press_meas_client_report */


/* temperature report received from server*/
static void
zcl_temp_meas_client_report(struct ZbZclClusterT *clusterPtr, struct ZbApsdeDataIndT *dataIndPtr, uint16_t attributeId,
    enum ZclDataTypeT dataType, const uint8_t *in_payload, uint16_t in_len)
{
    int attrLen;
    int16_t attr_val;

    /* Verify the source of the reported attribute. */
    /*if(dataIndPtr->src.nwkAddr!=nwkAddr) 
    {
      APP_DBG("[TEMP MEAS] Report error wrong source addr");
        return;
    }*/
    if (dataIndPtr->src.endpoint!= SW1_ENDPOINT) 
    {
        APP_DBG("[TEMP MEAS] Report error wrong endpoint");
        return;
    }
    if (attributeId == ZCL_TEMP_MEAS_ATTR_MEAS_VAL)
    {

        APP_DBG("[TEMP MEAS] Received a report from Server");
        attrLen = ZbZclAttrParseLength(dataType, in_payload, dataIndPtr->asduLength, 0);
        if (attrLen < 0) {
            return;
        }
        if (attrLen > (int)in_len) {
           return;
        }
    
        attr_val= pletoh16(in_payload);
        
        for (int i = 0; i < MAX_SENSOR_COUNT; i++){
          if (dataIndPtr->src.nwkAddr == zigbee_app_data.AqaraSensor[i].address){
            zigbee_app_data.AqaraSensor[i].temperature = (int16_t)attr_val;
            zigbee_app_data.AqaraSensor[i].LQI = dataIndPtr->linkQuality;
            
            zigbee_app_data.AqaraSensor[i].temperature_new = true;
            if (zigbee_app_data.AqaraSensor[i].pressure_new == true &&
                zigbee_app_data.AqaraSensor[i].water_content_new == true){
                  zigbee_app_data.AqaraSensor[i].all_new = true;
                  UTIL_SEQ_SetTask(1U << CFG_TASK_SEND_NEW_DATA, CFG_SCH_PRIO_0);
                }
          }      
        }
    }
  
} /* zcl_press_meas_client_report */


/* water content report received from server*/
static void
zcl_wc_meas_client_report(struct ZbZclClusterT *clusterPtr, struct ZbApsdeDataIndT *dataIndPtr, uint16_t attributeId,
    enum ZclDataTypeT dataType, const uint8_t *in_payload, uint16_t in_len)
{  
    int attrLen;
    int16_t attr_val;

    /* Verify the source of the reported attribute. */
    /*if(dataIndPtr->src.nwkAddr!=nwkAddr) 
    {
      APP_DBG("[HUMIDITY MEAS] Report error wrong source addr");
        return;
    }*/
    if (dataIndPtr->src.endpoint!= SW1_ENDPOINT) 
    {
        APP_DBG("[HUMIDITY MEAS] Report error wrong endpoint");
        return;
    }
    if (attributeId == ZCL_WC_MEAS_ATTR_MEAS_VAL)
    {

        APP_DBG("[HUMIDITY MEAS] Received a report from Server");
        attrLen = ZbZclAttrParseLength(dataType, in_payload, dataIndPtr->asduLength, 0);
        if (attrLen < 0) {
            return;
        }
        if (attrLen > (int)in_len) {
           return;
        }
    
        attr_val= pletoh16(in_payload);
        
        for (int i = 0; i < MAX_SENSOR_COUNT; i++){
          if (dataIndPtr->src.nwkAddr == zigbee_app_data.AqaraSensor[i].address){
            zigbee_app_data.AqaraSensor[i].water_content = (int16_t)attr_val;
            zigbee_app_data.AqaraSensor[i].LQI = dataIndPtr->linkQuality;
            
            zigbee_app_data.AqaraSensor[i].water_content_new = true;
            if (zigbee_app_data.AqaraSensor[i].pressure_new == true &&
                zigbee_app_data.AqaraSensor[i].temperature_new == true){
                  zigbee_app_data.AqaraSensor[i].all_new = true;
                  UTIL_SEQ_SetTask(1U << CFG_TASK_SEND_NEW_DATA, CFG_SCH_PRIO_0);
                }
          }      
        }
    }
  
} /* zcl_press_meas_client_report */


/**
 * @brief  Handle Zigbee network forming and joining
 * @param  None
 * @retval None
 */
static void APP_ZIGBEE_NwkForm(void)
{
  if ((zigbee_app_info.join_status != ZB_STATUS_SUCCESS) && (HAL_GetTick() >= zigbee_app_info.join_delay))
  {
    struct ZbStartupT config;
    enum ZbStatusCodeT status;

    /* Configure Zigbee Logging */
    ZbSetLogging(zigbee_app_info.zb, ZB_LOG_MASK_LEVEL_5, NULL);

    /* Attempt to join a zigbee network */
    ZbStartupConfigGetProDefaults(&config);

    /* Set the centralized network */
    APP_DBG("Network config : APP_STARTUP_CENTRALIZED_COORDINATOR");
    config.startupControl = zigbee_app_info.startupControl;

    /* Using the default HA preconfigured Link Key */
    memcpy(config.security.preconfiguredLinkKey, sec_key_ha, ZB_SEC_KEYSIZE);

    config.channelList.count = 1;
    config.channelList.list[0].page = 0;
    config.channelList.list[0].channelMask = 1 << CHANNEL; /*Channel in use */

    /* Using ZbStartupWait (blocking) */
    status = ZbStartupWait(zigbee_app_info.zb, &config);

    APP_DBG("ZbStartup Callback (status = 0x%02x)", status);
    zigbee_app_info.join_status = status;

    if (status == ZB_STATUS_SUCCESS) {
      /* USER CODE BEGIN 0 */
      zigbee_app_info.join_delay = 0U;
      
      bool res_duration = ZbNlmePermitJoin(0xff);
      assert(res_duration == true);
      
      // Register recieving messages about joining new devices
      struct ZbMsgFilterT * filter;
      filter = ZbMsgFilterRegister(zigbee_app_info.zb, ZB_MSG_FILTER_NLME, ZB_MSG_DEFAULT_PRIO, 
                                   app_nwk_msg_filter_cb, &zigbee_app_info);
    }
    else
    {
      /* USER CODE END 0 */
      APP_DBG("Startup failed, attempting again after a short delay (%d ms)", APP_ZIGBEE_STARTUP_FAIL_DELAY);
      zigbee_app_info.join_delay = HAL_GetTick() + APP_ZIGBEE_STARTUP_FAIL_DELAY;
    }
  }

  /* If Network forming/joining was not successful reschedule the current task to retry the process */
  if (zigbee_app_info.join_status != ZB_STATUS_SUCCESS)
  {
    UTIL_SEQ_SetTask(1U << CFG_TASK_ZIGBEE_NETWORK_FORM, CFG_SCH_PRIO_0);
  }

  /* USER CODE BEGIN NW_FORM */
  /* USER CODE END NW_FORM */
} /* APP_ZIGBEE_NwkForm */

/*************************************************************
 * ZbStartupWait Blocking Call
 *************************************************************/
struct ZbStartupWaitInfo {
  bool active;
  enum ZbStatusCodeT status;
};

static void ZbStartupWaitCb(enum ZbStatusCodeT status, void *cb_arg)
{
  struct ZbStartupWaitInfo *info = cb_arg;

  info->status = status;
  info->active = false;
  UTIL_SEQ_SetEvt(EVENT_ZIGBEE_STARTUP_ENDED);
} /* ZbStartupWaitCb */

enum ZbStatusCodeT ZbStartupWait(struct ZigBeeT *zb, struct ZbStartupT *config)
{
  struct ZbStartupWaitInfo *info;
  enum ZbStatusCodeT status;

  info = malloc(sizeof(struct ZbStartupWaitInfo));
  if (info == NULL) {
    return ZB_STATUS_ALLOC_FAIL;
  }
  memset(info, 0, sizeof(struct ZbStartupWaitInfo));

  info->active = true;
  status = ZbStartup(zb, config, ZbStartupWaitCb, info);
  if (status != ZB_STATUS_SUCCESS) {
    info->active = false;
    return status;
  }
  UTIL_SEQ_WaitEvt(EVENT_ZIGBEE_STARTUP_ENDED);
  status = info->status;
  free(info);
  return status;
} /* ZbStartupWait */

/**
 * @brief  Trace the error or the warning reported.
 * @param  ErrId :
 * @param  ErrCode
 * @retval None
 */
void APP_ZIGBEE_Error(uint32_t ErrId, uint32_t ErrCode)
{
  switch (ErrId) {
  default:
    APP_ZIGBEE_TraceError("ERROR Unknown ", 0);
    break;
  }
} /* APP_ZIGBEE_Error */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

/**
 * @brief  Warn the user that an error has occurred.
 *
 * @param  pMess  : Message associated to the error.
 * @param  ErrCode: Error code associated to the module (Zigbee or other module if any)
 * @retval None
 */
static void APP_ZIGBEE_TraceError(const char *pMess, uint32_t ErrCode)
{
  APP_DBG("**** Fatal error = %s (Err = %d)", pMess, ErrCode);
  /* USER CODE BEGIN TRACE_ERROR */
  /* USER CODE END TRACE_ERROR */

} /* APP_ZIGBEE_TraceError */

/**
 * @brief Check if the Coprocessor Wireless Firmware loaded supports Zigbee
 *        and display associated information
 * @param  None
 * @retval None
 */
static void APP_ZIGBEE_CheckWirelessFirmwareInfo(void)
{
  WirelessFwInfo_t wireless_info_instance;
  WirelessFwInfo_t *p_wireless_info = &wireless_info_instance;

  if (SHCI_GetWirelessFwInfo(p_wireless_info) != SHCI_Success)
  {
    APP_ZIGBEE_Error((uint32_t)ERR_ZIGBEE_CHECK_WIRELESS, (uint32_t)ERR_INTERFACE_FATAL);
  }
  else
  {
    APP_DBG("**********************************************************");
    APP_DBG("WIRELESS COPROCESSOR FW:");
    /* Print version */
    APP_DBG("VERSION ID = %d.%d.%d", p_wireless_info->VersionMajor, p_wireless_info->VersionMinor, p_wireless_info->VersionSub);

    switch (p_wireless_info->StackType)
    {
      case INFO_STACK_TYPE_ZIGBEE_FFD:
        APP_DBG("FW Type : FFD Zigbee stack");
        break;
      case INFO_STACK_TYPE_ZIGBEE_RFD:
        APP_DBG("FW Type : RFD Zigbee stack");
        break;
      default:
        /* No Zigbee device supported ! */
        APP_ZIGBEE_Error((uint32_t)ERR_ZIGBEE_CHECK_WIRELESS, (uint32_t)ERR_INTERFACE_FATAL);
        break;
    }

    /* print the application name */
    char *__PathProject__ = (strstr(__FILE__, "Zigbee") ? strstr(__FILE__, "Zigbee") + 7 : __FILE__);
    char *pdel = NULL;
    if((strchr(__FILE__, '/')) == NULL)
    {
      pdel = strchr(__PathProject__, '\\');
    }
    else
    {
      pdel = strchr(__PathProject__, '/');
    }

    int index = (int)(pdel - __PathProject__);
    APP_DBG("Application flashed: %*.*s", index, index, __PathProject__);

    /* print channel */
    APP_DBG("Channel used: %d", CHANNEL);
    /* print Link Key */
    APP_DBG("Link Key: %.16s", sec_key_ha);
    /* print Link Key value hex */
    char Z09_LL_string[ZB_SEC_KEYSIZE*3+1];
    Z09_LL_string[0] = 0;
    for(int str_index=0; str_index < ZB_SEC_KEYSIZE; str_index++)
    {
      sprintf(&Z09_LL_string[str_index*3],"%02x ",sec_key_ha[str_index]);
    }

    APP_DBG("Link Key value: %s", Z09_LL_string);
    /* print clusters allocated */
    APP_DBG("Clusters allocated are:");
    APP_DBG("OnOff Client on Endpoint %d", SW1_ENDPOINT);
    APP_DBG("**********************************************************");
  }
} /* APP_ZIGBEE_CheckWirelessFirmwareInfo */

/*************************************************************
 *
 * WRAP FUNCTIONS
 *
 *************************************************************/

void APP_ZIGBEE_RegisterCmdBuffer(TL_CmdPacket_t *p_buffer)
{
  p_ZIGBEE_otcmdbuffer = p_buffer;
} /* APP_ZIGBEE_RegisterCmdBuffer */

Zigbee_Cmd_Request_t * ZIGBEE_Get_OTCmdPayloadBuffer(void)
{
  return (Zigbee_Cmd_Request_t *)p_ZIGBEE_otcmdbuffer->cmdserial.cmd.payload;
} /* ZIGBEE_Get_OTCmdPayloadBuffer */

Zigbee_Cmd_Request_t * ZIGBEE_Get_OTCmdRspPayloadBuffer(void)
{
  return (Zigbee_Cmd_Request_t *)((TL_EvtPacket_t *)p_ZIGBEE_otcmdbuffer)->evtserial.evt.payload;
} /* ZIGBEE_Get_OTCmdRspPayloadBuffer */

Zigbee_Cmd_Request_t * ZIGBEE_Get_NotificationPayloadBuffer(void)
{
  return (Zigbee_Cmd_Request_t *)(p_ZIGBEE_notif_M0_to_M4)->evtserial.evt.payload;
} /* ZIGBEE_Get_NotificationPayloadBuffer */

Zigbee_Cmd_Request_t * ZIGBEE_Get_M0RequestPayloadBuffer(void)
{
  return (Zigbee_Cmd_Request_t *)(p_ZIGBEE_request_M0_to_M4)->evtserial.evt.payload;
}

/**
 * @brief  This function is used to transfer the commands from the M4 to the M0.
 *
 * @param   None
 * @return  None
 */
void ZIGBEE_CmdTransfer(void)
{
  Zigbee_Cmd_Request_t *cmd_req = (Zigbee_Cmd_Request_t *)p_ZIGBEE_otcmdbuffer->cmdserial.cmd.payload;

  /* Zigbee OT command cmdcode range 0x280 .. 0x3DF = 352 */
  p_ZIGBEE_otcmdbuffer->cmdserial.cmd.cmdcode = 0x280U;
  /* Size = otCmdBuffer->Size (Number of OT cmd arguments : 1 arg = 32bits so multiply by 4 to get size in bytes)
   * + ID (4 bytes) + Size (4 bytes) */
  p_ZIGBEE_otcmdbuffer->cmdserial.cmd.plen = 8U + (cmd_req->Size * 4U);

  TL_ZIGBEE_SendM4RequestToM0();

  /* Wait completion of cmd */
  Wait_Getting_Ack_From_M0();
} /* ZIGBEE_CmdTransfer */

/**
 * @brief  This function is called when the M0+ acknowledge the fact that it has received a Cmd
 *
 *
 * @param   Otbuffer : a pointer to TL_EvtPacket_t
 * @return  None
 */
void TL_ZIGBEE_CmdEvtReceived(TL_EvtPacket_t *Otbuffer)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Otbuffer);

  Receive_Ack_From_M0();
} /* TL_ZIGBEE_CmdEvtReceived */

/**
 * @brief  This function is called when notification from M0+ is received.
 *
 * @param   Notbuffer : a pointer to TL_EvtPacket_t
 * @return  None
 */
void TL_ZIGBEE_NotReceived(TL_EvtPacket_t *Notbuffer)
{
  p_ZIGBEE_notif_M0_to_M4 = Notbuffer;

  Receive_Notification_From_M0();
} /* TL_ZIGBEE_NotReceived */

/**
 * @brief  This function is called before sending any ot command to the M0
 *         core. The purpose of this function is to be able to check if
 *         there are no notifications coming from the M0 core which are
 *         pending before sending a new ot command.
 * @param  None
 * @retval None
 */
void Pre_ZigbeeCmdProcessing(void)
{
  UTIL_SEQ_WaitEvt(EVENT_SYNCHRO_BYPASS_IDLE);
} /* Pre_ZigbeeCmdProcessing */

/**
 * @brief  This function waits for getting an acknowledgment from the M0.
 *
 * @param  None
 * @retval None
 */
static void Wait_Getting_Ack_From_M0(void)
{
  UTIL_SEQ_WaitEvt(EVENT_ACK_FROM_M0_EVT);
} /* Wait_Getting_Ack_From_M0 */

/**
 * @brief  Receive an acknowledgment from the M0+ core.
 *         Each command send by the M4 to the M0 are acknowledged.
 *         This function is called under interrupt.
 * @param  None
 * @retval None
 */
static void Receive_Ack_From_M0(void)
{
  UTIL_SEQ_SetEvt(EVENT_ACK_FROM_M0_EVT);
} /* Receive_Ack_From_M0 */

/**
 * @brief  Receive a notification from the M0+ through the IPCC.
 *         This function is called under interrupt.
 * @param  None
 * @retval None
 */
static void Receive_Notification_From_M0(void)
{
    CptReceiveNotifyFromM0++;
    UTIL_SEQ_SetTask(1U << (uint32_t)CFG_TASK_NOTIFY_FROM_M0_TO_M4, CFG_SCH_PRIO_0);
}

/**
 * @brief  This function is called when a request from M0+ is received.
 *
 * @param   Notbuffer : a pointer to TL_EvtPacket_t
 * @return  None
 */
void TL_ZIGBEE_M0RequestReceived(TL_EvtPacket_t *Reqbuffer)
{
    p_ZIGBEE_request_M0_to_M4 = Reqbuffer;

    CptReceiveRequestFromM0++;
    UTIL_SEQ_SetTask(1U << (uint32_t)CFG_TASK_REQUEST_FROM_M0_TO_M4, CFG_SCH_PRIO_0);
}

/**
 * @brief Perform initialization of TL for Zigbee.
 * @param  None
 * @retval None
 */
void APP_ZIGBEE_TL_INIT(void)
{
    ZigbeeConfigBuffer.p_ZigbeeOtCmdRspBuffer = (uint8_t *)&ZigbeeOtCmdBuffer;
    ZigbeeConfigBuffer.p_ZigbeeNotAckBuffer = (uint8_t *)ZigbeeNotifRspEvtBuffer;
    ZigbeeConfigBuffer.p_ZigbeeNotifRequestBuffer = (uint8_t *)ZigbeeNotifRequestBuffer;
    TL_ZIGBEE_Init(&ZigbeeConfigBuffer);
}

/**
 * @brief Process the messages coming from the M0.
 * @param  None
 * @retval None
 */
void APP_ZIGBEE_ProcessNotifyM0ToM4(void)
{
    if (CptReceiveNotifyFromM0 != 0) {
        /* If CptReceiveNotifyFromM0 is > 1. it means that we did not serve all the events from the radio */
        if (CptReceiveNotifyFromM0 > 1U) {
            APP_ZIGBEE_Error(ERR_REC_MULTI_MSG_FROM_M0, 0);
        }
        else {
            Zigbee_CallBackProcessing();
        }
        /* Reset counter */
        CptReceiveNotifyFromM0 = 0;
    }
}

/**
 * @brief Process the requests coming from the M0.
 * @param
 * @return
 */
void APP_ZIGBEE_ProcessRequestM0ToM4(void)
{
    if (CptReceiveRequestFromM0 != 0) {
        Zigbee_M0RequestProcessing();
        CptReceiveRequestFromM0 = 0;
    }
}


/* USER CODE BEGIN FD_LOCAL_FUNCTIONS */
/**
 * @brief Function to permit joining new devices
 * @param Duration : time period when it is allowed to join
          0x00       - prohibit joining
          0x01..0xfe - time in seconds
          0xff       - permit until this function called again
 * @return
*/
static bool ZbNlmePermitJoin(uint8_t Duration)
{
  // Permit Joining with no time limit
  struct ZbNlmePermitJoinReqT  PermJoinReq;     
  struct ZbNlmePermitJoinConfT PermJoinConf;
  
  if(zigbee_app_info.zb == NULL){
    return 0;
  }
  
  memset(&PermJoinReq, 0, sizeof(PermJoinReq));
  PermJoinReq.permitDuration = Duration;
  ZbNlmePermitJoinReq(zigbee_app_info.zb, &PermJoinReq, &PermJoinConf);
  if(PermJoinConf.status != ZB_STATUS_SUCCESS)
  {
    return false;
  }
  return true;
}
      
      
/**
 * @brief Callback function after receiving any NWK indication
 * @param
 * @return
 */
static enum zb_msg_filter_rc app_nwk_msg_filter_cb(struct ZigBeeT *zb, uint32_t id, void *msg, void *arg)
{
  //struct zigbee_app_info *app = arg;
  if (id == ZB_MSG_FILTER_JOIN_IND) {
    struct ZbNlmeJoinIndT *ind = msg;
    
    for (int i = 0; i < MAX_SENSOR_COUNT; i++){
      if (ind->nwkAddr == zigbee_app_data.AqaraSensor[i].address)
        break;
      if (zigbee_app_data.AqaraSensor[i].address == 0x0000){
        zigbee_app_data.AqaraSensor[i].address = ind->nwkAddr;
        break;
      }
    }
    
    // Do something?
    return ZB_MSG_CONTINUE;
  }
  if (id == ZB_MSG_FILTER_LEAVE_IND) {
    struct ZbNlmeLeaveIndT *ind = msg;
    
    for (int i = 0; i < MAX_SENSOR_COUNT; i++){
      if (ind->shortAddr == zigbee_app_data.AqaraSensor[i].address){
        memset(&(zigbee_app_data.AqaraSensor[i]),0x00,sizeof(AqaraSensor_t));
        break;
      }
    }
    
    // Do something?
    return ZB_MSG_CONTINUE;
  }
  if (id == ZB_MSG_FILTER_STATUS_IND) {
    struct ZbNlmeNetworkStatusIndT *ind = msg;
    // Do something?
    return ZB_MSG_CONTINUE;
  }
  return ZB_MSG_CONTINUE;
}


/**
 * @brief Set ZB_GPIO1_Pin to high level to cause interrupt
 * @param
 * @return
 */
static void Send_Data(void)
{
  HAL_GPIO_WritePin(ZB_GPIO1_GPIO_Port, ZB_GPIO1_Pin, GPIO_PIN_SET); 
}
/* USER CODE END FD_LOCAL_FUNCTIONS */
