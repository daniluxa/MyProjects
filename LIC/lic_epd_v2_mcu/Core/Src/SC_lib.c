#include "SC_lib.h"


uint8_t SC_ATR(){
  
  uint8_t data_rd [256] = {0};
  uint8_t i = 0;

  if (HAL_GPIO_ReadPin(SIM_Connected_GPIO_Port, SIM_Connected_Pin) == GPIO_PIN_RESET){ // if SC is connected
    HAL_GPIO_WritePin(SIM_RST_GPIO_Port, SIM_RST_Pin, GPIO_PIN_RESET); // RST low (active)
    
    // Power on (turn off and then turn on if already powered on)
    if(HAL_GPIO_ReadPin(SIM_VCC_EN_GPIO_Port, SIM_VCC_EN_Pin) == GPIO_PIN_RESET){
      HAL_GPIO_WritePin(SIM_VCC_EN_GPIO_Port, SIM_VCC_EN_Pin, GPIO_PIN_SET);
      HAL_Delay(1);
      HAL_GPIO_WritePin(SIM_VCC_EN_GPIO_Port, SIM_VCC_EN_Pin, GPIO_PIN_RESET);
    }
    else 
      HAL_GPIO_WritePin(SIM_VCC_EN_GPIO_Port, SIM_VCC_EN_Pin, GPIO_PIN_RESET);
    
    
    HAL_Delay(1); // Wait 4000 clocks
    HAL_GPIO_WritePin(SIM_RST_GPIO_Port, SIM_RST_Pin, GPIO_PIN_SET); // RST up (inactive)

    while (HAL_SMARTCARD_Receive(&SC_UART, data_rd+i, 1, 10) == HAL_OK){ // ATR Receive in 40000 clocks
      i++;
      if (i == 0) {
        SC_Deactivate();
        return 2; // ERROR: TOO LONG ATR
      }
    }

    if (i == 0)
    {
      SC_Deactivate();
      return 3; // ERROR: NO ATR
    }

    return 0; // OK
  }
  
  return 1; // ERROR: SC is not connected
}


uint8_t SC_PPS(){
  
  // FF - initial byte, 10 - next PPS messsages index,
  // 95 - Fi and Di (table), 7A - XOR checksum
  uint8_t PPS[] = {0xFF,0x10,0x95,0x7A};

  uint8_t data_rd[256] = {0}; // buffer for reading data
  uint8_t i = 0;

  if (HAL_GPIO_ReadPin(SIM_Connected_GPIO_Port, SIM_Connected_Pin) == GPIO_PIN_RESET){ // if SC is connected
    HAL_SMARTCARD_Transmit(&SC_UART, PPS, sizeof(PPS), 1000);

    while (HAL_SMARTCARD_Receive(&SC_UART, data_rd+i, 1, 10) == HAL_OK){
      i++;
      if (i == 0) {
        SC_Deactivate();
        return 4; // ERROR: TOO LONG PPS
      }
    }

    if ((data_rd[0] != 0xFF) || (data_rd[1] != 0xFF) || (data_rd[2] != 0x10) ||
        (data_rd[3] != 0x95) || (data_rd[4] != 0x7A) || (data_rd[5] != 0x00))
    {
      SC_Deactivate();
      return 5; // ERROR: PPS NOT APPROVED
    }

    return 0; // OK
  }
  
  return 1; // ERROR: SC is not connected
}


