/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "global.h"
#include "timer.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define BACK_END_Pin GPIO_PIN_2
#define BACK_END_GPIO_Port GPIOA
#define BACK_HAND_Pin GPIO_PIN_3
#define BACK_HAND_GPIO_Port GPIOA
#define BACK_GRIP_Pin GPIO_PIN_4
#define BACK_GRIP_GPIO_Port GPIOA
#define LEFT_ARM_Pin GPIO_PIN_5
#define LEFT_ARM_GPIO_Port GPIOA
#define LEFT_HAND_Pin GPIO_PIN_6
#define LEFT_HAND_GPIO_Port GPIOA
#define LEFT_GRIP_Pin GPIO_PIN_7
#define LEFT_GRIP_GPIO_Port GPIOA
#define RIGHT_GRIP_Pin GPIO_PIN_15
#define RIGHT_GRIP_GPIO_Port GPIOA
#define RIGHT_HAND_Pin GPIO_PIN_3
#define RIGHT_HAND_GPIO_Port GPIOB
#define RIGHT_ARM_Pin GPIO_PIN_4
#define RIGHT_ARM_GPIO_Port GPIOB
#define FRONT_GRIP_Pin GPIO_PIN_5
#define FRONT_GRIP_GPIO_Port GPIOB
#define FRONT_HAND_Pin GPIO_PIN_6
#define FRONT_HAND_GPIO_Port GPIOB
#define FRONT_ARM_Pin GPIO_PIN_7
#define FRONT_ARM_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
