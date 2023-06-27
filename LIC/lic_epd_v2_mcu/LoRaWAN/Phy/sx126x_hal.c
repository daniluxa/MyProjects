/* Includes ------------------------------------------------------------------*/

#include "hw.h"
#include "radio.h"
#include "sx126x_board.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define BOARD_TCXO_WAKEUP_TIME  0 // no TCXO
#define BOARD_TCXO_WAKEUP_TIME  640 // TCXO delay 10 ms

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

extern irq_handler_addr irq_handler_DIO1;

void SX126xIoInit( void )
{
  /*GPIO_InitTypeDef initStruct={0};

  //   Set DioIrqHandler port in IT_RISING mode
  initStruct.Mode = GPIO_MODE_IT_RISING;
  initStruct.Pull = GPIO_NOPULL;
  initStruct.Speed = GPIO_SPEED_HIGH;
  HW_GPIO_Init( RADIO_DIO_1_PORT, RADIO_DIO_1_PIN, &initStruct);

  initStruct.Mode = GPIO_MODE_INPUT;
  initStruct.Pull = GPIO_NOPULL;
  HW_GPIO_Init( DEVICE_SEL_PORT, DEVICE_SEL_PIN, &initStruct);
  HW_GPIO_Init( RADIO_BUSY_PORT, RADIO_BUSY_PIN, &initStruct);

  initStruct.Pull = GPIO_NOPULL;
  initStruct.Mode = GPIO_MODE_OUTPUT_PP;
  HW_GPIO_Init( RADIO_NSS_PORT, RADIO_NSS_PIN,  &initStruct );*/
  HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin,  1 );

  /*HW_GPIO_Init( RADIO_LEDTX_PORT, RADIO_LEDTX_PIN,  &initStruct );
  HW_GPIO_Write( RADIO_LEDTX_PORT, RADIO_LEDTX_PIN,  0 );

  HW_GPIO_Init( RADIO_LEDRX_PORT, RADIO_LEDRX_PIN,  &initStruct );
  HW_GPIO_Write( RADIO_LEDRX_PORT, RADIO_LEDRX_PIN,  0 );*/

  //HW_GPIO_Init( RADIO_ANT_SWITCH_POWER_PORT, RADIO_ANT_SWITCH_POWER_PIN, &initStruct);
  //HW_GPIO_Write( RADIO_ANT_SWITCH_POWER_PORT, RADIO_ANT_SWITCH_POWER_PIN, 0);
}

void SX126xIoIrqInit( DioIrqHandler dioIrq )
{
//#define LORA_DIO1_EXTI_IRQn EXTI0_IRQn
  HW_GPIO_SetIrq( LORA_DIO1_GPIO_Port, LORA_DIO1_Pin, IRQ_HIGH_PRIORITY, dioIrq );
  irq_handler_DIO1 = (irq_handler_addr)dioIrq;
}

void SX126xIoDeInit( void )
{
}

uint32_t SX126xGetBoardTcxoWakeupTime( void )
{
    return BOARD_TCXO_WAKEUP_TIME;
}

void SX126xReset( void )
{
  // Wait 10 ms
  DelayMs(10);

  // Set RESET pin to 0
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = LORA_NRST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LORA_NRST_GPIO_Port, &GPIO_InitStruct);

  HW_GPIO_Write(LORA_NRST_GPIO_Port, LORA_NRST_Pin, 0);

  // Wait 20 ms
  DelayMs(20);
  HW_GPIO_Write(LORA_NRST_GPIO_Port, LORA_NRST_Pin, 1);

  // Configure RESET as input
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  HAL_GPIO_Init(LORA_NRST_GPIO_Port, &GPIO_InitStruct);
//
//  HW_GPIO_Write(LORA_NRST_GPIO_Port, LORA_NRST_Pin, 0);

  // Wait 10 ms
  DelayMs(10);
}

void SX126xWaitOnBusy( void )
{
    while( HW_GPIO_Read(LORA_BUSY_GPIO_Port, LORA_BUSY_Pin) == 1 );
}

void SX126xWakeup( void )
{
    //NSS = 0;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 0 );
    
    HW_SPI_InOut(RADIO_GET_STATUS);
    HW_SPI_InOut(0);
    
    //NSS = 1;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 1 );

    // Wait for chip to be ready.
    SX126xWaitOnBusy( );
}

void SX126xWriteCommand( RadioCommands_t command, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 0 );

    HW_SPI_InOut(command);
    
    HW_SPI_Out(buffer, size);
//    for( uint16_t i = 0; i < size; i++ )
//    {
//        HW_SPI_InOut( buffer[i] );
//    }
    //NSS = 1;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 1 );

    if( command != RADIO_SET_SLEEP )
    {
        SX126xWaitOnBusy( );
    }
}

uint8_t SX126xReadCommand( RadioCommands_t command, uint8_t *buffer, uint16_t size )
{
    uint8_t status = 0;

    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 0 );

    HW_SPI_InOut(command);
    status = HW_SPI_InOut(0x00);
