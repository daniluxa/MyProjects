/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Bleeper board SPI driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
/**
  ******************************************************************************
  * @file    hw_spi.c
  * @author  MCD Application Team
  * @brief   manages the SPI interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hw.h"
#include "utilities.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern SPI_HandleTypeDef hspi;
/* Private function prototypes -----------------------------------------------*/

/* Exported functions ---------------------------------------------------------*/

/*!
 * @brief Sends outData and receives inData
 *
 * @param [IN] outData Byte to be sent
 * @retval inData      Received byte.
 */
uint16_t HW_SPI_InOut(uint16_t txData)
{
  uint16_t rxData ;

  __disable_irq();
  HAL_SPI_TransmitReceive(&hspi, (uint8_t *) &txData, (uint8_t *) &rxData, 1, HAL_MAX_DELAY);
  __enable_irq();

  return rxData;
}

void HW_SPI_In(uint8_t* rxData, uint32_t size)
{
  __disable_irq();  
  HAL_SPI_Receive(&hspi, rxData, size, 100);	  
  __enable_irq();
}

void HW_SPI_Out(uint8_t* txData, uint32_t size)
{
  __disable_irq();
  HAL_SPI_Transmit(&hspi, txData, size, 100);  
  __enable_irq();
}

/* Private functions ---------------------------------------------------------*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
