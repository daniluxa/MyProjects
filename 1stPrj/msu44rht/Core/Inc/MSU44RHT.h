#ifndef MSU44RHT_H_
#define MSU44RHT_H_

#include "stdint.h"
#include "stm32f2xx_hal.h"
#include "main.h"

extern UART_HandleTypeDef huart1;

#define _MSU                huart1  
#define RS_transmit_mode()  HAL_GPIO_WritePin(RS1_VCC_EN_GPIO_Port, RS1_VCC_EN_Pin, GPIO_PIN_SET)
#define RS_receive_mode()   HAL_GPIO_WritePin(RS1_VCC_EN_GPIO_Port, RS1_VCC_EN_Pin, GPIO_PIN_RESET)

void LED_set_color(uint8_t color);
void Read_Reg(uint8_t Func_Code, uint8_t Register_Hi, uint8_t Register_Lo, uint8_t amount_reg, uint8_t* dataRead, uint8_t data_size);
void Change_Slave_Address(uint8_t new_address);
void Write_Reg(uint8_t Func_Code, uint8_t Register_Hi, uint8_t Register_Lo, uint8_t value);
//void Reboot();
uint8_t Read_Temp();
uint8_t Read_Humidity();
uint16_t crc16(uint8_t* data, uint16_t num);

#endif /* MSU44RHT_H_ */