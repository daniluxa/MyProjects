/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_entry.c
  * @author  MCD Application Team
  * @brief   Entry point of the application
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
#include "main.h"
#include "app_entry.h"
#include "app_zigbee.h"
#include "app_conf.h"
#include "hw_conf.h"
#include "stm32_seq.h"
#include "stm_logging.h"
#include "shci_tl.h"
#include "stm32_lpm.h"
#include "dbg_trace.h"
#include "shci.h"
#include "otp.h"

/* Private includes -----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
extern RTC_HandleTypeDef hrtc;
/* USER CODE BEGIN PTD */
extern SPI_HandleTypeDef hspi1;

extern zigbee_app_data_t zigbee_app_data;
extern struct zigbee_app_info zigbee_app_info;

typedef void (*pFunction)(void);
/* USER CODE END PTD */

/* Private defines -----------------------------------------------------------*/
/* POOL_SIZE = 2(TL_PacketHeader_t) + 258 (3(TL_EVT_HDR_SIZE) + 255(Payload size)) */
#define POOL_SIZE (CFG_TL_EVT_QUEUE_LENGTH * 4U * DIVC((sizeof(TL_PacketHeader_t) + TL_EVENT_FRAME_SIZE), 4U))

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros ------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static uint8_t EvtPool[POOL_SIZE];
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static TL_CmdPacket_t SystemCmdBuffer;
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static uint8_t SystemSpareEvtBuffer[sizeof(TL_PacketHeader_t) + TL_EVT_HDR_SIZE + 255U];

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Global function prototypes -----------------------------------------------*/
#if (CFG_DEBUG_TRACE != 0)
size_t DbgTraceWrite(int handle, const unsigned char * buf, size_t bufSize);
#endif /* CFG_DEBUG_TRACE != 0 */

/* USER CODE BEGIN GFP */

/* USER CODE END GFP */

/* Private functions prototypes-----------------------------------------------*/
static void Config_HSE(void);
static void Reset_Device(void);
#if (CFG_HW_RESET_BY_FW == 1)
static void Reset_IPCC(void);
static void Reset_BackupDomain(void);
#endif /* CFG_HW_RESET_BY_FW == 1*/
static void System_Init(void);
static void SystemPower_Config(void);
static void Init_Debug(void);
static void appe_Tl_Init(void);
static void APPE_SysStatusNot(SHCI_TL_CmdStatus_t status);
static void APPE_SysUserEvtRx(void * pPayload);
static void APPE_SysEvtReadyProcessing(void);
static void APPE_SysEvtError(SCHI_SystemErrCode_t ErrorCode);

#if (CFG_HW_LPUART1_ENABLED == 1)
extern void MX_LPUART1_UART_Init(void);
#endif /* CFG_HW_LPUART1_ENABLED == 1 */
#if (CFG_HW_USART1_ENABLED == 1)
extern void MX_USART1_UART_Init(void);
#endif /* CFG_HW_USART1_ENABLED == 1 */
static void Init_Rtc(void);

/* USER CODE BEGIN PFP */
static void Start_Bootloader(void);
static void Transmit_Data_To_OU(void);
static void MX_SPI1_Init(void);
static void MX_SPI1_DeInit(void);
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void MX_APPE_Config(void)
{
  /**
   * The OPTVERR flag is wrongly set at power on
   * It shall be cleared before using any HAL_FLASH_xxx() api
   */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

  /**
   * Reset some configurations so that the system behave in the same way
   * when either out of nReset or Power On
   */
  Reset_Device();

  /* Configure HSE Tuning */
  Config_HSE();

  return;
}

