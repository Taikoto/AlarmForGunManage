/*******************************************************
 *  ��������: USART3.h
 *  �����ܣ�����3���ó�ʼ��ͷ�ļ�
 *  �������ߣ���̫��
 *  ����ʱ�䣺2015-11-19
 *  �޸�ʱ�䣺
 *  ����汾��V1.0
 ******************************************************/
 
#ifndef __USART3__H_
#define	__USART3__H_

/*
 *  ����ͷ�ļ�
 */ 
#include "stm32f10x.h"


//#define USART3_RX_LEN       USART_RX_LEN

extern u8 USART3_RX[];

extern volatile vu16 usart_rx3_num ;
extern volatile vu16 usart_rx3_use;
extern volatile u8 usart_rx3_full;   //0 or 1
extern volatile u8 usart_rx3_end;    /// timer ticks watch on rx , pass 20ms take as end transfer
extern volatile u8  rx3_begin_watching;
extern volatile vu16 last_usart_rx3_num;


extern u8 usart3_rx_buf[];
extern vu16 usart3_recvd_len;


/******************************************************
 * �������ƣ�uart3_init
 * �������ܣ�USART3 ��ʼ������
 * ��ڲ�����void

* ���ڲ�����
*******************************************************/ 
extern void uart3_init(u32 bound);

/******************************************************
 * �������ƣ�USART3_transmit
 * �������ܣ�USART3 ����һ���ֽ�
 * ��ڲ�����unsigned char byte
 * ���ڲ�����
*******************************************************/ 
extern void USART3_transmit(unsigned char byte);
/******************************************************
 * �������ƣ�USART3_transmitS
 * �������ܣ�USART3 ���Ͷ���ֽ����飻dat�����͵��ֽ���������num�����͵��ֽ���
 * ��ڲ�����unsigned char *dat,unsigned char num
 * ���ڲ��������͵�����   
*******************************************************/ 
extern void USART3_transmitS(unsigned char *dat,unsigned int num);


extern int USART3_recv_buf(void);

extern int if_USART3_has_new_data(void);
extern int USART3_clear(void);
extern vu16	rx3_watching(void);


#endif