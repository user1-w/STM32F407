#include "user.h"


void Timer4_Config(unsigned short int psc,unsigned short int period)
{
	//配置时钟 - 一般外设42mhz 如果是定时器就是84
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	//配置时基单元-定时器初始化
	
	TIM_TimeBaseInitTypeDef time4struct;
	//预分频系数 - 总线时钟 做除法
	//84mhz/8400 = 0.01mhz-> 10000hz
	//8400为自定义的数
	time4struct.TIM_Prescaler = psc;
	//自动装载数值 = 定时时间 =自动装数值 * 基础时间（1/10000）
	time4struct.TIM_Period = period;
	//计数模式
	time4struct.TIM_CounterMode = TIM_CounterMode_Up;
	time4struct.TIM_ClockDivision = TIM_CKD_DIV1;
	//
	TIM_TimeBaseInit(TIM4,&time4struct);
	
	//允许定时时间到，执行中断函数
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	//定时器使能
	TIM_Cmd(TIM4,ENABLE);
	
	//中断配置
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = TIM4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}



//中断函数
void TIM4_IRQHandler()
{
	//LED_Flow();
	//GPIO_ToggleBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}


