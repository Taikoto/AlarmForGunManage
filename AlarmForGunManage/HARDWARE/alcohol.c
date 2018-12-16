#include "alcohol.h"
#include "adc2.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   
extern __IO uint16_t ADC2_ConvertedValue; //==> volatile unsigned short ADC_ConvertedValue
//��ʼ��PB12��PB13Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void ALCOHOL_Init(void)
{
	ADC2_Init();
}

float ALCOHOL_ReadData(void)
{
	// ����ľƾ�Ũ��ֵ
	float Current_AlcoholValue;
	// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
	float ADC2_ConvertedValueLocal;
	
	ADC2_ConvertedValueLocal =(float)(2*ADC2_ConvertedValue)/4096*3.3;
	Current_AlcoholValue = (ADC2_ConvertedValueLocal - ReferenceValue) * 20;

	return Current_AlcoholValue;
}


