
#include "user.h"

int beepflag = 0;

//1.����pwm ����
//PB10 + TIMER2_CH3

void Timer2_BEEP_PwmConfig()
{
	//1����ʱ�� APB1
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//2.�������� b��15�� ���ó� ��ʱ��12
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);
	//3.GPIO�������� Ϊ����ģʽ
	GPIO_InitTypeDef fanstruct;
	fanstruct.GPIO_Pin = GPIO_Pin_10;
	//����ģʽ
	fanstruct.GPIO_Mode = GPIO_Mode_AF;
	fanstruct.GPIO_Speed = GPIO_Low_Speed;
	//��������
	fanstruct.GPIO_OType = GPIO_OType_PP;
	fanstruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&fanstruct);

	
	
	//4.���ö�ʱ��
	TIM_TimeBaseInitTypeDef tim12struct;
	//Ԥ��Ƶ��84 / 84 = 1mhz = 10^6hz
	//1���������� ��0.000001s
	tim12struct.TIM_Prescaler = 400 - 1;
	//�Զ�װ��ֵ
	tim12struct.TIM_Period = 100 -1;
	//��ʱ����20000 = 20ms
	;
	//���ϼ���
	tim12struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim12struct.TIM_ClockDivision = TIM_CKD_DIV1;
	
   TIM_TimeBaseInit(TIM2, &tim12struct);

	
	
	//5.����TIMER12 ͨ��2
	TIM_OCInitTypeDef oc2struct;
	//ģʽ1
	oc2struct.TIM_OCMode = TIM_OCMode_PWM1;
	//���� - �ߵ�ƽ
	oc2struct.TIM_OCPolarity = TIM_OCPolarity_High;
	//���ʹ��λ
	oc2struct.TIM_OutputState = TIM_OutputState_Enable;
	oc2struct.TIM_Pulse = 0;
	
	TIM_OC3Init(TIM2,&oc2struct);
	
	//6.�Ƚϲ���Ĵ���ʹ��
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);

	//7.�Զ���װ�ؼĴ���ʹ��
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	//8.��ʱ������ʹ
	TIM_Cmd(TIM2,ENABLE);
}

void Beep_Control(unsigned int value)
{
	TIM_SetCompare3(TIM2,value);
	delay_ms(1);
}

void Pwm_Alarm()
{
	if(beepflag)
	{
			for(int i=0 ;i<99;i++)
		{
			Beep_Control(i);
			delay_ms(10);
		}
		for(int i=99;i>=0;i--)
		{
			Beep_Control(i);
			delay_ms(10);
		}
	}
	
}


