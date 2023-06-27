#ifndef ADS1220_LIB_H
#define ADS1220_LIB_H

#include "main.h"

extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim12;

#define ADC_VREF 2.5

#define _ADC_CS_PORT        CS_ADC_GPIO_Port
#define _ADC_CS_PIN         CS_ADC_Pin
#define _ADC_SPI            hspi1
#define _ADC_CLK_TIMER      &htim12
#define _ADC_CLK_CHANNEL    TIM_CHANNEL_1

typedef enum
{
  ADS_RESET = 0x06U,
  START     = 0x08U,
  SYNC      = 0x08U,
  POWERDOWN = 0x02U,
  RDATA     = 0x10U,
  RREG      = 0x20U,
  WREG      = 0x40U,
} ADS1220_CMD;

#define ADC_code_to_value(_code) (_code * ADC_VREF / 0x7FFFFF)
#define ADC_CS_UP() HAL_GPIO_WritePin(_ADC_CS_PORT, _ADC_CS_PIN, GPIO_PIN_SET);
#define ADC_CS_DOWN() HAL_GPIO_WritePin(_ADC_CS_PORT, _ADC_CS_PIN, GPIO_PIN_RESET);


void ads1220_Enable();
void ads1220_Disable();
void ads1220_init();
uint32_t ads1220_read_data_by_command();
uint32_t ads1220_read_data_cont();
void ads1220_cmd(uint8_t cmd);
void ads1220_write_reg_all();
uint8_t ads1220_read_reg(uint8_t addr);
void ads1220_write_reg(uint8_t addr, uint8_t val);
void ads1220_set_channel(uint8_t ain);



#endif /*ADS1220_LIB_H*/