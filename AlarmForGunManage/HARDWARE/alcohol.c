#include "alcohol.h"
#include "adc2.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   
extern __IO uint16_t ADC2_ConvertedValue; //==> volatile unsigned short ADC_ConvertedValue
//初始化PB12和PB13为输出口.并使能这两个口的时钟		    
//LED IO初始化
void ALCOHOL_Init(void)
{
	ADC2_Init();
}

float ALCOHOL_ReadData(void)
{
	// 计算的酒精浓度值
	float Current_AlcoholValue;
	// 局部变量，用于保存转换计算后的电压值 	 
	float ADC2_ConvertedValueLocal;
	
	ADC2_ConvertedValueLocal =(float)(2*ADC2_ConvertedValue)/4096*3.3;
	Current_AlcoholValue = (ADC2_ConvertedValueLocal - ReferenceValue) * 20;

	return Current_AlcoholValue;
}


