#include "gps.h"

GPS_t GPS = {0,0,0,0,0,0,0,0,0,false,false,0,0,0,0,0,0,0};

// Часовые пояса
int8_t GPS_timezone_h = 3;
int8_t GPS_timezone_m = 0;


void GPS_Enable(){
  
  HAL_GPIO_WritePin(GPS_RES_GPIO_Port, GPS_RES_Pin, GPIO_PIN_SET);
  
  if(HAL_GPIO_ReadPin(GPS_EN_GPIO_Port, GPS_EN_Pin) == GPIO_PIN_RESET)
  {
    HAL_GPIO_WritePin(GPS_EN_GPIO_Port, GPS_EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
  }
  HAL_GPIO_WritePin(GPS_EN_GPIO_Port, GPS_EN_Pin, GPIO_PIN_RESET);
  
  // Минимальное время, спустя которое модуль отзывается на команды
  HAL_Delay(340);
  GPS_Config();
  
  return;
}


uint32_t GPS_Config(){
  
  // Отключение ненужных дыннах, чтобы освободить шину
  /*HAL_UART_Transmit(&GPS_UART, GSV_off, sizeof(GSV_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  HAL_UART_Transmit(&GPS_UART, GSA_off, sizeof(GSA_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  HAL_UART_Transmit(&GPS_UART, VTG_off, sizeof(VTG_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  HAL_UART_Transmit(&GPS_UART, GLL_off, sizeof(GLL_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  HAL_UART_Transmit(&GPS_UART, GGA_off, sizeof(GGA_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  HAL_UART_Transmit(&GPS_UART, RMC_off, sizeof(RMC_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);*/
  
  HAL_I2C_Master_Transmit(&GPS_I2C, GPS_dev_adr, GSV_off, sizeof(GSV_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  HAL_I2C_Master_Transmit(&GPS_I2C, GPS_dev_adr, GSA_off, sizeof(GSA_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  HAL_I2C_Master_Transmit(&GPS_I2C, GPS_dev_adr, VTG_off, sizeof(VTG_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  HAL_I2C_Master_Transmit(&GPS_I2C, GPS_dev_adr, GLL_off, sizeof(GLL_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  HAL_I2C_Master_Transmit(&GPS_I2C, GPS_dev_adr, GGA_off, sizeof(GGA_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  HAL_I2C_Master_Transmit(&GPS_I2C, GPS_dev_adr, RMC_off, sizeof(RMC_off) / sizeof(uint8_t), 1000);
  HAL_Delay(1);
  
  // Конфигурация UART на 115200 бит/с и UBX/NMEA протоколы
  /*uint8_t rx_buffer[256] = {0};
  uint8_t char_get = '0';
  uint8_t i = 0;
  uint8_t k = 0;
  
  HAL_UART_Transmit(&GPS_UART, UART_conf, sizeof(UART_conf) / sizeof(uint8_t), 1000);
  while(1){
    if (i == 255) return 1; // ошибка конфигурации UART
    i++;
    
    HAL_UART_Receive(&GPS_UART, &char_get, (uint16_t)1, (uint32_t)10);
    if(char_get != 0xFF){
      rx_buffer[k] = char_get;
      k++;
      if(k > 1 && rx_buffer[k-1] == 0x37 && rx_buffer[k-2] == 0x0E) break;
      // потому что верный ответ: B5 62 05 01 02 00 06 00 0E 37
    }
  }*/
 
  // Конфигурация DDC (I2C) на 400000 бит/с и UBX/NMEA протоколы
  uint8_t rx_buffer[256] = {0};
  uint8_t char_get = '0';
  uint8_t i = 0;
  uint8_t k = 0;
   
  HAL_I2C_Master_Transmit(&GPS_I2C, GPS_dev_adr, I2C_conf, sizeof(I2C_conf) / sizeof(uint8_t), 1000);
  while(1){
    if (i == 255) return 1; // ошибка конфигурации DDC (I2C)
    i++;
    
    HAL_I2C_Master_Receive(&GPS_I2C, GPS_dev_adr, &char_get, (uint16_t)1, (uint32_t)10);
    if(char_get != 0xFF){
      rx_buffer[k] = char_get;
      k++;
      if(k > 1 && rx_buffer[k-1] == 0x37 && rx_buffer[k-2] == 0x0E) break;
      // потому что верный ответ: B5 62 05 01 02 00 06 00 0E 37
    }
  }
    
  // Настройка режима работы только по внешнему сигналу и прочи енастройки по питанию/таймингам
  //HAL_UART_Transmit(GPS_UART, PM2_conf, sizeof(PM2_conf) / sizeof(uint8_t), 1000);
  //HAL_Delay(10);
  
  /*//TODO: сохранение и загрузка не работают
  // Сохранение конфигурации в энергонезависимую память
  HAL_UART_Transmit(GPS_UART, Save_conf, sizeof(Save_conf) / sizeof(uint8_t), 1000);
  HAL_Delay(10);
  
  // Загрузка конфигурации из энергонезависимой памяти
  HAL_UART_Transmit(GPS_UART, Load_conf, sizeof(Load_conf) / sizeof(uint8_t), 1000);
  HAL_Delay(10);*/
  
  return 0;
}


void GPS_Disable(){
  
  HAL_GPIO_WritePin(GPS_EN_GPIO_Port, GPS_EN_Pin, GPIO_PIN_SET);
  
  return;
}


void PollGPSData() {
  
  //HAL_UART_Transmit(&GPS_UART, POS_poll, sizeof(POS_poll) / sizeof(uint8_t), 100);
  HAL_I2C_Master_Transmit(&GPS_I2C, GPS_dev_adr, NAV_poll, sizeof(NAV_poll) / sizeof(uint8_t), 100);

  return;
}

         
void GetGPSData(){
  
  uint8_t rx_buffer[256] = {0};
  uint8_t GPSstr[256] = {0};
  uint8_t validate_attempts = 0;
  uint8_t i;
  
  do {
    i = 0;
    memset(rx_buffer,'\0',256*sizeof(uint8_t));
    
    //HAL_UART_Receive(&GPS_UART, rx_buffer, (uint16_t)256, (uint32_t)1000);
    HAL_I2C_Master_Receive(&GPS_I2C, GPS_dev_adr, rx_buffer, (uint16_t)256, (uint32_t)1000);   
    
    // Ищем индекс первого не 0xFF элемента
    while (rx_buffer[i++] == 0xFF){
      if (i == 255) break;
    } 
    i--;
    
    if (i != 254)
      memcpy(GPSstr,&(rx_buffer[i]),256);
    else
      memset(GPSstr,'\0',256*sizeof(uint8_t));
    
    validate_attempts++;
    if(validate_attempts > 10) break;
  }
  while ( (GPS_validate((char*)GPSstr) != 0) || (GPS_parse((char*)GPSstr) != 0) );
  
  return;
}


uint32_t GPS_validate(char *GPSstr){
  
  uint32_t i = 0;
  
  // если GPSstr начинается с '0xB5 0x62', значит это UBX протокол
  if ( (GPSstr[i] == 0xB5) && (GPSstr[i+1] == 0x62) ){
    uint8_t check_A = GPSstr[98];
    uint8_t check_B = GPSstr[99];
    uint8_t CK_A = 0;
    uint8_t CK_B = 0;

    for (uint8_t i = 2; i < 98; i++)
    {
        CK_A = CK_A + GPSstr[i];
        CK_B = CK_B + CK_A;
    }
    return ( (CK_A == check_A) && (CK_B == check_B) ) ? 0 : 1;
  }
  
  else
    return 2; // не UBX протокол (unknown command)
}


uint32_t GPS_parse(char * GPSstr){
  
  int16_t year   = *((uint16_t*)  (GPSstr+10));
  int8_t  month  =   (uint8_t)   *(GPSstr+12);
  int8_t  day    =   (uint8_t)   *(GPSstr+13);
  
  int8_t hours   =   (uint8_t) (*(GPSstr+14) + GPS_timezone_h);
  int8_t minutes =   (uint8_t) (*(GPSstr+15) + GPS_timezone_m);
  
  bool perenos_plus = false;
  bool perenos_minus = false;
  
  bool is_year_leap = ( ((year%400)==0) || (((year%4)==0) && ((year%100)!=0)) ) ? true : false;
  
  
  if (!strncmp(GPSstr, NAV_cmp, 6)){
    
    /**********************************ВРЕМЯ**********************************/
    // Секунды
    GPS.seconds =  (uint8_t)  *(GPSstr+16);
    
    // Минуты
    if (minutes < 0){
      GPS.minutes = 60 + minutes;
      perenos_minus = true;                     // перенос на час назад
    }
    else{
      GPS.minutes = minutes % 60;
      if (minutes >= 60) perenos_plus = true;   // перенос на час вперед
    }
    
    // Часы
    if (perenos_minus){
      hours--;
      if (hours < 0){
        GPS.hours = 24 + hours;
        perenos_minus = true;           // перенос на сутки назад
      }
      else{
        GPS.hours = hours;
        perenos_minus = false;          // без переноса на сутки назад
      }
    }
    else if (perenos_plus){
      hours++;
      GPS.hours = hours % 24;
      if (hours >= 24)
        perenos_plus = true;            // перенос на сутки вперед
      else perenos_plus = false;        // без переноса на сутки вперед
    }
    else{
      if (hours < 0){
        GPS.hours = 24 + hours;
        perenos_minus = true;           // перенос на сутки назад
      }
      else if (hours >= 24){
        GPS.hours = hours % 24;
        perenos_plus = true;            // перенос на сутки вперед
      }
      else GPS.hours = hours;
    }
    
    /**********************************ДАТА***********************************/
    // День
    if (perenos_minus){
      day--;
      if (day < 1){
        GPS.day = days_in_month(month-1,is_year_leap) + day;
        perenos_minus = true;           // перенос на месяц назад
      }
      else{
        GPS.day = day;
        perenos_minus = false;           // без переноса на месяц назад
      }
    }
    else if (perenos_plus){
      day++;
      if (day > days_in_month(month,is_year_leap)){
        GPS.day = 1;
        perenos_plus = true;            // перенос на месяц вперед
      }
      else{
        GPS.day = day;
        perenos_plus = false;           // без переноса на месяц назад
      }
    }
    else{
      GPS.day = day;
    }
    
    // Месяц
    if (perenos_minus){
      month--;
      if (month < 1){
        GPS.month = 12;
        perenos_minus = true;           // перенос на год назад
      }
      else{
        GPS.month = month;
        perenos_minus = false;          // без переноса на год назад
      }
    }
    else if (perenos_plus){
      month++;
      if (month > 12){
        GPS.month = 1;
        perenos_plus = true;            // перенос на год вперед
      }
      else{
        GPS.month = month;
        perenos_plus = false;           // без переноса на год назад
      }
    }
    else{
      GPS.month = month;
    }
    
    // Год
    if (perenos_minus){
      year--;
      GPS.year = year;
    }
    else if (perenos_plus){
      year++;
      GPS.year = year;
    }
    else 
      GPS.year = year;

    
    
    // Флаги валидности
    GPS.valid_flags = (uint8_t) *(GPSstr+17);
    if (GPS.valid_flags & 0x02) GPS.valid_time = true;
    else GPS.valid_time = false;
    if (GPS.valid_flags & 0x01) GPS.valid_date = true;
    else GPS.valid_date = false;
    
    // Погрешность времени / fix type
    GPS.time_acc     = *( (uint32_t*)(GPSstr+18) );
    GPS.fraction_ns  = *( (uint32_t*)(GPSstr+22) );
    GPS.fix_type     =    (uint8_t) *(GPSstr+26);
    
    // Координаты
    GPS.longitude =              *( (int*)(GPSstr+30) );
    GPS.latitude  =              *( (int*)(GPSstr+34) );
    GPS.altitude  = (uint16_t) ( *( (int*)(GPSstr+38) ) / 1000 );
    
    // Погрешности координат
    uint32_t horizontal_acc_mm = *( (uint32_t*)(GPSstr+46) );
    if (horizontal_acc_mm > 255000) GPS.horizontal_acc = 0xFF;
    else GPS.horizontal_acc = (uint8_t) (horizontal_acc_mm / 1000 + 1);
    
    uint32_t vertical_acc_mm   = *( (uint32_t*)(GPSstr+50) );
    if (vertical_acc_mm > 255000) GPS.vertical_acc = 0xFF;
    else GPS.vertical_acc = (uint8_t) (vertical_acc_mm / 1000 + 1);
    
    // Скорость
    GPS.speed_ms = *( (int*)(GPSstr+66) ) / 1000 + 1;
      
    return 0;
  }
  return 1;
}


uint32_t days_in_month(uint8_t month, bool is_year_leap){
  
  uint32_t ret = 0;
  
  switch (month){
  case 1:
    ret = JAN;
    break;
  case 2:
    if (is_year_leap) ret = FEB_LEAP;
    else ret = FEB;
    break;
  case 3:
    ret = MAR;
    break;
  case 4:
    ret = APR;
    break;
  case 5:
    ret = MAY;
    break;
  case 6:
    ret = JUN;
    break;
  case 7:
    ret = JUL;
    break;
  case 8:
    ret = AUG;
    break;
  case 9:
    ret = SEP;
    break;
  case 10:
    ret = OCT;
    break;
  case 11:
    ret = NOV;
    break;
  case 12:
    ret = DEC;
    break;
  }
  
  return ret;
}
