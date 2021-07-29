/*
 * Copyright (c) 2021 LongYorke <1269217124@qq.com>
 * All rights reserved
 */

#include "operatingflash.h"



/* FLASH 更新 普通参数 */
void Flash_Update(void)
{
		ef_port_erase(Nor_FLASH_ADDRESS,4);	//【普通参数FLASH】先擦后写  擦除的为一个扇区4096 Byte 

		for(int i = 0;i <16;i++){
				ef_port_write(Nor_FLASH_ADDRESS + 4*(i) ,(uint32 *)&FDC2214_Data_In_Flash[i],4); //
		}
	
		
		ef_port_write(Nor_FLASH_ADDRESS + 4*(104) ,(uint32 *)&Div_Parameter.Div_30_40,4); 
		ef_port_write(Nor_FLASH_ADDRESS + 4*(105) ,(uint32 *)&Div_Parameter.Div_40_50,4);
		ef_port_write(Nor_FLASH_ADDRESS + 4*(106) ,(uint32 *)&Div_Parameter.Div_50_60,4); 
		ef_port_write(Nor_FLASH_ADDRESS + 4*(107) ,(uint32 *)&Div_Parameter.Div_60_70,4); 
		ef_port_write(Nor_FLASH_ADDRESS + 4*(108) ,(uint32 *)&Div_Parameter.Div_70_80,4); 
		ef_port_write(Nor_FLASH_ADDRESS + 4*(109) ,(uint32 *)&Div_Parameter.Div_80_90,4); 
		ef_port_write(Nor_FLASH_ADDRESS + 4*(113) ,(uint32 *)&Div_Parameter.Div_90_100,4); 			
}	

