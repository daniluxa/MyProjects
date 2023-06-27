/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
//uint8_t dataWrite[1]  = {0x79};  //     0x20      or      0xDD     or     0x9d  or 39
//uint8_t dataWrite1[1] = {0x46};  //     0x46      or      0xc6
//uint8_t dataWrite2[1] = {0x39};  //     0xc4      or      0x39
//uint8_t dataWrite3[1] = {0xB0};

uint8_t dataWrite0[1]  = {0xA0};
uint8_t dataWrite1[1]  = {0x5E};
uint8_t dataWrite2[1]  = {0x84};
uint8_t dataWrite3[1]  = {0x39};
uint8_t dataWrite4[1]  = {0x22};
uint8_t dataWrite5[1]  = {0x9D};
uint8_t dataWrite6[1]  = {0x7D};
uint8_t dataWrite7[1]  = {0x00};
uint8_t dataWrite8[1]  = {0x0D};
uint8_t dataWrite9[1]  = {0x00};
uint8_t dataWrite10[1] = {0xff};
uint8_t dataWrite11[1] = {0xff};
uint8_t dataWrite12[1] = {0xff};
uint8_t dataWrite13[1] = {0xff};
uint8_t dataWrite14[1] = {0xff};
uint8_t dataWrite15[1] = {0x00};
uint8_t dataWrite16[1] = {0x00};
uint8_t dataWrite17[1] = {0x00};
uint8_t dataWrite18[1] = {0x00};
uint8_t dataWrite19[1] = {0x00};
uint8_t dataWrite20[1] = {0x00};
uint8_t dataWrite21[1] = {0x30};
uint8_t dataWrite22[1] = {0x00};
uint8_t dataWrite23[1] = {0x00};
uint8_t dataWrite24[1] = {0x00};
uint8_t dataWrite25[1] = {0x00};
uint8_t dataWrite26[1] = {0x00};
uint8_t dataWrite27[1] = {0x00};
uint8_t dataWrite28[1] = {0x00};
uint8_t dataWrite29[1] = {0x00};
uint8_t dataWrite30[1] = {0x00};
uint8_t dataWrite31[1] = {0x00};
uint8_t dataWrite32[1] = {0x00};
uint8_t dataWrite33[1] = {0x00};
uint8_t dataWrite34[1] = {0x00};
uint8_t dataWrite35[1] = {0x00};
uint8_t dataWrite36[1] = {0x00};
uint8_t dataWrite37[1] = {0x28};
uint8_t dataWrite38[1] = {0x00};
uint8_t dataWrite39[1] = {0x00};
uint8_t dataWrite40[1] = {0x2A};
uint8_t dataWrite41[1] = {0xF4};
uint8_t dataWrite42[1] = {0x81};
uint8_t dataWrite43[1] = {0x00};
uint8_t dataWrite44[1] = {0x00};