void MX_APPE_Init(void)
{
  System_Init();       /**< System initialization */

  SystemPower_Config(); /**< Configure the system Power Mode */

  HW_TS_Init(hw_ts_InitMode_Full, &hrtc); /**< Initialize the TimerServer */

/* USER CODE BEGIN APPE_Init_1 */
  
/* USER CODE END APPE_Init_1 */
  appe_Tl_Init();	/* Initialize all transport layers */

  /**
   * From now, the application is waiting for the ready event (VS_HCI_C2_Ready)
   * received on the system channel before starting the Stack
   * This system event is received with APPE_SysUserEvtRx()
   */
/* USER CODE BEGIN APPE_Init_2 */

/* USER CODE END APPE_Init_2 */
   return;
}

void Init_Smps(void)
{
#if (CFG_USE_SMPS != 0)
  /**
   *  Configure and enable SMPS
   *
   *  The SMPS configuration is not yet supported by CubeMx
   *  when SMPS output voltage is set to 1.4V, the RF output power is limited to 3.7dBm
   *  the SMPS output voltage shall be increased for higher RF output power
   */
  LL_PWR_SMPS_SetStartupCurrent(LL_PWR_SMPS_STARTUP_CURRENT_80MA);
  LL_PWR_SMPS_SetOutputVoltageLevel(LL_PWR_SMPS_OUTPUT_VOLTAGE_1V40);
  LL_PWR_SMPS_Enable();
#endif /* CFG_USE_SMPS != 0 */

  return;
}

void Init_Exti(void)
{
  /* Enable IPCC(36), HSEM(38) wakeup interrupts on CPU1 */
  LL_EXTI_EnableIT_32_63(LL_EXTI_LINE_36 | LL_EXTI_LINE_38);

  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/
static void Init_Debug(void)
{
#if (CFG_DEBUGGER_SUPPORTED == 1)
  /**
   * Keep debugger enabled while in any low power mode
   */
  HAL_DBGMCU_EnableDBGSleepMode();

  /***************** ENABLE DEBUGGER *************************************/
  LL_EXTI_EnableIT_32_63(LL_EXTI_LINE_48);
  LL_C2_EXTI_EnableIT_32_63(LL_EXTI_LINE_48);

#else

  GPIO_InitTypeDef gpio_config = {0};

  gpio_config.Pull = GPIO_NOPULL;
  gpio_config.Mode = GPIO_MODE_ANALOG;

  gpio_config.Pin = GPIO_PIN_15 | GPIO_PIN_14 | GPIO_PIN_13;
  __HAL_RCC_GPIOA_CLK_ENABLE();
  HAL_GPIO_Init(GPIOA, &gpio_config);
  __HAL_RCC_GPIOA_CLK_DISABLE();

  gpio_config.Pin = GPIO_PIN_4 | GPIO_PIN_3;
  __HAL_RCC_GPIOB_CLK_ENABLE();
  HAL_GPIO_Init(GPIOB, &gpio_config);
  __HAL_RCC_GPIOB_CLK_DISABLE();

  HAL_DBGMCU_DisableDBGSleepMode();
  HAL_DBGMCU_DisableDBGStopMode();
  HAL_DBGMCU_DisableDBGStandbyMode();

#endif /* (CFG_DEBUGGER_SUPPORTED == 1) */

#if (CFG_DEBUG_TRACE != 0)
  DbgTraceInit();
#endif /* CFG_DEBUG_TRACE != 0 */

  return;
}
static void Reset_Device(void)
{
#if (CFG_HW_RESET_BY_FW == 1)
  Reset_BackupDomain();

  Reset_IPCC();
#endif /* CFG_HW_RESET_BY_FW == 1 */

  return;
}

#if (CFG_HW_RESET_BY_FW == 1)
static void Reset_BackupDomain(void)
{
  if ((LL_RCC_IsActiveFlag_PINRST() != FALSE) && (LL_RCC_IsActiveFlag_SFTRST() == FALSE))
  {
    HAL_PWR_EnableBkUpAccess(); /**< Enable access to the RTC registers */

    /**
     *  Write twice the value to flush the APB-AHB bridge
     *  This bit shall be written in the register before writing the next one
     */
    HAL_PWR_EnableBkUpAccess();

    __HAL_RCC_BACKUPRESET_FORCE();
    __HAL_RCC_BACKUPRESET_RELEASE();
  }

  return;
}

static void Reset_IPCC(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_IPCC);

  LL_C1_IPCC_ClearFlag_CHx(
      IPCC,
      LL_IPCC_CHANNEL_1 | LL_IPCC_CHANNEL_2 | LL_IPCC_CHANNEL_3 | LL_IPCC_CHANNEL_4
      | LL_IPCC_CHANNEL_5 | LL_IPCC_CHANNEL_6);

  LL_C2_IPCC_ClearFlag_CHx(
      IPCC,
      LL_IPCC_CHANNEL_1 | LL_IPCC_CHANNEL_2 | LL_IPCC_CHANNEL_3 | LL_IPCC_CHANNEL_4
      | LL_IPCC_CHANNEL_5 | LL_IPCC_CHANNEL_6);

  LL_C1_IPCC_DisableTransmitChannel(
      IPCC,
      LL_IPCC_CHANNEL_1 | LL_IPCC_CHANNEL_2 | LL_IPCC_CHANNEL_3 | LL_IPCC_CHANNEL_4
      | LL_IPCC_CHANNEL_5 | LL_IPCC_CHANNEL_6);

  LL_C2_IPCC_DisableTransmitChannel(
      IPCC,
      LL_IPCC_CHANNEL_1 | LL_IPCC_CHANNEL_2 | LL_IPCC_CHANNEL_3 | LL_IPCC_CHANNEL_4
      | LL_IPCC_CHANNEL_5 | LL_IPCC_CHANNEL_6);

  LL_C1_IPCC_DisableReceiveChannel(
      IPCC,
      LL_IPCC_CHANNEL_1 | LL_IPCC_CHANNEL_2 | LL_IPCC_CHANNEL_3 | LL_IPCC_CHANNEL_4
      | LL_IPCC_CHANNEL_5 | LL_IPCC_CHANNEL_6);

  LL_C2_IPCC_DisableReceiveChannel(
      IPCC,
      LL_IPCC_CHANNEL_1 | LL_IPCC_CHANNEL_2 | LL_IPCC_CHANNEL_3 | LL_IPCC_CHANNEL_4
      | LL_IPCC_CHANNEL_5 | LL_IPCC_CHANNEL_6);

  return;
}
#endif /* CFG_HW_RESET_BY_FW == 1 */

