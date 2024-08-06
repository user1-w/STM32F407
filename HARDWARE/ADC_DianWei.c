

#include"user.h"

//�������� - PA0
//1.����adc��·
void ADC_DianWei_Config()
{
	//ʱ��APB2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef adc_gpiostruct;
	adc_gpiostruct.GPIO_Mode = GPIO_Mode_AN;
	adc_gpiostruct.GPIO_Pin = GPIO_Pin_0;
	adc_gpiostruct.GPIO_PuPd =  GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC,&adc_gpiostruct);
	

	
	//���õ�·
	ADC_CommonInitTypeDef adc_commonsturct;
	adc_commonsturct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	//����ģʽ һ�βɼ�һ��
	adc_commonsturct.ADC_Mode = ADC_Mode_Independent;
	//Ԥ��Ƶϵ�� 84/4 = 21 <36mhz
	adc_commonsturct.ADC_Prescaler = ADC_Prescaler_Div4;
	//���βɼ������ʱ��
	adc_commonsturct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&adc_commonsturct);
	
	
	//
	ADC_InitTypeDef adcstruct;
	//�ֱ���
	adcstruct.ADC_Resolution = ADC_Resolution_12b;
	//�Ƿ�ɨ�� ���μ���
	adcstruct.ADC_ScanConvMode = DISABLE;
	//ת��һ�ξ�ֹͣ
	adcstruct.ADC_ContinuousConvMode = DISABLE;
	//���������Ҷ���
	adcstruct.ADC_DataAlign = ADC_DataAlign_Right;
	//������ʽ �������Ӳ����· 
	adcstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	adcstruct.ADC_ExternalTrigConv = 1;
	ADC_Init(ADC1,&adcstruct);
	
	
	//ʹ��
	ADC_Cmd(ADC1,ENABLE);
}


//�ɼ��źŲ�������
//ͨ����ֵ
//��ʼ�ɼ����ź�
unsigned short int Get_ADC_dianwei_Channel(unsigned int channel)
{
	//adc��·  ͨ��  һ������  �ɼ�ʱ��
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_480Cycles);
	
	//��ʼ�ɼ�,�������
	ADC_SoftwareStartConv(ADC1);
	
	//�ȴ��ɼ�����
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	//��ȡ�ɼ��Ľ��
	return	ADC_GetConversionValue(ADC1);
	
}

//��ֵ��������
//��βɼ�
unsigned short int get_DianWei_ADCaverage(unsigned int channel,char times)
{
	unsigned short int value = 0;
	int i =0;
	for( i =0;i<times;i++)
	{
		value += Get_AdcChannel(channel);
		delay_ms(5);
	}
	
	return value/times;
}


