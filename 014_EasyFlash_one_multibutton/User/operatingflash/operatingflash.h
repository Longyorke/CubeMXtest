/*
 * Copyright (c) 2021 LongYorke <1269217124@qq.com>
 * All rights reserved
 */

#ifndef _OPERATION_FLASH_H_
#define _OPERATION_FLASH_H_

#include "config.h"
#include "main.h"
#include "DataType.h"

/** @brief  FDC2214_Data_In_Flash 将要写入Flash的数组*/
extern float FDC2214_Data_In_Flash[15];
/** @brief  Div_Parameter 区间分段的系数*/
extern Div_Parameter_Type Div_Parameter;

//FLASH起始地址   W25Q128 16M 的容量分为 256 个块（Block）
#define Nor_FLASH_ADDRESS    (0x0000) 	//W25Q128 FLASH的 普通起始地址   【第个扇区】

#define IMP_FLASH_ADDRESS    (0x1000) 	//W25Q128 FLASH的 重要参数起始地址 【第个扇区】



/** @brief  Flash_Update 更新 普通参数*/
void Flash_Update(void);



#endif
