#ifndef  __CONFIG_H__
#define  __CONFIG_H__

//无符号类型的定义

	
//----------------------------------------


//全局宏定义

//----------------------------------------


//全局类型定义
//typedef enum{FALSE = 0, TRUE = !FALSE}BOOL;

typedef enum //定义消息枚举类型
{
	MSG_NULL = 0,
	/******************************/
	//添加用户消息常量，例如：MSG_XXX,
//	MSG_KEY1_PRESS,
//	MSG_KEY2_PRESS,
//	MSG_AT24CXX_TEST,
	MSG_W25QXX_TEST,
	MSG_EASYFLASH_TEST,
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
	#include "spi.h"
	#include "usart.h"
//#include "bsp_led.h"	
//#include "bsp_usart.h"
//#include "bsp_key.h"
//#include "bsp_iwdg.h"
//#include "bsp_timer.h"
//#include "bsp_adc.h"
//#include "bsp_at24cxx.h"
//#include "bsp_w25qxx.h"
	
//----------------------------------------	

//软件包头文件包含
//#include "multi_timer.h"
#include "multi_button.h"
#include "sfud.h"
#include "ringbuffer.h"
#include "easyflash.h"
#include "iic.h"
#include "fdc2214.h"

//----------------------------------------
//应用相关头文件包含
//#include "task.h"


//----------------------------------------
//全局变量定义,请使用EXT修饰
EXT unsigned char g_Var;	

EXT struct rt_ringbuffer msg_ring_buf;//存储消息的环形队列,在main.c中初始化


//----------------------------------------	
//外部函数调用
EXT void w25qxx_test(void);
EXT void test_env(void);
EXT void HAL_Delay_us(uint16_t us);


//----------------------------------------	

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014 
#define GPIOJ_ODR_ADDr    (GPIOJ_BASE+20) //0x40022414
#define GPIOK_ODR_ADDr    (GPIOK_BASE+20) //0x40022814

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 
#define GPIOJ_IDR_Addr    (GPIOJ_BASE+16) //0x40022410 
#define GPIOK_IDR_Addr    (GPIOK_BASE+16) //0x40022810 

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入

#define PJout(n)   BIT_ADDR(GPIOJ_ODR_Addr,n)  //输出 
#define PJin(n)    BIT_ADDR(GPIOJ_IDR_Addr,n)  //输入

#define PKout(n)   BIT_ADDR(GPIOK_ODR_Addr,n)  //输出 
#define PKin(n)    BIT_ADDR(GPIOK_IDR_Addr,n)  //输入

//----------------------------------------	
#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
