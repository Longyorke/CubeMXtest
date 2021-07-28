/*
 * Copyright (c) 2021 LongYorke <1269217124@qq.com>
 * All rights reserved
 */

#include "operatingfdc.h"

TargetCountEngine_Type Paper = {
			.Finish_Flag = 2
};/*Paper数据结构体*/

float CapacitanceDP= 0;

Div_Parameter_Type Div_Parameter = {30,30,30,30,30,30,30};//区间分段的系数

int Cap_Probability[110] ={0}; //存放纸张可能性

float Cap_Value[10] ={0}; //存放 10次采集的电容值

float Cap_Division[50]= {0};/*电容切分后的值*/

/**
  * @brief  DataSubsection 电容值分割，获取区间
  * @param  Cap_Division电容切分后的值、arrey事先存入的电容值
  * @retval 
  * @notice 
  */
void DataSubsection(float Cap_Division[],float arrey[])
{

		static int rec = 1;
		
		for(int i = 2;i <= 30;i++){
				CapacitanceDP = (arrey[i-1]-arrey[i]) /2.0f;
				Cap_Division[i-1]= arrey[i-1]-CapacitanceDP;

		}
		for(int i=31;i<=40;i++){
				CapacitanceDP = Div_Parameter.Div_30_40*(arrey[i-1]-arrey[i]) /100.0f;
				Cap_Division[i-1]= arrey[i-1]-CapacitanceDP;
		}
		for(int i=41;i<=50;i++){
				CapacitanceDP = Div_Parameter.Div_40_50*(arrey[i-1]-arrey[i]) /100.0f;
				Cap_Division[i-1]= arrey[i-1]-CapacitanceDP;
		}
		
		for(int i=51;i<=60;i++){
				CapacitanceDP = Div_Parameter.Div_50_60*(arrey[i-1]-arrey[i]) /100.0f;
				Cap_Division[i-1]= arrey[i-1]-CapacitanceDP;
		}
		for(int i=61;i<=70;i++){
				CapacitanceDP = Div_Parameter.Div_60_70*(arrey[i-1]-arrey[i]) /100.0f;
				Cap_Division[i-1]= arrey[i-1]-CapacitanceDP;
		}
		for(int i=71;i<=80;i++){
				CapacitanceDP = Div_Parameter.Div_70_80*(arrey[i-1]-arrey[i]) /100.0f;
				Cap_Division[i-1]= arrey[i-1]-CapacitanceDP;
		}
		for(int i=81;i<=90;i++){
				CapacitanceDP = Div_Parameter.Div_80_90*(arrey[i-1]-arrey[i]) /100.0f;
				Cap_Division[i-1]= arrey[i-1]-CapacitanceDP;
		}				
		for(int i=91;i<=100;i++){
				CapacitanceDP = Div_Parameter.Div_90_100*(arrey[i-1]-arrey[i]) /100.0f;
				Cap_Division[i-1]= arrey[i-1]-CapacitanceDP;
		}				
		if(rec==1){
				Cap_Division[0] =arrey[1]+(arrey[1]-arrey[2]) /2.0f;
				rec = 0;
		}
}



//float Data_Diff_Value = 0.0f; //FLash 上下两次的差值
float FDC2214_Paper_Data[15]  = {0.0f};//测15张纸
float FDC2214_Data_In_Flash[15] = {0.0f};//将要写入Flash的数组
uint32 _cnt = 0;//调用一次加一，用于限制纸张数


/**
  * @brief  纸张数校准
  * @param  None
  * @retval 0:校准成功  1：校准失败
  */
/* 发送给串口屏 写入的状态
01:写入成功
02:写入失败
03:正在写入
04:提示hmi清屏
*/
void FDC2214_Data_Adjust(void)//数据校准 存储
{
		static char str[30] = {0};

		_cnt ++;
		FDC2214_Paper_Data[HMI_Page_Number] = get_single_capacity(); /* 获取电容 数值*/

//		if(HMI_Page_Number > 1 && 0x01 == HMI_Debug_Write_Button){
//				Data_Diff_Value = FDC2214_Paper_Data[HMI_Page_Number] - FDC2214_Paper_Data[HMI_Page_Number-1];
//		}
		while(1)//循环至按键按下
		{
				if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin))
				{
					HAL_Delay_us(100);//按键消抖
					if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin))
					{
						FDC2214_Data_In_Flash[HMI_Page_Number] = FDC2214_Paper_Data[HMI_Page_Number] ;//单板 对应页 电容值保存
						Flash_Update();/* FLASH 写入 */
						sprintf(str,"pagenum:%02d,cap:%f\r\n",HMI_Page_Number,FDC2214_Data_In_Flash[HMI_Page_Number]);
						HAL_UART_Transmit(&huart1,(uint8_t *)str,20,10000);
						Paper.Status = 0x01; //写入成功
						printf("纸张对象状态：%s\r\n",&Paper.Status);//返回状态信息
					}
				}
			else if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) || _cnt>=16)
			{
				HAL_Delay_us(100);//按键消抖
				if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) || _cnt>=16)
				{
					_cnt = 0;
					Paper.Status = 0x04; //清空	
					printf("纸张对象状态：%s\r\n",&Paper.Status);//返回状态信息
				}

			}
			Short_Circuit_Detection();  //短路检测
			printf("所测纸张数目：%d\r\n",HMI_Page_Number);//所测纸张数目

		}
}


