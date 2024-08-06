
#include "user.h"


//1.����pwm ����
//PB15 + TIMER12_CH2

void Timer12_Ch2_PwmConfig()
{
	//1����ʱ�� APB1
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//2.�������� b��15�� ���ó� ��ʱ��12
 GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM12);
	//3.GPIO�������� Ϊ����ģʽ
	GPIO_InitTypeDef fanstruct;
	fanstruct.GPIO_Pin = GPIO_Pin_15;
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
	tim12struct.TIM_Prescaler = 84 - 1;
	//�Զ�װ��ֵ
	tim12struct.TIM_Period = 1000 -1;
	//��ʱ����20000 = 20ms
	;
	//���ϼ���
	tim12struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim12struct.TIM_ClockDivision = TIM_CKD_DIV1;
	
   TIM_TimeBaseInit(TIM12, &tim12struct);

	
	
	//5.����TIMER12 ͨ��2
	TIM_OCInitTypeDef oc2struct;
	//ģʽ1
	oc2struct.TIM_OCMode = TIM_OCMode_PWM1;
	//���� - �ߵ�ƽ
	oc2struct.TIM_OCPolarity = TIM_OCPolarity_High;
	//���ʹ��λ
	oc2struct.TIM_OutputState = TIM_OutputState_Enable;
	oc2struct.TIM_Pulse = 0;
	
	TIM_OC2Init(TIM12,&oc2struct);
	
	//6.�Ƚϲ���Ĵ���ʹ��
	TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Enable);

	//7.�Զ���װ�ؼĴ���ʹ��
	TIM_ARRPreloadConfig(TIM12,ENABLE);
	//8.��ʱ������ʹ
	TIM_Cmd(TIM12,ENABLE);
}


void Fan_On()
{
	TIM_Cmd(TIM12,ENABLE);
	delay_ms(1);
}

void Fan_Off()
{
	TIM_SetCompare2(TIM12,0);
	//TIM_Cmd(TIM12,DISABLE);
	delay_ms(1);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

void Fan_Control(unsigned int value)
{
	TIM_SetCompare2(TIM12,value);
	delay_ms(1);
}


