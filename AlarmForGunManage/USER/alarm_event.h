#ifndef __ALARM_EVENT_H
#define __ALARM_EVENT_H	 

#include "sys.h"

extern u8 Cmd_Open_Lock_flag;

u8 Get_Lock_Status(void);


u8 Abnormal_Open_Door(void);

	
u8 Abnormal_Recieve_Firearms(void);

	
u8 Door_Timeout_Unlocked(void);


u8 Cabinet_Power_Outage(void);

	
u8 Alternate_Way_Open_Door(void);

	
u8 Temperature_Humidity_Alarm(void);	

	
u8 Alcohol_Detection_Alarm(void);

extern void Start_Alarm(void);

extern void Times_Start_Alarm(u8 count);// Éù¾¯±¨

		 				    
#endif
