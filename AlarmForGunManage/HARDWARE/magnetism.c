#include "magnetism.h"

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


#define MAGNETISM_ON  0
#define MAGNETISM_OFF 1



//��ʼ��PB5Ϊ�����.��ʹ��ʱ��		    
//ALARM IO��ʼ��
void MAGNETISM_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //MAGNETISM-->PC.13 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //�������
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.13
  //GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PC.13 �����
}

 
