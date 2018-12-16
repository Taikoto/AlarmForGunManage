#include "adc2.h"

__IO uint16_t ADC2_ConvertedValue;


/**
  * @brief  ADC GPIO ��ʼ��
  * @param  ��
  * @retval ��
  */
static void ADC2_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// �� ADC IO�˿�ʱ��
	macADC_GPIO_APBxClock_FUN ( macADC_GPIO_CLK, ENABLE );
	
	// ���� ADC IO ����ģʽ
	GPIO_InitStructure.GPIO_Pin = macADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	// ��ʼ�� ADC IO
	GPIO_Init(macADC_PORT, &GPIO_InitStructure);				
}

/**
  * @brief  ����ADC����ģʽ
  * @param  ��
  * @retval ��
  */
static void ADC2_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;	

	// ��ADCʱ��
	macADC_APBxClock_FUN ( macADC_CLK, ENABLE );
	
	// ADC ģʽ����
	// ֻʹ��һ��ADC�����ڵ�ģʽ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	
	// ��ֹɨ��ģʽ����ͨ����Ҫ����ͨ������Ҫ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 

	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;

	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;

	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
	// ת��ͨ��1��
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
		
	// ��ʼ��ADC
	ADC_Init(macADCx, &ADC_InitStructure);
	
	// ����ADCʱ�ӣΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
	ADC_RegularChannelConfig(macADCx, macADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	
	// ADC ת�����������жϣ����жϷ�������ж�ȡת��ֵ
	ADC_ITConfig(macADCx, ADC_IT_EOC, ENABLE);
	
	// ����ADC ������ʼת��
	ADC_Cmd(macADCx, ENABLE);
	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(macADCx);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(macADCx));
	
	// ADC��ʼУ׼
	ADC_StartCalibration(macADCx);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(macADCx));
	
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(macADCx, ENABLE);
}

static void ADC_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  // �����ж����ȼ�
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


/**
  * @brief  ADC��ʼ��
  * @param  ��
  * @retval ��
  */
void ADC2_Init(void)
{
	ADC2_GPIO_Config();
	ADC2_Mode_Config();
	ADC_NVIC_Config();
}


void ADC1_2_IRQHandler(void)
{

  ADC2_ConvertedValue = ADC_GetConversionValue(macADCx);
}
/*********************************************END OF FILE**********************/
