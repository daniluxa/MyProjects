#include "W25Qxx.h"
#include "some_stuff.h"

#define W25QXX_DUMMY_BYTE         0xA5

#define SELECT    GPIO_PIN_RESET
#define UNSELECT  GPIO_PIN_SET
#define	W25qxx_Delay(delay)	 HAL_Delay(delay)
#define W25qxx_ChipSelect(x)     HAL_GPIO_WritePin(_W25QXX_CS_GPIO, _W25QXX_CS_PIN, x)

#define W25Q_PAGE_PROGRAM       0x02
#define W25Q_FAST_READ          0x0B
#define W25Q_SECTOR_ERASE       0x20
#define W25Q_ENABLE_RESET       0x66
#define W25Q_WRITE_ENABLE       0x06
#define W25Q_WRITE_DISABLE      0x04
#define W25Q_RESET              0x99
#define W25Q_JEDEC_ID           0x9F
#define W25Q_READ_UNIQUE_ID     0x4B
#define W25Q_READ_STATUS_REG1   0x05
#define W25Q_READ_STATUS_REG2   0x35

#define SET_ADDR(x, y)           do{                             \
                                  (x)[0] = (y >> 16) & 0xFF;     \
                                  (x)[1] = (y >> 8)  & 0xFF;     \
                                  (x)[2] =  y        & 0xFF;     \
                                 }while(0)

w25qxx_t	w25qxx;

void W25qxx_SetFlagFirmware(bool flag){
  uint8_t buff[1] = {flag};
  W25qxx_WritePage(buff, W25qxx_SectorToPage(FLASH_FIRM_PARAM_SECTOR), 64, 1);
}

bool W25qxx_GetFlagFirmware(){
   uint8_t buff[1];
   W25qxx_ReadPage(buff, W25qxx_SectorToPage(FLASH_FIRM_PARAM_SECTOR), 64, 1);
   return (buff[0] == 1);
}

uint32_t W25qxx_CRCFirmware(uint32_t firm_len)
{
  uint32_t page_num = 0;
  uint32_t crc = 0;
  uint8_t page_data[256];
  uint32_t  remain = firm_len % 256;  
  firm_len = firm_len / 256;
  
  while( firm_len-- > 0 ){
    W25qxx_ReadPage(page_data, FLASH_FIRM_START_PAGE + page_num++, 0, 256);
    crc = crc32_byte(crc, page_data, 256);
    if ( page_num % 10 == 0 ) HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
  }
  if ( remain )
  {
    W25qxx_ReadPage(page_data, FLASH_FIRM_START_PAGE + page_num, 0, remain);
    crc = crc32_byte(crc, page_data, remain);  
  }
  return crc;
}

uint8_t	W25qxx_SPI(uint8_t Data)
{
  uint8_t ret;
  HAL_SPI_TransmitReceive(&_W25QXX_SPI,&Data,&ret,1,100);
  
  return ret;	
}

uint32_t W25qxx_ReadID(void)
{
  uint32_t ID;
  uint8_t rx_buff[3];
  
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(0);
  W25qxx_SPI(W25Q_JEDEC_ID);
  HAL_SPI_Receive(&_W25QXX_SPI, rx_buff, 3, 100);	
  W25qxx_ChipSelect(UNSELECT);
  ID = ((uint32_t)(rx_buff[0]) << 16) | ((uint32_t)(rx_buff[1]) << 8) | (uint32_t)rx_buff[2];
  return ID;
}

void W25qxx_ReadUniqID(void)
{
  uint8_t cmd[5] = {W25Q_READ_UNIQUE_ID};
  
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(0);
  HAL_SPI_Transmit(&_W25QXX_SPI, cmd, 5, 100);
  HAL_SPI_Receive(&_W25QXX_SPI, w25qxx.UniqID, 8, 100);	
  W25qxx_ChipSelect(UNSELECT);
}

void W25qxx_WriteEnable(void)
{
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(0);
  W25qxx_SPI(W25Q_WRITE_ENABLE);
  W25qxx_ChipSelect(UNSELECT);
  W25qxx_Delay(1);
}

