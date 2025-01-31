#ifndef GPS_H
#define GPS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "main.h"

/*extern  UART_HandleTypeDef huart6;
#define	GPS_UART           huart6*/
extern  I2C_HandleTypeDef hi2c1;
#define	GPS_I2C	          hi2c1
#define GPS_dev_adr       (0x42 << 1)

typedef enum
{
  NF       = 0,            // No Fix
  DR       = 1,            // Dead Reckoning only
  G2       = 2,            // Stand alone 2D solution
  G3       = 3,            // Stand alone 3D solution
  RK       = 4,            // Combined GPS + dead reckoning solution
  TT       = 5,            // Time only solution
} GPS_FIX_TYPES;

typedef enum
{
  JAN       = 31,
  FEB       = 28,
  FEB_LEAP  = 29,
  MAR       = 31,
  APR       = 30,
  MAY       = 31,
  JUN       = 30,
  JUL       = 31,
  AUG       = 31,
  SEP       = 30,
  OCT       = 31,
  NOV       = 30,
  DEC       = 31
} GPS_MONTHS_LEN;

typedef struct GPS_t{
  
  uint16_t year;
  uint8_t  month;
  uint8_t  day;
  
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
  
  uint32_t time_acc;    // ����������� ������� ������������ UTC � ������������
  int32_t fraction_ns;  // ���� ������� � ������������ (UTC)

  
  uint8_t valid_flags;
  bool valid_date;      // true, ����� �������� year, month � day �������
  bool valid_time;      // true, ����� �������� hours, minutes � seconds �������
  uint8_t fix_type;
  
  
  int32_t latitude;       // ������  � 1e-7 ��������
  int32_t longitude;      // ������� � 1e-7 ��������
  int16_t altitude;       // ������  � ������
  
  uint8_t horizontal_acc; // ����������� ������ � ������� � ������
  uint8_t vertical_acc;   // ����������� ������ � ������
  
  int32_t speed_ms;

} GPS_t;

extern GPS_t GPS;
extern int8_t GPS_timezone_h;
extern int8_t GPS_timezone_m;

void     GPS_Enable();                  // ������ ������� � �������������
uint32_t GPS_Config();                  // ������������ ������
void     GPS_Disable();                 // ���������� �������
void     PollGPSData();                 // �������� ������� �� ��������� ������
void     GetGPSData();                  // ��������� ������ � ��������� � ���������
uint32_t GPS_validate(char * GPSstr);   // �������� ����������� ���������� ������
uint32_t GPS_parse(char * GPSstr);      // ������� ������ � ���������

// ���������� ���������� ���� � ������
uint32_t days_in_month(uint8_t month, bool is_year_leap);      


// ���������� �������� ������, ����� ���������� ����
static uint8_t GSV_off[] = {0x24,0x50,0x55,0x42,0x58,0x2c,0x34,0x30,0x2c,0x47,0x53,0x56,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2a,0x35,0x39,0x0d,0x0a};
static uint8_t GSA_off[] = {0x24,0x50,0x55,0x42,0x58,0x2c,0x34,0x30,0x2c,0x47,0x53,0x41,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2a,0x34,0x45,0x0d,0x0a};
static uint8_t VTG_off[] = {0x24,0x50,0x55,0x42,0x58,0x2c,0x34,0x30,0x2c,0x56,0x54,0x47,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2a,0x35,0x45,0x0d,0x0a};
static uint8_t GLL_off[] = {0x24,0x50,0x55,0x42,0x58,0x2c,0x34,0x30,0x2c,0x47,0x4c,0x4c,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2a,0x35,0x43,0x0d,0x0a};
static uint8_t GGA_off[] = {0x24,0x50,0x55,0x42,0x58,0x2c,0x34,0x30,0x2c,0x47,0x47,0x41,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2a,0x35,0x41,0x0d,0x0a};
static uint8_t RMC_off[] = {0x24,0x50,0x55,0x42,0x58,0x2c,0x34,0x30,0x2c,0x52,0x4d,0x43,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2c,0x30,0x2a,0x34,0x37,0x0d,0x0a};


// ������������ DDC (I2C) �� 400000 ���/� � UBX/NMEA ���������
//static uint8_t I2C_conf[]  = {0x24,0x50,0x55,0x42,0x58,0x2c,0x34,0x31,0x2c,0x30,0x2c,0x30,0x30,0x30,0x33,0x2c,0x30,0x30,0x30,0x33,0x2c,0x34,0x30,0x30,0x30,0x30,0x30,0x2c,0x30,0x2a,0x31,0x45,0x0d,0x0a};
static uint8_t I2C_conf[]  = {0xB5,0x62,0x06,0x00,0x14,0x00,0x00,0x00,0x00,0x00,0x84,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x00,0x02,0x00,0x00,0x00,0xA6,0xBA};

// ������������ UART �� 115200 ���/� � UBX/NMEA ���������
//static uint8_t UART_conf[] =  {0x24,0x50,0x55,0x42,0x58,0x2c,0x34,0x31,0x2c,0x31,0x2c,0x30,0x30,0x30,0x33,0x2c,0x30,0x30,0x30,0x33,0x2c,0x31,0x31,0x35,0x32,0x30,0x30,0x2c,0x30,0x2a,0x31,0x43,0x0d,0x0a};
static uint8_t UART_conf[]  = {0xB5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0xC0,0x08,0x00,0x00,0x00,0xC2,0x01,0x00,0x03,0x00,0x03,0x00,0x02,0x00,0x00,0x00,0xAE,0x66};


// �������-������ PUBX POS
static uint8_t POS_poll[] = {0x24,0x50,0x55,0x42,0x58,0x2c,0x30,0x30,0x2a,0x33,0x33,0x0d,0x0a};
static char POS_cmp[] = "$PUBX,00";

// �������-������ UBX NAV-PVT
static uint8_t NAV_poll[] = {0xB5,0x62,0x01,0x07,0x00,0x00,0x08,0x19};
static char NAV_cmp[] = {0xB5,0x62,0x01,0x07,0x5C,0x00};


#endif /* GPS_H */

