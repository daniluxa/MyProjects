/* SC_lib.h - библиотека для работы с ЭБ в виде смарт-карты на МК STM32
*
* Начало работы со смарт-картой:
*
* uint8_t SC_Activate(); // активация смарт-карты
*
* Состоит из подачи питания, отключения сброса и:
* uint8_t SC_ATR(); // проверка факта получения Answer-to-Reset
* uint8_t SC_PPS(); // настройка режима общения МК и смарт-карты
*
*
* После инициализации смарт-карты можно формировать/раскрывать сообщения:
*
* // формирование сообщения encrypted_data длиной encrypted_size
* // из данных plain_data длиной plain_size
* uint8_t SC_Wrap(uint8_t * plain_data, uint8_t plain_size,
*              uint8_t * encrypted_data, uint8_t * encrypted_size);
*
* // расшифровка сообщения msg длиной msg_size, возвращает указатель
* // на расшифрованное сообщение
* uint8_t SC_Unwrap(uint8_t * encrypted_data, uint8_t encrypted_size,
*                uint8_t * plain_data, uint8_t * plain_size);
*
*
* По окончании работы со смарт-картой:
*
* uint8_t SC_Deactivate(); // деактивация смарт-карты
*
*
* Пример использования:
*
* uint8_t SC_error = SC_Activate();
* if (SC_error == 0){
*   static uint8_t test_hw[] = "Hello, world!";
*
*   uint8_t encrypted_data[256] = {0};
*   uint8_t encrypted_size = 0;
*   uint8_t plain_data[256] = {0};
*   uint8_t plain_size = 0;
* 
*   SC_error = SC_Wrap(test_hw, (uint8_t)sizeof(test_hw),
*                      encrypted_data, &encrypted_size);
* 
*   encrypted_data[11]++; // server counter++
*   encrypted_data[15] = 0x00; // from server to client
* 
*   SC_error = SC_Unwrap(encrypted_data, encrypted_size,
*                        plain_data, &plain_size);
* }
* SC_error = SC_Deactivate();
*
*/

#ifndef SC_LIB_H
#define SC_LIB_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

extern  SMARTCARD_HandleTypeDef  hsc1;
#define	SC_UART                  hsc1


/*static uint8_t get_status[] = {0x80,0xF2,0x40,0x00,0x08,0x4F,0x06,0x31,0x32,
                               0x33,0x34,0x35,0x36};*/
                                 
uint8_t SC_ATR();
uint8_t SC_PPS();

uint8_t SC_Wrap(uint8_t * plain_data, uint8_t plain_size,
             uint8_t * encrypted_data, uint8_t * encrypted_size);

uint8_t SC_Unwrap(uint8_t * encrypted_data, uint8_t encrypted_size,
               uint8_t * plain_data, uint8_t * plain_size);

uint8_t SC_Activate();

uint8_t SC_Deactivate();

#endif

