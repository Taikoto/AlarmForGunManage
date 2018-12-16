
/*************************************************
 *  �������ƣ�74hc595.hͷ�ļ�
 *  �����ܣ�74hc595�������ü�Ӧ���ļ�
 *  �������ߣ���̫��
 *  ����ʱ�䣺2017-2-9
 *  �޸�ʱ�䣺
 *  ����汾��V0.1
 *************************************************/

#ifndef __HC595__H__
#define __HC595__H__

/* 
 *  ����ͷ�ļ�
 */
#include "stm32f10x.h"


/* 
 *  �궨��
 */
#define S_CLK    GPIO_Pin_14
#define R_CLK    GPIO_Pin_15
#define MOSI     GPIO_Pin_8

#define Fill_on          0x01         //  Q0
#define Fill_off         0xFE

#define Led1_on          0x02        //  Q1
#define Led1_off         0xFD

#define Led2_on          0x04         //  Q2
#define Led2_off         0xFB

#define NrfCE_H          0x08        //  Q3
#define NrfCE_L          0xF7

#define NrfData_H        0x10         //  Q4
#define NrfData_L        0xEF

#define Alarm_on         0xDF       
#define Alarm_off        0x20         //  Q5

#define Lock1_on         0xBF   
#define Lock1_off        0x40         //  Q6

#define Lock2_on         0x80         //  Q7
#define Lock2_off        0x7F

/*************************************************
 *  �������ƣ�74HC595_Init
 *  �������ܣ��̵�������74HC595��ʼ������
 *  ��ڲ�����void
 *  ���ڲ�����void
 ************************************************/
extern void HC595_Init(void);


/*************************************************
 *  �������ƣ�HC595SendData
 *  �������ܣ�HC595��SPI���߷�������
 *  ��ڲ�����unsigned char ucSendValue Ҫ���͵����� 
 *  ���ڲ�����void
 ************************************************/
extern void HC595SendData(unsigned char ucSendValue);

/*************************************************
 *  �������ƣ�HC595_IO_Out_Updata_Status
 *  �������ܣ�HC595������������
 *  ��ڲ�����unsigned char ucStatus Ҫ���͵����� 
 *  ���ڲ�����void
 ************************************************/
extern void HC595_IO_Out(void );

extern void HC595_IO_Out_Updata_Status(unsigned char ucStatus);    // �˺������ⲿ����

extern void Open_Lock(void);     //  ����

extern void Close_Lock(void);   // ����        ��բ��������ʱ5ms ����ִ�йر������ʱʱ�䲻�˳���10ms

extern void Open_Alarm(void);     //  ����

extern void Close_Alarm(void);   // ����        ��բ��������ʱ5ms ����ִ�йر������ʱʱ�䲻�˳���10ms
 

extern unsigned char Lock_Control_flag;
extern unsigned char Alarm_Control_flag;

#endif