static void Config_HSE(void)
{
    OTP_ID0_t * p_otp;

  /**
   * Read HSE_Tuning from OTP
   */
  p_otp = (OTP_ID0_t *) OTP_Read(0);
  if (p_otp)
  {
    LL_RCC_HSE_SetCapacitorTuning(p_otp->hse_tuning);
  }

  return;
}

static void System_Init(void)
{
  Init_Smps();

  Init_Exti();

  Init_Rtc();

  return;
}

static void Init_Rtc(void)
{
  /* Disable RTC registers write protection */
  LL_RTC_DisableWriteProtection(RTC);

  LL_RTC_WAKEUP_SetClock(RTC, CFG_RTC_WUCKSEL_DIVIDER);

  /* Enable RTC registers write protection */
  LL_RTC_EnableWriteProtection(RTC);

  return;
}

/**
 * @brief  Configure the system for power optimization
 *
 * @note  This API configures the system to be ready for low power mode
 *
 * @param  None
 * @retval None
 */
static void SystemPower_Config(void)
{
  /**
   * Select HSI as system clock source after Wake Up from Stop mode
   */
  LL_RCC_SetClkAfterWakeFromStop(LL_RCC_STOP_WAKEUPCLOCK_HSI);

  /* Initialize low power manager */
  UTIL_LPM_Init();
  /* Initialize the CPU2 reset value before starting CPU2 with C2BOOT */
  LL_C2_PWR_SetPowerMode(LL_PWR_MODE_SHUTDOWN);

#if (CFG_USB_INTERFACE_ENABLE != 0)
  /**
   *  Enable USB power
   */
  HAL_PWREx_EnableVddUSB();
#endif /* CFG_USB_INTERFACE_ENABLE != 0 */

  return;
}