uint8_t dataRead[8];
uint8_t dataRead0[1];
uint8_t dataRead1[1];
uint8_t dataRead2[1];
uint8_t dataRead3[1];
uint8_t dataRead4[1];
uint8_t dataRead5[1];
uint8_t dataRead6[1];
uint8_t dataRead7[1];
uint8_t dataRead8[1];
uint8_t dataRead9[1];
uint8_t dataRead10[1];
uint8_t dataRead11[1];
uint8_t dataRead12[1];
uint8_t dataRead13[1];
uint8_t dataRead14[1];
uint8_t dataRead15[1];
uint8_t dataRead16[1];
uint8_t dataRead17[1];
uint8_t dataRead18[1];
uint8_t dataRead19[1];
uint8_t dataRead20[1];
uint8_t dataRead21[1];
uint8_t dataRead22[1];
uint8_t dataRead23[1];
uint8_t dataRead24[1];
uint8_t dataRead25[1];
uint8_t dataRead26[1];
uint8_t dataRead27[1];
uint8_t dataRead28[1];
uint8_t dataRead29[1];
uint8_t dataRead30[1];
uint8_t dataRead31[1];
uint8_t dataRead32[1];
uint8_t dataRead33[1];
uint8_t dataRead34[1];
uint8_t dataRead35[1];
uint8_t dataRead36[1];
uint8_t dataRead37[1];
uint8_t dataRead38[1];
uint8_t dataRead39[1];
uint8_t dataRead40[1];
uint8_t dataRead41[1];
uint8_t dataRead42[1];
uint8_t dataRead43[1];
uint8_t dataRead44[1];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
   // BQ25887_Charge_Current_Limit(1500);
    /*BQ25887_Input_Voltage_Limit(4300);
    BQ25887_Input_Current_Limit(3000);*/
      //BQ25887_RESET();
  while (1)
  {
    /* USER CODE END WHILE */
   
    HAL_Delay(2000);
    BQ25887_Get_Vbat();
    BQ25887_Get_VBUS_Current();
    BQ25887_Get_Charge_Current();
    BQ25887_Get_Vcell_top();
    BQ25887_Get_Vcell_bot();
    BQ25887_Get_Temp();
    
    Vbus_Stat();
    BQ25887_Charge_Current_Limit(500);
    
////    BQ25887_Reg_Write(0x03, dataWrite);
////    BQ25887_Reg_Read(0x06, dataRead, 1);
////    BQ25887_Reg_Read(0x29, dataRead1, 1);
////    BQ25887_Reg_Read(0x0B, dataRead2, 1);
////    BQ25887_Reg_Read(0x0C, dataRead3, 1);
    
//    BQ25887_Reg_Read(0x00, dataRead0, 1);
//    BQ25887_Reg_Read(0x01, dataRead1, 1);
//    BQ25887_Reg_Read(0x02, dataRead2, 1);
//    BQ25887_Reg_Read(0x03, dataRead3, 1);
//    BQ25887_Reg_Read(0x04, dataRead4, 1);
//    BQ25887_Reg_Read(0x05, dataRead5, 1);
//    BQ25887_Reg_Read(0x06, dataRead6, 1);
//    BQ25887_Reg_Read(0x07, dataRead7, 1);
//    BQ25887_Reg_Read(0x08, dataRead8, 1);
//    BQ25887_Reg_Read(0x09, dataRead9, 1);
//    BQ25887_Reg_Read(0x0A, dataRead10, 1);
//    BQ25887_Reg_Read(0x0B, dataRead11, 1);
//    BQ25887_Reg_Read(0x0C, dataRead12, 1);
//    BQ25887_Reg_Read(0x0D, dataRead13, 1);
//    BQ25887_Reg_Read(0x0E, dataRead14, 1);
//    BQ25887_Reg_Read(0x0F, dataRead15, 1);
//    BQ25887_Reg_Read(0x10, dataRead16, 1);
//    BQ25887_Reg_Read(0x11, dataRead17, 1);
//    BQ25887_Reg_Read(0x12, dataRead18, 1);
//    BQ25887_Reg_Read(0x13, dataRead19, 1);
//    BQ25887_Reg_Read(0x14, dataRead20, 1);
//    BQ25887_Reg_Read(0x15, dataRead21, 1);
//    BQ25887_Reg_Read(0x16, dataRead22, 1);
//    BQ25887_Reg_Read(0x17, dataRead23, 1);
//    BQ25887_Reg_Read(0x18, dataRead24, 1);
//    BQ25887_Reg_Read(0x19, dataRead25, 1);
//    BQ25887_Reg_Read(0x1A, dataRead26, 1);
//    BQ25887_Reg_Read(0x1B, dataRead27, 1);
//    BQ25887_Reg_Read(0x1C, dataRead28, 1);
//    BQ25887_Reg_Read(0x1D, dataRead29, 1);
//    BQ25887_Reg_Read(0x1E, dataRead30, 1);
//    BQ25887_Reg_Read(0x1F, dataRead31, 1);
//    BQ25887_Reg_Read(0x20, dataRead32, 1);
//    BQ25887_Reg_Read(0x21, dataRead33, 1);
//    BQ25887_Reg_Read(0x22, dataRead34, 1);
//    BQ25887_Reg_Read(0x23, dataRead35, 1);
//    BQ25887_Reg_Read(0x24, dataRead36, 1);
//    BQ25887_Reg_Read(0x25, dataRead37, 1);
//    BQ25887_Reg_Read(0x26, dataRead38, 1);
//    BQ25887_Reg_Read(0x27, dataRead39, 1);
//    BQ25887_Reg_Read(0x28, dataRead40, 1);
//    BQ25887_Reg_Read(0x29, dataRead41, 1);
//    BQ25887_Reg_Read(0x2A, dataRead42, 1);
//    BQ25887_Reg_Read(0x2B, dataRead43, 1);
//    BQ25887_Reg_Read(0x2C, dataRead44, 1);
    
    BQ25887_Charge_Status();
    BQ25887_Cancel_Charge(0);
    
    LED_set_color(PURPLE);

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPS_EN_GPIO_Port, GPS_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CH_CD_GPIO_Port, CH_CD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED_R_Pin|LED_G_Pin|LED_B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : GPS_EN_Pin */
  GPIO_InitStruct.Pin = GPS_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPS_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CH_STATUS_Pin */
  GPIO_InitStruct.Pin = CH_STATUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(CH_STATUS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CH_CD_Pin */
  GPIO_InitStruct.Pin = CH_CD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CH_CD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_R_Pin LED_G_Pin LED_B_Pin */
  GPIO_InitStruct.Pin = LED_R_Pin|LED_G_Pin|LED_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

