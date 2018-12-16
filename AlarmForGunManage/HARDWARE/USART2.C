/*******************************************************
 *  ��������: USART2.c
 *  �����ܣ�����2���ó�ʼ��
 *  �������ߣ���̫��
 *  ����ʱ�䣺2015-11-19
 *  �޸�ʱ�䣺
 *  ����汾��V1.1
 ******************************************************/
 
/*
 *  Ӳ�����ã� TXD2 --- PA2 --- Pin16��   RXD2 --- PA3 --- Pin17
 */

/*
 *  ����ͷ�ļ�
 */


#include "USART1.H"
#include "USART2.H"

//u8 USART2_RX[USART2_RX_LEN] = {0};      // ���ڽ��ջ����� 
volatile vu16 usart_rx2_num = 0;
volatile vu16 usart_rx2_use=0;
volatile u8 usart_rx2_full=0;   //0 or 1
volatile u8 usart_rx2_end=0;    /// timer ticks watch on rx , pass 20ms take as end transfer

volatile u8  rx2_begin_watching=0;
volatile vu16 last_usart_rx2_num=0;

//u8 usart2_rx_buf[USART2_RX_LEN];
vu16 usart2_recvd_len=0;

extern COMM_USART g_usart2; 

 /******************************************************
 * �������ƣ�uart2_init
 * �������ܣ�USART2 ��ʼ������
 * ��ڲ�����void
 * ���ڲ�����
*******************************************************/ 
/*
void uart2_init(u32 bound)
{
			//GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //ʹ��USART2��GPIOAʱ��
		USART_DeInit(USART2);  //��λ����2
		//USART2_TX   PA.2
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		 
			//USART2_RX	  PA.3
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
		GPIO_Init(GPIOA, &GPIO_InitStructure);  
		
		 //Usart1 NVIC ����
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���0λ��ռ���ȼ���16λ��Ӧ���ȼ�
		
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
		
		 //USART ��ʼ������

		USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

		USART_Init(USART2, &USART_InitStructure); //��ʼ������
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�

	g_usart2.usart = USART2;
	g_usart2.p_tx_buf = 0;
	g_usart2.p_rx_buf = USART2_RX;
	g_usart2.rx_MAXLEN = USART2_RX_LEN;  //1024 , can receive 1024 bytes, last byte keep 0
	g_usart2.rx_state =  0;
	g_usart2.rx_num = 0;        //0 to rx_MAXLEN
	g_usart2.rx_last_num = 0;
	g_usart2.rx_use = 0;
 	//g_usart2.send_over = 0;	 
	//g_usart2.receive_new = 0; 


		//USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

//}

*/

/******************************************************
 * �������ƣ�USART2_transmit
 * �������ܣ�USART2 ����һ���ֽ�
 * ��ڲ�����unsigned char byte
 * ���ڲ�����
*******************************************************/ 
void USART2_transmit(unsigned char byte)
{
	USART_SendData(USART2,byte);                                     // ��������
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);		 // �ȴ�UART1�������		              				    
}


/******************************************************
 * �������ƣ�USART2_transmitS
 * �������ܣ�USART2 ���Ͷ���ֽ����飻dat�����͵��ֽ���������num�����͵��ֽ���
 * ��ڲ�����unsigned char *dat,unsigned char num
 * ���ڲ��������͵�����   
*******************************************************/ 
void USART2_transmitS(unsigned char *dat,unsigned int num)
{
	unsigned int i;
	for(i=0;i<num;i++) 
	{
		USART2_transmit(dat[i]);
	}
}

