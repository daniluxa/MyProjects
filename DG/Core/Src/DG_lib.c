#include "main.h"
#include "DG_lib.h"
#include <stdio.h>
#include <string.h>

/*------------------------------DEFINES---------------------------------------*/

#define DG_ADDRESS              0x7B
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

//#define POWER_VOLTAGE           0x00
//#define TEMP_FOR_FORMULA        0x13
//#define HUMIDITY_FOR_FORMULA    0x14
//#define TEMP_WHOLE_PART         0x1E
//#define TEMP_10_PART            0x1F
//#define HUMIDITY_WHOLE_PART     0x20
//#define HUMIDITY_10_PART        0x21

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
    uint8_t state = HAL_UART_GetState(&huart1);
    uint16_t crc_calc = 0;
    uint8_t msg_cmd[8] = {DG_ADDRESS, Func_Code, Register_Hi, Register_Lo, 0x00, amount_reg, 0x00, 0x00};
    crc_calc = crc16(msg_cmd, (sizeof(msg_cmd) - 2));
    memcpy(&msg_cmd[(sizeof(msg_cmd) - 2)], &crc_calc, sizeof(crc_calc));
    RS_transmit_mode();
    HAL_UART_Transmit(&_DG, msg_cmd, sizeof(msg_cmd),TIMEOUT);
    RS_receive_mode();
    HAL_StatusTypeDef a = HAL_UART_Receive(&_DG, dataRead, data_size, TIMEOUT);
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
    uint8_t msg_cmd[8] = {DG_ADDRESS, Func_Code, Register_Hi, Register_Lo, 0x00, value, 0x00, 0x00};
    crc_calc = crc16(msg_cmd, (sizeof(msg_cmd) - 2));
    memcpy(&msg_cmd[(sizeof(msg_cmd) - 2)], &crc_calc, sizeof(crc_calc));
    RS_transmit_mode();
    HAL_UART_Transmit(&_DG, msg_cmd, sizeof(msg_cmd), TIMEOUT);
}

/*------------------------WRITE DATA FROM DG FUNCTION--------------------------*/

void Read_Data_DG(){
    uint8_t k = 0;
    uint8_t msg_rec[200];
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
    Read_Reg(0x03, 0x00, 0x00, 0x6D, msg_rec, 200);
    //(msg_rec[0] == 123 && && msg_rec[1] == 3) ? k = 0 : k = 1;
    if (msg_rec[0] == 123 && msg_rec[1] == 3) k = 0;
    else k = 1;
    Anum = msg_rec[7 + k] + msg_rec[8 + k] * 256 + msg_rec[9 + k] * 256 * 256;
    PAC_num = msg_rec[11 + k] + msg_rec[12 + k] * 256;
    for(int i = 0; i < 4; i++){
      Unit_num[i] = msg_rec[19 + i + k];
    }
    for(int i = 0; i < 8; i++){
      SOFTdata[i] = msg_rec[27 + i + k];
    }
    PROBAtimer = msg_rec[44 + k];
    Mflag = msg_rec[51 + k];
    T0 = (msg_rec[71 + k] + msg_rec[72 + k] * 256 + msg_rec[73 + k] * 256 * 256 ) / 100;
    T1 = (msg_rec[87 + k] + msg_rec[88 + k] * 256 + msg_rec[89 + k] * 256 * 256 ) / 100;
    T2 = (msg_rec[103 + k] + msg_rec[104 + k] * 256 + msg_rec[105 + k] * 256 * 256 ) / 100;
    T3 = (msg_rec[119 + k] + msg_rec[120 + k] * 256 + msg_rec[121 + k] * 256 * 256 ) / 100;
    P0 = (msg_rec[167 + k] + msg_rec[168 + k] * 256 + msg_rec[169 + k] * 256 * 256 ) / 100;
    P1 = (msg_rec[175 + k] + msg_rec[176 + k] * 256 + msg_rec[177 + k] * 256 * 256 ) / 100;
    P2 = (msg_rec[183 + k] + msg_rec[184 + k] * 256 + msg_rec[185 + k] * 256 * 256 ) / 100;
    P3 = (msg_rec[191 + k] + msg_rec[192 + k] * 256 + msg_rec[193 + k] * 256 * 256 ) / 100;
    Valves = msg_rec[43 + k] - 0x60;
    Dpower = 0x0f - msg_rec[46 + k];
    printf("Anum: %d;\nPAC_num: %d;\nUnit_num: %c%c%c%c;\nSOFTdate: %c%c.%c%c.%c%c%c%c;\nPROBAtimer: %d;\nMflag: %x;\nT0: %d;\nT1: %d;\nT2: %d;\nT3: %d;\nP0: %d;\nP1: %d;\nP2: %d;\nP3: %d;\nValves: %x;\nDpower: %x;\n", Anum, PAC_num, Unit_num[0], Unit_num[1], Unit_num[2],Unit_num[3], SOFTdata[0], SOFTdata[1], SOFTdata[2], SOFTdata[3], SOFTdata[4], SOFTdata[5], SOFTdata[6], SOFTdata[7], PROBAtimer, Mflag, T0, T1, T2, T3, P0, P1, P2, P3, Valves, Dpower);
    printf("\n");
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