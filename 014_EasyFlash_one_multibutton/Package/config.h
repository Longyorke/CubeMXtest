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


//----------------------------------------	
#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