static void appe_Tl_Init(void)
{
  TL_MM_Config_t tl_mm_config;
  SHCI_TL_HciInitConf_t SHci_Tl_Init_Conf;
  /**< Reference table initialization */
  TL_Init();

  /**< System channel initialization */
  UTIL_SEQ_RegTask(1<< CFG_TASK_SYSTEM_HCI_ASYNCH_EVT, UTIL_SEQ_RFU, shci_user_evt_proc);
  SHci_Tl_Init_Conf.p_cmdbuffer = (uint8_t*)&SystemCmdBuffer;
  SHci_Tl_Init_Conf.StatusNotCallBack = APPE_SysStatusNot;
  shci_init(APPE_SysUserEvtRx, (void*) &SHci_Tl_Init_Conf);

  /**< Memory Manager channel initialization */
  tl_mm_config.p_BleSpareEvtBuffer = 0;
  tl_mm_config.p_SystemSpareEvtBuffer = SystemSpareEvtBuffer;
  tl_mm_config.p_AsynchEvtPool = EvtPool;
  tl_mm_config.AsynchEvtPoolSize = POOL_SIZE;
  TL_MM_Init(&tl_mm_config);

  TL_Enable();

  return;
}

static void APPE_SysStatusNot(SHCI_TL_CmdStatus_t status)
{
  UNUSED(status);
  return;
}

/**
 * The type of the payload for a system user event is tSHCI_UserEvtRxParam
 * When the system event is both :
 *    - a ready event (subevtcode = SHCI_SUB_EVT_CODE_READY)
 *    - reported by the FUS (sysevt_ready_rsp == FUS_FW_RUNNING)
 * The buffer shall not be released
 * (eg ((tSHCI_UserEvtRxParam*)pPayload)->status shall be set to SHCI_TL_UserEventFlow_Disable)
 * When the status is not filled, the buffer is released by default
 */
static void APPE_SysUserEvtRx(void * pPayload)
{
  TL_AsynchEvt_t *p_sys_event;
  p_sys_event = (TL_AsynchEvt_t*)(((tSHCI_UserEvtRxParam*)pPayload)->pckt->evtserial.evt.payload);

  switch(p_sys_event->subevtcode)
  {
     case SHCI_SUB_EVT_CODE_READY:
         APPE_SysEvtReadyProcessing();
         break;
     case SHCI_SUB_EVT_ERROR_NOTIF:
         APPE_SysEvtError((SCHI_SystemErrCode_t) (p_sys_event->payload[0]));
         break;
     default:
         break;
  }
  return;
}

/**
 * @brief Notify a system error coming from the M0 firmware
 * @param  ErrorCode  : errorCode detected by the M0 firmware
 *
 * @retval None
 */
static void APPE_SysEvtError(SCHI_SystemErrCode_t ErrorCode)
{
  switch(ErrorCode)
  {
  case ERR_ZIGBEE_UNKNOWN_CMD:
       APP_DBG("** ERR_ZIGBEE : UNKNOWN_CMD \n");
       break;
  default:
       APP_DBG("** ERR_ZIGBEE : ErroCode=%d \n",ErrorCode);
       break;
  }
  return;
}

static void APPE_SysEvtReadyProcessing(void)
{
  /* Traces channel initialization */
  TL_TRACES_Init();

  APP_ZIGBEE_Init();
  UTIL_LPM_SetOffMode(1U << CFG_LPM_APP, UTIL_LPM_ENABLE);
  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS */

/* USER CODE END FD_LOCAL_FUNCTIONS */

/*************************************************************
 *
 * WRAP FUNCTIONS
 *
 *************************************************************/
void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += HAL_GetTickFreq();
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
    /************************************************************************************
     * ENTER SLEEP MODE
     ***********************************************************************************/
    LL_LPM_EnableSleep(); /**< Clear SLEEPDEEP bit of Cortex System Control Register */

    /**
     * This option is used to ensure that store operations are completed
     */
  #if defined (__CC_ARM)
    __force_stores();
  #endif /* __CC_ARM */

    __WFI();
  }
}

