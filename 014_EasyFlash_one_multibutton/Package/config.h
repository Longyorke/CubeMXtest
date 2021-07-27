#ifndef  __CONFIG_H__
#define  __CONFIG_H__

//�޷������͵Ķ���

	
//----------------------------------------


//ȫ�ֺ궨��

//----------------------------------------


//ȫ�����Ͷ���
//typedef enum{FALSE = 0, TRUE = !FALSE}BOOL;

typedef enum //������Ϣö������
{
	MSG_NULL = 0,
	/******************************/
	//����û���Ϣ���������磺MSG_XXX,
//	MSG_KEY1_PRESS,
//	MSG_KEY2_PRESS,
//	MSG_AT24CXX_TEST,
	MSG_W25QXX_TEST,
	MSG_EASYFLASH_TEST,
	MSG_USART1_REC_FINISH,//����1���յ�һ֡������Ϣ
	/******************************/
	MSG_NUM
	
}MSG_TYPE;

typedef struct 
{
	MSG_TYPE msg_type;            //ϵͳ��Ϣ���ͣ����磺MSG_USART1_REC_FINISH��������1����һ֡���ݽ���
	unsigned char msg_parameter;  //ϵͳ��Ϣ���������磺����Ϣ����ΪMSG_USART1_REC_FINISH��msg_parameter����֡����
	
}system_message;

//-------------------------------------


#ifdef MAIN_CONFIG  //ͷ�ļ������C����ʱ�����������ͻ����
	#define EXT
#else 
	#define EXT extern
#endif
	
	
//-------------------------------------
	
//����ͷ�ļ�����
#include "stm32f4xx.h"  //оƬ����ͷ�ļ�
#include "stdio.h"
#include "string.h"
#include "math.h"
#include <stdarg.h> 
#include <stdbool.h>
#include <stdlib.h>

	
//-------------------------------------
	
//��������ͷ�ļ�����
//#include "system.h"  //ϵͳ���ͷ�ļ�
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

//�����ͷ�ļ�����
//#include "multi_timer.h"
#include "multi_button.h"
#include "sfud.h"
#include "ringbuffer.h"
#include "easyflash.h"
#include "iic.h"
#include "fdc2214.h"

//----------------------------------------
//Ӧ�����ͷ�ļ�����
//#include "task.h"


//----------------------------------------
//ȫ�ֱ�������,��ʹ��EXT����
EXT unsigned char g_Var;	

EXT struct rt_ringbuffer msg_ring_buf;//�洢��Ϣ�Ļ��ζ���,��main.c�г�ʼ��


//----------------------------------------	
//�ⲿ��������
EXT void w25qxx_test(void);
EXT void test_env(void);
EXT void HAL_Delay_us(uint16_t us);


//----------------------------------------	

//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).M4ͬM3����,ֻ�ǼĴ�����ַ����.
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
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

//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //��� 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //����

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //��� 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //����

#define PJout(n)   BIT_ADDR(GPIOJ_ODR_Addr,n)  //��� 
#define PJin(n)    BIT_ADDR(GPIOJ_IDR_Addr,n)  //����

#define PKout(n)   BIT_ADDR(GPIOK_ODR_Addr,n)  //��� 
#define PKin(n)    BIT_ADDR(GPIOK_IDR_Addr,n)  //����

//----------------------------------------	
#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
