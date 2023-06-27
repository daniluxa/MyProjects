#include "sensors.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "timers.h"
#include "init.h"
#include "gps.h"
#include "some_stuff.h"


/* Задержка перед подключением кабеля к интерфейсу и первым опросом датчиков */
#define MAX_SENSOR_DATASIZE     100

extern Isa_LIC isa_lic;
//extern Isa_Settings isa_set;
extern GPS_t GPS;

RSx_SensorsChain RS1_SensorsChain, RS2_SensorsChain, RS3_SensorsChain;



void RS_TR_SET(UART_HandleTypeDef* huart, bool TR)
{
    if (huart == &RS1_huart)
      HAL_GPIO_WritePin(RS1_TR_GPIO_Port, RS1_TR_Pin, (GPIO_PinState)!TR);
    else if(huart == &RS2_huart)
      HAL_GPIO_WritePin(RS2_TR_GPIO_Port, RS2_TR_Pin, (GPIO_PinState)TR);
    else if(huart == &RS3_huart)
      HAL_GPIO_WritePin(RS3_TR_GPIO_Port, RS3_TR_Pin, (GPIO_PinState)TR);
    HAL_Delay(0);
}

uint32_t RS_SensorRead(UART_HandleTypeDef* huart, pSensorElem pSensor, uint8_t* buf, uint32_t* size)
{ 
  if ( pSensor->SensorType >= 5 && pSensor->SensorType <= 18 ) return rs_read_EKSIK(huart, pSensor, buf, size);
  if ( pSensor->SensorType == ISA_LIC_v2 ) return rs_read_ISA_LIC (huart, pSensor, buf, size);
  else return 0;
}

//uint8_t rs_read_EKSIK(UART_HandleTypeDef* huart, uint8_t* buf, uint8_t Sensor_type){
uint32_t rs_read_EKSIK(UART_HandleTypeDef* huart, pSensorElem pSensor, uint8_t* buf, uint32_t* size)
{ 
  HAL_StatusTypeDef st;
  //float res = 0;
  uint8_t dev_addr = pSensor->DevAddr;
  uint16_t crc_calc = 0;
  uint8_t ans_cmd[9];
  uint8_t msg_cmd[8] = {/*dev_addr*/ 0x01, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00};

  *size = 0;
  switch(pSensor->SensorType)
  {
    case EKSIK_HUM:  msg_cmd[3] = 2; break;
    case EKSIK_PRES: msg_cmd[3] = 4; break;   
    case EKSIK_DUST_PM10: msg_cmd[3] = 8; break;
 
    /* в датчиках ниже используется нулевой регистр, ничего менять не надо */
    /*    
    case EKSIK_TEMP:    
    case EKSIK_CH4:    
    case EKSIK_O2:     
    case EKSIK_CO2:     
    case EKSIK_NH3:     
    case EKSIK_H2S:     
    case EKSIK_CO:     
    case EKSIK_NO2:     
    case EKSIK_SO2: break;  */
  }

  *((uint16_t*)&msg_cmd[6]) = crc16(msg_cmd, 6);
  
//  int i = 0;
//  do
//  {
//    if (i > 2)
//      return 1;
//
    
  RS_TR_SET(huart, true);
    if ( huart == &huart4 ) HAL_HalfDuplex_EnableTransmitter(huart);
    
    st = HAL_UART_Transmit(huart, msg_cmd, sizeof(msg_cmd), 100);
    if ( st == HAL_OK) 
    {
      HAL_Delay(1);
      RS_TR_SET(huart, false);
      if ( huart == &huart4 ) HAL_HalfDuplex_EnableReceiver(huart);
      st = HAL_UART_Receive(huart, ans_cmd, sizeof(ans_cmd), 100);
    }
    if ( st != HAL_OK) return 1;
//    i++;
//  } while (st != HAL_OK);
  
  //*(uint32_t*)&res = (uint32_t)ans_cmd[4] | (uint32_t)ans_cmd[3] << 8 | (uint32_t)ans_cmd[6] << 16 | (uint32_t)ans_cmd[5] << 24;
  crc_calc = crc16(ans_cmd, 7);
  if ( !((ans_cmd[0] == dev_addr) && (ans_cmd[1] == 0x04)
   && (*(uint16_t*)&ans_cmd[7] == crc_calc)) )
    return 2;

  memcpy(buf, &ans_cmd[3], 4);
  *size = 4;
  return 0;
}

