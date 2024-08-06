
#include "user.h"

int beepflag = 0;

//1.配置pwm 风扇
//PB10 + TIMER2_CH3

void Timer2_BEEP_PwmConfig()
{
	//1配置时钟 APB1
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//2.复用配置 b组15号 配置成 定时器12
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);
	//3.GPIO引脚配置 为复用模式
	GPIO_InitTypeDef fanstruct;
	fanstruct.GPIO_Pin = GPIO_Pin_10;
	//复用模式
	fanstruct.GPIO_Mode = GPIO_Mode_AF;
	fanstruct.GPIO_Speed = GPIO_Low_Speed;
	//上拉电阻
	fanstruct.GPIO_OType = GPIO_OType_PP;
	fanstruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&fanstruct);

	
	
	//4.配置定时器
	TIM_TimeBaseInitTypeDef tim12struct;
	//预分频：84 / 84 = 1mhz = 10^6hz
	//1个机器周期 ：0.000001s
	tim12struct.TIM_Prescaler = 400 - 1;
	//自动装载值
	tim12struct.TIM_Period = 100 -1;
	//定时周期20000 = 20ms
	;
	//向上计数
	tim12struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim12struct.TIM_ClockDivision = TIM_CKD_DIV1;
	
   TIM_TimeBaseInit(TIM2, &tim12struct);

	
	
	//5.配置TIMER12 通道2
	TIM_OCInitTypeDef oc2struct;
	//模式1
	oc2struct.TIM_OCMode = TIM_OCMode_PWM1;
	//极性 - 高电平
	oc2struct.TIM_OCPolarity = TIM_OCPolarity_High;
	//输出使能位
	oc2struct.TIM_OutputState = TIM_OutputState_Enable;
	oc2struct.TIM_Pulse = 0;
	
	TIM_OC3Init(TIM2,&oc2struct);
	
	//6.比较捕获寄存器使能
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);

	//7.自动重装载寄存器使能
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	//8.定时器本身使
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


