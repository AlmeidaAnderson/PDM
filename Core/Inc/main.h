/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define IN2_Pin LL_GPIO_PIN_13
#define IN2_GPIO_Port GPIOC
#define IN3_Pin LL_GPIO_PIN_14
#define IN3_GPIO_Port GPIOC
#define IN4_Pin LL_GPIO_PIN_15
#define IN4_GPIO_Port GPIOC
#define VS_Pin LL_GPIO_PIN_0
#define VS_GPIO_Port GPIOA
#define VS4_Pin LL_GPIO_PIN_1
#define VS4_GPIO_Port GPIOA
#define IS4_Pin LL_GPIO_PIN_2
#define IS4_GPIO_Port GPIOA
#define VS3_Pin LL_GPIO_PIN_3
#define VS3_GPIO_Port GPIOA
#define IS3_Pin LL_GPIO_PIN_4
#define IS3_GPIO_Port GPIOA
#define VS2_Pin LL_GPIO_PIN_5
#define VS2_GPIO_Port GPIOA
#define IS2_Pin LL_GPIO_PIN_6
#define IS2_GPIO_Port GPIOA
#define VS1_Pin LL_GPIO_PIN_7
#define VS1_GPIO_Port GPIOA
#define IS1_Pin LL_GPIO_PIN_0
#define IS1_GPIO_Port GPIOB
#define CTRL4_Pin LL_GPIO_PIN_2
#define CTRL4_GPIO_Port GPIOB
#define CTRL3_Pin LL_GPIO_PIN_10
#define CTRL3_GPIO_Port GPIOB
#define CTRL2_Pin LL_GPIO_PIN_11
#define CTRL2_GPIO_Port GPIOB
#define CTRL1_Pin LL_GPIO_PIN_12
#define CTRL1_GPIO_Port GPIOB
#define F1_Pin LL_GPIO_PIN_13
#define F1_GPIO_Port GPIOB
#define F2_Pin LL_GPIO_PIN_14
#define F2_GPIO_Port GPIOB
#define F3_Pin LL_GPIO_PIN_15
#define F3_GPIO_Port GPIOB
#define F4_Pin LL_GPIO_PIN_8
#define F4_GPIO_Port GPIOA
#define LED1_Pin LL_GPIO_PIN_9
#define LED1_GPIO_Port GPIOA
#define LED2_Pin LL_GPIO_PIN_10
#define LED2_GPIO_Port GPIOA
#define SD_Pin LL_GPIO_PIN_6
#define SD_GPIO_Port GPIOB
#define IN1_Pin LL_GPIO_PIN_7
#define IN1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