/**
  * @brief read data from MSU44RHTL sensor
  * @param choose uart
  * @param the buffer in which the data will be written
  * @param address this sensor
  * @retval status
  */

uint8_t rs_read_MSU44RHTL(UART_HandleTypeDef* huart, uint8_t* buf, uint8_t dev_addr){

  HAL_StatusTypeDef st;

  uint16_t crc_calc = 0;
  uint8_t msg_cmd[8] = {dev_addr, 0x04, 0x00, 0x1E, 0x00, 0x0F, 0x00, 0x00};
  uint8_t ans_cmd[35];

  *((uint16_t*)&msg_cmd[6]) = crc16(msg_cmd, 6);

  int i = 0;
  do
  {
    if (i > 2) return 1;

    RS_TR_SET(huart, true);
    HAL_UART_Transmit(huart, msg_cmd, sizeof(msg_cmd), 50);
    RS_TR_SET(huart, false);
    st = HAL_UART_Receive(huart, ans_cmd, sizeof(ans_cmd), 20);
    i++;
  } while (st != HAL_OK);


  crc_calc = crc16(ans_cmd, 33);
  if (!((ans_cmd[0] == dev_addr)
   && (ans_cmd[1] == 0x04)
   && (ans_cmd[33] == (uint8_t)crc_calc)
   && (ans_cmd[34] == crc_calc >> 8)))
    return 2;

  memcpy(buf, &ans_cmd[3], 30);
  return 0;
}

void power_manage_ISA_LIC(bool state){
  if(state) HAL_GPIO_WritePin(RS_48V_EN_GPIO_Port, RS_48V_EN_Pin, GPIO_PIN_RESET);
  else HAL_GPIO_WritePin(RS_48V_EN_GPIO_Port, RS_48V_EN_Pin, GPIO_PIN_SET);
}

/**
  * @brief read data from WIND sensor
  * @param choose uart
  * @param the buffer in which the data will be written
  * @param address this sensor
  * @retval status
  */

