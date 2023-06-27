#ifndef __AT24MAC402_H
#define __AT24MAC402_H

#include "stm32f4xx_hal.h"

#define LORA_AT24_DEVICE_ADR      0xA0 // Адрес для операций чтения/записи с памятью
#define LORA_AT24_SWP_ADR         0x60 // Адрес управления регистром защиты от записи
#define LORA_AT24_SN_ADR          0xB0 // Адрес для доступа к серийному номеру микросхемы

#define ZIGBEE_AT24_DEVICE_ADR    0xA2 // Адрес для операций чтения/записи с памятью
#define ZIGBEE_AT24_SWP_ADR       0x62 // Адрес управления регистром защиты от записи
#define ZIGBEE_AT24_SN_ADR        0xB2 // Адрес для доступа к серийному номеру микросхемы


/* Первая половина памяти (возможна блокировка изменений */
//#define yyy       0x00


/* Вторая половина памяти */
//#define xxx  0x80

int32_t at24_read_sn(uint32_t adr, uint8_t *);
int32_t at24_read_data(uint32_t device_adr, uint8_t MemAdr, uint8_t *pData, uint32_t size);
int32_t at24_write_data(uint32_t device_adr, uint8_t MemAdr, uint8_t *pData, uint32_t size);
int32_t at24_perm_protect(uint32_t adr);

#endif //__AT24MAC402_H