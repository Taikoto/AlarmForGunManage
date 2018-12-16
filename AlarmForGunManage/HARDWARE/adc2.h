#ifndef __ADC2_H
#define	__ADC2_H


#include "stm32f10x.h"

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC����ͨ�������ţ�����**************************/
#define    macADC_APBxClock_FUN             RCC_APB2PeriphClockCmd

// ������ ADC1/2�����ʹ��ADC3���ж���ص�Ҫ�ĳ�ADC3��
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



/**************************��������********************************/
void               ADC2_Init                               (void);


#endif /* __ADC2_H */