uint32_t rs_read_ISA_LIC(UART_HandleTypeDef* huart, pSensorElem pSensor, uint8_t* buf, uint32_t* size)
{
  
  Isa_LIC* pISA_Data = (Isa_LIC*)buf;
  HAL_StatusTypeDef st;
  
  int k = 0;
  uint16_t crc_calc = 0;
  uint8_t msg_cmd[8] = {pSensor->DevAddr, 0x04, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00};
  uint8_t ans_cmd[100]; 
  uint8_t dev_addr;
  uint8_t amount_bytes;
  uint32_t *data_ptr;
  
  *((uint16_t*)&msg_cmd[6]) = crc16(msg_cmd, 6);

  *size = 0;

  RS_TR_SET(huart, true);
  st = HAL_UART_Transmit(huart, msg_cmd, sizeof(msg_cmd), 100);
  if ( st == HAL_OK )
  {
    RS_TR_SET(huart, false);
    st = HAL_UART_Receive(huart, ans_cmd, 67 /*sizeof(ans_cmd)*/, 100);
  }
  if ( st != HAL_OK ) return 1;
    
  crc_calc = crc16(ans_cmd, 65);

  uint16_t qwdf = (uint16_t)ans_cmd[66] << 8 | (uint16_t)ans_cmd[65];
  if(crc_calc != qwdf){
    st = HAL_UART_Receive(huart, &ans_cmd[67], 1 /*sizeof(ans_cmd)*/, 10);
    if ( st == HAL_OK )
    {
      qwdf = (uint16_t)ans_cmd[67] << 8 | (uint16_t)ans_cmd[66];
      crc_calc = crc16(&ans_cmd[1], 65);
      if(crc_calc != qwdf) return 1;
      k = 1;
    }
    else return 1;
  }

  dev_addr = ans_cmd[0 + k];
  //uint8_t func_code = ans_cmd[1 + k];
  amount_bytes = ans_cmd[2 + k];
  if ( (dev_addr != msg_cmd[0]) || amount_bytes != 62 ) return 1;
  
  pISA_Data->Self_Diagnostic = (uint32_t)ans_cmd[4+k] | (uint32_t)ans_cmd[3+k] << 8; 
  /* заполняем структуру адаптированными данными */
  data_ptr = (uint32_t*)&pISA_Data->Long_Comp_Speed_Wind;
  for (int i = 0; i < 15; i++ ) data_ptr[i] = ISA_LIC_Filling(ans_cmd, k, 5+i*4);
/*  *(uint32_t*)&pISA_Data->Long_Comp_Speed_Wind      = ISA_LIC_Filling(ans_cmd, k, 5);
  *(uint32_t*)&pISA_Data->Trans_Comp_Speed_Wind     = ISA_LIC_Filling(ans_cmd, k, 9);
  *(uint32_t*)&pISA_Data->ABS_Speed_Wind            = ISA_LIC_Filling(ans_cmd, k, 13);
  *(uint32_t*)&pISA_Data->Direct_Wind               = ISA_LIC_Filling(ans_cmd, k, 17);
  *(uint32_t*)&pISA_Data->Temp_Air                  = ISA_LIC_Filling(ans_cmd, k, 21);
  *(uint32_t*)&pISA_Data->Air_pressure_mm_hg        = ISA_LIC_Filling(ans_cmd, k, 25);
  *(uint32_t*)&pISA_Data->Air_pressure_gPa          = ISA_LIC_Filling(ans_cmd, k, 29);
  *(uint32_t*)&pISA_Data->Humidity                  = ISA_LIC_Filling(ans_cmd, k, 33);
  *(uint32_t*)&pISA_Data->Light                     = ISA_LIC_Filling(ans_cmd, k, 37);
  *(uint32_t*)&pISA_Data->Angle_Inclination_Zenith  = ISA_LIC_Filling(ans_cmd, k, 41);
  *(uint32_t*)&pISA_Data->Angle_Inclination_Azimuth = ISA_LIC_Filling(ans_cmd, k, 45);
  *(uint32_t*)&pISA_Data->Direct_to_North           = ISA_LIC_Filling(ans_cmd, k, 49);
  *(uint32_t*)&pISA_Data->Latitude                  = ISA_LIC_Filling(ans_cmd, k, 53);
  *(uint32_t*)&pISA_Data->Longitude                 = ISA_LIC_Filling(ans_cmd, k, 57);
  *(uint32_t*)&pISA_Data->Altitude                  = ISA_LIC_Filling(ans_cmd, k, 61);*/
  
  *size = sizeof(Isa_LIC);
  

  return 0;
}

/**
  * @brief write setting's data to WIND sensor
  * @param choose uart
  * @param address this sensor
  * @param union of struct
  * @retval status
  */
         
//uint8_t rs_write_settings_ISA_LIC(UART_HandleTypeDef* huart, uint8_t dev_addr, Isa_Settings isa_set){
//  
//  HAL_StatusTypeDef st;
//  
//  //uint16_t crc_calc = 0;  
//  uint8_t msg_cmd[8] = {dev_addr, 0x06, 0x00, 0x01, (isa_set.parity << 1) || isa_set.stop_bits, isa_set.speed, 0x00, 0x00};
//  *((uint16_t*)&msg_cmd[6]) = crc16(msg_cmd, 6);
//
//  int i = 0;
//  do
//  {
//    if (i > 2)
//      return 1;
//
//    RS_TR_SET(huart, true);
//    st = HAL_UART_Transmit(huart, msg_cmd, sizeof(msg_cmd), 100);
//    i++;
//  } while (st != HAL_OK);
//
//  return 0;
//}

