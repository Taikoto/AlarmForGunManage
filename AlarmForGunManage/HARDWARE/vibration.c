#include "vibration.h"

#include "vibration_adc1.h"
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

//��ʼ��PB8��PB9Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
#if 1
void VIBRATION_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;				 //VIBRATION-->PB.8 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.8
  //GPIO_SetBits(GPIOB,GPIO_Pin_8);						 //PB.8 �����

  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	    		 //VIBRATION-->PB.9 �˿�����, �������
  //GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
  //GPIO_SetBits(GPIOB,GPIO_Pin_9); 						 //PB.9 ����� 
}

#endif

#if 0	
void VIBRATION_Init(void)
{
	Vibration_ADC1_Init();
}

#endif 
