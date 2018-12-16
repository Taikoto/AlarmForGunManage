#ifndef __ADC2_H
#define	__ADC2_H


#include "stm32f10x.h"

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC输入通道（引脚）配置**************************/
#define    macADC_APBxClock_FUN             RCC_APB2PeriphClockCmd

// 可以是 ADC1/2，如果使用ADC3，中断相关的要改成ADC3的
//#define    macADCx                          ADC1
//#define    macADC_CLK                       RCC_APB2Periph_ADC1
#define    macADCx                          ADC2
#define    macADC_CLK                       RCC_APB2Periph_ADC2
//#define    macADCx                          ADC3
//#define    macADC_CLK                       RCC_APB2Periph_ADC3



#define    macADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    macADC_GPIO_CLK                  RCC_APB2Periph_GPIOB  
#define    macADC_PORT                      GPIOB

#define    macADC_PIN                       GPIO_Pin_1
#define    macADC_CHANNEL                   ADC_Channel_9



/**************************函数声明********************************/
void               ADC2_Init                               (void);


#endif /* __ADC2_H */