uint8_t rs_read_WIND(UART_HandleTypeDef* huart, uint8_t* buf){

  HAL_StatusTypeDef st;

  uint16_t crc_calc = 0;
  uint8_t msg_cmd[5] = {0x05, 0x41, 0x04, 0, 0};
  uint8_t ans_cmd[13];

  *((uint16_t*)&msg_cmd[3]) = crc16(msg_cmd, 3);

  int i = 0;
  do
  {
    if (i > 2)
      return 1;

    RS_TR_SET(huart, true);
    HAL_UART_Transmit(huart, msg_cmd, sizeof(msg_cmd), 50);
    RS_TR_SET(huart, false);
    st = HAL_UART_Receive(huart, ans_cmd, sizeof(ans_cmd), 50);
    i++;
  } while (st != HAL_OK);


  crc_calc = crc16(ans_cmd, 11);
  if (!((ans_cmd[0] == 0x05)
   && (ans_cmd[1] == 0x41)
   && (ans_cmd[2] == 0x04)
   && (ans_cmd[11] == (uint8_t)crc_calc)
   && (ans_cmd[12] == crc_calc >> 8)))
    return 2;

  memcpy(buf, &ans_cmd[3], 8);
  return 0;
}

/**
  * @brief read data from OXYGEN sensor
  * @param choose uart
  * @param the buffer in which the data will be written
  * @param address this sensor
  * @retval status
  */

uint8_t rs_read_OXYGEN(UART_HandleTypeDef* huart, uint8_t* buf, uint8_t dev_addr){

  HAL_StatusTypeDef st;

  uint16_t crc_calc = 0;
  uint8_t msg_cmd[8] = {dev_addr, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00};
  uint8_t ans_cmd[9];

  *((uint16_t*)&msg_cmd[6]) = crc16(msg_cmd, 6);

  int i = 0;
  do
  {
    if (i > 2)
      return 1;

    RS_TR_SET(huart, true);
    HAL_UART_Transmit(huart, msg_cmd, sizeof(msg_cmd), 100);
    RS_TR_SET(huart, false);
    st = HAL_UART_Receive(huart, ans_cmd, sizeof(ans_cmd), 100);
    i++;
  } while (st != HAL_OK);


  crc_calc = crc16(ans_cmd, 7);
  if (!((ans_cmd[0] == dev_addr)
   && (ans_cmd[1] == 0x04)
   && (ans_cmd[7] == (uint8_t)crc_calc)
   && (ans_cmd[8] == crc_calc >> 8)))
    return 2;

  memcpy(buf, &ans_cmd[3], 4);
  return 0;
}

uint8_t MSU44RHTL_form_array(uint8_t* data, char* dataRead)
{
   dataRead[0] = 1;
   dataRead[1] = data[1];
   dataRead[2] = data[3];
   dataRead[3] = data[5];
   dataRead[4] = data[7];
   dataRead[5] = data[28];
   dataRead[6] = data[29];
   return 7;
}

uint8_t SEROV_form_array(uint8_t *data, char *dataRead)
{  
   dataRead[0] = 3;
   memcpy(dataRead + 1, data, 8);
   return 9;
}

uint8_t OXYGEN_form_array(uint8_t *data, char *dataRead)
{
   float val_oxy;
   *(uint32_t*)&val_oxy = (uint32_t)data[1] | (uint32_t)data[0] << 8 | (uint32_t)data[3] << 16 | (uint32_t)data[2] << 24;
   val_oxy *= 100000;
   dataRead[0] = 2;
   *(uint32_t*)&dataRead[1] = (uint32_t)val_oxy;
   //memcpy(dataRead + 1, &val_oxy, 4);
   return 5;
}

/**
  * @brief  
  * @param  
  * @retval 
  */

