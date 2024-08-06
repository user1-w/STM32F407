
#include "user.h"


//1.配置pwm 风扇
//PB15 + TIMER12_CH2

void Timer12_Ch2_PwmConfig()
{
	//1配置时钟 APB1
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//2.复用配置 b组15号 配置成 定时器12
 GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM12);
	//3.GPIO引脚配置 为复用模式
	GPIO_InitTypeDef fanstruct;
	fanstruct.GPIO_Pin = GPIO_Pin_15;
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
	tim12struct.TIM_Prescaler = 84 - 1;
	//自动装载值
	tim12struct.TIM_Period = 1000 -1;
	//定时周期20000 = 20ms
	;
	//向上计数
	tim12struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim12struct.TIM_ClockDivision = TIM_CKD_DIV1;
	
   TIM_TimeBaseInit(TIM12, &tim12struct);

	
	
	//5.配置TIMER12 通道2
	TIM_OCInitTypeDef oc2struct;
	//模式1
	oc2struct.TIM_OCMode = TIM_OCMode_PWM1;
	//极性 - 高电平
	oc2struct.TIM_OCPolarity = TIM_OCPolarity_High;
	//输出使能位
	oc2struct.TIM_OutputState = TIM_OutputState_Enable;
	oc2struct.TIM_Pulse = 0;
	
	TIM_OC2Init(TIM12,&oc2struct);
	
	//6.比较捕获寄存器使能
	TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Enable);

	//7.自动重装载寄存器使能
	TIM_ARRPreloadConfig(TIM12,ENABLE);
	//8.定时器本身使
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