void W25qxx_WriteDisable(void)
{
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(0);
  W25qxx_SPI(W25Q_WRITE_DISABLE);
  W25qxx_ChipSelect(UNSELECT);
  W25qxx_Delay(1);
}

uint8_t W25qxx_ReadStatusRegister(uint8_t	SelectStatusRegister_1_2_3)
{
	uint8_t	status=0;
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(0);
	if(SelectStatusRegister_1_2_3==1)
	{
		W25qxx_SPI(W25Q_READ_STATUS_REG1);
		status=W25qxx_SPI(W25QXX_DUMMY_BYTE);	
		w25qxx.StatusRegister1 = status;
	}
	else if(SelectStatusRegister_1_2_3==2)
	{
		W25qxx_SPI(W25Q_READ_STATUS_REG2);
		status=W25qxx_SPI(W25QXX_DUMMY_BYTE);	
		w25qxx.StatusRegister2 = status;
	}
	else
	{
		W25qxx_SPI(0x15);
		status=W25qxx_SPI(W25QXX_DUMMY_BYTE);	
		w25qxx.StatusRegister3 = status;
	}	
  W25qxx_ChipSelect(UNSELECT);
	return status;
}

void W25qxx_WriteStatusRegister(uint8_t	SelectStatusRegister_1_2_3,uint8_t Data)
{
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(1);
	if(SelectStatusRegister_1_2_3==1)
	{
		W25qxx_SPI(0x01);
		w25qxx.StatusRegister1 = Data;
	}
	else if(SelectStatusRegister_1_2_3==2)
	{
		W25qxx_SPI(0x31);
		w25qxx.StatusRegister2 = Data;
	}
	else
	{
		W25qxx_SPI(0x11);
		w25qxx.StatusRegister3 = Data;
	}
	W25qxx_SPI(Data);
  W25qxx_ChipSelect(UNSELECT);
}

void W25qxx_WaitForWriteEnd(void)
{
  W25qxx_Delay(1);
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(0);
  W25qxx_SPI(W25Q_READ_STATUS_REG1);
  do {
    w25qxx.StatusRegister1 = W25qxx_SPI(W25QXX_DUMMY_BYTE);
    W25qxx_Delay(1);
  } while ( (w25qxx.StatusRegister1 & 0x01) == 0x01 );
  W25qxx_ChipSelect(UNSELECT);
}

bool W25qxx_Init(void)
{
  uint32_t	id;
  
  w25qxx.Lock=1;	
  //while(HAL_GetTick()<100) W25qxx_Delay(1);
  HAL_Delay(100);
  
  W25qxx_Reset();
  
  id = W25qxx_ReadID();

  switch( id&0x0000FFFF )
  {
    case 0x401A:	// 	w25q512
            w25qxx.ID=W25Q512;
            w25qxx.BlockCount=1024;
    break;
    case 0x4019:	// 	w25q256
            w25qxx.ID=W25Q256;
            w25qxx.BlockCount=512;
    break;
    case 0x4018:	// 	w25q128
            w25qxx.ID=W25Q128;
            w25qxx.BlockCount=256;
    break;
    case 0x4017:	//	w25q64
            w25qxx.ID=W25Q64;
            w25qxx.BlockCount=128;
    break;
    case 0x4016:	//	w25q32
            w25qxx.ID=W25Q32;
            w25qxx.BlockCount=64;
    break;
    case 0x4015:	//	w25q16
            w25qxx.ID=W25Q16;
            w25qxx.BlockCount=32;
    break;
    case 0x4014:	//	w25q80
            w25qxx.ID=W25Q80;
            w25qxx.BlockCount=16;
    break;
    case 0x4013:	//	w25q40
            w25qxx.ID=W25Q40;
            w25qxx.BlockCount=8;
    break;
    case 0x4012:	//	w25q20
            w25qxx.ID=W25Q20;
            w25qxx.BlockCount=4;
    break;
    case 0x4011:	//	w25q10
            w25qxx.ID=W25Q10;
            w25qxx.BlockCount=2;
    break;
    default:
            w25qxx.Lock=0;	
            return false;
                    
  }		
  w25qxx.PageSize=256;
  w25qxx.SectorSize=0x1000;
  w25qxx.SectorCount=w25qxx.BlockCount*16;
  w25qxx.PageCount=(w25qxx.SectorCount*w25qxx.SectorSize)/w25qxx.PageSize;
  w25qxx.BlockSize=w25qxx.SectorSize*16;
  w25qxx.CapacityInKiloByte=(w25qxx.SectorCount*w25qxx.SectorSize)/1024;
  w25qxx.StatusRegister1 = W25qxx_ReadStatusRegister(1);
  w25qxx.StatusRegister2 = W25qxx_ReadStatusRegister(2);
  W25qxx_ReadUniqID();
  //w25qxx.StatusRegister3 = W25qxx_ReadStatusRegister(3);
  w25qxx.Lock=0;	
  return true;
}	