pSensorElem AddSensor(uint16_t sensor_type, uint8_t dev_addr, char *sens_name, uint32_t poll_period, 
                  uint32_t (* get_data_cb)(UART_HandleTypeDef*, pSensorElem, uint8_t*, uint32_t*),
                  uint32_t (* send_data_cb)(UART_HandleTypeDef*, pSensorElem, uint8_t*, uint32_t))
{    
  pSensorElem pNewSensor;
  uint32_t name_len;
  
  pNewSensor = malloc(sizeof(SensorElem));
  if ( pNewSensor == NULL ) return NULL;
  
  name_len = strlen(sens_name);
  if ( name_len > 0 && name_len < 16 )
  {
    pNewSensor->SensorName = malloc(name_len+1);
    if ( pNewSensor->SensorName == NULL ) return NULL;
    strcpy(pNewSensor->SensorName, sens_name);
  }
  
  pNewSensor->SensorEnabled = 1;
  pNewSensor->NotACKcount = 0;
  pNewSensor->DevAddr = dev_addr;
  pNewSensor->SensorType = sensor_type;
  pNewSensor->PollPeriod = poll_period;
  pNewSensor->GetData = get_data_cb;
  pNewSensor->SendData = send_data_cb;
  pNewSensor->pNext = NULL;
  pNewSensor->PollTimer = get_timer();
  init_timer(pNewSensor->PollTimer, 10000);  

  return pNewSensor;
}

/**
  * @brief  
  * @param  
  * @retval 
  */

uint32_t AddSensor2Chain(pRSx_SensorsChain pRS, pSensorElem pNewSensor)
{
  pSensorElem pTemp = pRS->pSensorsChain;
  if ( pTemp ) 
  {
    while ( pTemp->pNext ) pTemp = pTemp->pNext;
    pTemp->pNext = pNewSensor;
  }
  else pRS->pSensorsChain = pNewSensor;       
  
  return 0;
}

/**
  * @brief  
  * @param  
  * @retval 
  */

uint32_t DelSensorFromChain(pRSx_SensorsChain pRS, uint16_t sensor_type, uint8_t dev_addr)
{
  pSensorElem pSensor = pRS->pSensorsChain;
  pSensorElem pPrev = pRS->pSensorsChain;
  
  while ( pSensor ) 
  {
    /* Удаляем все датчики */
    if ( sensor_type == 0 && dev_addr == 0 )
    {
      pSensorElem pNext = pSensor->pNext;
      if ( pSensor->SensorName ) free(pSensor->SensorName);
      free(pSensor);      
      pRS->pSensorsChain = pSensor = pNext;
      continue;
    }
    
    /* Удаляем конкретный датчик */
    if ( (pSensor->DevAddr == dev_addr) && (pSensor->SensorType == sensor_type) )
    {
      if ( pPrev == pSensor )
        pRS->pSensorsChain = pRS->pSensorsChain->pNext;
      else
        pPrev->pNext = pSensor->pNext;

      if ( pSensor->SensorName ) free(pSensor->SensorName);
      free(pSensor);
      return 0;
    }
    pPrev = pSensor;
    pSensor = pSensor->pNext;    
  }  
  return 1;
}

/**
  * @brief  
  * @param  
  * @retval 
  */

void RSSensorsChainPwrControl(pRSx_SensorsChain pRSChain, GPIO_PinState connected)
{
  if(pRSChain->InterfaceEnabled){
    pRSChain->Connected = connected;
    if ( pRSChain->Connected ) pRSChain->Powered = GPIO_PIN_SET;
    else pRSChain->Powered = GPIO_PIN_RESET;
    HAL_GPIO_WritePin( pRSChain->PowerPort, pRSChain->PowerPin, pRSChain->Powered);
    pRSChain->PowerCallback(pRSChain);
    /* сбрасываем признак отключения датчика, если до этого он не отвечал*/
    if ( pRSChain->Powered ) 
    {
        pSensorElem pSensor = pRSChain->pSensorsChain;
        
        if ( pRSChain->Init ) 
        {
          pRSChain->Init();
          uint8_t dummy[8] = {0,0,0,0,0,0,0,0};
          HAL_UART_Transmit(pRSChain->pHuart, dummy, sizeof(dummy), 100);
        }
        
        while ( pSensor )
        {
          pSensor->SensorEnabled = 1;
          pSensor->NotACKcount = 0;
          pSensor = pSensor->pNext;
        }
        /* добавляем задержку опроса после включения питания */
        pRSChain->LastPollTime = HAL_GetTick() + (pRSChain->FirstReqDelay * 1000);                           
    }
    else pRSChain->DeInit(pRSChain->pHuart);
  }
}

/**
  * @brief  
  * @param  
  * @retval 
  */

