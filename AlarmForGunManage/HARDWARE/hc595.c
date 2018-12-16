 /*
 *  包含头文件
 */
#include "hc595.h"


unsigned char ucTemp = 0;         

unsigned char ucHc595Out_update = 0;      //  刷新变量，每次更改LED的状态都要更新一次。
unsigned char ucHc595Out_Temp = 0x0f;     //  代表底层74HC595输出状态的中间变量

unsigned char ucHc595Out_Q0 = 0;       //  代表8个输出口状态，0 代表灭，1代表亮
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
 *  函数名称：74HC595_Init
 *  函数功能：继电器部分74HC595初始化函数
 *  入口参数：void
 *  出口参数：void
 ************************************************/
void HC595_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				   //PA.8 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化PA.8
  GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8  输出高
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;				 //ALARM-->PC.14/PC.15 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.14/PC.15
  GPIO_SetBits(GPIOB,GPIO_Pin_14|GPIO_Pin_15);						 //PB.14/PB.15 输出高	
}

void NOP()
{
	unsigned char i;
  for(i=0; i<30; i++); 
}

/*************************************************
 *  函数名称：HC595SendData
 *  函数功能：HC595向SPI总线发送数据
 *  入口参数：unsigned char ucSendValue 要发送的数据 
 *  出口参数：void
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
		GPIO_ResetBits(GPIOB,S_CLK);      // 先移位
		NOP();
		NOP();
		GPIO_SetBits(GPIOB,S_CLK);	
	}
	
	GPIO_ResetBits(GPIOB,R_CLK);         // 再存储
	NOP();
	NOP();
	GPIO_SetBits(GPIOB,R_CLK);	
}

/*************************************************
 *  函数名称：HC595_IO_Out
 *  函数功能：HC595输出口输出数据
 *  入口参数：unsigned char ucHc595Status 要发送的数据 
 *  出口参数：void
 ************************************************/
void HC595_IO_Out( void )
{
  if(ucHc595Out_update ==1)
	{
	  ucHc595Out_update = 0;
		
		if(ucHc595Out_Q0 == 1)                          // 表示Q0输出低电平
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0x0e;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x01;
		}
		
		if(ucHc595Out_Q1 == 1)                          // 表示Q1输出低电平
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0x0d;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x02;
		}
		
		if(ucHc595Out_Q2 == 1)                         // 表示Q2输出低电平
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0x0b;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x04;
		}
		
		if(ucHc595Out_Q3 == 1)                         // 表示Q3输出低电平
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0x07;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x08;
		}
////////////////////////////////////////////////////////////////////////////////		
		if(ucHc595Out_Q4 == 1)                          // 表示Q4输出高电平
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x10;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0xef;
		}
		
		if(ucHc595Out_Q5 == 1)                         // 表示Q5输出高电平
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x20;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0xdf;
		}
		
		if(ucHc595Out_Q6 == 1)                         // 表示Q6输出高电平
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x40;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0xbf;
		}
		
		if(ucHc595Out_Q7 == 1)                        // 表示Q7输出高电平            
		{
		  ucHc595Out_Temp = ucHc595Out_Temp | 0x80;
		}
		else
		{
		  ucHc595Out_Temp = ucHc595Out_Temp & 0x7f;
		}

		
//		if(ucHc595Out_Q0 == 1)     // 为什么一定要放到最后，难道只是因为 只有它是高电平触发吗？
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
		
		case NrfCE_H:       ucHc595Out_Q3 = 1;  ucHc595Out_update = 1; break;        // 按此配置即可。
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



void Open_Lock(void)     //  开锁
{
	  Lock_Control_flag = 1;
		HC595_IO_Out_Updata_Status(Lock1_on);
		HC595_IO_Out_Updata_Status(Led1_on);	      // D6	作为继电器指示
}

void Close_Lock(void)   // 关锁        道闸开启后延时5ms 马上执行关闭命令。延时时间不宜超过10ms
{
	  Lock_Control_flag = 0;
	  HC595_IO_Out_Updata_Status(Lock1_off);
		HC595_IO_Out_Updata_Status(Led1_off);	
}

void Open_Alarm(void)     //  开锁
{
	  Alarm_Control_flag = 1;
	  
		HC595_IO_Out_Updata_Status(Alarm_on);
}

void Close_Alarm(void)   // 关锁        道闸开启后延时5ms 马上执行关闭命令。延时时间不宜超过10ms
{
    Alarm_Control_flag = 0;
	
	  HC595_IO_Out_Updata_Status(Alarm_off);
}