/**
  * @brief  get_single_capacity 获取极板容值
  * @param  None
  * @retval 电容值
  * @notice 
  */
float get_single_capacity(void)
{
		static unsigned int res_CH4_DATA = 0;
		static float res_ch4 = 0.0f;
		
		FDC2214_GetChannelData(FDC2214_Channel_3, &res_CH4_DATA);//读FDC2214_Channel_3,也就是通道4，放到res_CH4_DATA中
		res_ch4 = Cap_Calculate(&res_CH4_DATA);

		return res_ch4;
}

/* 短路判断 */
int Short_Circuit_Detection(void)
{
    //当数据在 短路数值范围变化
		//或者当值非常小的时候，判定为受到干扰
		if( //((is_in_range(FDC2214_Paper_Data[0],FDC2214_Data_In_Flash[0],50.0f)) && HMI_Status_Flag == 1) \
			//||((is_in_range(Paper.Capacitance,FDC2214_Data_In_Flash[0],50.0f)) && HMI_Status_Flag == 2) 
			//||((is_in_range(Paper.Capacitance,FDC2214_Data_In_Flash[0],50.0f)) && HMI_Status_Flag == 4) )
				(FDC2214_Paper_Data[0] <= (FDC2214_Data_In_Flash[0]+50) )  \
				 || (Paper.Capacitance <= (FDC2214_Data_In_Flash[0]+50) ) 
		)
		
		{
				Paper.ShortStatus = 0x01;//判定短路
				Paper.TargetNumber = 0; //如果短路即为0
				printf("短路");//提示短路
		}			
		else{
				printf("短路");//提示不短路
				Paper.ShortStatus = 0x02; //判定不短路
		}

		return Paper.ShortStatus;
}		




void Get_Paper(void){

		for(int i = 0;i < 10;i++){
				Cap_Value[i] = get_single_capacity();//获取10组数据
		}	
    __disable_irq(); /* 调度器上锁或者关闭中断 */
		Paper.TargetNumber = ProbablityCapacitance(Cap_Value);	//比较数据，获取最终 纸张数
    __enable_irq();	 /* 调度器上锁或者关闭中断 */	 
}


/* 电容 纸张 检测 */
void Capcity_Paper_Detection(void)
{
		Paper.Capacitance = get_single_capacity();/* 获取单次 电容值*/

		/*-----------------------短路检测、如短路直接return-------------------------*/
		if(0x01 == Short_Circuit_Detection())//判定短路则不进行数据比对
		{

//						Buzzer_Set(&Beep,1,1);//蜂鸣器响一声或上云操作
				printf("纸张数量：%d/r/n",Paper.TargetNumber);
				HAL_Delay_us(5); //当直接返回是，延时，以防读取过快
				return;
		}
		
		/*-----------------------获取50组数据、解算落区间-------------------------*/	


				Get_Paper();/* 获取纸张数量 */
				printf("纸张数量：%d/r/n",Paper.TargetNumber);
}

int Level = 15;//等级 0~100,此处比较15张纸
int Probability_Max = 0;
/**
  * @brief  ProbablityCapacitance 根据分割函数，获取可能的纸张数量
  * @param  50组电容值地址
  * @retval 电容值
  * @notice 按最大百分比返回对应的纸张数，因此只是可能值
  */
uint8 ProbablityCapacitance(float CompareArrey[])	//传入 需要比较的数据,此处没有传入有多少个数组元素所以用了level
{

		memset(Cap_Probability,0,sizeof(Cap_Probability));//清空电容值落点可能性
	
		for(int i=0;i <= Level;i++ ){//level是需要比较的电容分割区的元素?
				for(int j=0; j<10 ;j++){
						if( (CompareArrey[j] < Cap_Division[i])  && (CompareArrey[j] >= Cap_Division[i+1])){
								Cap_Probability[i]++;
						}
				}
		}
		for(int n = 0;n < Level ;n++){
				if(Cap_Probability[n] > Cap_Probability[Probability_Max]){
						Probability_Max = (n + 1);
				}
				if(Cap_Probability[0] >= 5){	//纸张数的特殊处理
						Probability_Max = 1;
				}	
		}
		
		if(0 == Cap_Probability[Probability_Max-1]){
				Probability_Max = 0;
		}
		return Probability_Max;
}
