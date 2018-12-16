/*******************************************************
 *  程序名称: timer3.c
 *  程序功能：定时器3配置初始化
 *  程序作者：钟太松
 *  创建时间：2015-11-19
 *  修改时间：
 *  程序版本：V1.1
 ******************************************************/
#include "timer3.h"
#include "hc595.h"
//////////////////////////////////////////////////////////////////////////////////   	 

extern u8 Cmd_Open_Lock_flag;
//extern u8 LockDelayFlag;

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(unsigned int arr,unsigned int psc)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
		
		//定时器TIM3初始化
		TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
	 
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断
		
		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

		//中断优先级NVIC设置
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1 ;  //先占优先级0级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //从优先级1级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
		NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


		TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}

/******************************************************
 * 函数名称：TIM3_IRQHandler
 * 函数功能：定时器3中断服务函数，查询键盘状态，发送给上位机
 * 入口参数：void
 * 出口参数：
*******************************************************/ 

 //定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	static int count = 0;//static 不加只计数一次
	
 	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
 	  if(1 == Cmd_Open_Lock_flag)
		{
		  if(count >= 1500)//1500 * 10ms//不>=，连续触发会乱时间
		  {
				count = 0;//不加，连激发多次会一直触发
		    Close_Lock();Close_Alarm();
		  }
			count++;
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志 
 	}
	
 }

