
/*
 *  ����ͷ�ļ�
 */
 
#include "timer2.h"
#include "timer3.h"
#include "timer4.h"
#include "global.h"
#include "USARTx.h"
#include "ups.h"
//#include "MyVirtualUart.h"

/*
 *  ȫ�ֱ���
 */
#define  EEP_Firstpage      0x00
#define  EEP_Secondpage     0x16
#define  CharLen  16

COMM_USART g_usart1;
COMM_USART g_usart2;
COMM_USART g_usart_spi;
COMM_USART g_usart3;
COMM_USART g_usartvirt;     //virtual usart, realize by timer && gpio

COMM_USART *g_pcom_test        = &g_usart1;        // define USART1 used for finger print ;     default 57600
COMM_USART *g_pcom_ser       = &g_usart2;        // define USART2 used for server comm  ;    default 115200
COMM_USART *g_pcom_virt      = &g_usartvirt;

COMM_USART *g_pcom_ups      = &g_usart3;        // define USART2 used for ups comm;   default 2400

COMM_USART *g_p_usart_debug  = &g_usart3;        
COMM_USART *g_p_debug_recv  = &g_usart3;

//COMM_USART *g_p_usart_debug  = &g_usartvirt;
//COMM_USART *g_p_debug_recv  = &g_usartvirt;

//COMM_USART *g_p_usart_debug  = &g_usartvirt;
//COMM_USART *g_p_debug_recv  = &g_usart2;


	
vu16 tim4_ticks=0;
vu16 last_tim4_ticks=0;
vu16 tim4_pass=0;

void initial_myself(void);
void initial_peripheral(void);
u16  task_item(void);
u16  ups_item(void);
u32 I2c_Buf_Write[1] = {0x01};

u8 Cmd_Open_Lock_flag = 0;

u16  test_item(void)
{
	u8 Inquire_UPS[3] = {0x51,0x31,0x0d};
  u8 UPS_Electricity[3] = {0x51,0x32,0x0d};
	u8 TestBuf[4] = {0x55,0xaa,0xaa,0x0d};
	u8 *ups_rx_buf = g_pcom_ups->rx_buf;
	
	while(1)
	{
		switch(g_pcom_ups->rx_buf[2])
		{
			case 0x01:
			  //RX_Clear(g_pcom_test);
			  USART_transmitS(g_pcom_ups,g_pcom_ups->rx_buf,sizeof(g_pcom_ups->rx_buf));
			  
			  RX_Clear(g_pcom_ups);
				break;
			default:
				break;
		}
		
	}
	
}


/***************
u8 InquireUPSData(void)
{
	//u8 UPSElectricity;
	u8 UPSPowerStatus = 0xff;
	u8 Inquire_UPS[3] = {0x51,0x31,0x0d};
  
  //RX_Clear(g_pcom_ups);	
	USART_transmitS(g_pcom_ups,Inquire_UPS,3);
	if(0x28 == g_pcom_ups->rx_buf[0] && 0x0d == g_pcom_ups->rx_buf[46])
	{
		//RS485_Send_Data(g_pcom_ups->rx_buf,47);
		UPSPowerStatus = g_pcom_ups->rx_buf[38] - 0x30;	
	}
	
	RX_Clear(g_pcom_ups);
	
	return UPSPowerStatus;//0 ��ʾ�е������� 1 ��ʾ�е��쳣
	//return UPSElectricity;//��ص���
}


u8 UPSElectricity(void)
{
	u8 UPSElectricityValue = 0xff;
	u8 UPS_Electricity[3] = {0x51,0x32,0x0d};
	u8 Electricity_H = 0xff;
	u8 Electricity_L = 0xff;
	
	//RX_Clear(g_pcom_ups);
	u8 Inquire_UPS[3] = {0x51,0x31,0x0d};
	USART_transmitS(g_pcom_ups,Inquire_UPS,3);
	
	if(0x28 == g_pcom_ups->rx_buf[0] && 0x0d == g_pcom_ups->rx_buf[46])
	{
		//RS485_Send_Data(g_pcom_ups->rx_buf,47);
		
		Electricity_H = g_pcom_ups->rx_buf[33] - 0x30;
		Electricity_L = g_pcom_ups->rx_buf[34] - 0x30;
		UPSElectricityValue = Electricity_H * 0x0a + Electricity_L;
	  //RS485_Send_Data(&UPSElectricityValue,1);
	}
	
	//RX_Clear(g_pcom_ups);//Ϊʲô����ֵ���䣿����������������������
	
	return UPSElectricityValue;//��ص���
}
*******************/


