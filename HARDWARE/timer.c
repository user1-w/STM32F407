#include "user.h"


void Timer4_Config(unsigned short int psc,unsigned short int period)
{
	//����ʱ�� - һ������42mhz ����Ƕ�ʱ������84
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	//����ʱ����Ԫ-��ʱ����ʼ��
	
	TIM_TimeBaseInitTypeDef time4struct;
	//Ԥ��Ƶϵ�� - ����ʱ�� ������
	//84mhz/8400 = 0.01mhz-> 10000hz
	//8400Ϊ�Զ������
	time4struct.TIM_Prescaler = psc;
	//�Զ�װ����ֵ = ��ʱʱ�� =�Զ�װ��ֵ * ����ʱ�䣨1/10000��
	time4struct.TIM_Period = period;
	//����ģʽ
	time4struct.TIM_CounterMode = TIM_CounterMode_Up;
	time4struct.TIM_ClockDivision = TIM_CKD_DIV1;
	//
	TIM_TimeBaseInit(TIM4,&time4struct);
	
	//����ʱʱ�䵽��ִ���жϺ���
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	//��ʱ��ʹ��
	TIM_Cmd(TIM4,ENABLE);
	
	//�ж�����
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = TIM4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}



//�жϺ���
void TIM4_IRQHandler()
{
	//LED_Flow();
	//GPIO_ToggleBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}


