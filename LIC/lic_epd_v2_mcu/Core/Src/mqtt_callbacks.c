#include "mqtt.h"
#include "mqtt_callbacks.h"
#include "string.h"
#include "main.h"

char mqtt_last_topicname[256];
char mqtt_rx_buffer[512];
uint32_t rx_buffer_len = 0;

uint8_t flag_pub_busy = 0;
uint8_t flag_conn_ack = 0;
uint8_t flag_sub_ack = 0;

uint32_t msent = 0;


void mqtt_incoming_publish_cb(void *arg, const char *topic, uint32_t tot_len);
void mqtt_incoming_data_cb(void *arg, const uint8_t *data, uint16_t len, uint8_t flags);
void mqtt_sub_request_cb(void *arg, err_t result);
void mqtt_pub_request_cb(void *arg, err_t result);
void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
extern void mqtt_receive(uint32_t datasize);
////

extern int poll_period_ms;


err_t mqtt_user_after_connection(mqtt_client_t *client, void *arg)
{
  flag_conn_ack = 1;
  return ERR_OK;
}

//void mqtt_user_after_receive()
//{
//  mqtt_receive();
//}

void print_err(int8_t err)
{
  switch(err)
  {
    case 0:
      //DIAG_MSG("OK\n");
      break;
    case -1:
      DIAG_MSG("Error: Out of memory\n");
      break;
    case -2:
      DIAG_MSG("Error: Buffer\n");
      break;
    case -3:
      DIAG_MSG("Error: Timeout\n");
      break;
    case -4:
      DIAG_MSG("Error: Routing\n");
      break;
    case -5:
      DIAG_MSG("Error: In progress\n");
      break;
    case -6:
      DIAG_MSG("Error: Illegal value\n");
      break;
    case -7:
      DIAG_MSG("Error: Would block\n");
      break;
    case -8:
      DIAG_MSG("Error: Address in use\n");
      break;
    case -9:
      DIAG_MSG("Error: Already connecting\n");
      break;
    case -10:
      DIAG_MSG("Error: Already connected\n");
      break;
    case -11:
      DIAG_MSG("Error: Not connected\n");
      break;
    case -12:
      DIAG_MSG("Error: Low-level netif\n");
      break;
    case -13:
      DIAG_MSG("Error: Connection aborted\n");
      break;
    case -14:
      DIAG_MSG("Error: Connection reset\n");
      break;
    case -15:
      DIAG_MSG("Error: Connection closed\n");
      break;
    case -16:
      DIAG_MSG("Error: Illegal arguement\n");
      break;
  }
}

////

void mqtt_incoming_publish_cb(void *arg, const char *topic, uint32_t tot_len)
{
  DIAG_MSG("Incoming publish at topic %s with total length %u\n", topic, (unsigned int)tot_len);
  
  uint32_t tlen = strlen(topic);
  if (tlen <= sizeof(mqtt_last_topicname))
    strcpy(mqtt_last_topicname, topic);
  else
    DIAG_MSG("Too long topic name!\n");
}

void mqtt_incoming_data_cb(void *arg, const uint8_t *data, uint16_t len, uint8_t flags)
{
  DIAG_MSG("Incoming publish payload with length %d, flags %u\n", len, (unsigned int)flags);
  
  if ( len )
  {
    if (rx_buffer_len + len <= sizeof(mqtt_rx_buffer))
    {
      memcpy(&mqtt_rx_buffer[rx_buffer_len], data, len);
      rx_buffer_len += len;
    }
    else
    {
      DIAG_MSG("Too long payload!\n");
    }
  }
  
  if (flags & MQTT_DATA_FLAG_LAST)
  {
    DIAG_MSG("Incoming payload data: %s\n", (const char *)mqtt_rx_buffer);
    //
    mqtt_receive(rx_buffer_len);
    //
    memset(mqtt_rx_buffer, 0, sizeof(mqtt_rx_buffer));
    rx_buffer_len = 0;
  }
}

void mqtt_sub_request_cb(void *arg, err_t result)
{
  DIAG_MSG("Subscribe result: %d\n", result);
  print_err(result);
  flag_sub_ack = 1;
}

void mqtt_pub_request_cb(void *arg, err_t result)
{
  DIAG_MSG("Publish result: %d\n", result);
  print_err(result);
  flag_pub_busy = 0;
}

/*
void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
  if (status == MQTT_CONNECT_ACCEPTED)
  {
    DIAG_MSG("Successfully connected to Broker\n");
    //mconnection++;
    //
    flag_conn_ack = 1;
    mqtt_user_after_connection(client, arg);
    //
  }
  else
  {
    DIAG_MSG("mqtt_connection_cb: Disconnected, reason: %d\n", status);
    flag_pub_ack = 2;
    // reconnect ?
  }
}*/

void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) 
{
    //err_t err;
    if (status == MQTT_CONNECT_ACCEPTED) {
            DIAG_MSG("mqtt_connection_cb: Successfully connected\n");

//            /* Setup callback for incoming publish requests */
//            mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, arg);
//
//            /* Subscribe to a topic named "test/topic" with QoS level 0, call mqtt_sub_request_cb with result */
//            err = mqtt_subscribe(client, "test/topic", 0, mqtt_sub_request_cb, arg);
//            if (err != ERR_OK) {
//                    printf("mqtt_subscribe return: %d\n", err);
//            }
    } else {
            DIAG_MSG("mqtt_connection_cb: Disconnected, reason: %d\n", status);
            flag_pub_busy = 0;

            /* Its more nice to be connected, so try to reconnect */
            //example_do_connect(client);
    }
}