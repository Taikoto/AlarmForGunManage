/******************************
单片机通过串口（波特率为2400，十六进制）获取ups数据
1、UPS参数查询命令：Q1<cr>
电脑发送: Q1<cr> (ASCII值的十六进制：51 31 0d)
UPS返回: (MMM.M NNN.N PPP.P QQQ RR.R S.SS TT.T b7b6b5b4b3b2b1b0<cr>
MMM.M（223.5）	输入电压
NNN.N（223.5）	输入电压异常转电池逆变输出时的输入电压值
PPP.P（223.0）	输出电压
QQQ（000）	    输出功率分比
RR.R（49.9）	  输出电压的频率
SS.S（27.5）	  电池电压
TTTT（25.0）	  温度（后备机返回零，预留，数据没有意义）

 7  	1: 市电异常 （ASCII值十六进制位：31）
      0: 市电正常 （ASCII值十六进制位：30）
 6  	1 : 电池低压   
      0 : 电池正常   
 5  	1 : 市电AVR模式输出   
      0 : 电池逆变输出        
 4  	1 : UPS 发生故障        
      0 : UPS没有故障         
 3  	默认1  
 2  	默认0                    
 1  	1 :输出开关打开 
      0 :输出开关关闭 
 0  	默认0           

2、电池百分比查询命令：Q2<cr>
电脑发送: Q2<cr> (ASCII值的十六进制：51 32 0d)
UPS返回: (PPP<cr>

按照十六进制显示：28 30 38 39 0d
表示电池百分比为89%

******************************/
#include "ups.h"
#include "USARTx.h"
#include "rs485.h"

//u8 Inquire1_UPS[3] = {0x51,0x31,0x0d};
//u8 UPS1_Electricity[3] = {0x51,0x32,0x0d};


//u8 read_ups_rxd_data[12] = {0};    // UPS 数据接收缓存区

#if 1

u8 InquireUPSData(void)
{
	u8 Inquire1_UPS[3] = {0x51,0x31,0x0d};
	u8 UPSPowerStatus = 0;
	u8 CheckStatus = 0; 
  
	//RX_Clear(g_pcom_ups);
	USART_transmitS(g_pcom_ups,Inquire1_UPS,3);
	delay_ms(1000);
	if(2 == g_pcom_ups->rx_state)
	{
	  if(0x28 == g_pcom_ups->rx_buf[0] && 0x0d == g_pcom_ups->rx_buf[46])
		{
			UPSPowerStatus = g_pcom_ups->rx_buf[38] - 0x30;	
			//RS485_RX_Clear();
			//RS485_Send_Data(&UPSPowerStatus,1);
			//RS485_Send_Byte(0x33);
			CheckStatus = 1;
			RX_Clear(g_pcom_ups);
		}
		else
		{
		  RX_Clear(g_pcom_ups);
      CheckStatus = 0;
		}	
	}
	//RX_Clear(g_pcom_ups);
	return UPSPowerStatus;//0 表示市电正常， 1 表示市电异常
}


u8 UPSElectricity(void)
{
	u8 Inquire1_UPS[3] = {0x51,0x31,0x0d};
	u8 UPSElectricityValue = 0;
	u8 Electricity_H = 0;
	u8 Electricity_L = 0;
	u8 CheckStatus = 0;
  //RX_Clear(g_pcom_ups);
	
	USART_transmitS(g_pcom_ups,Inquire1_UPS,3);
	delay_ms(1000);
	if(2 == g_pcom_ups->rx_state)
	{
		if(0x28 == g_pcom_ups->rx_buf[0] && 0x0d == g_pcom_ups->rx_buf[46])
		{		
			Electricity_H = g_pcom_ups->rx_buf[33] - 0x30;
			Electricity_L = g_pcom_ups->rx_buf[34] - 0x30;
			UPSElectricityValue = Electricity_H * 0x0a + Electricity_L;
			//RS485_Send_Data(&UPSElectricityValue,1);
			//RS485_Send_Byte(0x55);
			CheckStatus = 1;
		}
		else
		{
			RX_Clear(g_pcom_ups);
			CheckStatus = 0;
		}
	}
  //RX_Clear(g_pcom_ups);//为什么加了值不变？？？？？？？？？？？？
	
	return UPSElectricityValue;//电池电量
}

#endif

/**************************************************
u8 UPSElectricity(void)
{
	u8 Electricity;
	u8 Electricity_H = 0xff;
	u8 Electricity_L = 0xff;
	//RX_Clear(g_pcom_ups);
	USART_transmitS(g_pcom_ups,UPS1_Electricity,3);
	
	//RS485_RX_Clear();
	if(0x28 == g_pcom_ups->rx_buf[0] && 0x0d == g_pcom_ups->rx_buf[4])
	{
		//RS485_Send_Data(g_pcom_ups->rx_buf,5);
		Electricity_H = g_pcom_ups->rx_buf[2] - 0x30;
		Electricity_L = g_pcom_ups->rx_buf[3] - 0x30;
	}
	
	RX_Clear(g_pcom_ups);
	Electricity = Electricity_H * 10 + Electricity_L;
	
	return Electricity;
}
****************************************************/

	
