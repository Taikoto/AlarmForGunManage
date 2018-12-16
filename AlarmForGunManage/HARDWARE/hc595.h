
/*************************************************
 *  程序名称：74hc595.h头文件
 *  程序功能：74hc595驱动配置及应用文件
 *  程序作者：钟太松
 *  创建时间：2017-2-9
 *  修改时间：
 *  程序版本：V0.1
 *************************************************/

#ifndef __HC595__H__
#define __HC595__H__

/* 
 *  包含头文件
 */
#include "stm32f10x.h"


/* 
 *  宏定义
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
 *  函数名称：74HC595_Init
 *  函数功能：继电器部分74HC595初始化函数
 *  入口参数：void
 *  出口参数：void
 ************************************************/
extern void HC595_Init(void);


/*************************************************
 *  函数名称：HC595SendData
 *  函数功能：HC595向SPI总线发送数据
 *  入口参数：unsigned char ucSendValue 要发送的数据 
 *  出口参数：void
 ************************************************/
extern void HC595SendData(unsigned char ucSendValue);

/*************************************************
 *  函数名称：HC595_IO_Out_Updata_Status
 *  函数功能：HC595输出口输出数据
 *  入口参数：unsigned char ucStatus 要发送的数据 
 *  出口参数：void
 ************************************************/
extern void HC595_IO_Out(void );

extern void HC595_IO_Out_Updata_Status(unsigned char ucStatus);    // 此函数供外部调用

extern void Open_Lock(void);     //  开锁

extern void Close_Lock(void);   // 关锁        道闸开启后延时5ms 马上执行关闭命令。延时时间不宜超过10ms

extern void Open_Alarm(void);     //  开锁

extern void Close_Alarm(void);   // 关锁        道闸开启后延时5ms 马上执行关闭命令。延时时间不宜超过10ms
 

extern unsigned char Lock_Control_flag;
extern unsigned char Alarm_Control_flag;

#endif