void MX_APPE_Process(void)
{
  /* USER CODE BEGIN MX_APPE_Process_1 */

  /* USER CODE END MX_APPE_Process_1 */
  UTIL_SEQ_Run(UTIL_SEQ_DEFAULT);
  /* USER CODE BEGIN MX_APPE_Process_2 */

  /* USER CODE END MX_APPE_Process_2 */
}

void UTIL_SEQ_Idle(void)
{
#if (CFG_LPM_SUPPORTED == 1)
  UTIL_LPM_EnterLowPower();
#endif /* CFG_LPM_SUPPORTED == 1 */
  return;
}

/**
  * @brief  This function is called by the scheduler each time an event
  *         is pending.
  *
  * @param  evt_waited_bm : Event pending.
  * @retval None
  */
void UTIL_SEQ_EvtIdle(UTIL_SEQ_bm_t task_id_bm, UTIL_SEQ_bm_t evt_waited_bm)
{
  switch(evt_waited_bm)
  {
  case EVENT_ACK_FROM_M0_EVT:
    /**
     * Run only the task CFG_TASK_REQUEST_FROM_M0_TO_M4 to process
     * direct requests from the M0 (e.g. ZbMalloc), but no stack notifications
     * until we're done the request to the M0.
     */
    UTIL_SEQ_Run((1U << CFG_TASK_REQUEST_FROM_M0_TO_M4));
    break;
  case EVENT_SYNCHRO_BYPASS_IDLE:
    UTIL_SEQ_SetEvt(EVENT_SYNCHRO_BYPASS_IDLE);
    /* Process notifications and requests from the M0 */
    UTIL_SEQ_Run((1U << CFG_TASK_NOTIFY_FROM_M0_TO_M4) | (1U << CFG_TASK_REQUEST_FROM_M0_TO_M4));
    break;
  default :
    /* default case */
  UTIL_SEQ_Run(UTIL_SEQ_DEFAULT);
    break;
  }
}

void shci_notify_asynch_evt(void* pdata)
{
  UNUSED(pdata);
  UTIL_SEQ_SetTask(1U << CFG_TASK_SYSTEM_HCI_ASYNCH_EVT, CFG_SCH_PRIO_0);
  return;
}

void shci_cmd_resp_release(uint32_t flag)
{
  UNUSED(flag);
  UTIL_SEQ_SetEvt(1U << CFG_EVT_SYSTEM_HCI_CMD_EVT_RESP);
  return;
}

void shci_cmd_resp_wait(uint32_t timeout)
{
  UNUSED(timeout);
  UTIL_SEQ_WaitEvt(1U << CFG_EVT_SYSTEM_HCI_CMD_EVT_RESP);
  return;
}

/* Received trace buffer from M0 */
void TL_TRACES_EvtReceived(TL_EvtPacket_t * hcievt)
{
#if (CFG_DEBUG_TRACE != 0)
  /* Call write/print function using DMA from dbg_trace */
  /* - Cast to TL_AsynchEvt_t* to get "real" payload (without Sub Evt code 2bytes),
     - (-2) to size to remove Sub Evt Code */
  DbgTraceWrite(1U, (const unsigned char *) ((TL_AsynchEvt_t *)(hcievt->evtserial.evt.payload))->payload, hcievt->evtserial.evt.plen - 2U);
#endif /* CFG_DEBUG_TRACE != 0 */
  /* Release buffer */
  TL_MM_EvtDone(hcievt);
}
/**
  * @brief  Initialisation of the trace mechanism
  * @param  None
  * @retval None
  */
#if (CFG_DEBUG_TRACE != 0)
void DbgOutputInit(void)
{
#ifdef CFG_DEBUG_TRACE_UART
  MX_USART1_UART_Init();
  return;
#endif /* CFG_DEBUG_TRACE_UART */
}

/**
  * @brief  Management of the traces
  * @param  p_data : data
  * @param  size : size
  * @param  call-back :
  * @retval None
  */
void DbgOutputTraces(uint8_t *p_data, uint16_t size, void (*cb)(void))
{
  HW_UART_Transmit_DMA(CFG_DEBUG_TRACE_UART, p_data, size, cb);

  return;
}
#endif /* CFG_DEBUG_TRACE != 0 */

/* USER CODE BEGIN FD_WRAP_FUNCTIONS */
/**
  * @brief This function manage the Push button action
  * @param  GPIO_Pin : GPIO pin which has been activated
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  uint8_t rx_data[2] = {0xFF, 0xFF};
  switch (GPIO_Pin){
  case ZB_CS_Pin:
    {
      HAL_StatusTypeDef res;
      
      MX_SPI1_Init();
      res = HAL_SPI_Receive(&hspi1,rx_data,2,10);
      if(res != HAL_OK) return;
      
      switch (rx_data[0]){
      case 0x10:
        {
          if (rx_data[1] == 0x11){
            MX_SPI1_DeInit();
            Start_Bootloader();
          }
          break;
        }
      case 0x20:
        {
          //Receive_data_from_OU();
          break;
        }
      case 0x30:
        {
          if (rx_data[1] == 0x11)
            Transmit_Data_To_OU();
          break;
        }
      default: // пришла неизвестная команда
        {
          uint8_t err_data[2] = {0xF0, 0xFF};
          res = HAL_SPI_Transmit(&hspi1,err_data,2,10);
          break;
        }
      }
      
      MX_SPI1_DeInit();
      break;
    }
  default:
    break;
  }
}


/**
  * @brief Bootloader starter function
  * @param None
  * @retval None
  */
static void Start_Bootloader(void)
{
  // jump to bootloader
  if ((((*(__IO uint32_t*)ADDR_FLASH_BOOTLOADER_START) & 0xFF000000 ) == 0x20000000) || 
  (((*(__IO uint32_t*)ADDR_FLASH_BOOTLOADER_START) & 0xFF000000 ) == 0x10000000))
  {
    __disable_irq();
    HAL_RCC_DeInit();
    
    uint32_t jumpAddress = *(__IO uint32_t*) (ADDR_FLASH_BOOTLOADER_START + 4);
    pFunction Jump_To_Application = (pFunction) jumpAddress;
    __set_MSP(*(__IO uint32_t*) ADDR_FLASH_BOOTLOADER_START);
    Jump_To_Application();
  }
  else
  {
    //HAL_Delay(1000000); // Что делать в случае неудачи?
    
    uint8_t err[2] = {0x10, 0xFF};
    HAL_SPI_Transmit(&hspi1,err,2,10);
  }
}


/**
  * @brief Data transmition to OU
  * @param None
  * @retval None
  */
