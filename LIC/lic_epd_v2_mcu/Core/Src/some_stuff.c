#include "some_stuff.h"
#include "W25Qxx.h"
#include "gps.h"

#define CRC32_POLY_R 0xEDB88320

extern RTC_HandleTypeDef hrtc;

static uint32_t crc32r_table[256];


/**
  * @brief  
  * @param  
  * @retval 
  */
HAL_StatusTypeDef MakeTimeStamp(uint8_t *buff)
{
  HAL_StatusTypeDef res;
    
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  
  /* Get the RTC current Time */
  res = HAL_RTC_GetTime(&hrtc, &sTime, FORMAT_BIN);
  /* Get the RTC current Date */
  res = HAL_RTC_GetDate(&hrtc, &sDate, FORMAT_BIN);        
  
  buff[0] = sDate.Year;
  buff[1] = sDate.Month;
  buff[2] = sDate.Date;
  buff[3] = sTime.Hours;
  buff[4] = sTime.Minutes;
  buff[5] = sTime.Seconds;
  
  return res;
}


/**
  * @brief  
  * @param  
  * @retval 
  */
void act_led(led_color led, uint32_t act_time)
{
  static uint32_t leds_turnoff_time[5] = {0, 0, 0, 0, 0};
  
  if (led != NO_LED)
  {
    leds_turnoff_time[led] = HAL_GetTick() + act_time;
    switch ( led )
    {
      case LED_RED: HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET); break;
      case LED_GREEN: HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET); break;
      case LED_BLUE: HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET); break;
      case LED_ZB_GRN: HAL_GPIO_WritePin(ZB_LED2_GPIO_Port, ZB_LED2_Pin, GPIO_PIN_SET); break;
      case LED_ZB_YEL: HAL_GPIO_WritePin(ZB_LED1_GPIO_Port, ZB_LED1_Pin, GPIO_PIN_SET); break;
    }
    
    return;
  }
  
  if ( leds_turnoff_time[LED_RED] )
  {
    if ( HAL_GetTick() >= leds_turnoff_time[(uint8_t)LED_RED] )
    {
      HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
      leds_turnoff_time[LED_RED] = 0;
    }
  }
  
  if ( leds_turnoff_time[LED_GREEN] )
  {
    if ( HAL_GetTick() >= leds_turnoff_time[(uint8_t)LED_GREEN] )
    {
      HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
      leds_turnoff_time[LED_GREEN] = 0;
    }
  }
  
  if ( leds_turnoff_time[LED_BLUE] )
  {
    if ( HAL_GetTick() >= leds_turnoff_time[(uint8_t)LED_BLUE] )
    {
      HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET);
      leds_turnoff_time[LED_BLUE] = 0;
    }
  }
  
  if ( leds_turnoff_time[LED_ZB_GRN] )
  {
    if ( HAL_GetTick() >= leds_turnoff_time[(uint8_t)LED_ZB_GRN] )
    {
      HAL_GPIO_WritePin(ZB_LED2_GPIO_Port, ZB_LED2_Pin, GPIO_PIN_RESET);
      leds_turnoff_time[LED_ZB_GRN] = 0;
    }
  }
  
  if ( leds_turnoff_time[LED_ZB_YEL] )
  {
    if ( HAL_GetTick() >= leds_turnoff_time[(uint8_t)LED_ZB_YEL] )
    {
      HAL_GPIO_WritePin(ZB_LED1_GPIO_Port, ZB_LED1_Pin, GPIO_PIN_RESET);
      leds_turnoff_time[LED_ZB_YEL] = 0;
    }
  }
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint16_t crc16(uint8_t* data, uint16_t num)
{
  uint16_t crc = 0xFFFF;
  uint16_t polynom = 0xA001;
  uint16_t i = 0;
  uint16_t j = 0;

  for (i = 0; i < num; i++)
  {
    crc = crc ^ data[i];

    for (j = 0; j < 8; j++)
      if(crc & 0x0001)
      {
        crc = crc >> 1;
        crc = crc ^ polynom;
      }
      else
      {
        crc = crc >>1;
      }
  }
  return(crc);
}

