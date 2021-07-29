/*
 * Copyright (c) 2021 LongYorke <1269217124@qq.com>
 * All rights reserved
 */

#ifndef _OPERATION_FLASH_H_
#define _OPERATION_FLASH_H_

#include "config.h"
#include "main.h"
#include "DataType.h"

/** @brief  FDC2214_Data_In_Flash ��Ҫд��Flash������*/
extern float FDC2214_Data_In_Flash[15];
/** @brief  Div_Parameter ����ֶε�ϵ��*/
extern Div_Parameter_Type Div_Parameter;

//FLASH��ʼ��ַ   W25Q128 16M ��������Ϊ 256 ���飨Block��
#define Nor_FLASH_ADDRESS    (0x0000) 	//W25Q128 FLASH�� ��ͨ��ʼ��ַ   ���ڸ�������

#define IMP_FLASH_ADDRESS    (0x1000) 	//W25Q128 FLASH�� ��Ҫ������ʼ��ַ ���ڸ�������



/** @brief  Flash_Update ���� ��ͨ����*/
void Flash_Update(void);



#endif
