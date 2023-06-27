#include "stm32f2xx_hal.h"
#include "stm32f2xx_it.h"
#include "stm32f2xx_hal_i2c.h"
#include <stdbool.h>
#include "string.h"
#include "stdio.h"
#include "main.h"
#include "BQ25887.h"

/*-------------------------------DEFINES--------------------------------------*/
#define     BQ25887_ADDRESS                             0x6A

/*-----------------------only read--------------------------*/
#define     Reg_ICO_Current_Limit                       0x0A
#define     Reg_Charger_Status_1                        0x0B 
#define     Reg_Charger_Status_2                        0x0C     
#define     Reg_NTC_Status                              0x0D
#define     Reg_FAULT_Status                            0x0E
#define     Reg_Charger_Flag_1                          0x0F
#define     Reg_Charger_Flag_2                          0x10
#define     Reg_Fault_Flag                              0x11
#define     Reg_IBUS_ADC1                               0x17
#define     Reg_IBUS_ADC0                               0x18
#define     Reg_ICHG_ADC1                               0x19
#define     Reg_ICHG_ADC0                               0x1A
#define     Reg_VBUS_ADC1                               0x1B
#define     Reg_VBUS_ADC0                               0x1C
#define     Reg_VBAT_ADC1                               0x1D
#define     Reg_VBAT_ADC0                               0x1E
#define     Reg_VCELLTOP_ADC1                           0x1F
#define     Reg_VCELLTOP_ADC0                           0x20
#define     Reg_TS_ADC1                                 0x21
#define     Reg_TS_ADC0                                 0x22
#define     Reg_TDIE_ADC1                               0x23
#define     Reg_TDIE_ADC0                               0x24
#define     Reg_VCELLBOT_ADC1                           0x26
#define     Reg_VCELLBOT_ADC0                           0x27
#define     Reg_Cell_Balancing_Flag                     0x2B

/*-------------------write and read--------------------------*/
#define     Reg_Cell_Voltage_Limit                      0x00
#define     Reg_Charge_Current_Limit                    0x01
#define     Reg_Input_Voltage_Limit                     0x02
#define     Reg_Input_Current_Limit                     0x03
#define     Reg_Precharge_and_Termination_Control       0x04
#define     Reg_Charger_Control_1                       0x05
#define     Reg_Charger_Control_2                       0x06
#define     Reg_Charger_Control_3                       0x07
#define     Reg_Charger_Control_4                       0x08
#define     Reg_Reserved                                0x09
#define     Reg_Charger_Mask_1                          0x12
#define     Reg_Charger_Mask_2                          0x13
#define     Reg_Fault_Mask                              0x14
#define     Reg_ADC_Control                             0x15
#define     Reg_ADC_Function_Disable                    0x16
#define     Reg_Part_Information                        0x25
#define     Reg_Cell_Balancing_Control_1                0x28
#define     Reg_Cell_Balancing_Control_2                0x29
#define     Reg_Cell_Balancing_Status_and_Control       0x2A
#define     Reg_Cell_Balancing_Mask                     0x2C


/*-------------------------------FUNCTIONS-------------------------------------*/


/*-----------------------Read FUNCTION---------------------------*/

 /**
  * @brief  reads data from the reg
  * @param reg from read
  * @param data you want to read
  * @retval -
  */

HAL_StatusTypeDef BQ25887_Reg_Read(uint16_t Register, uint8_t* dataRead, uint8_t len)
{
   return HAL_I2C_Mem_Read(&_BQ_I2C, BQ25887_ADDRESS << 1, Register, 1, dataRead, len, 1000);
}

/*-----------------------Write FUNCTION--------------------------*/

 /**
  * @brief  writes data to the reg
  * @param reg ro write 
  * @param data you want to write
  * @retval -
  */

HAL_StatusTypeDef BQ25887_Reg_Write(uint16_t Register, uint8_t* dataWrite)
{
    return HAL_I2C_Mem_Write(&_BQ_I2C, BQ25887_ADDRESS << 1, Register, 1, dataWrite, 1, 1000);
}

