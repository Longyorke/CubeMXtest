/*
 * Copyright (c) 2021 LongYorke <1269217124@qq.com>
 * All rights reserved
 */

#include "operatingfdc.h"

TargetCountEngine_Type Paper = {
			.Finish_Flag = 2
};/*Paper���ݽṹ��*/

float CapacitanceDP= 0;

Div_Parameter_Type Div_Parameter = {30,30,30,30,30,30,30};//����ֶε�ϵ��

int Cap_Probability[110] ={0}; //���ֽ�ſ�����

float Cap_Value[10] ={0}; //��� 10�βɼ��ĵ���ֵ

float Cap_Division[50]= {0};/*�����зֺ��ֵ*/

/**
  * @brief  DataSubsection ����ֵ�ָ��ȡ����
  * @param  Cap_Division�����зֺ��ֵ��arrey���ȴ���ĵ���ֵ
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



//float Data_Diff_Value = 0.0f; //FLash �������εĲ�ֵ
float FDC2214_Paper_Data[15]  = {0.0f};//��15��ֽ
float FDC2214_Data_In_Flash[15] = {0.0f};//��Ҫд��Flash������
uint32 _cnt = 0;//����һ�μ�һ����������ֽ����


/**
  * @brief  ֽ����У׼
  * @param  None
  * @retval 0:У׼�ɹ�  1��У׼ʧ��
  */
/* ���͸������� д���״̬
01:д��ɹ�
02:д��ʧ��
03:����д��
04:��ʾhmi����
*/
void FDC2214_Data_Adjust(void)//����У׼ �洢
{
		static char str[30] = {0};

		_cnt ++;
		FDC2214_Paper_Data[HMI_Page_Number] = get_single_capacity(); /* ��ȡ���� ��ֵ*/

//		if(HMI_Page_Number > 1 && 0x01 == HMI_Debug_Write_Button){
//				Data_Diff_Value = FDC2214_Paper_Data[HMI_Page_Number] - FDC2214_Paper_Data[HMI_Page_Number-1];
//		}
		while(1)//ѭ������������
		{
				if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin))
				{
					HAL_Delay_us(100);//��������
					if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin))
					{
						FDC2214_Data_In_Flash[HMI_Page_Number] = FDC2214_Paper_Data[HMI_Page_Number] ;//���� ��Ӧҳ ����ֵ����
						Flash_Update();/* FLASH д�� */
						sprintf(str,"pagenum:%02d,cap:%f\r\n",HMI_Page_Number,FDC2214_Data_In_Flash[HMI_Page_Number]);
						HAL_UART_Transmit(&huart1,(uint8_t *)str,20,10000);
						Paper.Status = 0x01; //д��ɹ�
						printf("ֽ�Ŷ���״̬��%s\r\n",&Paper.Status);//����״̬��Ϣ
					}
				}
			else if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) || _cnt>=16)
			{
				HAL_Delay_us(100);//��������
				if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) || _cnt>=16)
				{
					_cnt = 0;
					Paper.Status = 0x04; //���	
					printf("ֽ�Ŷ���״̬��%s\r\n",&Paper.Status);//����״̬��Ϣ
				}

			}
			Short_Circuit_Detection();  //��·���
			printf("����ֽ����Ŀ��%d\r\n",HMI_Page_Number);//����ֽ����Ŀ

		}
}


/**
  * @brief  get_single_capacity ��ȡ������ֵ
  * @param  None
  * @retval ����ֵ
  * @notice 
  */
float get_single_capacity(void)
{
		static unsigned int res_CH4_DATA = 0;
		static float res_ch4 = 0.0f;
		
		FDC2214_GetChannelData(FDC2214_Channel_3, &res_CH4_DATA);//��FDC2214_Channel_3,Ҳ����ͨ��4���ŵ�res_CH4_DATA��
		res_ch4 = Cap_Calculate(&res_CH4_DATA);

		return res_ch4;
}

/* ��·�ж� */
int Short_Circuit_Detection(void)
{
    //�������� ��·��ֵ��Χ�仯
		//���ߵ�ֵ�ǳ�С��ʱ���ж�Ϊ�ܵ�����
		if( //((is_in_range(FDC2214_Paper_Data[0],FDC2214_Data_In_Flash[0],50.0f)) && HMI_Status_Flag == 1) \
			//||((is_in_range(Paper.Capacitance,FDC2214_Data_In_Flash[0],50.0f)) && HMI_Status_Flag == 2) 
			//||((is_in_range(Paper.Capacitance,FDC2214_Data_In_Flash[0],50.0f)) && HMI_Status_Flag == 4) )
				(FDC2214_Paper_Data[0] <= (FDC2214_Data_In_Flash[0]+50) )  \
				 || (Paper.Capacitance <= (FDC2214_Data_In_Flash[0]+50) ) 
		)
		
		{
				Paper.ShortStatus = 0x01;//�ж���·
				Paper.TargetNumber = 0; //�����·��Ϊ0
				printf("��·");//��ʾ��·
		}			
		else{
				printf("��·");//��ʾ����·
				Paper.ShortStatus = 0x02; //�ж�����·
		}

		return Paper.ShortStatus;
}		




void Get_Paper(void){

		for(int i = 0;i < 10;i++){
				Cap_Value[i] = get_single_capacity();//��ȡ10������
		}	
    __disable_irq(); /* �������������߹ر��ж� */
		Paper.TargetNumber = ProbablityCapacitance(Cap_Value);	//�Ƚ����ݣ���ȡ���� ֽ����
    __enable_irq();	 /* �������������߹ر��ж� */	 
}


/* ���� ֽ�� ��� */
void Capcity_Paper_Detection(void)
{
		Paper.Capacitance = get_single_capacity();/* ��ȡ���� ����ֵ*/

		/*-----------------------��·��⡢���·ֱ��return-------------------------*/
		if(0x01 == Short_Circuit_Detection())//�ж���·�򲻽������ݱȶ�
		{

//						Buzzer_Set(&Beep,1,1);//��������һ�������Ʋ���
				printf("ֽ��������%d/r/n",Paper.TargetNumber);
				HAL_Delay_us(5); //��ֱ�ӷ����ǣ���ʱ���Է���ȡ����
				return;
		}
		
		/*-----------------------��ȡ50�����ݡ�����������-------------------------*/	


				Get_Paper();/* ��ȡֽ������ */
				printf("ֽ��������%d/r/n",Paper.TargetNumber);
}

int Level = 15;//�ȼ� 0~100,�˴��Ƚ�15��ֽ
int Probability_Max = 0;
/**
  * @brief  ProbablityCapacitance ���ݷָ������ȡ���ܵ�ֽ������
  * @param  50�����ֵ��ַ
  * @retval ����ֵ
  * @notice �����ٷֱȷ��ض�Ӧ��ֽ���������ֻ�ǿ���ֵ
  */
uint8 ProbablityCapacitance(float CompareArrey[])	//���� ��Ҫ�Ƚϵ�����,�˴�û�д����ж��ٸ�����Ԫ����������level
{

		memset(Cap_Probability,0,sizeof(Cap_Probability));//��յ���ֵ��������
	
		for(int i=0;i <= Level;i++ ){//level����Ҫ�Ƚϵĵ��ݷָ�����Ԫ��?
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
				if(Cap_Probability[0] >= 5){	//ֽ���������⴦��
						Probability_Max = 1;
				}	
		}
		
		if(0 == Cap_Probability[Probability_Max-1]){
				Probability_Max = 0;
		}
		return Probability_Max;
}
