#ifndef EEPROM_LIB_H
#define EEPROM_LIB_H

#include "main.h"

extern I2C_HandleTypeDef hi2c1;

#define PRIMARY_CONF_SECT         1
#define RESERV_CONF_SECT          2


HAL_StatusTypeDef read_cfg_eeprom();
uint8_t* get_param_ptr(Cfg_fields field, uint32_t *size);
uint32_t set_param(Cfg_fields field, uint8_t* pdata, uint32_t size);
uint32_t read_device_info(void);
void write_device_info(void);

#endif /*EEPROM_LIB_H*/