void W25qxx_EraseChip(void)
{
  while( w25qxx.Lock == 1 ) W25qxx_Delay(1);
  w25qxx.Lock = 1;	
  W25qxx_WriteEnable();
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(1);
  W25qxx_SPI(0xC7);
  W25qxx_ChipSelect(UNSELECT);
  W25qxx_WaitForWriteEnd();
  W25qxx_Delay(10);
  w25qxx.Lock=0;	
}

void W25qxx_EraseSector(uint32_t SectorAddr)
{
  uint8_t cmd[4] = {W25Q_SECTOR_ERASE};
  
  while(w25qxx.Lock==1) W25qxx_Delay(1);
  w25qxx.Lock=1;	
  W25qxx_WaitForWriteEnd();
  SectorAddr = SectorAddr * w25qxx.SectorSize;
  W25qxx_WriteEnable();
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(0);
//	if(w25qxx.ID>=W25Q256)
//		W25qxx_SPI((SectorAddr & 0xFF000000) >> 24);
  SET_ADDR(cmd+1, SectorAddr);
  HAL_SPI_Transmit(&_W25QXX_SPI, cmd, 4, 100);  
  W25qxx_ChipSelect(UNSELECT);
  W25qxx_WaitForWriteEnd();
  W25qxx_Delay(1);
  w25qxx.Lock=0;
}

void W25qxx_EraseBlock(uint32_t BlockAddr)
{
	while(w25qxx.Lock==1)
		W25qxx_Delay(1);
	w25qxx.Lock=1;	
	W25qxx_WaitForWriteEnd();
	BlockAddr = BlockAddr * w25qxx.SectorSize*16;
  W25qxx_WriteEnable();
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(1);
  W25qxx_SPI(0xD8);
	if(w25qxx.ID>=W25Q256)
		W25qxx_SPI((BlockAddr & 0xFF000000) >> 24);
  W25qxx_SPI((BlockAddr & 0xFF0000) >> 16);
  W25qxx_SPI((BlockAddr & 0xFF00) >> 8);
  W25qxx_SPI(BlockAddr & 0xFF);
	W25qxx_ChipSelect(UNSELECT);
  W25qxx_WaitForWriteEnd();
	W25qxx_Delay(1);
	w25qxx.Lock=0;
}

uint32_t W25qxx_PageToSector(uint32_t	PageAddress)
{
	return ((PageAddress*w25qxx.PageSize)/w25qxx.SectorSize);
}

uint32_t W25qxx_PageToBlock(uint32_t	PageAddress)
{
	return ((PageAddress*w25qxx.PageSize)/w25qxx.BlockSize);
}

uint32_t W25qxx_SectorToBlock(uint32_t	SectorAddress)
{
	return ((SectorAddress*w25qxx.SectorSize)/w25qxx.BlockSize);
}

uint32_t W25qxx_SectorToPage(uint32_t	SectorAddress)
{
	return (SectorAddress*w25qxx.SectorSize)/w25qxx.PageSize;
}

uint32_t W25qxx_BlockToPage(uint32_t	BlockAddress)
{
	return (BlockAddress*w25qxx.BlockSize)/w25qxx.PageSize;
}

