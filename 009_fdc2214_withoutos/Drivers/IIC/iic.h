#ifndef _MYIIC_H
#define _MYIIC_H
#include "gpio.h"
//////////////////////////////////////////////////////////////////////////////////	 
//????????ѧϰʹ???δ??????ɣ??????????????
//ALIENTEK STM32F429??????
//IIC??????	   
//?????@ALIENTEK
//????̳:www.openedv.com
//??????:2016/1/13
//?汾??V1.0
//???????????????
//Copyright(C) ???????ӿƼ?????˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//IO?????
#define SDA_IN()  {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=0<<5*2;}	//PH5??ģʽ
#define SDA_OUT() {GPIOH->MODER&=~(3<<(5*2));GPIOH->MODER|=1<<5*2;} //PH5???ģʽ
//IO???
#define IIC_SCL   PHout(4) //SCL
#define IIC_SDA   PHout(5) //SDA
#define READ_SDA  PHin(5)  //??SDA

//IIC????????
void IIC_Init(void);                //??ʼ??IIC??O??			 
void IIC_Start(void);				//???IIC??ʼ???
void IIC_Stop(void);	  			//???IICֹͣ???
void IIC_Send_Byte(uint8_t txd);			//IIC???һ?????
uint8_t IIC_Read_Byte(unsigned char ack);//IIC??ȡһ?????
uint8_t IIC_Wait_Ack(void); 				//IIC?ȴ?ACK???
void IIC_Ack(void);					//IIC???ACK???
void IIC_NAck(void);				//IIC?????ACK???

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	 
#endif

