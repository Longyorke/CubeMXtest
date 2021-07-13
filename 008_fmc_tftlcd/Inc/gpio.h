/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
	 void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */


//LEDµÆ
#define LED0_ON   HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);  //LD0 ON
#define LED0_OFF  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);   //LD0 OFF
#define LED0_TOG  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);                 //LD0 ·­×ª


/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */


//LEDµÆ
#define LED0_ON   HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);  //LD0 ON
#define LED0_OFF  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);   //LD0 OFF
#define LED0_TOG  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);                 //LD0 ·­×ª


/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */


//LEDµÆ
#define LED0_ON   HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);  //LD0 ON
#define LED0_OFF  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);   //LD0 OFF
#define LED0_TOG  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);                 //LD0 ·­×ª


/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */


//LEDµÆ
#define LED0_ON   HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);  //LD0 ON
#define LED0_OFF  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);   //LD0 OFF
#define LED0_TOG  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);                 //LD0 ·­×ª


/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */


//LEDµÆ
#define LED0_ON   HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);  //LD0 ON
#define LED0_OFF  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);   //LD0 OFF
#define LED0_TOG  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);                 //LD0 ·­×ª


/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */


//LEDµÆ
#define LED0_ON   HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);  //LD0 ON
#define LED0_OFF  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);   //LD0 OFF
#define LED0_TOG  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);                 //LD0 ·­×ª


/* USER CODE END Private defines */
void HAL_Delay_us(uint32_t nus);



/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
