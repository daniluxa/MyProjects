#ifndef __SOME_STUFF_H
#define __SOME_STUFF_H

#include "stm32f4xx_hal.h"
#include "main.h"

#define CAST2U32(x) *((uint32_t*)&x)
#define CAST2U16(x) *((uint16_t*)&x)

typedef enum 
{
  LED_RED   = 0,
  LED_GREEN,
  LED_BLUE,
  LED_ZB_GRN,
  LED_ZB_YEL,
  NO_LED 
} led_color;


HAL_StatusTypeDef MakeTimeStamp(uint8_t *buff);
uint16_t crc16(uint8_t* data, uint16_t num);
void act_led(led_color led, uint32_t act_time);
void LED_set_color(uint8_t color);
void Prepare4Reboot(void);
void crc32_init(void);
uint32_t crc32_byte(uint32_t init_crc, uint8_t *buf, int len);
void save_settings(uint32_t sector);
void SyncTimeGPS2RTC(void);


#endif // __SOME_STUFF_H