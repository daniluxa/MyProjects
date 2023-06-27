#include "at24mac402.h"

extern I2C_HandleTypeDef hi2c1;

int32_t at24_read_sn(uint32_t adr, uint8_t *pSN)
{
  int32_t status;
  
  //status = HAL_I2C_Mem_Write(&hi2c1, AT24_SN_ADR, 0x58, I2C_MEMADD_SIZE_8BIT, &temp, 1, 100);  
  
  do status = HAL_I2C_Mem_Read(&hi2c1, adr, 0x80, I2C_MEMADD_SIZE_8BIT, pSN, 16, 100); 
  while (status != HAL_OK );
  
  return status;
}

int32_t at24_read_data(uint32_t device_adr, uint8_t MemAdr, uint8_t *pData, uint32_t size)
{
  int32_t status;
 
  do status = HAL_I2C_Mem_Read(&hi2c1, device_adr, MemAdr, I2C_MEMADD_SIZE_8BIT, pData, size, 100);   
  while (status != HAL_OK );
  
  return status;
}

int32_t at24_write_data(uint32_t device_adr, uint8_t MemAdr, uint8_t *pData, uint32_t size)
{
  int32_t status;
  
  /*if ( size == 1 )
    status = I2C_Mem_Write_Byte(&hi2c1, AT24_DEVICE_ADR, MemAdr, *pData, 100);      
  else
  {*/
    int32_t page_remain = 16 - MemAdr % 16;
    int32_t data2write;
    
    if ( page_remain  > size ) page_remain = size;
    
    do status = HAL_I2C_Mem_Write(&hi2c1, device_adr, MemAdr, I2C_MEMADD_SIZE_8BIT, pData, page_remain, 100);      
    while (status != HAL_OK );

    size -= page_remain;
    MemAdr += page_remain;
    pData += page_remain;
    while ( size )
    {
      if ( size > 16 ) data2write = 16;
      else data2write = size;
      
      do status = HAL_I2C_Mem_Write(&hi2c1, device_adr, MemAdr, I2C_MEMADD_SIZE_8BIT, pData, data2write, 100);
      while (status != HAL_OK );
      
      size -= data2write;
      pData += data2write;
      MemAdr += data2write;
    }
 // }
  
  return status;
}

int32_t at24_perm_protect(uint32_t adr)
{
  uint8_t temp = 0;
  return at24_write_data(adr, 0xFF, &temp, 1);  
}