/******************************************************
 * �������ƣ�USART2_IRQHandler
 * �������ܣ�����2�жϷ����������յ�Դ��Ϣ
 * ��ڲ�����void
 * ���ڲ�����
*******************************************************/ 
void USART2_IRQHandler(void)         
{
//	   u8 i;
//	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE) != RESET)
//  {
//	  USART_ReceiveData(USART2);
//  }

 	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{ 
	  if(usart_rx2_full==0) //����δ�������Խ���
    {			
			//debug_print("aaaaaa",6);
				USART2_RX[usart_rx2_num++] = USART_ReceiveData(USART2);//(USART2->DR);	//��ȡ���յ�������

				if(usart_rx2_num >= USART2_RX_LEN) //��������
				{
					//USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);	 // ��Ҫ	
					usart_rx2_num = 0;		
					//USART2_transmitS(USART2_RX,USART2_RX_LEN);			  
				}
 		
				if(usart_rx2_num == usart_rx2_use)  //�պ���֡
				{			
					//�������������ֹͣ��������//���������򶪵�һ֡(USART2_RX_LEN)		, ȡ�ߺ��ٿ��ж�
					usart_rx2_full=1;
					//USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);				
				}
				else
					usart_rx2_full=0;

	 			//rx2_watching();
			
 	  }
		else  //��������������ж����ݼĴ���
			USART_ReceiveData(USART2);		
	}
	
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
		     //USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);	 // ��Ҫ	
       //debug_print("UART2 IRQ",9);	
	     //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	 // ��Ҫ		
}


/*********************************************END OF FILE**********************/
#if 0

111111111111111

int USART2_recv_buf(void)
{
	//return USART_recv_buf(usart2_rx_buf,USART2_RX,(int*)&usart_rx2_use,(int*)&usart_rx2_num);	
	int recv_len=0;

	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);	 //����ǰ���ж�

	if (usart_rx2_full)  //������֡�����
	{
		while(1)
		{	
		 usart2_rx_buf[recv_len++]=USART2_RX[usart_rx2_use++];
 		 
		 if(usart_rx2_use >= USART_RX_LEN)
		      usart_rx2_use=0;

	   if(((usart_rx2_use==usart_rx2_num))||recv_len==USART_RX_LEN)  //all data has been recved, recv to upper user end
		 {
			 //all data been received,reset num and use pointer to top
			 usart_rx2_full=0;
 			 break;
		 }
	  }
 	}
	else   //not full
	{
		while(1)  //һ�����
		{
			if(((usart_rx2_use==usart_rx2_num))||recv_len==USART_RX_LEN)  //all data has been recved, recv to upper user end
			{
				/*all data been received,reset num and use pointer to top*/
				break;
			}
		 
			usart2_rx_buf[recv_len++]=USART2_RX[usart_rx2_use++];
 		 
			if(usart_rx2_use >= USART_RX_LEN)
		      usart_rx2_use=0;
		}
    }
	
	usart2_recvd_len=recv_len;
	
  usart_rx2_num=0;   //IRQ BUF ����
	usart_rx2_use=0;
  //usart_rx2_full=0;
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	 //���պ��ж�

	return recv_len;
	
}

//extern void debug_print(u8* buf,unsigned int len);

int if_USART2_has_new_data(void)  //����IRQ_BUF�����ݳ���
{
	
	int recv_len=0;
	int rx2_use=usart_rx2_use;
  //u8 debugchar[1025]={0};
	
	//debug_printf("usart_rx2_num=%d,usart_rx2_use=%d,usart_rx2_full=%d,\n\r",usart_rx2_num,usart_rx2_use,usart_rx2_full);
	
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);	 //����ǰ���ж�
	
	if(usart_rx2_full)
	  recv_len=USART_RX_LEN;     //��֡
	else
	{
		/*
	  while(rx2_use!=usart_rx2_num)  //��ָ�����ʱ�������
		{
		  if(rx2_use++ >= USART_RX_LEN)
		      rx2_use=0;			

			recv_len++;
		}
		*/
				recv_len = usart_rx2_num;

	  //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	 ////�����ſ��ж�
  } 
	
	usart2_recvd_len = recv_len;
  
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	  
  
	return recv_len;
	
	
}

int USART2_clear(void)
{
	int recv_len=0;

	USART_ReceiveData(USART2);		
	
	if(usart_rx2_full==1)
	  recv_len=USART_RX_LEN;     
	else
	{	
 		recv_len = usart_rx2_num;
  } 
	usart2_recvd_len=recv_len;

  if(usart2_recvd_len>0 && usart_rx2_end==1 )  //�����ݣ�������
	{	
		usart_rx2_num=0;   //IRQ BUF ����
		usart_rx2_use=0;
		usart_rx2_full=0;
		usart_rx2_end=0;
		rx2_begin_watching=0;
		last_usart_rx2_num=0;
	}
	
	return recv_len;
}

#endif