u16  ups_item(void)
{
	u8 Inquire_UPS[3] = {0x51,0x31,0x0d};
  u8 UPS_Electricity[3] = {0x51,0x32,0x0d};
	u8 TestBuf[4] = {0x55,0xaa,0xaa,0x0d};
	u8 *ups_rx_buf = g_pcom_ups->rx_buf;
	u8 Status = 0xff;
	u8 UPSElectricityValue = 0xff;
	u8 Electricity_H = 0xff;
	u8 Electricity_L = 0xff;
	
	while(1)
	{
		switch(g_pcom_test->rx_buf[2])
		{
			case 0x01://UPS �е�״̬
				USART_transmitS(g_pcom_ups,Inquire_UPS,3);
        //RX_Clear(g_pcom_test);
			  if(0x28 == g_pcom_ups->rx_buf[0] && 0x0d == g_pcom_ups->rx_buf[46])
				{
					RS485_Send_Data(g_pcom_ups->rx_buf,47);
					Status = g_pcom_ups->rx_buf[38] - 0x30;
					RS485_Send_Data(&Status,1);
				}
			  
			  //RS485_RX_Clear();
				RX_Clear(g_pcom_test);
			  RX_Clear(g_pcom_ups);
				break;
			case 0x02://UPS ����
        USART_transmitS(g_pcom_ups,Inquire_UPS,3);
	
				if(0x28 == g_pcom_ups->rx_buf[0] && 0x0d == g_pcom_ups->rx_buf[46])
				{
					RS485_Send_Data(g_pcom_ups->rx_buf,47);
		
					Electricity_H = g_pcom_ups->rx_buf[33] - 0x30;
					Electricity_L = g_pcom_ups->rx_buf[34] - 0x30;
					UPSElectricityValue = Electricity_H * 0x0a + Electricity_L;
					RS485_Send_Data(&UPSElectricityValue,1);
				}				
			
	      RX_Clear(g_pcom_test);
				RX_Clear(g_pcom_ups);
			  break;
			default:
				break;
		}
		
	}
	
}


