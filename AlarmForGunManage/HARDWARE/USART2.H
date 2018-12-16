/*******************************************************
 *  ��������: USART2.h
 *  �����ܣ�����2���ó�ʼ��ͷ�ļ�
 *  �������ߣ���̫��
 *  ����ʱ�䣺2015-11-19
 *  �޸�ʱ�䣺
 *  ����汾��V1.0
 ******************************************************/
 
#ifndef __USART2__H_
#define	__USART2__H_

/*
 *  ����ͷ�ļ�
 */ 
#include "stm32f10x.h"


#define USART2_RX_LEN       USART_RX_LEN


extern u8 USART2_RX[];
extern volatile vu16 usart_rx2_num ;
extern volatile vu16 usart_rx2_use;
extern volatile u8 usart_rx2_full;   //0 or 1
extern volatile u8 usart_rx2_end;    /// timer ticks watch on rx , pass 20ms take as end transfer
extern volatile u8  rx2_begin_watching;
extern volatile vu16 last_usart_rx2_num;

extern u8 usart2_rx_buf[];
extern vu16 usart2_recvd_len;

 

/******************************************************
 * �������ƣ�uart2_init
 * �������ܣ�USART2 ��ʼ������
 * ��ڲ�����void

* ���ڲ�����
*******************************************************/ 
extern void uart2_init(u32 bound);

/******************************************************
 * �������ƣ�USART2_transmit
 * �������ܣ�USART2 ����һ���ֽ�
 * ��ڲ�����unsigned char byte
 * ���ڲ�����
*******************************************************/ 
extern void USART2_transmit(unsigned char byte);
/******************************************************
 * �������ƣ�USART2_transmitS
 * �������ܣ�USART2 ���Ͷ���ֽ����飻dat�����͵��ֽ���������num�����͵��ֽ���
 * ��ڲ�����unsigned char *dat,unsigned char num
 * ���ڲ��������͵�����   
*******************************************************/ 
extern void USART2_transmitS(unsigned char *dat,unsigned int num);


//extern int USART_recv_buf(u8 *rx_buf,u8 *usart_buf,int *p_rx_use,int *p_rx_num);
extern int USART2_recv_buf(void);
extern int if_USART2_has_new_data(void);
extern int USART2_clear(void);

extern vu16	rx2_watching(void);

#endif