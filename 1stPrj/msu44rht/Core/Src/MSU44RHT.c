#include "main.h"
#include "MSU44RHT.h"
#include <stdio.h>
#include <string.h>

/*------------------------------DEFINES---------------------------------------*/

#define MSU44RHT_ADDRESS        0x13    //0x01
#define TIMEOUT                 1000

/*--------------FUNC CODES--------------*/

#define READ_COILS              0x01
#define READ_DI                 0x02
#define READ_HR                 0x03
#define READ_IR                 0x04
#define WRITE_SINGLE_COIL       0x05
#define WRITE_SINGLE_HR         0x06
#define WRITE_MULTIPLE_COIL     0x15
#define WRITE_MULTIPLE_HR       0x16

/*--------------REG CODES--------------*/

#define POWER_VOLTAGE           0x00
#define TEMP_FOR_FORMULA        0x13
#define HUMIDITY_FOR_FORMULA    0x14
#define TEMP_WHOLE_PART         0x1E
#define TEMP_10_PART            0x1F
#define HUMIDITY_WHOLE_PART     0x20
#define HUMIDITY_10_PART        0x21

/*-----------------------------SET COLOR FUNCTION-----------------------------*/

/**
  * @brief set color 
  * @param color
  * @retval -
  */

void LED_set_color(uint8_t color)
{
    ((color >> 2) & 1) == 0 ? HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
    ((color >> 1) & 1) == 0 ? HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    ((color >> 0) & 1) == 0 ? HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET);  
}

/*-----------------------------READ REG FUNCTION------------------------------*/

/**
  * @brief reads data from the reg
  * @param function code
  * @param high register 
  * @param low register 
  * @param amount of registers
  * @param where to count
  * @param size of data
  * @retval -
  */

void Read_Reg(uint8_t Func_Code, uint8_t Register_Hi, uint8_t Register_Lo, uint8_t amount_reg, uint8_t* dataRead, uint8_t data_size)
{
    uint16_t crc_calc = 0;
    uint8_t msg_cmd[8] = {MSU44RHT_ADDRESS, Func_Code, Register_Hi, Register_Lo, 0x00, amount_reg, 0x00, 0x00};
    crc_calc = crc16(msg_cmd, (sizeof(msg_cmd) - 2));
    memcpy(&msg_cmd[(sizeof(msg_cmd) - 2)], &crc_calc, sizeof(crc_calc));
    RS_transmit_mode();
    HAL_UART_Transmit(&_MSU, msg_cmd, sizeof(msg_cmd), TIMEOUT);
    RS_receive_mode();
    HAL_UART_Receive(&_MSU, dataRead, data_size, TIMEOUT);
}
 
/*----------------------------WRITE REG FUNCTION------------------------------*/

/**
  * @brief write data to the reg
  * @param function code
  * @param high register 
  * @param low register 
  * @param data you want to write
  * @retval -
  */

void Write_Reg(uint8_t Func_Code, uint8_t Register_Hi, uint8_t Register_Lo, uint8_t value)
{
    uint16_t crc_calc = 0;
    uint8_t msg_cmd[8] = {MSU44RHT_ADDRESS, Func_Code, Register_Hi, Register_Lo, 0x00, value, 0x00, 0x00};
    crc_calc = crc16(msg_cmd, (sizeof(msg_cmd) - 2));
    memcpy(&msg_cmd[(sizeof(msg_cmd) - 2)], &crc_calc, sizeof(crc_calc));
    RS_transmit_mode();
    HAL_UART_Transmit(&_MSU, msg_cmd, sizeof(msg_cmd), TIMEOUT);
}

/*-----------------------------REBOOT FUNCTIONS-------------------------------*/
/*
void Reboot()
{
    Write_Reg(WRITE_SINGLE_HR, 0x16, 0x2E, 0x01);
}
*/
/*--------------------READ TEMP AND HUMIDITY FUNCTIONS------------------------*/

/**
  * @brief reads data from temperature and humidity registers 
  * @param where do you want to data read 
  * @param amount of this data
  * @retval -
  */

void Read_Temp_and_Hum(uint8_t* dataRead, uint8_t data_size)
{
    Read_Reg(READ_IR, 0x00, TEMP_WHOLE_PART, 4, dataRead, data_size);
}

/**
  * @brief temperature calculation
  * @param -
  * @param -
  * @retval temperature
  */

uint8_t Read_Temp()
{
    uint8_t dataRead[13];
    Read_Temp_and_Hum(dataRead, sizeof(dataRead));
    float a = dataRead[6];
    float result = dataRead[4] + a / 10;
    printf("Temperature = %.1f\n", result);
    return (result);
}

/**
  * @brief humidity calculation
  * @param -
  * @param -
  * @retval humidity
  */

uint8_t Read_Humidity()  
{
    uint8_t dataRead[13];
    Read_Temp_and_Hum(dataRead, sizeof(dataRead));
    float a = dataRead[10];
    float result = dataRead[8] + a / 10;
    printf("Humidity = %.1f\n", result);
    return (result);
}
   
/*-----------------------CHANGE SLAVE ADDRESS FUNCTION------------------------*/

/**
  * @brief change slave address
  * @param new address
  * @retval -
  */

void Change_Slave_Address(uint8_t new_address)
{
    Write_Reg(WRITE_SINGLE_HR, 0x00, 0x00, new_address);
}

/*------------------------------CRC SUM FUNCTION------------------------------*/

/**
  * @brief checksum calculation
  * @param data to count
  * @param amount of data
  * @retval -
  */

uint16_t crc16(uint8_t* data, uint16_t num)
{
  uint16_t crc = 0xFFFF;
  uint16_t polynom = 0xA001;
  uint16_t i = 0;
  uint16_t j = 0;
  
  for(i = 0; i < num; i++)
  {
    crc = crc ^ data[i];

    for(j = 0; j < 8; j++)
    {
      if(crc & 0x0001)
      {
        crc = crc >> 1;
        crc = crc ^ polynom;
      }
      else
      {
        crc = crc >> 1;
      }
    }
  }
  return(crc);
}