#ifndef __SENSORS_H
#define __SENSORS_H

#include "main.h"
#include <stdbool.h>

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

#define ISA_LIC_Filling(ans_cmd, k, fb)       ((uint32_t)ans_cmd[1  + k + fb] << 16 | (uint32_t)ans_cmd[0  + k + fb] << 24 | (uint32_t)ans_cmd[3  + k + fb] | (uint32_t)ans_cmd[2  + k + fb] << 8)

void power_manage_ISA_LIC(bool state);

/*typedef struct 
{
  uint32_t            BaudRate;
  uint8 _t            StopBits;
  uint8_t             Parity;
  void               *pData;
}UART_config;
*/

#define RS1     0
#define RS2     1
#define RS3     2

#define MAX_SENSOR_ID   19
typedef enum
{
  NO_SENS                = 0,
  MSU44RHTL              = 1,
  OXYGEN_SENS            = 2,
  SEROV                  = 3,
  ISA_LIC_v2             = 4,
  EKSIK_TEMP             = 5,
  EKSIK_HUM              = 6,
  EKSIK_PRES             = 7,
  EKSIK_CH4              = 8,
  EKSIK_O2               = 9,
  EKSIK_CO2              = 10,
  EKSIK_NH3              = 11,
  EKSIK_H2S              = 12,
  EKSIK_CO               = 13,
  EKSIK_NO2              = 14,
  EKSIK_SO2              = 15,
  EKSIK_LIGHT            = 16,
  EKSIK_DUST_PM25        = 17,
  EKSIK_DUST_PM10        = 18,
  AQARA                  = MAX_SENSOR_ID,
  
  GPS_SENS               = 100,
  RSxSTATUS              = 101,
  
  CTRL_OUT               = 0xFFFC,
  SUBSCRIBE              = 0xFFFD,
  MSG                    = 0xFFFE,
  STATUS                 = 0xFFFF
} Sensor_type;

typedef struct{
  uint16_t Self_Diagnostic;
  float Long_Comp_Speed_Wind;
  float Trans_Comp_Speed_Wind;
  float ABS_Speed_Wind;
  float Direct_Wind;
  float Temp_Air;
  float Air_pressure_mm_hg;
  float Air_pressure_gPa;
  float Humidity;
  float Light;
  float Angle_Inclination_Zenith;
  float Angle_Inclination_Azimuth;
  float Direct_to_North;
  float Latitude;
  float Longitude;
  float Altitude; 
}Isa_LIC;

typedef struct{
  uint32_t Anum;
  uint32_t PAC_num;
  uint32_t Unit_num[4];
  uint32_t SOFTdata[10];
  uint32_t PROBAtimer;
  uint32_t Mflag;
  uint32_t T0;
  uint32_t T1;
  uint32_t T2;
  uint32_t T3;
  uint32_t P0;
  uint32_t P1;
  uint32_t P2;
  uint32_t P3;
  uint32_t Valves;
  uint32_t Dpower;
}DG_struct;


typedef struct SensorElem
{
  uint8_t      SensorEnabled;
  uint8_t      NotACKcount;
  uint8_t      DevAddr;
  uint16_t     SensorType;
  char*        SensorName;
  uint32_t     PollPeriod;
  uint32_t     PollTimer;
  uint32_t  (* GetData)(UART_HandleTypeDef* pHuart, struct SensorElem* pSensor, uint8_t* pBuff, uint32_t* pDataSize);
  uint32_t  (* SendData)(UART_HandleTypeDef* pHuart, struct SensorElem* pSensor, uint8_t *pBuff, uint32_t DataSize);
  struct       SensorElem* pNext;
}SensorElem, *pSensorElem;

typedef struct RSx_SensorsChain
{      
  uint8_t              InterfaceID;
  uint8_t              InterfaceEnabled;
  GPIO_PinState        Connected;
  GPIO_PinState        Powered;
  GPIO_TypeDef*        PowerPort;
  uint16_t             PowerPin;  
  uint32_t             LastPollTime;
  uint8_t              FirstReqDelay;
  uint8_t              ErrorCnt;
  void              (* PowerCallback)(struct RSx_SensorsChain* pChain);
  void              (* Init)(void);
  HAL_StatusTypeDef (* DeInit)(UART_HandleTypeDef *huart);
  UART_HandleTypeDef*  pHuart; 
  pSensorElem          pSensorsChain;
} RSx_SensorsChain, *pRSx_SensorsChain;


extern RSx_SensorsChain RS1_SensorsChain, RS2_SensorsChain, RS3_SensorsChain;

void        InitRSSensorsChain(RSx_SensorsChain* pRSChain, uint8_t id, UART_HandleTypeDef* huart, GPIO_TypeDef* port, uint16_t pin, uint8_t enable, uint8_t error_cnt, uint8_t start_delay, void (* power_cb)(pRSx_SensorsChain));
void        RSSensorsChainPwrControl(RSx_SensorsChain *pRSChain, GPIO_PinState connected);
uint32_t    RSSensorsChainPwrSwitch(pRSx_SensorsChain pRSChain, uint32_t pwr_on);
uint32_t    RSSensorPause(RSx_SensorsChain *pRS, uint32_t address, uint32_t type, uint32_t action);
pSensorElem AddSensor(uint16_t sensor_type, uint8_t dev_addr, char *sens_name, uint32_t poll_period, 
                  uint32_t (* get_data_cb)(UART_HandleTypeDef*, pSensorElem, uint8_t*, uint32_t*),
                  uint32_t (* send_data_cb)(UART_HandleTypeDef*, pSensorElem, uint8_t*, uint32_t));
uint32_t    AddSensor2Chain(RSx_SensorsChain* pRS, pSensorElem pNewSensor);
uint32_t    DelSensorFromChain(pRSx_SensorsChain pRS, uint16_t sensor_type, uint8_t dev_addr);
uint32_t    SensorsChainProcess(RSx_SensorsChain* pRS);

uint32_t RS_SensorRead(UART_HandleTypeDef* huart, pSensorElem pSensor, uint8_t* buf, uint32_t* size);
uint8_t rs_read_MSU44RHTL(UART_HandleTypeDef* huart, uint8_t* buf, uint8_t dev_addr);
uint8_t rs_read_WIND(UART_HandleTypeDef* huart, uint8_t* buf);
uint8_t rs_read_OXYGEN(UART_HandleTypeDef* huart, uint8_t* buf, uint8_t dev_addr);
//uint8_t rs_read_ISA_LIC(UART_HandleTypeDef* huart, uint8_t* buf, uint8_t dev_addr);
//uint8_t rs_write_settings_ISA_LIC(UART_HandleTypeDef* huart, uint8_t dev_addr, Isa_Settings isa_set);
uint8_t MSU44RHTL_form_array(uint8_t* data, char* dataRead);
uint8_t SEROV_form_array(uint8_t *data, char *dataRead);
uint8_t OXYGEN_form_array(uint8_t *data, char *dataRead);
//uint8_t rs_read_EKSIK(UART_HandleTypeDef* huart, uint8_t* buf, uint8_t Sensor_type);
uint32_t rs_read_ISA_LIC(UART_HandleTypeDef* huart, pSensorElem pSensor, uint8_t* buf, uint32_t* size);
uint32_t rs_read_EKSIK(UART_HandleTypeDef* huart, pSensorElem pSensor, uint8_t* buf, uint32_t* size);


#endif //__SENSORS_H