#include "user.h"


unsigned int timedelay = 0;


void systick_config()
{
	//����ʱ��Դ 168
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//����ʱ��
	
	while(SysTick_Config(SystemCoreClock/1000))
	{
		LED_TurnOn(LED1);
	}
	
}




//1ms���жϺ���
void SysTick_Handler()
{
	if(timedelay != 0)
	{
		timedelay--;
	}
}
	

//�Զ��徫ȷ��ʱ
void systick_delay(unsigned int n)
{
	timedelay = n;
	while(timedelay != 0);
}

