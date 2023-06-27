#ifndef BQ25887_H_
#define BQ25887_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "main.h"
extern I2C_HandleTypeDef hi2c1;

#define _BQ_I2C         hi2c1
#define  BQ25887_Cancel_Charge(value)         HAL_GPIO_WritePin(CH_CD_GPIO_Port, CH_CD_Pin, (GPIO_PinState)value)

HAL_StatusTypeDef BQ25887_Reg_Write( uint16_t Register, uint8_t* dataWrite);
HAL_StatusTypeDef BQ25887_Reg_Read( uint16_t Register, uint8_t* dataRead, uint8_t len);
void BQ25887_Charge_Status();
void BQ25887_Charge_Current_Limit( int value);
void BQ25887_Input_Voltage_Limit( int voltage);
void BQ25887_Input_Current_Limit( int current);
void Vbus_Stat();
void BQ25887_ADC_ON();
void BQ25887_ADC_OFF();
uint16_t BQ25887_Get_Vbat();
uint16_t BQ25887_Get_VBUS_Current();
uint16_t BQ25887_Get_Charge_Current();
uint16_t BQ25887_Get_Vcell_top();
uint16_t BQ25887_Get_Temp();
uint16_t BQ25887_Get_Vcell_bot();

#endif /* BQ25887_H_ */