bool W25qxx_IsEmptyPage(uint32_t Page_Address,uint32_t OffsetInByte,uint32_t NumByteToCheck_up_to_PageSize)
{
	while(w25qxx.Lock==1)
	W25qxx_Delay(1);
	w25qxx.Lock=1;	
	if(((NumByteToCheck_up_to_PageSize+OffsetInByte)>w25qxx.PageSize)||(NumByteToCheck_up_to_PageSize==0))
		NumByteToCheck_up_to_PageSize=w25qxx.PageSize-OffsetInByte;	
	uint8_t	pBuffer[32];
	uint32_t	WorkAddress;
	uint32_t	i;
	for(i=OffsetInByte; i<w25qxx.PageSize; i+=sizeof(pBuffer))
	{
		W25qxx_ChipSelect(SELECT);
                HAL_Delay(1);
		WorkAddress=(i+Page_Address*w25qxx.PageSize);
		W25qxx_SPI(0x0B);
		if(w25qxx.ID>=W25Q256)
			W25qxx_SPI((WorkAddress & 0xFF000000) >> 24);
		W25qxx_SPI((WorkAddress & 0xFF0000) >> 16);
		W25qxx_SPI((WorkAddress & 0xFF00) >> 8);
		W25qxx_SPI(WorkAddress & 0xFF);
		W25qxx_SPI(0);
		HAL_SPI_Receive(&_W25QXX_SPI,pBuffer,sizeof(pBuffer),100);	
		W25qxx_ChipSelect(UNSELECT);	
		for(uint8_t x=0;x<sizeof(pBuffer);x++)
		{
			if(pBuffer[x]!=0xFF)
				goto NOT_EMPTY;		
		}			
	}	
	if((w25qxx.PageSize+OffsetInByte)%sizeof(pBuffer)!=0)
	{
		i-=sizeof(pBuffer);
		for( ; i<w25qxx.PageSize; i++)
		{
			W25qxx_ChipSelect(SELECT);
                        HAL_Delay(1);
			WorkAddress=(i+Page_Address*w25qxx.PageSize);
			W25qxx_SPI(0x0B);
			if(w25qxx.ID>=W25Q256)
				W25qxx_SPI((WorkAddress & 0xFF000000) >> 24);
			W25qxx_SPI((WorkAddress & 0xFF0000) >> 16);
			W25qxx_SPI((WorkAddress & 0xFF00) >> 8);
			W25qxx_SPI(WorkAddress & 0xFF);
			W25qxx_SPI(0);
			HAL_SPI_Receive(&_W25QXX_SPI,pBuffer,1,100);	
			W25qxx_ChipSelect(UNSELECT);	
			if(pBuffer[0]!=0xFF)
				goto NOT_EMPTY;
		}
	}	
	w25qxx.Lock=0;
	return true;	
	NOT_EMPTY:
	w25qxx.Lock=0;
	return false;
}

