#ifndef __AT24MAC402_H
#define __AT24MAC402_H

#include "stm32f4xx_hal.h"

#define LORA_AT24_DEVICE_ADR      0xA0 // ����� ��� �������� ������/������ � �������
#define LORA_AT24_SWP_ADR         0x60 // ����� ���������� ��������� ������ �� ������
#define LORA_AT24_SN_ADR          0xB0 // ����� ��� ������� � ��������� ������ ����������

#define ZIGBEE_AT24_DEVICE_ADR    0xA2 // ����� ��� �������� ������/������ � �������
#define ZIGBEE_AT24_SWP_ADR       0x62 // ����� ���������� ��������� ������ �� ������
#define ZIGBEE_AT24_SN_ADR        0xB2 // ����� ��� ������� � ��������� ������ ����������


/* ������ �������� ������ (�������� ���������� ��������� */
//#define yyy       0x00


/* ������ �������� ������ */
//#define xxx  0x80

int32_t at24_read_sn(uint32_t adr, uint8_t *);
int32_t at24_read_data(uint32_t device_adr, uint8_t MemAdr, uint8_t *pData, uint32_t size);
int32_t at24_write_data(uint32_t device_adr, uint8_t MemAdr, uint8_t *pData, uint32_t size);
int32_t at24_perm_protect(uint32_t adr);

#endif //__AT24MAC402_H