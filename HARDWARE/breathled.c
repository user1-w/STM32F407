#include"user.h"


int flg = 0;

//PE9 TIM1_CH1
//PE10 TIM1_CH2Ns
void pwm_ledconfig()
{
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_TIM1);

    GPIO_InitTypeDef fanstruct;
    fanstruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_10;
    fanstruct.GPIO_Mode = GPIO_Mode_AF;
    fanstruct.GPIO_Speed = GPIO_Low_Speed;
    fanstruct.GPIO_OType = GPIO_OType_PP;
    fanstruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOE, &fanstruct);
		

    TIM_TimeBaseInitTypeDef tim2struct;
    tim2struct.TIM_Prescaler = 400 - 1;
    tim2struct.TIM_Period = 100 - 1;
    tim2struct.TIM_CounterMode = TIM_CounterMode_Up;
    tim2struct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM1, &tim2struct);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
		TIM_OCInitStructure.TIM_Pulse = 110;
		
		
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
		TIM_OC2Init(TIM1, &TIM_OCInitStructure);
		

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
		TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
		TIM_Cmd(TIM1, ENABLE);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
		TIM_CtrlPWMOutputs(TIM1,ENABLE);
}


void Led_Control(unsigned int value)
{
		TIM_SetCompare1(TIM1,value);
		TIM_SetCompare2(TIM1,value);
		delay_ms(1);
}

void Led_Breath()
{
	if(flg)
	{
	int i = 0;
	for(i=99;i>0;i--)
	{
		Led_Control(i);
		delay_ms(10);
	}
	for(i=0;i<=105;i++)
	{
		Led_Control(i);
		delay_ms(10);
	}
}
	
}