bool W25qxx_IsEmptySector(uint32_t Sector_Address,uint32_t OffsetInByte,uint32_t NumByteToCheck_up_to_SectorSize)
{
	while(w25qxx.Lock==1)
	W25qxx_Delay(1);
	w25qxx.Lock=1;	
	if((NumByteToCheck_up_to_SectorSize>w25qxx.SectorSize)||(NumByteToCheck_up_to_SectorSize==0))
		NumByteToCheck_up_to_SectorSize=w25qxx.SectorSize;
	uint8_t	pBuffer[32];
	uint32_t	WorkAddress;
	uint32_t	i;
	for(i=OffsetInByte; i<w25qxx.SectorSize; i+=sizeof(pBuffer))
	{
		W25qxx_ChipSelect(SELECT);
                HAL_Delay(1);
		WorkAddress=(i+Sector_Address*w25qxx.SectorSize);
		W25qxx_SPI(0x0B);
		if(w25qxx.ID>=W25Q256)
			W25qxx_SPI((WorkAddress & 0xFF000000) >> 24);
		W25qxx_SPI((WorkAddress & 0xFF0000) >> 16);
		W25qxx_SPI((WorkAddress & 0xFF00) >> 8);
		W25qxx_SPI(WorkAddress & 0xFF);
		W25qxx_SPI(0);
		HAL_SPI_Receive(&_W25QXX_SPI,pBuffer,sizeof(pBuffer),100);	
		W25qxx_ChipSelect(UNSELECT);	
		for(uint8_t x=0;x<sizeof(pBuffer);x++)
		{
			if(pBuffer[x]!=0xFF)
				goto NOT_EMPTY;		
		}			
	}	
	if((w25qxx.SectorSize+OffsetInByte)%sizeof(pBuffer)!=0)
	{
		i-=sizeof(pBuffer);
		for( ; i<w25qxx.SectorSize; i++)
		{
			W25qxx_ChipSelect(SELECT);
                        HAL_Delay(1);
			WorkAddress=(i+Sector_Address*w25qxx.SectorSize);
			W25qxx_SPI(0x0B);
			if(w25qxx.ID>=W25Q256)
				W25qxx_SPI((WorkAddress & 0xFF000000) >> 24);
			W25qxx_SPI((WorkAddress & 0xFF0000) >> 16);
			W25qxx_SPI((WorkAddress & 0xFF00) >> 8);
			W25qxx_SPI(WorkAddress & 0xFF);
			W25qxx_SPI(0);
			HAL_SPI_Receive(&_W25QXX_SPI,pBuffer,1,100);	
			W25qxx_ChipSelect(UNSELECT);	
			if(pBuffer[0]!=0xFF)
				goto NOT_EMPTY;
		}
	}		
	w25qxx.Lock=0;
	return true;	
	NOT_EMPTY:
	w25qxx.Lock=0;
	return false;
}

bool W25qxx_IsEmptyBlock(uint32_t Block_Address,uint32_t OffsetInByte,uint32_t NumByteToCheck_up_to_BlockSize)
{
	while(w25qxx.Lock==1)
	W25qxx_Delay(1);
	w25qxx.Lock=1;	
	if((NumByteToCheck_up_to_BlockSize>w25qxx.BlockSize)||(NumByteToCheck_up_to_BlockSize==0))
		NumByteToCheck_up_to_BlockSize=w25qxx.BlockSize;		
	uint8_t	pBuffer[32];
	uint32_t	WorkAddress;
	uint32_t	i;
	for(i=OffsetInByte; i<w25qxx.BlockSize; i+=sizeof(pBuffer))
	{
		W25qxx_ChipSelect(SELECT);
                HAL_Delay(1);
		WorkAddress=(i+Block_Address*w25qxx.BlockSize);
		W25qxx_SPI(0x0B);
		if(w25qxx.ID>=W25Q256)
			W25qxx_SPI((WorkAddress & 0xFF000000) >> 24);
		W25qxx_SPI((WorkAddress & 0xFF0000) >> 16);
		W25qxx_SPI((WorkAddress & 0xFF00) >> 8);
		W25qxx_SPI(WorkAddress & 0xFF);
		W25qxx_SPI(0);
		HAL_SPI_Receive(&_W25QXX_SPI,pBuffer,sizeof(pBuffer),100);	
		W25qxx_ChipSelect(UNSELECT);	
		for(uint8_t x=0;x<sizeof(pBuffer);x++)
		{
			if(pBuffer[x]!=0xFF)
				goto NOT_EMPTY;		
		}			
	}	
	if((w25qxx.BlockSize+OffsetInByte)%sizeof(pBuffer)!=0)
	{
		i-=sizeof(pBuffer);
		for( ; i<w25qxx.BlockSize; i++)
		{
			W25qxx_ChipSelect(SELECT);
                        HAL_Delay(1);
			WorkAddress=(i+Block_Address*w25qxx.BlockSize);
			W25qxx_SPI(0x0B);
			if(w25qxx.ID>=W25Q256)
				W25qxx_SPI((WorkAddress & 0xFF000000) >> 24);
			W25qxx_SPI((WorkAddress & 0xFF0000) >> 16);
			W25qxx_SPI((WorkAddress & 0xFF00) >> 8);
			W25qxx_SPI(WorkAddress & 0xFF);
			W25qxx_SPI(0);
			HAL_SPI_Receive(&_W25QXX_SPI,pBuffer,1,100);	
			W25qxx_ChipSelect(UNSELECT);	
			if(pBuffer[0]!=0xFF)
				goto NOT_EMPTY;
		}
	}	
	w25qxx.Lock=0;
	return true;	
	NOT_EMPTY:
	w25qxx.Lock=0;
	return false;
}

