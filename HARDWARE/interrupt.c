#include "user.h"


extern int flg;//控制呼吸灯
extern int tep;//控制温湿度采集
extern int beepflag;

void INTERRUPT_KEY1_Config(void)//PE4
{
	//1.配置时钟
	//时钟使能
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//配置PE4
		//初始化
		GPIO_InitTypeDef keystruct;
		keystruct.GPIO_Mode = GPIO_Mode_IN;
		keystruct.GPIO_Pin = GPIO_Pin_4;
		keystruct.GPIO_PuPd = GPIO_PuPd_UP;
		keystruct.GPIO_Speed = GPIO_Low_Speed;
		GPIO_Init(GPIOE,&keystruct);
	//中断类型-外部中断-4号线
	//配置IO口为中断口
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	//外部中断初始化
		EXTI_InitTypeDef extistruct;
		extistruct.EXTI_Line = EXTI_Line4;
		extistruct.EXTI_LineCmd = ENABLE;
		extistruct.EXTI_Mode = EXTI_Mode_Interrupt;//中断模式IO中断
		extistruct.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿从高到低
		EXTI_Init(&extistruct);
		//配置中断优先级
		NVIC_InitTypeDef nvicstruct;
		nvicstruct.NVIC_IRQChannel =EXTI4_IRQn;
		nvicstruct.NVIC_IRQChannelCmd = ENABLE;
		nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
		nvicstruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&nvicstruct);
}

void INTERRUPT_KEY2_Config(void)//PE4
{
	//1.配置时钟
	//时钟使能
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//配置PE4
		//初始化
		GPIO_InitTypeDef keystruct;
		keystruct.GPIO_Mode = GPIO_Mode_IN;
		keystruct.GPIO_Pin = GPIO_Pin_5;
		keystruct.GPIO_PuPd = GPIO_PuPd_UP;
		keystruct.GPIO_Speed = GPIO_Low_Speed;
		GPIO_Init(GPIOE,&keystruct);
	//中断类型-外部中断-4号线
		//PE4配置成外部中断4；
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	//外部中断初始化
		EXTI_InitTypeDef extistruct;
		extistruct.EXTI_Line = EXTI_Line5;
		extistruct.EXTI_LineCmd = ENABLE;
		extistruct.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
		extistruct.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿从高到低
		EXTI_Init(&extistruct);
		//配置中断优先级
		NVIC_InitTypeDef nvicstruct;
		nvicstruct.NVIC_IRQChannel =EXTI9_5_IRQn;
		nvicstruct.NVIC_IRQChannelCmd = ENABLE;
		nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
		nvicstruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&nvicstruct);
}



void INTERRUPT_KEY3_Config(void)//PE4
{
	//1.配置时钟
	//时钟使能
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//配置PE4
		//初始化
		GPIO_InitTypeDef keystruct;
		keystruct.GPIO_Mode = GPIO_Mode_IN;
		keystruct.GPIO_Pin = GPIO_Pin_6;
		keystruct.GPIO_PuPd = GPIO_PuPd_UP;
		keystruct.GPIO_Speed = GPIO_Low_Speed;
		GPIO_Init(GPIOE,&keystruct);
	//中断类型-外部中断-4号线
		//PE4配置成外部中断4；
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
	//外部中断初始化
		EXTI_InitTypeDef extistruct;
		extistruct.EXTI_Line = EXTI_Line6;
		extistruct.EXTI_LineCmd = ENABLE;
		extistruct.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
		extistruct.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿从高到低
		EXTI_Init(&extistruct);
		//配置中断优先级
		NVIC_InitTypeDef nvicstruct;
		nvicstruct.NVIC_IRQChannel =EXTI9_5_IRQn;
		nvicstruct.NVIC_IRQChannelCmd = ENABLE;
		nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
		nvicstruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&nvicstruct);
}



void INTERRUPT_KEY4_Config(void)//PC13
{
	//1.配置时钟
	//时钟使能
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//配置PE4
		//初始化
		GPIO_InitTypeDef keystruct;
		keystruct.GPIO_Mode = GPIO_Mode_IN;
		keystruct.GPIO_Pin = GPIO_Pin_13;
		keystruct.GPIO_PuPd = GPIO_PuPd_UP;
		keystruct.GPIO_Speed = GPIO_Low_Speed;
		GPIO_Init(GPIOC,&keystruct);
	//中断类型-外部中断-4号线
		//PE4配置成外部中断4；
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
	//外部中断初始化
		EXTI_InitTypeDef extistruct;
		extistruct.EXTI_Line = EXTI_Line13;
		extistruct.EXTI_LineCmd = ENABLE;
		extistruct.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
		extistruct.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿从高到低
		EXTI_Init(&extistruct);
		//配置中断优先级
		NVIC_InitTypeDef nvicstruct;
		nvicstruct.NVIC_IRQChannel =EXTI15_10_IRQn;
		nvicstruct.NVIC_IRQChannelCmd = ENABLE;
		nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
		nvicstruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&nvicstruct);
}



		void EXTI4_IRQHandler()
	{
		if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
		{
			delay(10);
			if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
			{
				while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4));
				OLed_Fill(0);
				Oled_print(10,4,"System TurnOn");
				EXTI_ClearITPendingBit(EXTI_Line4);
			}
			
		}
		
	}

	
	
	
	void EXTI9_5_IRQHandler()
	{
		if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5))
		{
				OLed_Fill(0);
				Oled_print(10,4,"System TurnOff");
				flg = 0;
				tep = 0;
				beepflag = 0;
				delay_ms(2000);
				OLed_Fill(0);
			EXTI_ClearITPendingBit(EXTI_Line5);
		}
		if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6))
		{
			Fan_Control(10000);
			BeepOn();
			EXTI_ClearITPendingBit(EXTI_Line6);
		}
		
	}

//	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
//		{
//			delay(10);
//			if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
//			{
//				while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13));
//					BeepOff();
//				EXTI_ClearITPendingBit(EXTI_Line13);
//			}
//			
//		}
	

	void EXTI15_10_IRQHandler()
	{
		Fan_Control(6000);
		BeepOff();
		EXTI_ClearITPendingBit(EXTI_Line13);
	
	}
	
	
	
	
