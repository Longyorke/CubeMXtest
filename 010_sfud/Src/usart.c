/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "config.h"

/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */
	
		rt_ringbuffer_init(&usart1_recv_ring_buf,s_USART1_RxBuf,USART1_RX_BUF_SIZE);
		 /*ʹ�ܴ��ڽ��շǿ��ж� */
		__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);//�þ���Ҫ�ֶ�������cubeMX�����Զ�����;
																						 //���贮�ڽ��ջص�����ʹ��HAL_UART_Receive_IT ,ʹ�ûص����жϵ���˳��Ϊ USART1_IRQHandler ->HAL_UART_IRQHandler(&huart1)(�����жϴ���������ʾ����)->UART_Receive_IT -> HAL_UART_RxCpltCallback
		 /*ʹ�ܴ��ڽ��տ����ж� */
		__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE); //�þ���Ҫ�ֶ�������cubeMX�����Զ�����

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
int fputc(int ch, FILE *f)
{
#if 1
    if (ch == '\n') {
        HAL_UART_Transmit(&huart1, (void *)"\r", 1, 30000);
    }
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
#else
    while ((USART1->ISR & 0X40) == 0);
    USART1->TDR = (uint8_t)ch;
    return ch;
#endif
}

int _write(int fd, char *ptr, int len)
{
    (void)HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, 0xFFFF);
    return len;
}

int fgetc(FILE *f)
{
  /* Place your implementation of fgetc here */
  /* e.g. readwrite a character to the USART1 and Loop until the end of transmission */
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1,30000);
  return ch;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
