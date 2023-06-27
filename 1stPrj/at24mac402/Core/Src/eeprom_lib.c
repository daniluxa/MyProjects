#include "stm32f2xx_hal.h"
#include "stm32f2xx_it.h"
#include "string.h"
#include "main.h"

/*------------------------------DEFINES---------------------------------------*/

#define EEPROM_ADDRESS              0x50
#define PAGES_NUMBERS               16
#define BYTES_NUMBERS_OF_PAGE       16
#define MEM_SIZE                    PAGES_NUMBERS * BYTES_NUMBERS_OF_PAGE

/*---------------------------WRITE FUNCTION-----------------------------------*/

 /**
  * @brief writes up to 256 bytes to memory
  * @param pointer to data write
  * @param Amount of data you want write (sizeof(dataWrite))
  * @retval -
  */

void Eeprom_Write(uint16_t MemAddress, uint8_t *dataWrite, uint16_t dataWrite_Size)
{       
       if ((dataWrite_Size + MemAddress) > MEM_SIZE)
       {
           dataWrite_Size = MEM_SIZE - MemAddress;
       }
       uint8_t Attempt;
       for(int i = 0; i < (dataWrite_Size / PAGES_NUMBERS); i++) // i - page
       {
          while((dataWrite_Size - BYTES_NUMBERS_OF_PAGE) > 0)
          {
               Attempt = 0;
               while(HAL_I2C_Mem_Write(&_A24,(uint16_t)(EEPROM_ADDRESS << 1), MemAddress,1, dataWrite,(uint16_t)BYTES_NUMBERS_OF_PAGE, 1000)!= HAL_OK && Attempt < 10)
               {
                   Attempt++;
                   HAL_Delay(1);
               }
               
               dataWrite_Size -= BYTES_NUMBERS_OF_PAGE;
               dataWrite += BYTES_NUMBERS_OF_PAGE;
               MemAddress += BYTES_NUMBERS_OF_PAGE;
          }      
          Attempt = 0;
          while(HAL_I2C_Mem_Write(&_A24, (uint16_t)(EEPROM_ADDRESS << 1), MemAddress, 1, dataWrite, dataWrite_Size, 1000)!= HAL_OK && Attempt < 10)
          {
               Attempt++;
               HAL_Delay(1);
          }
       }
  }

/*----------------------------READ FUNCTION-----------------------------------*/

 /**
  * @brief  reads up to 256 bytes from memory
  * @param  pointer to data read 
  * @param  Amount of data you want read (sizeof(dataRead)
  * @retval -
  */

void Eeprom_Read(uint16_t MemAddress, uint8_t *dataRead, uint16_t dataRead_Size)
{
    if ((dataRead_Size + MemAddress) > MEM_SIZE)
    {
      dataRead_Size = MEM_SIZE - MemAddress;
    }
     uint8_t Attempt;
     for(int i = 0; i < (dataRead_Size / PAGES_NUMBERS); i++) // i - page
     {          
          while((dataRead_Size - BYTES_NUMBERS_OF_PAGE) > 0)
          {
                Attempt = 0;
                while(HAL_I2C_Mem_Read(&_A24, (uint16_t)(EEPROM_ADDRESS << 1), MemAddress, 1, dataRead,(uint16_t)BYTES_NUMBERS_OF_PAGE, 1000)!= HAL_OK && Attempt < 10)
                {
                    Attempt++;
                    HAL_Delay(1);
                }
        
                dataRead_Size -= BYTES_NUMBERS_OF_PAGE;
                dataRead += BYTES_NUMBERS_OF_PAGE;
                MemAddress += BYTES_NUMBERS_OF_PAGE;
          }
          Attempt = 0;
          while(HAL_I2C_Mem_Read(&_A24, (uint16_t)(EEPROM_ADDRESS << 1), MemAddress, 1, dataRead, dataRead_Size, 1000)!= HAL_OK && Attempt < 10)
          {
		Attempt++;
                HAL_Delay(1);
          }
     }
}

/*---------------------------ERASE FUNCTION-----------------------------------*/

 /**
  * @brief  clear the whole memory
  * @param  -
  * @retval -
  */

void Eeprom_Erase()
{       
    uint8_t data[MEM_SIZE];
    memset(data, 0xff, MEM_SIZE);
    Eeprom_Write(0x00, data, MEM_SIZE);
}
