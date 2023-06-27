#include "lib_LIS3DH.h"
#include "stm32f4xx_hal_i2c.h"
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "main.h"


#define TIMEOUT                         10
#define ADDRESS_ACCEL                   0x18
#define ADDRESS_WHOAMI                  0x0F
#define ADDRESS_OUT_X                   0x28  
#define ADDRESS_OUT_Y                   0x2A        
#define ADDRESS_OUT_Z                   0x2C
#define CTRL_REG1                       0x20
#define CTRL_REG2                       0x21
#define CTRL_REG3                       0x22
#define CTRL_REG4                       0x23
#define CTRL_REG5                       0x24
#define CTRL_REG6                       0x25
#define STATUS_REG                      0x07

extern  I2C_HandleTypeDef hi2c1;

uint8_t I2C_Accel_Sensitivity();

/**
  * @brief  Write an registers value in blocking mode to the CTRL_REG1-6 memory address to power the start
  * @param  -
  * @retval -
  */
void Init_ACC()
{
    HAL_Delay(100);
    uint8_t regData[6] = {0x47, 0, 0, 0, 0, 0};
    for(int i = 0; i < 6; i++)
    { 
      HAL_I2C_Mem_Write(&hi2c1, (ADDRESS_ACCEL << 1), 0x20 + i, 1, (uint8_t*)regData[i], 1, TIMEOUT); 
    }     
}

/**
  * @brief  Write the range value to the CTRL_REG4 memory address in blocking mode
  * @param  Value of range 
  *         2->+-2g, 4->+-4g, 8->+-8g, 16->+-16g
  * @retval -
  */
void Full_Scale_Selection(uint8_t FSS)
{
  uint8_t regData = 0x00;
  
  switch(FSS)
  {     
    // case 2 : default value 0x00
    case 4 : 
      regData = 0x10;
      break;      
    case 8 :
      regData = 0x20;
      break;    
    case 16 : 
      regData = 0x30;
      break;      
  }
  HAL_I2C_Mem_Write(&hi2c1, (ADDRESS_ACCEL << 1), CTRL_REG4, 1, &regData,  1, TIMEOUT);

}


/**
  * @brief  Read the value from the STATUS_REG in blocking mode
  * @param  -
  * @retval Data from STATUS_REG
  */
uint8_t I2C_Accel_ReadData_STATUS_REG()
{ 
  uint8_t regDataST = 0;
  HAL_I2C_Mem_Read(&hi2c1, (ADDRESS_ACCEL << 1), STATUS_REG, 1, &regDataST,  1, TIMEOUT);
 
 return regDataST;
}


/**
  * @brief  Read the value from the WhoAmI in blocking mode
  * @param  -
  * @retval Data from WhoAmI
  */
uint8_t I2C_Accel_ReadData_WhoAmI()
{ 
  uint8_t regData = 0;
  HAL_I2C_Mem_Read(&hi2c1, (ADDRESS_ACCEL << 1), ADDRESS_WHOAMI, 1, &regData,  1, TIMEOUT);
 
 return regData;
}

/**
  * @brief  Read the value from register INT1_SRC in blocking mode
  * @param  -
  * @retval Data from INT1_SRC
  */
uint8_t I2C_Accel_INT1_SRC()
{ 
  uint8_t regData = 0;
  HAL_I2C_Mem_Read(&hi2c1, (ADDRESS_ACCEL << 1), 0x31, 1, &regData,  1, TIMEOUT);
 
 return regData;
}


/**
  * @brief  Read an amount of data from the X or Y or Z axis in G in blocking mode
  * @param  char axis ('X' or 'Y' or 'Z')
  * @retval Data of choosen axis in G
  */
float I2C_Accel_ReadData_Axis_G(char axis)
{ 
  float data = 0;
  uint8_t ADDRESS_OUT = 0x28;   // for x axis
  uint8_t regData_L = 0;
  uint8_t regData_H = 0;
  switch(axis)
  {
    //case 'X' : default value 0x28
    case 'Y' : 
       ADDRESS_OUT = 0x2A;
       break;
        
    case 'Z' : 
      ADDRESS_OUT = 0x2C;
      break;
  }
  HAL_I2C_Mem_Read(&hi2c1, (ADDRESS_ACCEL << 1), ADDRESS_OUT, 1, &regData_L,  1, TIMEOUT);
  HAL_I2C_Mem_Read(&hi2c1, (ADDRESS_ACCEL << 1), ADDRESS_OUT+1, 1, &regData_H,  1, TIMEOUT);
  int16_t temp = (regData_H << 8) + regData_L;
  data = I2C_Accel_Sensitivity() * ((float)temp/64000); //convert the value to 10 bits and g's
         
 return data;
}




/**
  * @brief  Read range value from CTRL_REG4 in blocking mode
  * @param  -
  * @retval range value
  */
uint8_t I2C_Accel_Sensitivity()
{ 
  uint8_t tmp, FS; 
  uint8_t sens = 4;
 
  HAL_I2C_Mem_Read(&hi2c1, (ADDRESS_ACCEL << 1), CTRL_REG4, 1, &tmp,  1, TIMEOUT);
  FS = (tmp >> 4) & 3;  
  switch(FS){
    // case 0: default value sens = 4
    case 1:  sens = 8; //range +-4
             break;
    case 2:  sens = 16; //range +-8
             break;
    case 3: sens = 48; //range -+16
             break;
   }
 return sens;
}



void Init_ACC_INT1()
{
    uint8_t regData_R1[1] = {0x57}; 
    uint8_t regData_R2[1] = {0x00}; 
    uint8_t regData_R3[1] = {0x40}; 
    uint8_t regData_R5[1] = {0x08}; 
    uint8_t regData_R6[1] = {0x00};
    uint8_t regData_INT1_THS[1] = {0x25}; 
    uint8_t regData_INT1_DURATION[1] = {0x00}; // 0s
    uint8_t regData_INT1_CFG[1] = {0x2A}; // enabled interrupt request X, Y, Z Up 
    
    HAL_I2C_Mem_Write(&hi2c1, (ADDRESS_ACCEL << 1), 0x20, 1, regData_R1,  1, TIMEOUT);
    HAL_I2C_Mem_Write(&hi2c1, (ADDRESS_ACCEL << 1), 0x21, 1, regData_R2,  1, TIMEOUT);
    HAL_I2C_Mem_Write(&hi2c1, (ADDRESS_ACCEL << 1), 0x22, 1, regData_R3,  1, TIMEOUT);
    HAL_I2C_Mem_Write(&hi2c1, (ADDRESS_ACCEL << 1), 0x24, 1, regData_R5,  1, TIMEOUT);
    HAL_I2C_Mem_Write(&hi2c1, (ADDRESS_ACCEL << 1), 0x25, 1, regData_R6,  1, TIMEOUT);
    HAL_I2C_Mem_Write(&hi2c1, (ADDRESS_ACCEL << 1), 0x32, 1, regData_INT1_THS,  1, TIMEOUT);
    HAL_I2C_Mem_Write(&hi2c1, (ADDRESS_ACCEL << 1), 0x33, 1, regData_INT1_DURATION,  1, TIMEOUT);
    HAL_I2C_Mem_Write(&hi2c1, (ADDRESS_ACCEL << 1), 0x30, 1, regData_INT1_CFG,  1, TIMEOUT);
}


