#ifndef __VIBRATION_H
#define __VIBRATION_H	 
#include "sys.h"
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
#define VIBRATION0_DQ_IN PBin(8)// PB8
#define VIBRATION1_DQ_IN PBin(9)// PB9	


/* ���κ꣬��������������һ��ʹ�� */
#define VIBRATION0(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_8)



void VIBRATION_Init(void);//��ʼ��

		 				    
#endif