//    for( uint16_t i = 0; i < size; i++ )
//    {
//        buffer[i] = HW_SPI_InOut( 0 );
//    }
    HW_SPI_In(buffer, size);

    //NSS = 1;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 1 );

    SX126xWaitOnBusy( );

    return status;
}

void SX126xWriteRegisters( uint16_t address, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 0 );

    uint8_t cmd[] = {RADIO_WRITE_REGISTER, ( address & 0xFF00 ) >> 8, address & 0x00FF};
    HW_SPI_Out(cmd, sizeof(cmd));
//    HW_SPI_InOut(RADIO_WRITE_REGISTER );
//    HW_SPI_InOut(( address & 0xFF00 ) >> 8 );
//    HW_SPI_InOut(address & 0x00FF );

//    for( uint16_t i = 0; i < size; i++ )
//    {
//        HW_SPI_InOut(buffer[i] );
//    }
    HW_SPI_Out(buffer, size);

    //NSS = 1;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 1 );

    SX126xWaitOnBusy( );
}

void SX126xWriteRegister( uint16_t address, uint8_t value )
{
    SX126xWriteRegisters( address, &value, 1 );
}

void SX126xReadRegisters( uint16_t address, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 0 );

    uint8_t cmd[] = {RADIO_READ_REGISTER, ( address & 0xFF00 ) >> 8, address & 0x00FF, 0};
    HW_SPI_Out(cmd, sizeof(cmd));
//    HW_SPI_InOut(RADIO_READ_REGISTER);
//    HW_SPI_InOut(( address & 0xFF00) >> 8 );
//    HW_SPI_InOut(address & 0x00FF);
//    HW_SPI_InOut(0);
    HW_SPI_In(buffer, size);
    
//    for( uint16_t i = 0; i < size; i++ )
//    {
//        buffer[i] = HW_SPI_InOut( 0 );
//    }
    //NSS = 1;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 1 );

    SX126xWaitOnBusy( );
}

uint8_t SX126xReadRegister( uint16_t address )
{
    uint8_t data;
    SX126xReadRegisters( address, &data, 1 );
    return data;
}

void SX126xWriteBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 0 );

    uint8_t cmd[] = {RADIO_WRITE_BUFFER, offset};
    HW_SPI_Out(cmd, sizeof(cmd));
//    HW_SPI_InOut( RADIO_WRITE_BUFFER );
//    HW_SPI_InOut( offset );
    HW_SPI_Out(buffer, size);
//    for( uint16_t i = 0; i < size; i++ )
//    {
//        HW_SPI_InOut( buffer[i] );
//    }
    //NSS = 1;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 1 );

    SX126xWaitOnBusy( );
}


void SX126xReadBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    SX126xCheckDeviceReady( );

    //NSS = 0;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 0 );

    uint8_t cmd[] = {RADIO_READ_BUFFER, offset, 0};
    HW_SPI_Out(cmd, sizeof(cmd));
//    HW_SPI_InOut( RADIO_READ_BUFFER );
//    HW_SPI_InOut( offset );
//    HW_SPI_InOut( 0 );
    HW_SPI_In(buffer, size);    
//    for( uint16_t i = 0; i < size; i++ )
//    {
//        buffer[i] = HW_SPI_InOut( 0 );
//    }

    //NSS = 1;
    HW_GPIO_Write( LORA_CS_GPIO_Port, LORA_CS_Pin, 1 );

    SX126xWaitOnBusy( );
}
void SX126xSetRfTxPower( int8_t power )
{
    SX126xSetTxParams( power, RADIO_RAMP_40_US );
}



uint8_t SX126xGetPaSelect( uint32_t channel )
{
    /*if( HW_GPIO_Read( DEVICE_SEL_PORT, DEVICE_SEL_PIN) ==  1 )
    {
        return SX1261;
    }
    else
    {
        return SX1262;
    }*/
  return SX1262;
}

void SX126xAntSwOn( void )
{
  //HW_GPIO_Write( RADIO_ANT_SWITCH_POWER_PORT, RADIO_ANT_SWITCH_POWER_PIN, 1);
}

void SX126xAntSwOff( void )
{
  //HW_GPIO_Write( RADIO_ANT_SWITCH_POWER_PORT, RADIO_ANT_SWITCH_POWER_PIN, 0);
}



bool SX126xCheckRfFrequency( uint32_t frequency )
{
    // Implement check. Currently all frequencies are supported
    return true;
}

bool SX126xBoardIsTcxoPresent(void)
{ /* TCXO on board*/
  return true;
}

void SX126xBoardSetLedTx( bool state )
{
  if (state==false)
  {
    HW_GPIO_Write( LORA_LED1_GPIO_Port, LORA_LED1_Pin,  0 );
  }
  else
  {
    HW_GPIO_Write( LORA_LED1_GPIO_Port, LORA_LED1_Pin, 1 );
  }
}

void SX126xBoardSetLedRx( bool state )
{
  if (state==false)
  {
    HW_GPIO_Write( LORA_LED2_GPIO_Port, LORA_LED2_Pin, 0 );
  }
  else
  {
    HW_GPIO_Write( LORA_LED2_GPIO_Port, LORA_LED2_Pin, 1 );
  }
}