static void Transmit_Data_To_OU(void)
{
  HAL_StatusTypeDef res;
  HAL_GPIO_WritePin(ZB_GPIO1_GPIO_Port, ZB_GPIO1_Pin, GPIO_PIN_RESET);
  
  uint8_t data[256];
  memset(data, 0x00, sizeof(data));
  data[0] = 0x30;
  data[1] = 0x21;
  
  uint16_t count = 0; // общее кол-во байт в сообщении для ОУ
  uint8_t step = 28; // кол-во байт между данными от двух устройств
  for (int i = 0; i < MAX_SENSOR_COUNT; i++){
    if (zigbee_app_data.AqaraSensor[i].all_new == true){       
          // Заголовок данных с адресом и кол-вом данных
          data[2+step*count]   = zigbee_app_data.AqaraSensor[i].address >> 8;
          data[2+step*count+1] = zigbee_app_data.AqaraSensor[i].address & 0x00FF;
          data[2+step*count+2] = 4;
          // Температура
          data[2+step*count+3] = 0x04;
          data[2+step*count+4] = 0x02;
          data[2+step*count+5] = 0x00;
          data[2+step*count+6] = 0x00;
          data[2+step*count+7] = zigbee_app_data.AqaraSensor[i].temperature >> 8;
          data[2+step*count+8] = zigbee_app_data.AqaraSensor[i].temperature & 0x000000FF;
          // Давление
          data[2+step*count+9] = 0x04;
          data[2+step*count+10] = 0x03;
          data[2+step*count+11] = 0x00;
          data[2+step*count+12] = 0x00;
          data[2+step*count+13] = zigbee_app_data.AqaraSensor[i].pressure >> 8;
          data[2+step*count+14] = zigbee_app_data.AqaraSensor[i].pressure & 0x000000FF;
          // Влажность
          data[2+step*count+15] = 0x04;
          data[2+step*count+16] = 0x05;
          data[2+step*count+17] = 0x00;
          data[2+step*count+18] = 0x00;
          data[2+step*count+19] = zigbee_app_data.AqaraSensor[i].water_content >> 8;
          data[2+step*count+20] = zigbee_app_data.AqaraSensor[i].water_content & 0x000000FF;
          // LQI - Link Quality Indicator
          data[2+step*count+21] = zigbee_app_data.AqaraSensor[i].LQI;
          
          count++;
        }
  }
  
  count = count * 22 + 2; // 0x30 0x21 + 22 байт на данные от одного устройства 
  
  uint8_t tx_data[4] = {0x30, 0x12, count >> 8, count & 0x00FF};
  uint8_t rx_data[4] = {0xFF, 0xFF, 0xFF, 0xFF};
  
  res = HAL_SPI_Transmit(&hspi1,tx_data,4,10); // отправляем пакет с длиной данных
  if(res != HAL_OK) return;

  res = HAL_SPI_Receive(&hspi1,rx_data,4,10); // принимаем ответ-подтверждение
  if(res != HAL_OK) return;
  
  if (rx_data[1] != 0x13){ // что-то пошло не так
    tx_data[1] = 0xFF;
    res = HAL_SPI_Transmit(&hspi1,tx_data,2,10);
    return; 
  }  
  rx_data[1] = 0x12;
  if (*(uint32_t*)tx_data != *(uint32_t*)rx_data){ // что-то пошло не так
    tx_data[1] = 0xFF;
    res = HAL_SPI_Transmit(&hspi1,tx_data,2,10);
    return; 
  } 
  
  res = HAL_SPI_Transmit(&hspi1,data,count,10); // отправляем пакет с данными
  if(res != HAL_OK) return;
  
  MX_SPI1_DeInit();
  
  if (res == HAL_OK){
    for (int i = 0; i < MAX_SENSOR_COUNT; i++){
      if (zigbee_app_data.AqaraSensor[i].all_new == true){
        zigbee_app_data.AqaraSensor[i].pressure_new = false;
        zigbee_app_data.AqaraSensor[i].temperature_new = false;
        zigbee_app_data.AqaraSensor[i].water_content_new = false;
        zigbee_app_data.AqaraSensor[i].all_new = false;
      }
    }
  }
}


/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}


/**
  * @brief SPI1 Deinitialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_DeInit(void)
{

  /* USER CODE BEGIN SPI1_DeInit 0 */

  /* USER CODE END SPI1_DeInit 0 */

  /* USER CODE BEGIN SPI1_DeInit 1 */

  /* USER CODE END SPI1_DeInit 1 */
  if (HAL_SPI_DeInit(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_DeInit 2 */
  
  /* USER CODE END SPI1_DeInit 2 */

}
/* USER CODE END FD_WRAP_FUNCTIONS */