/*-------------------Charge Status FUNCTION----------------------*/

 /**
  * @brief find out the status of the charge 
  * @param -
  * @retval -
  */

void BQ25887_Charge_Status()
{
    uint8_t dataRead;
    BQ25887_Reg_Read( Reg_Charger_Status_1, &dataRead, 1);
    if ((dataRead >> 4) & 0x1 == 1)  printf("Default mode;  ");
    else                             printf("Host mode;  ");
    switch(dataRead & 0x07)
    {
      case 0x1: printf("Trickle Charge\n");
                  break;    
      case 0x2: printf("Pre-charge\n");
                  break;
      case 0x3: printf("Fast-charge\n");
                  break;           
      case 0x4: printf("Taper Charge\n");
                  break;           
      case 0x5: printf("Top-off Timer Charging\n");
                  break;           
      case 0x6: printf("Charge Termination Done\n");
                  break;
      case 0x7: printf("Reserved\n");
                  break; 
      default:    printf("Not Charging\n");
                  break;
    }
}

/*----------------Charge Current Limit FUNCTION------------------*/

 /**
  * @brief sets a current charge limit
  * @param value
  * @retval -
  */

void BQ25887_Charge_Current_Limit(int current)
{
    if (current >= 2200) current = 2200;
    if (current <= 100)  current = 100;
    uint8_t val = (uint8_t)(current  / 50);
    
    BQ25887_Reg_Write( 0x01, &val);
}

/*-----------------Input Voltage Limit FUNCTION------------------*/

 /**
  * @brief sets a input voltage limit
  * @param value
  * @retval -
  */

void BQ25887_Input_Voltage_Limit(int voltage)
{
    if (voltage >= 5500) voltage = 5500;
    if (voltage <= 3900)  voltage = 3900;
    uint8_t val = (uint8_t)((voltage - 3900) / 100);
    
    BQ25887_Reg_Write( 0x02, &val);
}

/*-----------------Input Current Limit FUNCTION------------------*/

 /**
  * @brief sets a input current limit
  * @param value
  * @retval -
  */

void BQ25887_Input_Current_Limit(int current)
{
    if (current >= 3300) current = 3300;
    if (current <= 500) current = 500;
    uint8_t val = (uint8_t)((current - 500) / 100);
    
    BQ25887_Reg_Write( 0x03, &val);
}

/*-----------------------SET COLOR FUNCTION-----------------------*/
 
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

/*--------------------VBUS STATUS FUNCTION-----------------------*/

/**
  * @brief  find out the Vbus Status
  * @param -
  * @retval -
  */

void Vbus_Stat()
{
    uint8_t dataRead;
    BQ25887_Reg_Read( Reg_Charger_Status_2, &dataRead, 1);
    LED_set_color((dataRead >> 4) & 0x07);
}


/*--------------------Get Charge FUNCTIONS--------------------*/

/**
  * @brief  value of called function
  * @param  register address
  * @retval value of called function
  */

uint16_t BQ25887_Get_Charge(uint8_t start_address)
{
  BQ25887_ADC_ON();
  HAL_Delay(100);
  uint16_t retval;
  uint8_t adc_read;
  BQ25887_Reg_Read(Reg_ADC_Control, &adc_read, 1);
  if (((adc_read >> 7) & 0x1) == 0)
  {
      printf("ADC is off\n");
  }
  else 
  {
      //printf("ADC is on\n");
      uint8_t dataRead[2];
      BQ25887_Reg_Read( start_address, dataRead, 2);
      retval = (uint16_t)dataRead[0] << 8 | (uint16_t)dataRead[1];
      //BQ25887_ADC_OFF();
      //printf("ADC is off\n");
      
   }
  return retval;
}

/**
  * @brief  shows the charge value
  * @param  -
  * @retval charge value
  */

