/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "global.h"
#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
enum SystemState {
	IDLE,
	SETUP,
	SOLVE
} systemState = IDLE;

enum SystemMode {
	MANUAL,
	AUTO
} systemMode = MANUAL;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
uint8_t usb_buf[200];
uint8_t usb_len = 0;
uint8_t usb_received = 0;
uint8_t color_loaded = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void servo_init();
void rubik_solve();
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
  MX_TIM2_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_TIM_Base_Start_IT(&htim2);
  servo_init();
  color_sensor_init();

  // Waiting user for select mode
  while (usb_received == 0);
  usb_received = 0;
  if (usb_buf[0] == 0)
  {
	  systemMode = MANUAL;
  }else
  {
	  systemMode = AUTO;
  }

  while (1)
  {
	  if (systemMode == MANUAL)
	  {
		  switch (systemState)
		  {
		  case IDLE:
			  if (usb_received == 1)
			  {
				  if (data_equal(usb_buf, 11, "color_setup"))
				  {
					  systemState = SETUP;
					  usb_received = 0;
				  }else if (data_equal(usb_buf, 11, "rubik_solve"))
				  {
					  systemState = SOLVE;
					  usb_received = 0;
				  }
			  }
			  break;
		  case SETUP:
			  color_setup();
			  color_loaded = 1;
			  systemState = IDLE;
			  break;
		  case SOLVE:
			  rubik_solve();
			  systemState = IDLE;
			  break;
		  }
	  }else
	  {
		  //TODO

		  //Receiving solution
		  while (usb_received == 0);
		  usb_received = 0;
		  HAL_Delay(USB_SPACE_DELAY);
		  if (data_equal(usb_buf, usb_len, "done"))
		  {
			  continue;
		  }
		  turn(usb_buf, usb_len);

		  CDC_Transmit_FS(usb_buf, usb_len);
		  HAL_Delay(USB_SPACE_DELAY);
	  }
    /* USER CODE END WHILE */

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 5;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1599;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, BACK_ARM_Pin|BACK_HAND_Pin|BACK_GRIP_Pin|LEFT_ARM_Pin
                          |LEFT_HAND_Pin|LEFT_GRIP_Pin|RIGHT_GRIP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RIGHT_HAND_Pin|RIGHT_ARM_Pin|FRONT_GRIP_Pin|FRONT_HAND_Pin
                          |FRONT_ARM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BACK_ARM_Pin BACK_HAND_Pin BACK_GRIP_Pin LEFT_ARM_Pin
                           LEFT_HAND_Pin LEFT_GRIP_Pin RIGHT_GRIP_Pin */
  GPIO_InitStruct.Pin = BACK_ARM_Pin|BACK_HAND_Pin|BACK_GRIP_Pin|LEFT_ARM_Pin
                          |LEFT_HAND_Pin|LEFT_GRIP_Pin|RIGHT_GRIP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RIGHT_HAND_Pin RIGHT_ARM_Pin FRONT_GRIP_Pin FRONT_HAND_Pin
                           FRONT_ARM_Pin */
  GPIO_InitStruct.Pin = RIGHT_HAND_Pin|RIGHT_ARM_Pin|FRONT_GRIP_Pin|FRONT_HAND_Pin
                          |FRONT_ARM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void load_color()
{
	// Read color from stored file
	for (int i = 0; i < 6; ++i)
	{
		uint8_t ack = 1;
		CDC_Transmit_FS(&ack, 1);
		HAL_Delay(USB_SPACE_DELAY);
		while (usb_received == 0 && usb_len != 3);
		usb_received = 0;
		set_color_range(i, usb_buf[0], usb_buf[1], usb_buf[2]);
	}
}

void rubik_solve()
{
	uint8_t need_load = 1; // 1: need load, 0: not need load
	if (color_loaded == 0)
	{
		CDC_Transmit_FS(&need_load, 1);
		HAL_Delay(USB_SPACE_DELAY);
		load_color();
		color_loaded = 1;
	}else
	{
		need_load = 0;
		CDC_Transmit_FS(&need_load, 1);
		HAL_Delay(USB_SPACE_DELAY);
	}

	for (int i = 0; i < 48; ++i)
	{
		while (usb_received == 0);
		usb_received = 0;
		enum color c = read_color();
		CDC_Transmit_FS((uint8_t*)&c, 1);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}
}

void servo_init()
{
	init_servo(&arm_port[0], &arm_pin[0], RIGHT_ARM_GPIO_Port, RIGHT_ARM_Pin);
	init_servo(&hand_port[0], &hand_pin[0], RIGHT_HAND_GPIO_Port, RIGHT_HAND_Pin);
	init_servo(&grip_port[0], &grip_pin[0], RIGHT_GRIP_GPIO_Port, RIGHT_GRIP_Pin);

	init_servo(&arm_port[1], &arm_pin[1], FRONT_ARM_GPIO_Port, FRONT_ARM_Pin);
	init_servo(&hand_port[1], &hand_pin[1], FRONT_HAND_GPIO_Port, FRONT_HAND_Pin);
	init_servo(&grip_port[1], &grip_pin[1], FRONT_GRIP_GPIO_Port, FRONT_GRIP_Pin);

	init_servo(&arm_port[2], &arm_pin[2], LEFT_ARM_GPIO_Port, LEFT_ARM_Pin);
	init_servo(&hand_port[2], &hand_pin[2], LEFT_HAND_GPIO_Port, LEFT_HAND_Pin);
	init_servo(&grip_port[2], &grip_pin[2], LEFT_GRIP_GPIO_Port, LEFT_GRIP_Pin);

	init_servo(&arm_port[3], &arm_pin[3], BACK_ARM_GPIO_Port, BACK_ARM_Pin);
	init_servo(&hand_port[3], &hand_pin[3], BACK_HAND_GPIO_Port, BACK_HAND_Pin);
	init_servo(&grip_port[3], &grip_pin[3], BACK_GRIP_GPIO_Port, BACK_GRIP_Pin);
}

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
