#ifndef __VIBRATION_ADC1_H
#define	__VIBRATION_ADC1_H


#include "stm32f10x.h"


#if 0

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC1输入通道（引脚）配置**************************/
#define    macADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    macADC_CLK                       RCC_APB2Periph_ADC1

#define    macADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    macADC_GPIO_CLK                  RCC_APB2Periph_GPIOB  
#define    macADC_PORT                      GPIOB

// PB0-通道8 独立IO
#define    macADC_PIN                       GPIO_Pin_0
#define    macADC_CHANNEL                   ADC_Channel_8

#define    macADCx                          ADC1
#define    macADC_DMA_CHANNEL               DMA1_Channel1

#endif

/**************************函数声明********************************/

void Vibration_ADC1_Init(void);

#endif /* __VIBRATION_ADC1_H */

