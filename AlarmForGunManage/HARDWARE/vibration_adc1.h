#ifndef __VIBRATION_ADC1_H
#define	__VIBRATION_ADC1_H


#include "stm32f10x.h"


#if 0

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    macADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    macADC_CLK                       RCC_APB2Periph_ADC1

#define    macADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    macADC_GPIO_CLK                  RCC_APB2Periph_GPIOB  
#define    macADC_PORT                      GPIOB

// PB0-ͨ��8 ����IO
#define    macADC_PIN                       GPIO_Pin_0
#define    macADC_CHANNEL                   ADC_Channel_8

#define    macADCx                          ADC1
#define    macADC_DMA_CHANNEL               DMA1_Channel1

#endif

/**************************��������********************************/

void Vibration_ADC1_Init(void);

#endif /* __VIBRATION_ADC1_H */