void W25qxx_WriteByte(uint8_t pBuffer, uint32_t WriteAddr_inBytes)
{
	while(w25qxx.Lock==1)
		W25qxx_Delay(1);
	w25qxx.Lock=1;
	W25qxx_WaitForWriteEnd();
  W25qxx_WriteEnable();
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(1);
  W25qxx_SPI(0x02);
	if(w25qxx.ID>=W25Q256)
		W25qxx_SPI((WriteAddr_inBytes & 0xFF000000) >> 24);
  W25qxx_SPI((WriteAddr_inBytes & 0xFF0000) >> 16);
  W25qxx_SPI((WriteAddr_inBytes & 0xFF00) >> 8);
  W25qxx_SPI(WriteAddr_inBytes & 0xFF);
  W25qxx_SPI(pBuffer);
	W25qxx_ChipSelect(UNSELECT);
  W25qxx_WaitForWriteEnd();
	w25qxx.Lock=0;
}

void W25qxx_WritePage(uint8_t *pBuffer	,uint32_t Page_Address,uint32_t OffsetInByte,uint32_t NumByteToWrite_up_to_PageSize)
{
  uint8_t cmd[4] = {W25Q_PAGE_PROGRAM};
  
  while(w25qxx.Lock==1)
          W25qxx_Delay(1);
  w25qxx.Lock=1;
  if(((NumByteToWrite_up_to_PageSize+OffsetInByte)>w25qxx.PageSize)||(NumByteToWrite_up_to_PageSize==0))
          NumByteToWrite_up_to_PageSize=w25qxx.PageSize-OffsetInByte;
  if((OffsetInByte+NumByteToWrite_up_to_PageSize) > w25qxx.PageSize)
          NumByteToWrite_up_to_PageSize = w25qxx.PageSize-OffsetInByte;
  W25qxx_WaitForWriteEnd();
  W25qxx_WriteEnable();
  W25qxx_ChipSelect(SELECT);
  HAL_Delay(1);
  Page_Address = (Page_Address*w25qxx.PageSize)+OffsetInByte;	
//  if(w25qxx.ID>=W25Q256)
//          W25qxx_SPI((Page_Address & 0xFF000000) >> 24);
  SET_ADDR(cmd+1, Page_Address);
  HAL_SPI_Transmit(&_W25QXX_SPI, cmd, 4, 100);  
  HAL_SPI_Transmit(&_W25QXX_SPI, pBuffer, NumByteToWrite_up_to_PageSize, 100);	
  W25qxx_ChipSelect(UNSELECT);
  W25qxx_WaitForWriteEnd();	
  W25qxx_Delay(1);
  w25qxx.Lock=0;
}

void W25qxx_WriteSector(uint8_t *pBuffer	,uint32_t Sector_Address,uint32_t OffsetInByte	,uint32_t NumByteToWrite_up_to_SectorSize)
{
	if((NumByteToWrite_up_to_SectorSize>w25qxx.SectorSize)||(NumByteToWrite_up_to_SectorSize==0))
		NumByteToWrite_up_to_SectorSize=w25qxx.SectorSize;	
	if(OffsetInByte>=w25qxx.SectorSize)
	{
		return;
	}	
	uint32_t	StartPage;
	int32_t		BytesToWrite;
	uint32_t	LocalOffset;	
	if((OffsetInByte+NumByteToWrite_up_to_SectorSize) > w25qxx.SectorSize)
		BytesToWrite = w25qxx.SectorSize-OffsetInByte;
	else
		BytesToWrite = NumByteToWrite_up_to_SectorSize;	
	StartPage = W25qxx_SectorToPage(Sector_Address)+(OffsetInByte/w25qxx.PageSize);
	LocalOffset = OffsetInByte%w25qxx.PageSize;	
	do
	{		
		W25qxx_WritePage(pBuffer,StartPage,LocalOffset,BytesToWrite);
		StartPage++;
		BytesToWrite-=w25qxx.PageSize-LocalOffset;
		pBuffer+=w25qxx.PageSize;	
		LocalOffset=0;
	}while(BytesToWrite>0);		
}