uint32_t RSSensorsChainPwrSwitch(pRSx_SensorsChain pRSChain, uint32_t pwr_on)
{
  if ( pRSChain->InterfaceEnabled && pRSChain->Connected ) 
  {
    if ( pwr_on == 0 )
    {
      pRSChain->Powered = (GPIO_PinState)pwr_on;
      HAL_GPIO_WritePin( pRSChain->PowerPort, pRSChain->PowerPin, pRSChain->Powered);            
      pRSChain->PowerCallback(pRSChain);    
    }
    else RSSensorsChainPwrControl(pRSChain, (GPIO_PinState)pwr_on);
    return 0;
  }
  return 1;
}

/**
  * @brief  
  * @param  
  * @retval 
  */

void InitRSSensorsChain(RSx_SensorsChain* pRSChain, uint8_t id, UART_HandleTypeDef* huart, GPIO_TypeDef* port, uint16_t pin, uint8_t enable, uint8_t error_cnt, uint8_t start_delay, void (* power_cb)(pRSx_SensorsChain pChain))
{
  pRSChain->InterfaceID         = id;
  pRSChain->InterfaceEnabled    = enable;
  pRSChain->pHuart              = huart;
  pRSChain->pSensorsChain       = NULL;
  pRSChain->Connected           = GPIO_PIN_RESET;
  pRSChain->Powered             = GPIO_PIN_RESET;
  pRSChain->PowerPort           = port;
  pRSChain->PowerPin            = pin;
  pRSChain->PowerCallback       = power_cb;
  pRSChain->LastPollTime        = 0;
  pRSChain->FirstReqDelay       = start_delay;
  pRSChain->ErrorCnt            = error_cnt;
  pRSChain->DeInit              = HAL_UART_DeInit;//HAL_UART_MspDeInit;
  switch (id)
  {
    case RS1: pRSChain->Init = MX_USART3_UART_Init; break;
    case RS2: pRSChain->Init = MX_USART2_UART_Init; break;
    case RS3: pRSChain->Init = MX_UART4_Init; break;
    default:  pRSChain->Init = NULL;
  }
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t RSSensorPause(RSx_SensorsChain *pRS, uint32_t address, uint32_t type, uint32_t action)
{
  pSensorElem pSensor = pRS->pSensorsChain;
  
  while ( pSensor ) 
  {
    if ( (pSensor->DevAddr == address) && (pSensor->SensorType == type) )
    {
      pSensor->SensorEnabled = action;
      if ( action ) pSensor->NotACKcount = 0;
      return 0;
    }
    pSensor = pSensor->pNext;    
  }  
  return 1;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t SensorsChainProcess(RSx_SensorsChain *pRS)
{
  pSensorElem pSensor;
  
  if ( (pRS->InterfaceEnabled == 0) || (pRS->Powered == 0)) return 1;
  
  pSensor = pRS->pSensorsChain;
  
  while ( pSensor )
  {
    uint32_t ticks = HAL_GetTick();
    
    if ( pSensor->SensorEnabled && (check_timer(pSensor->PollTimer) == 0) && (ticks > (pRS->LastPollTime+100)) ) // здесь добавлена задержка опроса следующего датчика после предыдущего, если делать сразу - будут пропуски
    {
      uint8_t buff[MAX_SENSOR_DATASIZE];
      uint32_t size;
      
      init_timer(pSensor->PollTimer, pSensor->PollPeriod);     
      
      volatile uint8_t temp = pRS->pHuart->Instance->DR;
      
      MakeTimeStamp(buff);
      if ( pSensor->GetData(pRS->pHuart, pSensor, &buff[6], &size) )
      { 
        if ( ++pSensor->NotACKcount == pRS->ErrorCnt ) pSensor->SensorEnabled = 0;
      }
      else pSensor->NotACKcount = 0;
      
      pSensor->SendData(pRS->pHuart, pSensor, buff, size);
      pRS->LastPollTime = HAL_GetTick();

      /* выходим из опроса после первого прочитанного датчика, чтобы не блокировать цикл и необходимой паузы между опросами */
      return 0;
    }
    
    pSensor = pSensor->pNext;    
  }

  return 1;
}

