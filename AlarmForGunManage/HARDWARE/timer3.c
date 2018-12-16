/*******************************************************
 *  ��������: timer3.c
 *  �����ܣ���ʱ��3���ó�ʼ��
 *  �������ߣ���̫��
 *  ����ʱ�䣺2015-11-19
 *  �޸�ʱ�䣺
 *  ����汾��V1.1
 ******************************************************/
#include "timer3.h"
#include "hc595.h"
//////////////////////////////////////////////////////////////////////////////////   	 

extern u8 Cmd_Open_Lock_flag;
//extern u8 LockDelayFlag;

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(unsigned int arr,unsigned int psc)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
		
		//��ʱ��TIM3��ʼ��
		TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	 
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,���������ж�
		
		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

		//�ж����ȼ�NVIC����
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1 ;  //��ռ���ȼ�0��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�1��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
		NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


		TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}

/******************************************************
 * �������ƣ�TIM3_IRQHandler
 * �������ܣ���ʱ��3�жϷ���������ѯ����״̬�����͸���λ��
 * ��ڲ�����void
 * ���ڲ�����
*******************************************************/ 

 //��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	static int count = 0;//static ����ֻ����һ��
	
 	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
 	  if(1 == Cmd_Open_Lock_flag)
		{
		  if(count >= 1500)//1500 * 10ms//��>=��������������ʱ��
		  {
				count = 0;//���ӣ���������λ�һֱ����
		    Close_Lock();Close_Alarm();
		  }
			count++;
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
 	}
	
 }
