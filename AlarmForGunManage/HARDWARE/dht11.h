#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DHT11������ʪ�ȴ�������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//IO��������
#define DHT11_IO_IN()  {GPIOC->CRH&=0XF0FFFFFF;GPIOC->CRH|=8<<24;}
#define DHT11_IO_OUT() {GPIOC->CRH&=0XF0FFFFFF;GPIOC->CRH|=3<<24;}
////IO��������											   
#define	DHT11_DQ_OUT PCout(14) //���ݶ˿�	PC14 
#define	DHT11_DQ_IN  PCin(14)  //���ݶ˿�	PC14


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif














