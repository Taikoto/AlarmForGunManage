 /*
 *  ����ͷ�ļ�
 */
#include "hc595.h"


unsigned char ucTemp = 0;         

unsigned char ucHc595Out_update = 0;      //  ˢ�±�����ÿ�θ���LED��״̬��Ҫ����һ�Ρ�
unsigned char ucHc595Out_Temp = 0x0f;     //  ����ײ�74HC595���״̬���м����

unsigned char ucHc595Out_Q0 = 0;       //  ����8�������״̬��0 ������1������
unsigned char ucHc595Out_Q1 = 0; 
unsigned char ucHc595Out_Q2 = 0; 
unsigned char ucHc595Out_Q3 = 0; 
unsigned char ucHc595Out_Q4 = 0; 
unsigned char ucHc595Out_Q5 = 0; 
unsigned char ucHc595Out_Q6 = 0; 
unsigned char ucHc595Out_Q7 = 0; 

unsigned char Lock_Control_flag = 0;
unsigned char Alarm_Control_flag = 0;

//u8 magnetism_io_status = 0xff;
//u8 vibration_io_status = 0xff;
//u8 lock_io_status = 0xff;
//u8 alarm_event_flag = 0xff;

/*************************************************
 *  �������ƣ�74HC595_Init
 *  �������ܣ��̵�������74HC595��ʼ������
 *  ��ڲ�����void
 *  ���ڲ�����void
 ************************************************/
void HC595_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				   //PA.8 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��PA.8
  GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8  �����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;				 //ALARM-->PC.14/PC.15 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.14/PC.15
  GPIO_SetBits(GPIOB,GPIO_Pin_14|GPIO_Pin_15);						 //PB.14/PB.15 �����	
}

void NOP()
{
	unsigned char i;
  for(i=0; i<30; i++); 
}

/*************************************************
 *  �������ƣ�HC595SendData
 *  �������ܣ�HC595��SPI���߷�������
 *  ��ڲ�����unsigned char ucSendValue Ҫ���͵����� 
 *  ���ڲ�����void
 ************************************************/
void HC595SendData(unsigned char ucSendValue)
{
  unsigned char i;
	for(i = 0; i<8; i++)
	{
	  if((ucSendValue <<i)&0x80)
		{
		  GPIO_SetBits(GPIOA,MOSI);
		}
		else
		{
		  GPIO_ResetBits(GPIOA,MOSI);
		}
		GPIO_ResetBits(GPIOB,S_CLK);      // ����λ
		NOP();
		NOP();
		GPIO_SetBits(GPIOB,S_CLK);	
	}
	
	GPIO_ResetBits(GPIOB,R_CLK);         // �ٴ洢
	NOP();
	NOP();
	GPIO_SetBits(GPIOB,R_CLK);	
}

/*************************************************
 *  �������ƣ�HC595_IO_Out
 *  �������ܣ�HC595������������
 *  ��ڲ�����unsigned char ucHc595Status Ҫ���͵����� 
 *  ���ڲ�����void
 ************************************************/
void HC595_IO_Out( void )
{
  if(ucHc595Out_update ==1)
	{
	  ucHc595Out_update = 0;
		
		if(ucHc595Out_Q0 == 1)                          // ��ʾQ0����͵�ƽ
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0x0e;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x01;
		}
		
		if(ucHc595Out_Q1 == 1)                          // ��ʾQ1����͵�ƽ
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0x0d;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x02;
		}
		
		if(ucHc595Out_Q2 == 1)                         // ��ʾQ2����͵�ƽ
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0x0b;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x04;
		}
		
		if(ucHc595Out_Q3 == 1)                         // ��ʾQ3����͵�ƽ
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0x07;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x08;
		}
////////////////////////////////////////////////////////////////////////////////		
		if(ucHc595Out_Q4 == 1)                          // ��ʾQ4����ߵ�ƽ
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x10;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0xef;
		}
		
		if(ucHc595Out_Q5 == 1)                         // ��ʾQ5����ߵ�ƽ
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x20;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0xdf;
		}
		
		if(ucHc595Out_Q6 == 1)                         // ��ʾQ6����ߵ�ƽ
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x40;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0xbf;
		}
		
		if(ucHc595Out_Q7 == 1)                        // ��ʾQ7����ߵ�ƽ            
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x80;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0x7f;
		}

		
//		if(ucHc595Out_Q0 == 1)     // Ϊʲôһ��Ҫ�ŵ�����ѵ�ֻ����Ϊ ֻ�����Ǹߵ�ƽ������
//		{
//		  ucHc595Out_Temp = ucHc595Out_Temp | 0x01;
//		}
//		else
//		{
//		  ucHc595Out_Temp = ucHc595Out_Temp & 0xfe;
//		}
		
	}
	
	HC595SendData(ucHc595Out_Temp);
	
//  USART3_transmit(ucHc595Out_Temp);
}
	
void HC595_IO_Out_Updata_Status(unsigned char ucStatus)
{
  switch(ucStatus)
	{
	  case Fill_on:       ucHc595Out_Q0 = 1;  ucHc595Out_update = 1; break;
		case Fill_off:      ucHc595Out_Q0 = 0;  ucHc595Out_update = 1; break;
		
	  case Led1_on:       ucHc595Out_Q1 = 1;  ucHc595Out_update = 1; break;
		case Led1_off:      ucHc595Out_Q1 = 0;  ucHc595Out_update = 1; break;		
		
		case Led2_on:       ucHc595Out_Q2 = 1;  ucHc595Out_update = 1; break;
		case Led2_off:      ucHc595Out_Q2 = 0;  ucHc595Out_update = 1; break;	
		
		case NrfCE_H:       ucHc595Out_Q3 = 1;  ucHc595Out_update = 1; break;        // �������ü��ɡ�
		case NrfCE_L:       ucHc595Out_Q3 = 0;  ucHc595Out_update = 1; break;	 
    		
		case NrfData_H:     ucHc595Out_Q4 = 1;  ucHc595Out_update = 1; break;
		case NrfData_L:     ucHc595Out_Q4 = 0;  ucHc595Out_update = 1; break;	
		
		case Alarm_on:      ucHc595Out_Q5 = 1;  ucHc595Out_update = 1; break;
  	case Alarm_off:     ucHc595Out_Q5 = 0;  ucHc595Out_update = 1; break;	
		
		case Lock1_on:      ucHc595Out_Q6 = 1;  ucHc595Out_update = 1; break;
		case Lock1_off:     ucHc595Out_Q6 = 0;  ucHc595Out_update = 1; break;	
		
		case Lock2_on:      ucHc595Out_Q7 = 1;  ucHc595Out_update = 1; break;
		case Lock2_off:     ucHc595Out_Q7 = 0;  ucHc595Out_update = 1; break;		

		default: 
		{
			break;
		}
	}
	
	HC595_IO_Out( );
}



void Open_Lock(void)     //  ����
{
	  Lock_Control_flag = 1;
		HC595_IO_Out_Updata_Status(Lock1_on);
		HC595_IO_Out_Updata_Status(Led1_on);	      // D6	��Ϊ�̵���ָʾ
}

void Close_Lock(void)   // ����        ��բ��������ʱ5ms ����ִ�йر������ʱʱ�䲻�˳���10ms
{
	  Lock_Control_flag = 0;
	  HC595_IO_Out_Updata_Status(Lock1_off);
		HC595_IO_Out_Updata_Status(Led1_off);	
}

void Open_Alarm(void)     //  ����
{
	  Alarm_Control_flag = 1;
	  
		HC595_IO_Out_Updata_Status(Alarm_on);
}

void Close_Alarm(void)   // ����        ��բ��������ʱ5ms ����ִ�йر������ʱʱ�䲻�˳���10ms
{
    Alarm_Control_flag = 0;
	
	  HC595_IO_Out_Updata_Status(Alarm_off);
}
