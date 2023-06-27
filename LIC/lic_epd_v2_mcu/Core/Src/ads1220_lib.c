#include "ads1220_lib.h"
#include "string.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal.h"
#include "main.h"

// default reset values
// See https://www.ti.com/lit/ds/symlink/ads1220.pdf
uint8_t adc_reg_table[4] = { 0xB0, 0x04, 0x40, 0x00 };

void ads1220_Enable(){
  PERIPH_5V_ON();                                          // power
  HAL_TIM_PWM_Start(_ADC_CLK_TIMER, _ADC_CLK_CHANNEL);     // clk
}

void ads1220_Disable(){
  HAL_TIM_PWM_Stop(_ADC_CLK_TIMER, _ADC_CLK_CHANNEL);      // clk
}


/**
  * @brief  Write an amount of data in blocking mode
  * @param  pData pointer to data buffer
  * @param  Amount of data to be written
  * @retval -
  */
void spi_write(uint8_t *tx, uint16_t num)
{
  ADC_CS_DOWN();
  for(int i = 0; i < num; i++)
  {
    HAL_SPI_Transmit(&_ADC_SPI, (uint8_t *)&tx[i], 1, 10);
  }
  ADC_CS_UP();
}


/**
  * @brief  Read an amount of data in blocking mode
  * @param  Pointer to data buffer
  * @param  Amount of data to be read
  * @retval -
  */
void spi_read(uint8_t *rx, uint16_t num)
{
  uint8_t temp[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  ADC_CS_DOWN();
  HAL_SPI_TransmitReceive(&_ADC_SPI, temp, rx, num, 10);
  ADC_CS_UP();
}


/**
  * @brief  Read an amount of data in blocking mode
  * @param  Pointer to transmission data buffer
  * @param  Pointer to  reception data buffer
  * @param  Amount of data to be read
  * @retval -
  */
void spi_readwrite(uint8_t *tx, uint8_t *rx, uint16_t num)
{
  ADC_CS_DOWN();
  HAL_SPI_TransmitReceive(&_ADC_SPI, tx, rx, num, 10);
  ADC_CS_UP();
}

/**
  * @brief  Init ads1220 regs and send start command
  * @param  -
  * @retval -
  */
void ads1220_init(){
  ads1220_Enable();
  HAL_Delay(20);
  ads1220_cmd(ADS_RESET);
  HAL_Delay(5);
  ads1220_write_reg_all();
  HAL_Delay(5);
  ads1220_cmd(START);
}

/**
  * @brief  Read ADC data by command
  * @param  -
  * @retval ADC code (not voltage)
  */
uint32_t ads1220_read_data_by_command()
{
  uint8_t cmd[] = { RDATA, 0, 0, 0 };
  uint32_t data_adc;
  uint8_t retval[] = {0, 0, 0}; 

  spi_readwrite(cmd, retval, sizeof(cmd));
  data_adc = (uint32_t)(retval[sizeof(retval)-3] << 16) | (uint32_t)(retval[sizeof(retval)-2] << 8) | retval[sizeof(retval)-1];  
  
  return data_adc;

}

/**
  * @brief  Read ADC data when ready (use with DRDY pin falling edge interrupt)
  * @param  -
  * @retval ADC code (not voltage)
  */
uint32_t ads1220_read_data_cont(){
  uint32_t data_adc;
  uint8_t data_rev[3];
  spi_read(data_rev, 3);
  data_adc = (data_rev[0]<<16) | ((data_rev[1] & 0xFF)<<8) | (data_rev[2]);
  return data_adc;
}

/**
  * @brief  Send command to ADS1220
  * @param  Command byte
  * @retval -
  */
void ads1220_cmd(uint8_t cmd)
{
  spi_write(&cmd, sizeof(cmd));
}

/**
  * @brief  Write all config regs from 'adc_reg_table' to ADS1220
  * @param  -
  * @retval -
  */
void ads1220_write_reg_all()
{
  uint8_t cmd[1 + sizeof(adc_reg_table)] = { WREG | 3 };
  memcpy(&cmd[1], adc_reg_table, sizeof(adc_reg_table));
  spi_write(cmd, sizeof(cmd));
}

/**
  * @brief  Read register by address
  * @param  -
  * @retval Register value
  */
uint8_t ads1220_read_reg(uint8_t addr)
{
  uint8_t cmd[] = { RREG | (addr << 2), 0 };
  uint8_t retval[] = {0, 0}; 
  spi_readwrite(cmd, retval, sizeof(cmd));  
  
  return retval[sizeof(retval)-1];
}

/**
  * @brief  Write register value to ADS1220
  * @param  Register address
  * @param  Register value
  * @retval -
  */
void ads1220_write_reg(uint8_t addr, uint8_t val)
{
  uint8_t cmd[] = { WREG | (addr << 2), val };  
  spi_write(cmd, sizeof(cmd));
}

/**
  * @brief  Set analog input of ADS1220 to conversion
  * @param  Number of analog input
  * @retval -
  */
void ads1220_set_channel(uint8_t ain)// 0-AIN0 1-AIN1 2-AIN2 3-AIN3
{
  uint8_t ain_reg = (ads1220_read_reg(0x00) & 0x0F) | ((ain + 0x08) << 4);
  ads1220_write_reg(0x00, ain_reg);
}

