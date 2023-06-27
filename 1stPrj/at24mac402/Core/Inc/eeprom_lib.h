#ifndef EEPROM_LIB_H
#define EEPROM_LIB_H

#include "main.h"

extern I2C_HandleTypeDef hi2c1;

#define _A24         hi2c1

#define EUI_ADDRESS                     0x58
#define EEPROM_ADDRESS                  0x50

#define GET_EUI48(dataRead)             HAL_I2C_Mem_Read(&_A24, EUI_ADDRESS << 1, 0x9A, 1, dataRead, 6, 1000)
#define GET_SERIAL_NUMBER(dataRead)     HAL_I2C_Mem_Read(&_A24, EUI_ADDRESS << 1, 0x80, 1, dataRead, 16, 1000)

void Eeprom_Write(uint16_t MemAddress, uint8_t *dataWrite, uint16_t dataWrite_Size);
void Eeprom_Read(uint16_t MemAddress, uint8_t *dataRead, uint16_t dataRead_Size);
void Eeprom_Erase();

#endif /*EEPROM_LIB_H*/