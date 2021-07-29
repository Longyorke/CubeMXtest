/*
 * Copyright (c) 2021 LongYorke <1269217124@qq.com>
 * All rights reserved
 */

#ifndef _OPERATION_FDC_H_
#define _OPERATION_FDC_H_

#include "config.h"
#include "main.h"
#include "operatingflash.h"

typedef struct
{
	uint8_t Status;      //检测时状态
	uint8_t ShortStatus; //短路的状态 0x01:判定短路 0x02:判定不短路
	uint8_t Finish_Flag;  //读取完成的标志 02:未读  01：成功写入Flash 04：清空
	uint8_t TargetNumber;  //纸张数量
	float Capacitance;
	
	int Time; //时间


	
}TargetCountEngine_Type;//纸张测数器状态

/*电容切分后的值*/
extern float Cap_Division[50];


/** @brief  DataSubsection 电容值分割，获取区间*/
void DataSubsection(float Cap_Division[],float arrey[]);
/** @brief  FDC2214_Data_Adjust 纸张数校准*/
uint8_t FDC2214_Data_Adjust(void);
/** @brief  get_single_capacity 获取极板容值*/
float get_single_capacity(void);
/** @brief  Short_Circuit_Detection  短路判断*/
int Short_Circuit_Detection(void);
/** @brief  Get_Paper  获得纸张*/
void Get_Paper(void);
/** @brief  Capcity_Paper_Detection  电容 纸张 检测*/
void Capcity_Paper_Detection(void);
/** @brief  ProbablityCapacitance  根据分割函数，获取可能的纸张数量*/
uint8 ProbablityCapacitance(float CompareArrey[]);



#endif