void LED_set_color(uint8_t color)
{
  ((color >> 2) & 1) == 0 ? HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
  ((color >> 1) & 1) == 0 ? HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
  ((color >> 0) & 1) == 0 ? HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET);  
}
  
void Prepare4Reboot(void)
{
  HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET);
  
  HAL_GPIO_WritePin(GPIOE, ZB_3V3_En_Pin | ETH_3V3_En_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPS_EN_GPIO_Port, GPS_EN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SD_VCC_EN_GPIO_Port, SD_VCC_EN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Periph_5V_En_GPIO_Port, Periph_5V_En_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Periph_3V3_En_GPIO_Port, Periph_3V3_En_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LORA_3V3_En_GPIO_Port, LORA_3V3_En_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SIM_VCC_EN_GPIO_Port, SIM_VCC_EN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(RS1_PWR_DIS_GPIO_Port, RS1_PWR_DIS_Pin, GPIO_PIN_SET); 
  HAL_GPIO_WritePin(RS_48V_EN_GPIO_Port, RS_48V_EN_Pin, GPIO_PIN_RESET);   
  HAL_GPIO_WritePin(GPIOF, RS2_VCC_EN_Pin|RS3_VCC_EN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(RS1_VCC_EN_GPIO_Port, RS1_VCC_EN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOD, AN2_VCC_EN_Pin|CAN_VCC_EN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(AN1_VCC_EN_GPIO_Port, AN1_VCC_EN_Pin, GPIO_PIN_RESET);
  
}

void crc32_init(void)
{
        int i, j;
        uint32_t cr;
        for (i = 0; i < 256; ++i) {
                cr = i;
                for (j = 8; j > 0; --j) {
                        cr = cr & 0x00000001 ? (cr >> 1) ^ CRC32_POLY_R : (cr >> 1);
                        }
                crc32r_table[i] = cr;
        }
}

uint32_t crc32_byte(uint32_t init_crc, uint8_t *buf, int len)
{
        uint32_t v;
        uint32_t crc;
        crc = ~init_crc;
        while(len > 0) {
                v = *buf++;
                crc = ( crc >> 8 ) ^ crc32r_table[( crc ^ (v ) ) & 0xff];
                len --;
        }
        return ~crc;
}

void save_settings(uint32_t sector)
{
  W25qxx_EraseSector(sector);
  config.CRC32 = crc32_byte(0, (uint8_t*)&config, sizeof(config) - sizeof(config.CRC32));
  W25qxx_WriteSector((uint8_t*)&config, sector, 0, sizeof(config));
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void SyncTimeGPS2RTC(void)
{
  static uint32_t last_time_sync = 0;
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  
  /* Если данные не достоверны, то выходим */
  if ( GPS.valid_date == 0 || GPS.valid_time == 0 ) return;
  if ( !((HAL_GetTick()-last_time_sync)>86400000L || last_time_sync == 0) ) return;
    
  /* Get the RTC current Time */
  HAL_RTC_GetTime(&hrtc, &sTime, FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&hrtc, &sDate, FORMAT_BIN);        
  
  sDate.Year    = GPS.year-2000;
  sDate.Month   = GPS.month;
  sDate.Date    = GPS.day;
  sTime.Hours   = GPS.hours;
  sTime.Minutes = GPS.minutes;
  sTime.Seconds = GPS.seconds;
  if ( sTime.Seconds > 0 ) sTime.Seconds--;                                     // компенсируем одну секунду задержки при считывании GPS
  
  HAL_RTC_SetTime(&hrtc, &sTime, FORMAT_BIN);
  HAL_RTC_SetDate(&hrtc, &sDate, FORMAT_BIN);

  last_time_sync = HAL_GetTick();
}
