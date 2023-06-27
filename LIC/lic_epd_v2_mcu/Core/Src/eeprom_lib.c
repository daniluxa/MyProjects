#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "string.h"
#include "main.h"
#include "eeprom_lib.h"
#include "some_stuff.h"
#include "W25Qxx.h"

extern DeviceInfo devinfo;
/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t read_device_info(void)
{
  DeviceInfo info;
  uint32_t crc32;
  
  W25qxx_ReadPage((uint8_t*)&info, 0, 0, sizeof(DeviceInfo));
  crc32 = crc32_byte(0, (uint8_t*)&info, sizeof(DeviceInfo) - sizeof(crc32));
  if ( crc32 == info.CRC32 ) 
  {
    devinfo = info;
    return 0;
  }
  return 1;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void write_device_info(void)
{
  W25qxx_EraseSector(0);
  devinfo.CRC32 = crc32_byte(0, (uint8_t*)&devinfo, sizeof(DeviceInfo) - sizeof(devinfo.CRC32));
  W25qxx_WritePage((uint8_t*)&devinfo, 0, 0, sizeof(DeviceInfo));
}

/**
  * @brief  
  * @param  
  * @retval 
  */
HAL_StatusTypeDef read_cfg_eeprom(uint32_t sector)
{
  HAL_StatusTypeDef result = HAL_OK;
  DeviceConfig temp;
  uint32_t crc32;
  
  W25qxx_ReadSector((uint8_t*)&temp, sector, 0, sizeof(DeviceConfig));
  crc32 = crc32_byte(0, (uint8_t*)&temp, sizeof(DeviceConfig) - sizeof(crc32));
  if ( crc32 == temp.CRC32 ) config = temp;
  else
  {
    /* —ооружаем свой MAC-адрес из уникального ID контроллера */
    uint32_t id0 = HAL_GetUIDw0();
    uint32_t id1 = HAL_GetUIDw1();
    uint32_t id2 = HAL_GetUIDw2();
    
    crc32 = crc32_byte(0, (uint8_t*)&id1, sizeof(id1));
    crc32 = crc32_byte(crc32, (uint8_t*)&id2, sizeof(id2));
    crc32 = crc32_byte(crc32, (uint8_t*)&id0, sizeof(id0));  
    id0 += crc32;
    *(uint32_t*)cfg_eth->HW_addr = crc32;
    *(uint32_t*)&cfg_eth->HW_addr[2] = id0;
    if ( cfg_eth->HW_addr[0] % 2 ) cfg_eth->HW_addr[0]--;
    
    result = HAL_ERROR;
  }
  
   return result;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
uint8_t* get_param_ptr(Cfg_fields field, uint32_t *size)
{
  switch(field)
  {
    // -------------------              Overall
    case FIELD_BUILD_DATE:
      *size = sizeof(dev_info->Build_date);
      return dev_info->Build_date;
 
    case FIELD_SERIAL_NUM:
      *size = sizeof(dev_info->Serial_num);
      return (uint8_t*)&dev_info->Serial_num;
      
//    case FIELD_POLL_PERIOD_MS:
//      *size = sizeof(dev_info->Poll_period_ms);
//      return (uint8_t*)&dev_info->Poll_period_ms;
//      
//    case FIELD_STANDBY_TIME:
//      *size = sizeof(dev_info->Standby_time);
//      return (uint8_t*)&dev_info->Standby_time;
//      
//    case FIELD_WORK_TIME:
//      *size = sizeof(dev_info->Work_time);
//      return (uint8_t*)&dev_info->Work_time;
      
      
    // -------------------              Sensors
//    case FIELD_SENSOR_RS1:
//      *size = sizeof(cfg_sensors->RS1_sensor_type);
//      return &cfg_sensors->RS1_sensor_type;
//      
//    case FIELD_SENSOR_RS2:
//      *size = sizeof(cfg_sensors->RS2_sensor_type);
//      return &cfg_sensors->RS2_sensor_type;
//         
//    case FIELD_SENSOR_RS3:
//      *size = sizeof(cfg_sensors->RS3_sensor_type);
//      return &cfg_sensors->RS3_sensor_type;
       
    
    // -------------------              Ethernet   
    case FIELD_ETH_EN:
      *size = sizeof(cfg_eth->eth_enabled);
      return (uint8_t*)&cfg_eth->eth_enabled;
      
    case FIELD_DEV_IP:
      *size = sizeof(cfg_eth->Dev_IP);
      return cfg_eth->Dev_IP;
      
    case FIELD_NET_MASK:
      *size = sizeof(cfg_eth->Net_mask);
      return cfg_eth->Net_mask;
      
    case FIELD_GW_IP:
      *size = sizeof(cfg_eth->GW_IP);
      return cfg_eth->GW_IP;
      
    case FIELD_HW_ADDR:
      *size = sizeof(cfg_eth->HW_addr);
      return cfg_eth->HW_addr;
      
    case FIELD_DHCP_FLAG:
      *size = sizeof(cfg_eth->DHCP_flag);
      return &cfg_eth->DHCP_flag;
      
    case FIELD_MQTT_EN:
      *size = sizeof(cfg_eth->mqtt_enabled);
      return (uint8_t*)&cfg_eth->mqtt_enabled;
      
    case FIELD_BROKER_ADDR:
      *size = sizeof(cfg_eth->Broker_addr);
      return cfg_eth->Broker_addr;
      
    case FIELD_BROKER_ADDR_DNS_FLAG:
      *size = sizeof(cfg_eth->Broker_addr_dns_flag);
      return &cfg_eth->Broker_addr_dns_flag;
      
    case FIELD_BROKER_PORT:
      *size = sizeof(cfg_eth->Broker_port);
      return (uint8_t*)&cfg_eth->Broker_port;
          
    case FIELD_MQTT_TOPIC_DATA:
      *size = sizeof(cfg_eth->MQTT_topic_data);
      return (uint8_t*)cfg_eth->MQTT_topic_data;
      
//    case FIELD_MQTT_TOPIC_POLL_PERIOD:
//      *size = sizeof(cfg_eth->MQTT_topic_poll_period);
//      return (uint8_t*)cfg_eth->MQTT_topic_poll_period;
      
    case FIELD_MQTT_ID:
      *size = sizeof(cfg_eth->MQTT_ID);
      return (uint8_t*)cfg_eth->MQTT_ID;
      
    case FIELD_MQTT_USER:
      *size = sizeof(cfg_eth->MQTT_user);
      return (uint8_t*)cfg_eth->MQTT_user;
      
    case FIELD_MQTT_PASSWORD:
      *size = sizeof(cfg_eth->MQTT_password);
      return (uint8_t*)cfg_eth->MQTT_password;
      
      
    // -------------------              LoRa
    case FIELD_LORA_EN:
      *size = sizeof(cfg_lora->enabled);
      return (uint8_t*)&cfg_lora->enabled;
      
//    case FIELD_LORA_UID:
//      *size = sizeof(cfg_lora->LoRa_UID);
//      return (uint8_t*)&cfg_lora->LoRa_UID;
      
    case FIELD_LORA_DEV_EUI:
      *size = sizeof(cfg_lora->LoRa_Dev_EUI);
      return cfg_lora->LoRa_Dev_EUI;
      
    case FIELD_LORA_APP_EUI:
      *size = sizeof(cfg_lora->LoRa_App_EUI);
      return cfg_lora->LoRa_App_EUI;
      
    case FIELD_LORA_APP_KEY:
      *size = sizeof(cfg_lora->LoRa_App_Key);
      return cfg_lora->LoRa_App_Key;
      
    case FIELD_LORA_APP_PORT:
      *size = sizeof(cfg_lora->LoRa_App_Port);
      return (uint8_t*)&cfg_lora->LoRa_App_Port;
      
    case FIELD_LORA_DATARATE:
      *size = sizeof(cfg_lora->LoRa_Datarate);
      return (uint8_t*)&cfg_lora->LoRa_Datarate;
      
//    case FIELD_LORA_ADR:
//      *size = sizeof(cfg_lora->LoRa_ADR);
//      return (uint8_t*)&cfg_lora->LoRa_ADR;
      
    case FIELD_LORA_AUTO_DEV_EUI:
      *size = sizeof(cfg_lora->LoRa_AUTO_Dev_EUI);
      return (uint8_t*)&cfg_lora->LoRa_AUTO_Dev_EUI;
      
    case FIELD_LORA_MESSAGE_TYPE:
      *size = sizeof(cfg_lora->LoRa_Message_Type);
      return (uint8_t*)&cfg_lora->LoRa_Message_Type;
      
      
    // -------------------              ZigBee
    case FIELD_ZIGBEE_EN:
      *size = sizeof(cfg_zigbee->enabled);
      return (uint8_t*)&cfg_zigbee->enabled;
      
    case FIELD_ZIGBEE_DEV_ID:
      *size = sizeof(cfg_zigbee->ZigBee_Dev_ID);
      return (uint8_t*)&cfg_zigbee->ZigBee_Dev_ID;
      

    default:
      return 0;
  }
}
                                          
/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t set_param(Cfg_fields field, uint8_t* pdata, uint32_t size)
{
  uint32_t fsize;
  uint8_t *fptr = get_param_ptr(field, &fsize);
  if ( fptr )
  {    
    if ( size <= fsize )
    {
      if ( size < fsize ) memset(fptr, 0x00, fsize);
      memcpy(fptr, pdata, fsize );
      return 0;
    }
    else return 2;
  }
  
  return 1;
}