void W25qxx_WriteBlock(uint8_t* pBuffer ,uint32_t Block_Address	,uint32_t OffsetInByte	,uint32_t	NumByteToWrite_up_to_BlockSize)
{
	if((NumByteToWrite_up_to_BlockSize>w25qxx.BlockSize)||(NumByteToWrite_up_to_BlockSize==0))
		NumByteToWrite_up_to_BlockSize=w25qxx.BlockSize;
	if(OffsetInByte>=w25qxx.BlockSize)
	{
		return;
	}	
	uint32_t	StartPage;
	int32_t		BytesToWrite;
	uint32_t	LocalOffset;	
	if((OffsetInByte+NumByteToWrite_up_to_BlockSize) > w25qxx.BlockSize)
		BytesToWrite = w25qxx.BlockSize-OffsetInByte;
	else
		BytesToWrite = NumByteToWrite_up_to_BlockSize;	
	StartPage = W25qxx_BlockToPage(Block_Address)+(OffsetInByte/w25qxx.PageSize);
	LocalOffset = OffsetInByte%w25qxx.PageSize;	
	do
	{		
		W25qxx_WritePage(pBuffer,StartPage,LocalOffset,BytesToWrite);
		StartPage++;
		BytesToWrite-=w25qxx.PageSize-LocalOffset;
		pBuffer+=w25qxx.PageSize;	
		LocalOffset=0;
	}while(BytesToWrite>0);			
}

void W25qxx_ReadByte(uint8_t *pBuffer,uint32_t Bytes_Address)
{
	while(w25qxx.Lock==1)
		W25qxx_Delay(1);
	w25qxx.Lock=1;
	W25qxx_ChipSelect(SELECT);
  HAL_Delay(1);
  W25qxx_SPI(0x0B);
	if(w25qxx.ID>=W25Q256)
		W25qxx_SPI((Bytes_Address & 0xFF000000) >> 24);
  W25qxx_SPI((Bytes_Address & 0xFF0000) >> 16);
  W25qxx_SPI((Bytes_Address& 0xFF00) >> 8);
  W25qxx_SPI(Bytes_Address & 0xFF);
	W25qxx_SPI(0);
	*pBuffer = W25qxx_SPI(W25QXX_DUMMY_BYTE);
	W25qxx_ChipSelect(UNSELECT);	
	w25qxx.Lock=0;
}

void W25qxx_ReadBytes(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
	while(w25qxx.Lock==1)
		W25qxx_Delay(1);
	w25qxx.Lock=1;	
	W25qxx_ChipSelect(SELECT);
        HAL_Delay(1);
	W25qxx_SPI(0x0B);
	if(w25qxx.ID>=W25Q256)
		W25qxx_SPI((ReadAddr & 0xFF000000) >> 24);
  W25qxx_SPI((ReadAddr & 0xFF0000) >> 16);
  W25qxx_SPI((ReadAddr& 0xFF00) >> 8);
  W25qxx_SPI(ReadAddr & 0xFF);
	W25qxx_SPI(0);
	HAL_SPI_Receive(&_W25QXX_SPI,pBuffer,NumByteToRead,2000);	
	W25qxx_ChipSelect(UNSELECT);	
	W25qxx_Delay(1);
	w25qxx.Lock=0;
}

