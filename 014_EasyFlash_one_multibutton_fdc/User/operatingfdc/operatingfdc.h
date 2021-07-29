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
	uint8_t Status;      //���ʱ״̬
	uint8_t ShortStatus; //��·��״̬ 0x01:�ж���· 0x02:�ж�����·
	uint8_t Finish_Flag;  //��ȡ��ɵı�־ 02:δ��  01���ɹ�д��Flash 04�����
	uint8_t TargetNumber;  //ֽ������
	float Capacitance;
	
	int Time; //ʱ��


	
}TargetCountEngine_Type;//ֽ�Ų�����״̬

/*�����зֺ��ֵ*/
extern float Cap_Division[50];


/** @brief  DataSubsection ����ֵ�ָ��ȡ����*/
void DataSubsection(float Cap_Division[],float arrey[]);
/** @brief  FDC2214_Data_Adjust ֽ����У׼*/
uint8_t FDC2214_Data_Adjust(void);
/** @brief  get_single_capacity ��ȡ������ֵ*/
float get_single_capacity(void);
/** @brief  Short_Circuit_Detection  ��·�ж�*/
int Short_Circuit_Detection(void);
/** @brief  Get_Paper  ���ֽ��*/
void Get_Paper(void);
/** @brief  Capcity_Paper_Detection  ���� ֽ�� ���*/
void Capcity_Paper_Detection(void);
/** @brief  ProbablityCapacitance  ���ݷָ������ȡ���ܵ�ֽ������*/
uint8 ProbablityCapacitance(float CompareArrey[]);



#endif
