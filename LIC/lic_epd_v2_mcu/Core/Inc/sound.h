#ifndef _SOUND_H_
#define _SOUND_H_

//#include "datatypes.h"
#include "stm32f4xx_hal.h"

#define SOUND_ON                                                                // ���� ����������������, �� ����� �� �����
/*
"p"  | ����� 
"c"  | ��
"C"  | ��-����
"d"  | ��
"D"  | ��-����
"e"  | ��
"f"  | ��
"F"  | ��-����
"g"  | ����
"G"  | ����-����
"a"  | ��
"A"  | ��-����
"b"  | ��*/


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

void play_rt(char const *str, uint8_t alarm_flag, int8_t offset);               // ��������� ������������ �������
void sound_processing(void);                                                    // ����������. ����������� ���������� ������������ �������
void sound_stop(void);                                                          // ������������� ����� �����
uint8_t is_playing(void);

#endif
