#ifndef __INIT_H
#define __INIT_H

#include "stm32f4xx_hal.h"
#include "main.h"
#include "W25Qxx.h"
#include "BQ25887.h"
#include "gps.h"
#include "ads1220_lib.h"
#include "eeprom_lib.h"
#include "lib_LIS3DH.h"
#include "lwip.h"
#include "usb_device.h"
#include "timers.h"
#include "some_stuff.h"

extern CAN_HandleTypeDef hcan1;

extern CRC_HandleTypeDef hcrc;

extern I2C_HandleTypeDef hi2c1;

extern RTC_HandleTypeDef hrtc;

extern SD_HandleTypeDef hsd;

extern SPI_HandleTypeDef hspi1;

extern IWDG_HandleTypeDef hiwdg;

extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim12;

extern UART_HandleTypeDef huart4;
extern SMARTCARD_HandleTypeDef hsc1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

void MX_UART4_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);


void Device_Init(void);



#endif // __INIT_H