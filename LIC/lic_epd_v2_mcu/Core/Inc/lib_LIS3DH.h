#ifndef LIB_LIS3DH_H
#define LIB_LIS3DH_H

#include "main.h"


uint8_t I2C_Accel_ReadData_WhoAmI();
uint8_t I2C_Accel_ReadData_STATUS_REG();
uint8_t I2C_Accel_INT1_SRC();

float I2C_Accel_ReadData_Axis_G(char axis);

void Init_ACC();
void Full_Scale_Selection(uint8_t FSS);

void Init_ACC_INT1();





#endif /*STM32F207VC_LIB_ACCEL_H*/
