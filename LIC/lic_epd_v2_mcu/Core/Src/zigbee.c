#include "zigbee.h"
#include "some_stuff.h"
#include "main.h"
#include "sensors.h"
#include "mqtt_stuff.h"

Zigbee_data_T Zigbee_data = {0,0,0,0};
//uint8_t zigbee_enable = 1;

uint32_t ZigBee2MQTT(uint32_t sensor_type, uint8_t *pBuff, uint32_t DataSize);



void ZigBeeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  if ( cfg_zigbee->enabled == 0 ) return;
  
  if( ZIGBEE_CONNECTED ){
    ZIGBEE_POWER_ON();
    HAL_GPIO_WritePin(ZB_LED2_GPIO_Port, ZB_LED2_Pin, GPIO_PIN_SET);
  }
  else return;
  
  HAL_Delay(200);
  
  /*Configure GPIO pins : ZB_GPIO1_Pin*/
  GPIO_InitStruct.Pin = ZB_GPIO1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 7, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void ZigBeeParse(void)
{
  uint8_t rx_data[32];
  memset(rx_data, 0x00, 32);
  HAL_StatusTypeDef res;

  if ( cfg_zigbee->enabled == 0 ) return;
  
  HAL_GPIO_WritePin(ZB_CS_GPIO_Port, ZB_CS_Pin, GPIO_PIN_RESET);
  HAL_Delay(1); // Вынужденное ожидание для обработки прерывания на модуле Zigbee
  res = HAL_SPI_Receive(&hspi1,rx_data,15,10); // Calls TransmitReceive anyway
  HAL_GPIO_WritePin(ZB_CS_GPIO_Port, ZB_CS_Pin, GPIO_PIN_SET);  
  if ( res != HAL_OK ) return;
  
  if (rx_data[0] == 0x20 && rx_data[1] == 0x13){
    if (rx_data[2] == 0x11){
      Zigbee_data.sensor.pressure = *((int16_t*)(&rx_data[3]));
    }  
    
    if (rx_data[5] == 0x12){
      Zigbee_data.sensor.temp = *((int16_t*)(&rx_data[6]));
    }
    
    if (rx_data[8] == 0x13){
      Zigbee_data.sensor.humidity = *((uint16_t*)(&rx_data[9]));
    }
    
    if (rx_data[11] == 0x21){
      Zigbee_data.sensor.LQI = *((uint8_t*)(&rx_data[12]));
    }
    
    if (rx_data[13] == 0x22){
      Zigbee_data.sensor.RSSI = *((int8_t*)(&rx_data[14]));
    }
    
    MakeTimeStamp(Zigbee_data.timestamp);
    ZigBee2MQTT(AQARA, (uint8_t*)&Zigbee_data, sizeof(Zigbee_data));
    act_led(LED_ZB_YEL, 50);
  }
}


/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t ZigBee2MQTT(uint32_t sensor_type, uint8_t *pBuff, uint32_t DataSize)
{
  uint32_t len;
  char mqtt_payload[MAX_PAYLOAD_SIZE];
  char mqtt_topic[MAX_TOPIC_LEN];
  SensorElem Sensor;

 
  Sensor.SensorType = sensor_type;
  Sensor.SensorEnabled = 1;
  get_mqtt_topic((void*)iZIGBEE, AQARA, mqtt_topic);
  len = get_sensor_data_string(&Sensor, pBuff, mqtt_payload, DataSize);
  mqtt_add2queue(mqtt_topic, (uint8_t*)mqtt_payload, len);
  
  return 0;
}