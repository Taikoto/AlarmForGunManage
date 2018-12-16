
#ifndef __GLOBAL_H
#define __GLOBAL_H

#include <stdio.h>

#include "stm32f10x.h"
#include "delay.h"

#include "stdarg.h"	 	 
#include "string.h"

#include "hc595.h"
#include "at24c02.h"
#include "myiic.h"
#include "alarm.h"
#include "alcohol.h"
#include "led.h"
#include "lock.h"
#include "beep.h"
#include "magnetism.h"
//#include "ups.h"
#include "vibration.h"
#include "dht11.h"
#include "adc2.h"
#include "rs485.h"
#include "vibration_adc1.h"
#include "alarm_event.h"

//#include "USARTx.H"

#define MODEL_LEN             512           //FP charter/model data len =512
#define MAX_C_GUN_NUM          10            //MAX_CHECKING_GUN_NUM


typedef struct
{
  USART_TypeDef *usart;	     /* USART1,USART2,USART3 */
 	uint8_t *tx_buf;			     /* send buf */
	uint8_t *rx_buf;			     /* receive buf */
	uint16_t rx_num;		       /* received num, bytes ,max=rx_maxlen, not loop*/
	uint16_t rx_last_num;		   /* last timer tick received num, use to watching receiving end */
	uint8_t  key_in;           /* receive: key input, enter key(0x0d) as end */
	uint16_t rx_begin;         /* passed head begin locate in rx_buf *///合格包头在rx_buf相对起始位置(前面可能有一串乱字符)，0 to rx_num
	
	uint16_t rx_use;		        /* read num, max rx_use=rx_num */
	uint16_t rx_state;		      /* 0--no any data,1--receiving, 2--receiv end ,wait for process*/
	uint16_t rx_MAXLEN;		      /* rx buf len = USART_RX_LEN */
 	void (*send_over)(void);   	/* after send, recall function , NULL */
	void (*receive_new)(void);	/* after send, recall function , NULL */
}COMM_USART;


#define ABNORMAL_OPEN_DOOR               1
#define ABNORMAL_RECIEVE_FIRARMS         2
#define DOOR_TIMEOUT_UNLOCKED            3
#define CABINET_POWER_OUTAGE             4
#define ALTERNATE_WAY_OPEN_DOOR          5
#define TEMPERATURE_HUMIDITY_ALARM       6
#define ALCOHOL_DETECTION_ALARM          7
 

typedef struct
{
	uint16_t abnormal_open_door;
	uint16_t abnormal_recieve_firarms;
	uint16_t door_timeout_unlock;
	uint16_t cabinet_power_outage;
	uint16_t alternate_way_open_door;
	uint16_t temperature_humidity_alarm;
	uint16_t alcohol_detection_alarm;
	
}ALARM_EVENT;

//----------------------------------------

extern COMM_USART g_usart1;
extern COMM_USART g_usart2;
extern COMM_USART g_usart3;
extern COMM_USART g_usartvirt;    //virtual usart, realize by timer && gpio

extern COMM_USART *g_pcom_fp ;  //= &g_usart1;   // define USART1 used for finger print
extern COMM_USART *g_pcom_ser ; //= &g_usart2;   // define USART2 used for server comm
extern COMM_USART *g_pcom_ups; //=&g_usart3;
extern COMM_USART *g_pcom_virt;

extern COMM_USART *g_p_debug_recv;   // =&g_usart3;


extern u16          g_fp_frame_data_len ; //=128;     

extern u8           g_fp_byte32[4][32] ;     //g_fp_byte32[4][32]={0};



extern u8 g_ack_status;  //00--ok ,others --- failed

extern u16 g_debug_detail;   //0 -- normal; 1 -- print debug info

#endif