uint16_t BQ25887_Get_Vbat()
{
    uint16_t a = BQ25887_Get_Charge(Reg_VBAT_ADC1);
    printf("Vbat = %d\n", a);
    return a;
}

/**
  * @brief  shows the temp value
  * @param  -
  * @retval temp value
  */

uint16_t BQ25887_Get_Temp()
{
    uint16_t a = BQ25887_Get_Charge(Reg_TDIE_ADC1);
    printf("Temp = %d\n", a >> 1);
    return a;
}

/**
  * @brief  shows the Vbus Current value
  * @param  -
  * @retval Vbus Current value
  */

uint16_t BQ25887_Get_VBUS_Current()
{
    uint16_t a = BQ25887_Get_Charge(Reg_IBUS_ADC1);
    printf("Vbus current = %d\n", a);
    return a;
}

/**
  * @brief  shows the Charge Current value
  * @param  -
  * @retval Charge Current value
  */

uint16_t BQ25887_Get_Charge_Current()
{
    uint16_t a = BQ25887_Get_Charge(Reg_ICHG_ADC1);
    printf("Charge current = %d\n", a);
    return a;
}

/**
  * @brief  shows the Charge of top battery value
  * @param  -
  * @retval Charge of top battery value
  */

uint16_t BQ25887_Get_Vcell_top()
{
    uint16_t a = BQ25887_Get_Charge(Reg_VCELLTOP_ADC1);
    printf("Vcell top = %d\n", a);
    return a;
}

/**
  * @brief  shows the Charge of bottom battery value
  * @param  -
  * @retval Charge of bottom battery value
  */

uint16_t BQ25887_Get_Vcell_bot()
{
    uint16_t a = BQ25887_Get_Charge(Reg_VCELLBOT_ADC1);
    printf("Vcell bot = %d\n", a);
    return a;
}

/**
  * @brief  turns on adc
  * @param  -
  * @retval -
  */

void BQ25887_ADC_ON()
{
  uint8_t dataWrite[1] = {0x80}; //80 or b0
  BQ25887_Reg_Write(Reg_ADC_Control, dataWrite);
}

/**
  * @brief  turns off adc
  * @param  -
  * @retval -
  */

void BQ25887_ADC_OFF()
{
  uint8_t dataWrite[1] = {0x00};
  BQ25887_Reg_Write(Reg_ADC_Control, dataWrite);
}

