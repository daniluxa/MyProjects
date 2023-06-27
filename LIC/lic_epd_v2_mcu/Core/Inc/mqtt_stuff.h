#ifndef __MQTT_STUFF_H
#define __MQTT_STUFF_H

#include "lwip.h"
#include "mqtt.h"
#include "mqtt_priv.h"
#include "mqtt_callbacks.h"
#include "sensors.h"

#define MAX_TOPIC_LEN 50
#define MAX_PAYLOAD_SIZE (MQTT_OUTPUT_RINGBUF_SIZE-MAX_TOPIC_LEN)

#define iZIGBEE         1001

void MQTT_Process(void);
void tim7_handle(void);
uint8_t get_mqtt_topic(void* interface, uint16_t msg_type, char* buf);
int32_t get_sensor_data_string(pSensorElem pSensor, uint8_t* data_in, char* data_out, uint32_t datasize);
int32_t mqtt_add2queue(char *pTopicName, uint8_t *pData, uint16_t DataSize);
void mqtt_init_user();

#endif /* __MQTT_STUFF_H */
