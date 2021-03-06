#ifndef  __CONFIG_H__
#define  __CONFIG_H__

//无符号类型的定义

	
//----------------------------------------


//全局宏定义

//----------------------------------------


//全局类型定义
typedef enum{FALSE = 0, TRUE = !FALSE}BOOL;

typedef enum //定义消息枚举类型
{
	MSG_NULL = 0,
	/******************************/
	//添加用户消息常量，例如：MSG_XXX,
//	MSG_KEY1_PRESS,
//	MSG_KEY2_PRESS,
	
	MSG_USART1_REC_FINISH,//串口1接收到一帧数据消息
	/******************************/
	MSG_NUM
	
}MSG_TYPE;

typedef struct 
{
	MSG_TYPE msg_type;            //系统消息类型，比如：MSG_USART1_REC_FINISH，代表串口1接收一帧数据结束
	unsigned char msg_parameter;  //系统消息参数，比如：当消息类型为MSG_USART1_REC_FINISH，msg_parameter代表帧长度
	
}system_message;

//-------------------------------------


#ifdef MAIN_CONFIG  //头文件被多个C调用时，避免变量冲突问题
	#define EXT
#else 
	#define EXT extern
#endif
	
	
//-------------------------------------
	
//常用头文件包含
#include "stm32f4xx.h"  //芯片基础头文件
#include "stdio.h"
#include "string.h"
#include "math.h"
#include <stdarg.h> 
#include <stdbool.h>
#include <stdlib.h>

	
//-------------------------------------
	
//外设驱动头文件包含
//#include "system.h"  //系统相关头文件
//#include "bsp_led.h"	

	
//----------------------------------------	

//软件包头文件包含
#include "ringbuffer.h"

//----------------------------------------
//应用相关头文件包含
//#include "task.h"


//----------------------------------------
//全局变量定义,请使用EXT修饰
EXT unsigned char g_Var;	


//----------------------------------------	
#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