uint8_t SC_Wrap(uint8_t * plain_data, uint8_t plain_size, uint8_t * encrypted_data, uint8_t * encrypted_size){

  if (plain_size > 235){
    return 6; // Too big data to be encrypted at once
  }
  
  uint32_t command_size = 5;
  uint8_t command[] = {0x80,0xB0,0x02,0x00,plain_size};

  uint8_t data_rd[256] = {0};
  uint8_t i = 0;

  HAL_SMARTCARD_Transmit(&SC_UART, command, command_size, 1000);
  while(HAL_SMARTCARD_Receive(&SC_UART, data_rd+i, 1, 10) == HAL_OK){
    i++;
    if (i == 0) {
      SC_Deactivate();
      return 7; // Too long answer on WRAP request command
    }
  }

  if (data_rd[1] != 0xB0) return 8; // WRAP command was not recognized by SC

  i = 0;
  memset(data_rd,0,256);
  
  
  HAL_SMARTCARD_Transmit(&SC_UART, plain_data, plain_size, 1000);
  while (HAL_SMARTCARD_Receive(&SC_UART, data_rd+i, 1, 100) == HAL_OK){
    i++;
    if (i == 0) {
      SC_Deactivate();
      return 9; // Too long answer of completing WRAP command
    }
  }

  if (data_rd[1] != 0x61) return 10; // WRAP command was not completed successfully on SC

  uint8_t remain_to_receive = data_rd[2];
  uint32_t enc_data_index = 0;
  
  while ((remain_to_receive == 0x00) || (remain_to_receive > 0xFC))
  {
    uint8_t get_response[] = {0x00,0xC0,0x00,0x00,0xFC};
    *encrypted_size += 252;
    
    i = 0;
    memset(data_rd,0,256);
    
    
    HAL_SMARTCARD_Transmit(&SC_UART, get_response, sizeof(get_response), 1000);
    while (HAL_SMARTCARD_Receive(&SC_UART, data_rd+i, 1, 10) == HAL_OK){
      i++;
      if (i == 0) break;
    }
    
    if (data_rd[254] != 0x61) return 11; // Receiving data after WRAP command was failed
    else {
      remain_to_receive = data_rd[255];
    }
    
    for (uint8_t k = 0; k < 252; k++){
      encrypted_data[enc_data_index] = data_rd[enc_data_index+2];
      enc_data_index++;
    }
  }
  
  uint8_t get_response[] = {0x00,0xC0,0x00,0x00,remain_to_receive};
  *encrypted_size += remain_to_receive;
  
  i = 0;
  memset(data_rd,0,256);
  
  
  HAL_SMARTCARD_Transmit(&SC_UART, get_response, sizeof(get_response), 1000);
  while (HAL_SMARTCARD_Receive(&SC_UART, data_rd+i, 1, 10) == HAL_OK){
    i++;
    if (i == 0) break;
  }
  
  if ((data_rd[remain_to_receive + 2] != 0x90) || 
      (data_rd[remain_to_receive + 3] != 0x00))
    return 12; // Received data after WRAP command is bad
  
  for (uint8_t k = 0; k < remain_to_receive; k++){
    encrypted_data[enc_data_index] = data_rd[k+2];
    enc_data_index++;
  }
  
  return 0; // OK
}


uint8_t SC_Unwrap(uint8_t * encrypted_data, uint8_t encrypted_size, uint8_t * plain_data, uint8_t * plain_size){

  uint32_t command_size = 5;
  uint8_t command[] = {0x80,0xB2,0x00,0x00,encrypted_size};

  uint8_t data_rd[256] = {0};
  uint8_t i = 0;

  HAL_SMARTCARD_Transmit(&SC_UART, command, command_size, 1000);
  while(HAL_SMARTCARD_Receive(&SC_UART, data_rd+i, 1, 10) == HAL_OK){
    i++;
    if (i == 0) {
      SC_Deactivate();
      return 13; // Too long answer on UNWRAP request command
    }
  }

  if (data_rd[1] != 0xB2) return 14; // UNWRAP command was not recognized by SC

  i = 0;
  memset(data_rd,0,256);
  
  
  HAL_SMARTCARD_Transmit(&SC_UART, encrypted_data, encrypted_size, 1000);
  while (HAL_SMARTCARD_Receive(&SC_UART, data_rd+i, 1, 100) == HAL_OK){
    i++;
    if (i == 0) {
      SC_Deactivate();
      return 15; // Too long answer of completing UNWRAP command
    }
  }

  if (data_rd[1] != 0x61) return 16; // UNWRAP command was not completed successfully on SC

  uint8_t get_response[] = {0x00,0xC0,0x00,0x00,data_rd[2]};
  *plain_size = data_rd[2];

  i = 0;
  memset(data_rd,0,256);


  HAL_SMARTCARD_Transmit(&SC_UART, get_response, sizeof(get_response), 1000);
  while (HAL_SMARTCARD_Receive(&SC_UART, data_rd+i, 1, 100) == HAL_OK){
    i++;
    if (i == 0) {
      SC_Deactivate();
      return 17; // Too long received data
    }
  }

  if ((data_rd[*plain_size + 2] != 0x90) || 
      (data_rd[*plain_size + 3] != 0x00)) 
    return 18; // Received data after UNWRAP command is bad

  for (uint8_t i = 0; i < *plain_size; ++i){
    plain_data[i] = data_rd[i+2];
  }

  return 0; // OK
}


uint8_t SC_Activate(){
  
  uint8_t error_code = SC_ATR(); // Receiving ATR
  if(error_code == 0){
    error_code = SC_PPS(); // Using PPS
    if(error_code == 0){ 
      SC_UART.Init.BaudRate = 125000; // Setting new baudrate
      if (HAL_SMARTCARD_Init(&SC_UART) != HAL_OK)
      {
        Error_Handler();
      }
      return 0; // OK
    }
    else return error_code; // PPS Error
  }
  else return error_code; // ATR Error
}


uint8_t SC_Deactivate(){
  
  HAL_GPIO_WritePin(SIM_RST_GPIO_Port, SIM_RST_Pin, GPIO_PIN_RESET); // RST low (active)
  HAL_GPIO_WritePin(SIM_VCC_EN_GPIO_Port, SIM_VCC_EN_Pin, GPIO_PIN_SET); // Power off
  
  SC_UART.Init.BaudRate = 10753; // 4_000_000 / 372
  if (HAL_SMARTCARD_Init(&SC_UART) != HAL_OK)
  {
    Error_Handler();
  }
  
  return 0; // OK
}
