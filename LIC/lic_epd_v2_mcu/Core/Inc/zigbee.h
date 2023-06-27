#ifndef __ZIGBEE_H
#define __ZIGBEE_H

#include <stdint.h>
#include <string.h>
#include "main.h"

#define	ZIGBEE_SPI	  hspi1

typedef __packed struct{  
  int16_t pressure;
  int16_t temp;
  uint16_t humidity;
  uint8_t LQI;
  int8_t RSSI;
} AqaraSensor;

typedef __packed struct{  
  uint8_t timestamp[6];
  AqaraSensor sensor;
} Zigbee_data_T;

extern Zigbee_data_T Zigbee_data;
extern SPI_HandleTypeDef hspi1;

void ZigBeeInit(void);
void ZigBeeParse();

#endif //__ZIGBEE_H