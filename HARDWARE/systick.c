#include "user.h"


unsigned int timedelay = 0;


void systick_config()
{
	//配置时钟源 168
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//配置时间
	
	while(SysTick_Config(SystemCoreClock/1000))
	{
		LED_TurnOn(LED1);
	}
	
}




//1ms后到中断函数
void SysTick_Handler()
{
	if(timedelay != 0)
	{
		timedelay--;
	}
}
	

//自定义精确延时
void systick_delay(unsigned int n)
{
	timedelay = n;
	while(timedelay != 0);
}

