#ifndef __DATA_TYPE_H
#define __DATA_TYPE_H


#define int8 	 char
#define uint8  unsigned char
	
#define int16  short
#define uint16 unsigned short
	
#define int32  int
#define uint32 unsigned int

#define int64  long long
#define uint64 unsigned long long
	
#define my_abs(x)  (((x)>0)?(x):-(x))

/* ------------------------�����ݽṹ�嶨�塿---------------------------------*/
typedef struct{
		int Div_30_40;
		int Div_40_50;
		int Div_50_60;
		int Div_60_70;
		int Div_70_80;
		int Div_80_90;	
		int Div_90_100;	
}Div_Parameter_Type;







/* ����Ҫ���� ֱ�Ӵ��趨�õ�ģʽ(Flash�ж�ȡ)*/




#endif



