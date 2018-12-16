#ifndef __ALCOHOL_H
#define __ALCOHOL_H	 
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	

//无酒精是电压值为1 
#define ReferenceValue  1


void ALCOHOL_Init(void);//初始化

float ALCOHOL_ReadData(void);
		 				    
#endif
