/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "config.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


//开辟一块内存用于存放环形队列消息缓冲区
#define MSG_BUFFDATA_SIZE	128
static uint8_t msg_buffdata[MSG_BUFFDATA_SIZE];

//用于存储消息的环形缓冲队列的rt_ringbuffer句柄
struct rt_ringbuffer	msg_ringbuffer;

//系统消息处理
static uint8_t message_buff[256];
void msg_process(void)  
{
	system_message sys_msg;
	
	if(rt_ringbuffer_data_len(&msg_ringbuffer)!= 0) //消息队列不为空，则有消息需要处理
	{
		rt_ringbuffer_get(&msg_ringbuffer,(uint8_t *) &sys_msg.msg_type, 2);//读取消息类型(1字节) + 消息参数(1字节)，其中：不同消息类型对应的消息参数意义也不同，由用户自行定义

	    
		switch(sys_msg.msg_type)
		{
			case MSG_USART1_REC_FINISH:
				rt_ringbuffer_get(&usart1_recv_ring_buf, message_buff, sys_msg.msg_parameter);
			    message_buff[sys_msg.msg_parameter] = '\0';//sys_msg.msg_parameter中存放的是串口1接收帧的长度信息
			    printf("%s\n",message_buff);
				break;
			
			case MSG_W25QXX_TEST:
				w25qxx_test();
				break;
			
			default:break;
		}
	}
}


//申请一个按键结构
struct Button button1;

//按键状态读取接口
uint8_t read_button1_GPIO() 
{
	return HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
}

//按键回调函数
void button1_callback(void *button)
{
		//系统消息
		system_message  sys_msg;
		
    uint32_t btn_event_val; 
    
    btn_event_val = get_button_event((struct Button *)button); 
    
    switch(btn_event_val)
    {
	    case PRESS_DOWN:
	        printf("---> key1 press down! <---\r\n"); 
	    	break; 
	
	    case PRESS_UP: 
	        printf("***> key1 press up! <***\r\n");
	    	break; 
	
	    case PRESS_REPEAT: 
	        printf("---> key1 press repeat! <---\r\n");
	    	break; 
	
	    case SINGLE_CLICK: 
	        printf("---> key1 single click! <---\r\n");
	    	break; 
	
			case DOUBLE_CLICK://send msg MSG_W25QXX_TEST,in order to test w25q64 example
				sys_msg.msg_type = MSG_W25QXX_TEST;
				sys_msg.msg_parameter = 0;
				rt_ringbuffer_put(&msg_ringbuffer,(uint8_t *)&sys_msg.msg_type,2);
					printf("---> key1 double click! <---\r\n");
				break;
	
	    case LONG_PRESS_START: 
	        printf("---> key1 long press start! <---\r\n");
	   		break; 
	
	    case LONG_PRESS_HOLD: 
	        printf("***> key1 long press hold! <***\r\n");
	    	break; 
	}
}

//TIM回调
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		if(htim->Instance == htim2.Instance)
		{
			button_ticks();
		}

}

/*****************************w25qxx example****************************************/
char w25qxx_test_string[6][128]={
	"***************************Copyright (c)***************************",
	"**----------------------Hello World !!! -------------------------**",
	"** Thanks to armink:https://github.com/armink/SFUD               **",
	"** reference:                                                    **",
	"** https://mculover666.blog.csdn.net/article/details/105516371   **",
	"*******************************************************************"
};
//w25qxx_test测试
void w25qxx_test(void)
{
	int i;
	char sBuff[256]={0};
//	sfud_err result = SFUD_SUCCESS;
    const sfud_flash *flash = sfud_get_device_table() + 0;
	
	for(i=0;i<6;i++)
	{
		sfud_erase_write(flash, 0, strlen(w25qxx_test_string[i]),(uint8_t *)w25qxx_test_string[i]);
	    sfud_read(flash, 0, strlen(w25qxx_test_string[i]),(uint8_t *) sBuff);
	    printf("%s\n",sBuff);	
	}

}


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
  MX_SPI5_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	
	printf("MultiButton+RingBuffer+SFUD Test...\r\n");
	
	//初始化消息环形队列
	rt_ringbuffer_init(&msg_ringbuffer, msg_buffdata, MSG_BUFFDATA_SIZE);
  HAL_Delay(1);
	
	//初始化sfud
	sfud_init();
	HAL_Delay(1);
	
	//初始化按键对象
	button_init(&button1, read_button1_GPIO, 0);
	
	//注册按钮事件回调函数

//	button_attach(&button1, PRESS_DOWN,       button1_callback);
//	button_attach(&button1, PRESS_UP,         button1_callback);
//	button_attach(&button1, PRESS_REPEAT,     button1_callback);
	button_attach(&button1, SINGLE_CLICK,     button1_callback);
	button_attach(&button1, DOUBLE_CLICK,     button1_callback);
//	button_attach(&button1, LONG_PRESS_START, button1_callback);
//	button_attach(&button1, LONG_PRESS_HOLD,  button1_callback);

	//启动按键
	button_start(&button1);
	
	//启动定时器
	HAL_TIM_Base_Start_IT(&htim2);
	
	


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
//		HAL_Delay(200);
		msg_process();
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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
