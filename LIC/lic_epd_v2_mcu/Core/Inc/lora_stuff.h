#ifndef __LORA_STUFF_H
#define __LORA_STUFF_H

typedef __packed struct{
  uint32_t sn;
  uint8_t  rev[4];
  uint8_t  info[16];  
} LoRaModuleInfo;
  
typedef __packed struct{
  uint8_t  enabled;
  uint8_t  LoRa_Dev_EUI[8];
  uint8_t  LoRa_App_EUI[8];
  uint8_t  LoRa_App_Key[16];
  uint16_t LoRa_App_Port;
  uint8_t  LoRa_Datarate;
  uint8_t  LoRa_AUTO_Dev_EUI;
  uint8_t  LoRa_Message_Type;
  uint32_t CRC32;
} LoRaConfig;

extern LoRaConfig  lora_config;

void LORA_Init_user(void);
void LORA_Process(void);
void HW_GetUniqueId(uint8_t *id);
void LORA_SaveConfig(void);
void LORA_ReadConfig(void);

#endif /* __LORA_STUFF_H */
