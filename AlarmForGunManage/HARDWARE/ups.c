/******************************
��Ƭ��ͨ�����ڣ�������Ϊ2400��ʮ�����ƣ���ȡups����
1��UPS������ѯ���Q1<cr>
���Է���: Q1<cr> (ASCIIֵ��ʮ�����ƣ�51 31 0d)
UPS����: (MMM.M NNN.N PPP.P QQQ RR.R S.SS TT.T b7b6b5b4b3b2b1b0<cr>
MMM.M��223.5��	�����ѹ
NNN.N��223.5��	�����ѹ�쳣ת���������ʱ�������ѹֵ
PPP.P��223.0��	�����ѹ
QQQ��000��	    ������ʷֱ�
RR.R��49.9��	  �����ѹ��Ƶ��
SS.S��27.5��	  ��ص�ѹ
TTTT��25.0��	  �¶ȣ��󱸻������㣬Ԥ��������û�����壩

 7  	1: �е��쳣 ��ASCIIֵʮ������λ��31��
      0: �е����� ��ASCIIֵʮ������λ��30��
 6  	1 : ��ص�ѹ   
      0 : �������   
 5  	1 : �е�AVRģʽ���   
      0 : ���������        
 4  	1 : UPS ��������        
      0 : UPSû�й���         
 3  	Ĭ��1  
 2  	Ĭ��0                    
 1  	1 :������ش� 
      0 :������عر� 
 0  	Ĭ��0           

2����ذٷֱȲ�ѯ���Q2<cr>
���Է���: Q2<cr> (ASCIIֵ��ʮ�����ƣ�51 32 0d)
UPS����: (PPP<cr>

����ʮ��������ʾ��28 30 38 39 0d
��ʾ��ذٷֱ�Ϊ89%

******************************/
#include "ups.h"
#include "USARTx.h"
#include "rs485.h"

//u8 Inquire1_UPS[3] = {0x51,0x31,0x0d};
//u8 UPS1_Electricity[3] = {0x51,0x32,0x0d};


//u8 read_ups_rxd_data[12] = {0};    // UPS ���ݽ��ջ�����

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
	return UPSPowerStatus;//0 ��ʾ�е������� 1 ��ʾ�е��쳣
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
  //RX_Clear(g_pcom_ups);//Ϊʲô����ֵ���䣿����������������������
	
	return UPSElectricityValue;//��ص���
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

	
