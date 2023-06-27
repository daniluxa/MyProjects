#ifndef _SOUND_H_
#define _SOUND_H_

//#include "datatypes.h"
#include "stm32f4xx_hal.h"

#define SOUND_ON                                                                // Если закомментировать, то звука не будет
/*
"p"  | пауза 
"c"  | до
"C"  | до-диез
"d"  | ре
"D"  | ре-диез
"e"  | ми
"f"  | фа
"F"  | фа-диез
"g"  | соль
"G"  | соль-диез
"a"  | ля
"A"  | ля-диез
"b"  | си*/


#define FALSE 0
#define TRUE  1


#define PRESCALER 0
#define PERIOD    1

extern const char alarm1[];
extern const char alarm2[];
extern const char alarm3[];
extern const char alarm4[];
extern const char rt_notready[];
extern const char rt_wdt[];
extern const char rt_turnon[];

void play_rt(char const *str, uint8_t alarm_flag, int8_t offset);               // запускаем проигрывание мелодии
void sound_processing(void);                                                    // обработчик. отслеживает правильное проигрывание мелодии
void sound_stop(void);                                                          // останавливаем любые звуки
uint8_t is_playing(void);

#endif
