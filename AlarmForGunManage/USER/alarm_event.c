#include "alarm_event.h"
#include "sys.h"
#include "global.h"
#include "ups.h"
#include "USARTx.h"

#define ABNORMAL_OPEN_DOOR               1
#define ABNORMAL_RECIEVE_FIREARMS        2
#define DOOR_TIMEOUT_UNLOCKED            3
#define CABINET_POWER_OUTAGE             4
#define ALTERNATE_WAY_OPEN_DOOR          5
#define TEMPERATURE_HUMIDITY_ALARM       6
#define ALCOHOL_DETECTION_ALARM          7

u8 magnetism_io_status = 0xff;
u8 vibration_io_status = 0xff;
u8 lock_io_status = 0xff;

u8 IsTimeFlag = 0xff;

u8 Get_Lock_Status(void)
{
	if(1 == magnetism_io_status )
	{
		 lock_io_status = 1;
	}
	else
	{
		 lock_io_status = 0;
	}
	
	return lock_io_status;
}


u8 Abnormal_Open_Door(void)
{
	u8 alarm_event_flag = 0xff;
	
	if(GPIOB->IDR& GPIO_IDR_IDR8)
	{
		 vibration_io_status = 0;
	}
	else
	{
		 vibration_io_status = 1;
	}
	
	if(GPIOC->IDR& GPIO_IDR_IDR13)
	{	
		 magnetism_io_status  = 1;
	}
	else
  {
		 magnetism_io_status = 0;
	}
	
	if((1 == magnetism_io_status) && (1 == vibration_io_status) )
	{
		 alarm_event_flag = 1;
	}
	else
	{
		 alarm_event_flag = 0;
	}
	
	return alarm_event_flag;	
}
	


u8 Abnormal_Recieve_Firearms(void)
{
	u8 alarm_event_flag = 0xff;
	
	if(GPIOB->IDR& GPIO_IDR_IDR8)
	{
		 vibration_io_status = 0;
	}
	else
	{
		 vibration_io_status = 1;
	}
	
	if(GPIOC->IDR& GPIO_IDR_IDR13)
	{	
		 magnetism_io_status  = 1;
	}
	else
  {
		 magnetism_io_status = 0;
	}
	
	if((1 == magnetism_io_status) && (1 == vibration_io_status) )
	{
		 alarm_event_flag = 1;
	}
	else
	{
		 alarm_event_flag = 0;
	}
	
	return alarm_event_flag;
}
	


u8 Door_Timeout_Unlocked(void)
{
	u8 alarm_event_flag = 0xff;
	
	if(GPIOC->IDR& GPIO_IDR_IDR13)
	{	
		 magnetism_io_status  = 1;
	}
	else
  {
		 magnetism_io_status = 0;
	}
	
	if((1 == magnetism_io_status) && (1 == IsTimeFlag))
	{
		 alarm_event_flag = 1;
	}
	else
	{
		 alarm_event_flag = 0;
	}
	
	return alarm_event_flag;
}



u8 Cabinet_Power_Outage(void)
{
	u8 alarm_event_flag = 0xff;
	//RX_Clear(g_pcom_ups);
	if(InquireUPSData())
	{
		alarm_event_flag = 1;
	}
	else
	{
		alarm_event_flag = 0;
	}
	
	return alarm_event_flag;
	//return InquireUPSData();
}
	


u8 Alternate_Way_Open_Door(void)
{
	static u8 alarm_event_flag = 0xff;
	
	if(Get_Lock_Status())
	{
		if((0x55 == RS485_RX_BUF[0] || 0x88 == RS485_RX_BUF[0]) && (0x03 == RS485_RX_BUF[2]))
		//if(Cmd_Open_Lock_flag)
		{
			alarm_event_flag = 0;//正常情况
		}
		else
		{
			alarm_event_flag = 1;
		}
	}
	else
	{
		if(!Get_Lock_Status())
		{
			alarm_event_flag = 0;//正常情况
		}
		else
		{
			alarm_event_flag = 1;
		}
	}
	
	return alarm_event_flag;
}
	
	
	
u8 Temperature_Humidity_Alarm(void)	
{
	u8 alarm_event_flag = 0xff;
	u8 temperature;  	    
	u8 humidity;
	
	DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值
	if(temperature > 40 && humidity > 80)
	{
		alarm_event_flag = 1;
	}
	else
	{
		alarm_event_flag = 0;
	}
	
	return alarm_event_flag;
}
	


u8 Alcohol_Detection_Alarm(void)
{
	u8 alarm_event_flag = 0xff;
	u8 TempValue;
	TempValue = ALCOHOL_ReadData();
	
	if(TempValue > 20)
	{
		alarm_event_flag = 1;
	}
	else
	{
		alarm_event_flag = 0;
	}
	
	return alarm_event_flag;
}


void Start_Alarm(void)
{
	if(Abnormal_Open_Door() || Abnormal_Recieve_Firearms() || Door_Timeout_Unlocked())// 一直响警报
	{
		Times_Start_Alarm(1);
	}
	
	if(Temperature_Humidity_Alarm() || Alcohol_Detection_Alarm())
	{
		Times_Start_Alarm(2);
	}
	
	if(Cabinet_Power_Outage())
	{
		Times_Start_Alarm(1);
	}
	
	if(Alternate_Way_Open_Door())
	{
		Times_Start_Alarm(3);
	}
}

void Times_Start_Alarm(u8 count)// 声警报
{
	u8 i = 0;
	if(i < count)
	{
		count++;
		Open_Alarm();
		delay_ms(500);
		Close_Alarm();
	}	
}

