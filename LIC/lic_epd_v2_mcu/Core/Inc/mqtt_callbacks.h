#ifndef __MQTT_CALLBACKS_H
#define __MQTT_CALLBACKS_H



void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
void mqtt_incoming_data_cb(void *arg, const uint8_t *data, u16_t len, uint8_t flags);
void mqtt_sub_request_cb(void *arg, err_t result);
void mqtt_pub_request_cb(void *arg, err_t result);
void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
void print_err(int8_t err);

enum mqtt_qos
{
  MQTT_QOS_AtMostOnce = 0,
  MQTT_QOS_AtLeastOnce,
  MQTT_QOS_ExactlyOnce
};

enum mqtt_retain
{
  MQTT_NoRetain = 0,
  MQTT_Retain
};



#endif /* __MQTT_CALLBACKS_H */