void W25qxx_ReadPage(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize)
{
  uint8_t cmd[5] = {W25Q_FAST_READ};
  
  W25qxx_ChipSelect(SELECT);
  while(w25qxx.Lock==1) W25qxx_Delay(1);
  w25qxx.Lock=1;
  if((NumByteToRead_up_to_PageSize>w25qxx.PageSize)||(NumByteToRead_up_to_PageSize==0))
          NumByteToRead_up_to_PageSize=w25qxx.PageSize;
  if((OffsetInByte+NumByteToRead_up_to_PageSize) > w25qxx.PageSize)
          NumByteToRead_up_to_PageSize = w25qxx.PageSize-OffsetInByte;
  Page_Address = Page_Address*w25qxx.PageSize+OffsetInByte;
//  if(w25qxx.ID>=W25Q256)
//          W25qxx_SPI((Page_Address & 0xFF000000) >> 24);
  SET_ADDR(cmd+1, Page_Address);
  HAL_SPI_Transmit(&_W25QXX_SPI, cmd, 5, 100);
  HAL_SPI_Receive(&_W25QXX_SPI, pBuffer, NumByteToRead_up_to_PageSize, 100);	
  W25qxx_ChipSelect(UNSELECT);
  W25qxx_Delay(1);
  w25qxx.Lock=0;
}

void W25qxx_ReadSector(uint8_t *pBuffer,uint32_t Sector_Address,uint32_t OffsetInByte,uint32_t NumByteToRead_up_to_SectorSize)
{	
	if((NumByteToRead_up_to_SectorSize>w25qxx.SectorSize)||(NumByteToRead_up_to_SectorSize==0))
		NumByteToRead_up_to_SectorSize=w25qxx.SectorSize;
	if(OffsetInByte>=w25qxx.SectorSize)
	{
		return;
	}	
	uint32_t	StartPage;
	int32_t		BytesToRead;
	uint32_t	LocalOffset;	
	if((OffsetInByte+NumByteToRead_up_to_SectorSize) > w25qxx.SectorSize)
		BytesToRead = w25qxx.SectorSize-OffsetInByte;
	else
		BytesToRead = NumByteToRead_up_to_SectorSize;	
	StartPage = W25qxx_SectorToPage(Sector_Address)+(OffsetInByte/w25qxx.PageSize);
	LocalOffset = OffsetInByte%w25qxx.PageSize;	
	do
	{		
		W25qxx_ReadPage(pBuffer,StartPage,LocalOffset,BytesToRead);
		StartPage++;
		BytesToRead-=w25qxx.PageSize-LocalOffset;
		pBuffer+=w25qxx.PageSize;	
		LocalOffset=0;
	}while(BytesToRead>0);			
}

void W25qxx_ReadBlock(uint8_t* pBuffer,uint32_t Block_Address,uint32_t OffsetInByte,uint32_t	NumByteToRead_up_to_BlockSize)
{
	if((NumByteToRead_up_to_BlockSize>w25qxx.BlockSize)||(NumByteToRead_up_to_BlockSize==0))
		NumByteToRead_up_to_BlockSize=w25qxx.BlockSize;
	if(OffsetInByte>=w25qxx.BlockSize)
	{
		return;
	}
	uint32_t	StartPage;
	int32_t		BytesToRead;
	uint32_t	LocalOffset;	
	if((OffsetInByte+NumByteToRead_up_to_BlockSize) > w25qxx.BlockSize)
		BytesToRead = w25qxx.BlockSize-OffsetInByte;
	else
		BytesToRead = NumByteToRead_up_to_BlockSize;	
	StartPage = W25qxx_BlockToPage(Block_Address)+(OffsetInByte/w25qxx.PageSize);
	LocalOffset = OffsetInByte%w25qxx.PageSize;	
	do
	{		
		W25qxx_ReadPage(pBuffer,StartPage,LocalOffset,BytesToRead);
		StartPage++;
		BytesToRead-=w25qxx.PageSize-LocalOffset;
		pBuffer+=w25qxx.PageSize;	
		LocalOffset=0;
	}while(BytesToRead>0);	
}


void W25qxx_Reset(void)
{
  W25qxx_ChipSelect(SELECT);
  W25qxx_SPI(W25Q_ENABLE_RESET);
  W25qxx_ChipSelect(UNSELECT);
  W25qxx_Delay(1);
  W25qxx_ChipSelect(SELECT);
  W25qxx_SPI(W25Q_RESET);
  W25qxx_ChipSelect(UNSELECT);
  W25qxx_Delay(1);
}

