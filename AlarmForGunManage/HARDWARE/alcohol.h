#ifndef __ALCOHOL_H
#define __ALCOHOL_H	 
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
	

//�޾ƾ��ǵ�ѹֵΪ1 
#define ReferenceValue  1


void ALCOHOL_Init(void);//��ʼ��

float ALCOHOL_ReadData(void);
		 				    
#endif
