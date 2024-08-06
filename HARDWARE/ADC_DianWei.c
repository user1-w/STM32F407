

#include"user.h"

//光敏电阻 - PA0
//1.配置adc电路
void ADC_DianWei_Config()
{
	//时钟APB2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef adc_gpiostruct;
	adc_gpiostruct.GPIO_Mode = GPIO_Mode_AN;
	adc_gpiostruct.GPIO_Pin = GPIO_Pin_0;
	adc_gpiostruct.GPIO_PuPd =  GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC,&adc_gpiostruct);
	

	
	//配置电路
	ADC_CommonInitTypeDef adc_commonsturct;
	adc_commonsturct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	//独立模式 一次采集一个
	adc_commonsturct.ADC_Mode = ADC_Mode_Independent;
	//预分频系数 84/4 = 21 <36mhz
	adc_commonsturct.ADC_Prescaler = ADC_Prescaler_Div4;
	//两次采集间隔的时间
	adc_commonsturct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&adc_commonsturct);
	
	
	//
	ADC_InitTypeDef adcstruct;
	//分辨率
	adcstruct.ADC_Resolution = ADC_Resolution_12b;
	//是否扫描 单次即可
	adcstruct.ADC_ScanConvMode = DISABLE;
	//转换一次就停止
	adcstruct.ADC_ContinuousConvMode = DISABLE;
	//数据左还是右对齐
	adcstruct.ADC_DataAlign = ADC_DataAlign_Right;
	//触发方式 软件还是硬件电路 
	adcstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	adcstruct.ADC_ExternalTrigConv = 1;
	ADC_Init(ADC1,&adcstruct);
	
	
	//使能
	ADC_Cmd(ADC1,ENABLE);
}


//采集信号操作函数
//通道数值
//开始采集的信号
unsigned short int Get_ADC_dianwei_Channel(unsigned int channel)
{
	//adc电路  通道  一个序列  采集时间
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_480Cycles);
	
	//开始采集,软件控制
	ADC_SoftwareStartConv(ADC1);
	
	//等待采集结束
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	//获取采集的结果
	return	ADC_GetConversionValue(ADC1);
	
}

//均值操作函数
//多次采集
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


