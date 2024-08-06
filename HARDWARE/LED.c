#include"user.h"


//延迟函数
void delay( unsigned int nCount)
{
	 nCount*=10000;
	while(nCount--)
	{
	}
}

//1.led模块配置函数

void LED_Config()
{
	//配置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//配置接口
	GPIO_InitTypeDef ledstruct;
	ledstruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	ledstruct.GPIO_Mode = GPIO_Mode_OUT;
	ledstruct.GPIO_OType = GPIO_OType_PP;
	ledstruct.GPIO_Speed = GPIO_Fast_Speed;
	ledstruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&ledstruct);
	//初始化接口
	GPIO_SetBits(GPIOE,GPIO_Pin_8);
	GPIO_SetBits(GPIOE,GPIO_Pin_9);
	GPIO_SetBits(GPIOE,GPIO_Pin_10);
}



//打开led
void LED_TurnOn(unsigned int LEDNUM)
{
	if(LEDNUM == LED1)
	GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	if(LEDNUM == LED2)
	GPIO_ResetBits(GPIOE,GPIO_Pin_9);
	if(LEDNUM == LED3)
	GPIO_ResetBits(GPIOE,GPIO_Pin_10);
	
}


//关闭led
void LED_TurnOff(unsigned int LEDNUM)
{
	switch(LEDNUM)
	{
		
		case LED1:GPIO_SetBits(GPIOE,GPIO_Pin_8);break;
		case LED2:GPIO_SetBits(GPIOE,GPIO_Pin_9);break;
		case LED3:GPIO_SetBits(GPIOE,GPIO_Pin_10);break;
		default: break;
	}
	
	
}


//闪烁led
void LED_Shine()
{
	LED_TurnOn(LED1);
	LED_TurnOn(LED2);
	LED_TurnOn(LED3);
	delay(500);
	LED_TurnOff(LED1);
	LED_TurnOff(LED2);
	LED_TurnOff(LED3);
	delay(500);
	
	
}


//流水led
void LED_Flow()
{
	LED_TurnOn(LED1);
	LED_TurnOff(LED2);
	LED_TurnOff(LED3);
	delay(500);
	LED_TurnOn(LED2);
	LED_TurnOff(LED1);;
	LED_TurnOff(LED3);
	delay(500);
	LED_TurnOn(LED3);
	LED_TurnOff(LED1);
	LED_TurnOff(LED2);
	delay(500);
	
}