void BQ25887_RESET()
{
  uint8_t dataWrite0[1]  = {0xA0};
  uint8_t dataWrite1[1]  = {0x5E};
  uint8_t dataWrite2[1]  = {0x84};
  uint8_t dataWrite3[1]  = {0x39};
  uint8_t dataWrite4[1]  = {0x22};
  uint8_t dataWrite5[1]  = {0x9D};
  uint8_t dataWrite6[1]  = {0x7D};
  uint8_t dataWrite7[1]  = {0x00};
  uint8_t dataWrite8[1]  = {0x0D};
  uint8_t dataWrite9[1]  = {0x00};
  uint8_t dataWrite10[1] = {0x0A}; //
  uint8_t dataWrite11[1] = {0x0f}; // 
  uint8_t dataWrite12[1] = {0x0f}; // 
  uint8_t dataWrite13[1] = {0x0f}; //
  uint8_t dataWrite14[1] = {0x0f}; //
  uint8_t dataWrite15[1] = {0x00};
  uint8_t dataWrite16[1] = {0x00};
  uint8_t dataWrite17[1] = {0x00};
  uint8_t dataWrite18[1] = {0x00};
  uint8_t dataWrite19[1] = {0x00};
  uint8_t dataWrite20[1] = {0x00};
  uint8_t dataWrite21[1] = {0x30};
  uint8_t dataWrite22[1] = {0x00};
  uint8_t dataWrite23[1] = {0x00};
  uint8_t dataWrite24[1] = {0x00};
  uint8_t dataWrite25[1] = {0x00};
  uint8_t dataWrite26[1] = {0x00};
  uint8_t dataWrite27[1] = {0x00};
  uint8_t dataWrite28[1] = {0x00};
  uint8_t dataWrite29[1] = {0x00};
  uint8_t dataWrite30[1] = {0x00};
  uint8_t dataWrite31[1] = {0x00};
  uint8_t dataWrite32[1] = {0x00};
  uint8_t dataWrite33[1] = {0x00};
  uint8_t dataWrite34[1] = {0x00};
  uint8_t dataWrite35[1] = {0x00};
  uint8_t dataWrite36[1] = {0x00};
  uint8_t dataWrite37[1] = {0x28};
  uint8_t dataWrite38[1] = {0x00};
  uint8_t dataWrite39[1] = {0x00};
  uint8_t dataWrite40[1] = {0x2A};
  uint8_t dataWrite41[1] = {0xF4};
  uint8_t dataWrite42[1] = {0x81};
  uint8_t dataWrite43[1] = {0x00};
  uint8_t dataWrite44[1] = {0x00};
  
  BQ25887_Reg_Write(0x00, dataWrite0);
  BQ25887_Reg_Write(0x01, dataWrite1);
  BQ25887_Reg_Write(0x02, dataWrite2);
  BQ25887_Reg_Write(0x03, dataWrite3);
  BQ25887_Reg_Write(0x04, dataWrite4);
  BQ25887_Reg_Write(0x05, dataWrite5);
  BQ25887_Reg_Write(0x06, dataWrite6);
  BQ25887_Reg_Write(0x07, dataWrite7);
  BQ25887_Reg_Write(0x08, dataWrite8);
  BQ25887_Reg_Write(0x09, dataWrite9);
  BQ25887_Reg_Write(0x0A, dataWrite10);
  BQ25887_Reg_Write(0x0B, dataWrite11);
  BQ25887_Reg_Write(0x0C, dataWrite12);
  BQ25887_Reg_Write(0x0D, dataWrite13);
  BQ25887_Reg_Write(0x0E, dataWrite14);
  BQ25887_Reg_Write(0x0F, dataWrite15);
  BQ25887_Reg_Write(0x10, dataWrite16);
  BQ25887_Reg_Write(0x11, dataWrite17);
  BQ25887_Reg_Write(0x12, dataWrite18);
  BQ25887_Reg_Write(0x13, dataWrite19);
  BQ25887_Reg_Write(0x14, dataWrite20);
  BQ25887_Reg_Write(0x15, dataWrite21);
  BQ25887_Reg_Write(0x16, dataWrite22);
  BQ25887_Reg_Write(0x17, dataWrite23);
  BQ25887_Reg_Write(0x18, dataWrite24);
  BQ25887_Reg_Write(0x19, dataWrite25);
  BQ25887_Reg_Write(0x1A, dataWrite26);
  BQ25887_Reg_Write(0x1B, dataWrite27);
  BQ25887_Reg_Write(0x1C, dataWrite28);
  BQ25887_Reg_Write(0x1D, dataWrite29);
  BQ25887_Reg_Write(0x1E, dataWrite30);
  BQ25887_Reg_Write(0x1F, dataWrite31);
  BQ25887_Reg_Write(0x20, dataWrite32);
  BQ25887_Reg_Write(0x21, dataWrite33);
  BQ25887_Reg_Write(0x22, dataWrite34);
  BQ25887_Reg_Write(0x23, dataWrite35);
  BQ25887_Reg_Write(0x24, dataWrite36);
  BQ25887_Reg_Write(0x25, dataWrite37);
  BQ25887_Reg_Write(0x26, dataWrite38);
  BQ25887_Reg_Write(0x27, dataWrite39);
  BQ25887_Reg_Write(0x28, dataWrite40);
  BQ25887_Reg_Write(0x29, dataWrite41);
  BQ25887_Reg_Write(0x2A, dataWrite42);
  BQ25887_Reg_Write(0x2B, dataWrite43);
  BQ25887_Reg_Write(0x2c, dataWrite44);
}