u16  task_item(void)
{
  u8 ReadCount = 0;
	u8 LockCount = 0;
	u8 CheckStatus = 0;
	u8 LockDelayFlag = 0;
  
	u8 EventsBuf[16] = {0x55,0xaa,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xaa,0x0d};//�����¼���ѯӦ�� 
  u8 InquireBuf[15] = {0x55,0xaa,0x03,0x07,0x05,0x06,0x07,0x05,0x02,0x04,0x05,0x07,0x08,0xaa,0x0d};//������ѯӦ��	
  u8 LockBuf[6] = {0x55,0xaa,0x01,0x01,0xaa,0x0d};//����Ӧ��
	u8 CancelBuf[4] = {0x55,0xaa,0xaa,0x0d};//����ȡ��Ӧ��
	u8 EditBuf[5] = {0x55,0xaa,0x01,0xaa,0x0d};//�޸�����ַӦ��
	u8 TestBuf[4] = {0x55,0xaa,0xaa,0x0d};
	
	u8 temperature;
	u8 humility;
	u8 ReadStatus = 0;
	
	while(1)
	{		
		Start_Alarm();
		
		if(ReadCount % 10 == 0)			//ÿ150ms��ȡһ��
		{									  
      ReadStatus = DHT11_Read_Data(&temperature,&humility);
      CheckStatus = DHT11_Check();
      ALCOHOL_ReadData();
		}				   
	 	delay_ms(15);
		ReadCount++;
		
		
		if(
		    0x88 == RS485_RX_BUF[0]//Ŀ�ĵ�ַΪ88��ʾ�����û�
		    || 0x55 == RS485_RX_BUF[0]//55��ʾ��ͨ�û�
		  )
		{
			switch(RS485_RX_BUF[2])
			{
				case 0x01://�����¼���ѯ���� 55 aa 01 0d
					RS485_RX_Clear();
			    
					EventsBuf[2] = Abnormal_Open_Door();
					EventsBuf[3] = Abnormal_Recieve_Firearms();
					EventsBuf[4] = Door_Timeout_Unlocked();
					EventsBuf[5] = Cabinet_Power_Outage();
					EventsBuf[6] = Alternate_Way_Open_Door();
					EventsBuf[7] = Temperature_Humidity_Alarm();
				  EventsBuf[8] = Alcohol_Detection_Alarm();
				
				  RX_Clear(g_pcom_ups);
					RS485_Send_Data(EventsBuf,16);
					break;
				case 0x02://������ѯ���� 55 aa 02 0d
					RS485_RX_Clear();
          
					InquireBuf[2] = temperature / 0x0a;
					InquireBuf[3] = temperature % 0x0a;
					InquireBuf[4] = temperature * 0x0a % 0x0a;
					InquireBuf[5] = humility / 0x0a;
					InquireBuf[6] = humility % 0x0a;
					InquireBuf[7] = humility * 0x0a % 0x0a;
				  InquireBuf[8] = ALCOHOL_ReadData() / 10;
					InquireBuf[9] = (u8)ALCOHOL_ReadData() % 10;
					InquireBuf[10] = (u8)(ALCOHOL_ReadData() * 10) % 10;
					InquireBuf[11] = UPSElectricity() / 0x0a;
					InquireBuf[12] = UPSElectricity() % 0x0a;
				
				  RX_Clear(g_pcom_ups);
					RS485_Send_Data(InquireBuf,15);
					break;
				case 0x03://�������� 55 aa 03 x1 0d  �������˵�ַ��ô�����ˣ���������
					Cmd_Open_Lock_flag = 1;
				  
					if(I2c_Buf_Write[0] == RS485_RX_BUF[3])
					{
						Open_Lock();//Open_Alarm();
												
						LockBuf[2] = RS485_RX_BUF[3];
						LockBuf[3] = Get_Lock_Status();
					  
						RS485_RX_Clear();
					
						RS485_Send_Data(LockBuf,6);
					}
					else
					{
						RS485_RX_Clear();
						break;
					}
				
					RS485_RX_Clear();
					break;
				case 0x04://����ȡ������ 55 aa 04 0d
					RS485_RX_Clear();
			
					RS485_Send_Data(CancelBuf,4);
					Close_Alarm();
					break;
				case 0x05://�޸�����ַ���� 55 aa 05 0d
					if(
					(0x88 == RS485_RX_BUF[0])//Ŀ�ĵ�ַΪ88��ʾ�����û�
					||((I2c_Buf_Write[0] == RS485_RX_BUF[3])
					&& (0x55 == RS485_RX_BUF[0]))//55��ʾ��ͨ�û�
					)
					{
						memset(I2c_Buf_Write,0x0,sizeof(I2c_Buf_Write));
						I2c_Buf_Write[0] = RS485_RX_BUF[4];
						delay_ms(10);
						AT24CXX_WriteLenByte(EEP_Firstpage, I2c_Buf_Write[0], sizeof(I2c_Buf_Write));
						//AT24CXX_ReadLenByte(EEP_Firstpage,sizeof(I2c_Buf_Write));
						EditBuf[2] = I2c_Buf_Write[0];
						RS485_RX_Clear();
						RS485_Send_Data(EditBuf,5);
					}
					else
					{
						RS485_RX_Clear();
						break;
					}
				
					RS485_RX_Clear();
					break;
				case 0x06://��������
					RS485_RX_Clear();
			
					InquireUPSData();
			
					RS485_Send_Data(USART3_RX,sizeof(USART3_RX));
					break;
				default:
					break;
			}
		}
		else
		{
			RS485_RX_Clear();
		}
			
	}
 			
}



/******************************************************
 *  �������ƣ�main
 *  �������ܣ�������
 *  ��ڲ�����
 *  ���ڲ�����
 ******************************************************/

int main()
{
	initial_myself();   
	//delay_ms(50);
	initial_peripheral();  
	//delay_ms(50);
	
	//Cmd_Open_Lock_flag = 0;
	I2c_Buf_Write[0] = AT24CXX_ReadLenByte(EEP_Firstpage,sizeof(I2c_Buf_Write));
	
	//Cmd_Open_Lock_flag = 0;
	task_item();
	//ups_item();
	//test_item();
}


 /******************************************************
 * �������ƣ�initial_myself
 * �������ܣ��ڲ���ʼ������
 * ��ڲ�����void
 * ���ڲ�����
*******************************************************/  
void initial_myself(void)
{	
	delay_init();	    //��ʱ������ʼ��	
  At24c02_Init();
	uart1_init(9600); 
  RS485_Init(9600);	
	uart3_init(2400);
	//uartvirt_init();
 	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	TIM2_Int_Init(99,7199);   // 10ms ��ʱ�жϺ��� 
  TIM3_Int_Init(99,7199);   // 10ms ��ʱ�жϺ��� 
	TIM4_Int_Init(99,7199);		//10ms Interrupt    
  TIM_Cmd(TIM4, ENABLE);
}
/************ ******************************************
 * �������ƣ�initial_peripheral
 * �������ܣ��ⲿ��ʼ������
 * ��ڲ�����void
 * ���ڲ�����
*******************************************************/ 
void initial_peripheral(void)
{
	HC595_Init();
	HC595_IO_Out_Updata_Status(0x0f);
  //LED_Init();
	//LOCK_Init();
	BEEP_Init();
	DHT11_Init();
	ALCOHOL_Init();
	VIBRATION_Init();
	MAGNETISM_Init();
}
