#include"user.h"

//按键配置函数
void Key1_2_3_Config(void)
{
		//时钟使能
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
		//初始化
		GPIO_InitTypeDef keystruct;
		keystruct.GPIO_Mode = GPIO_Mode_IN;
		keystruct.GPIO_OType = GPIO_OType_PP;
		keystruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
		keystruct.GPIO_PuPd = GPIO_PuPd_UP;
		keystruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOE,&keystruct);
}

//PC13
void Key_4_Config(void)
{
	//时钟使能
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		//初始化
		GPIO_InitTypeDef key1struct;
		key1struct.GPIO_Mode = GPIO_Mode_IN;
		key1struct.GPIO_OType = GPIO_OType_PP;
		key1struct.GPIO_Pin = GPIO_Pin_13;
		key1struct.GPIO_PuPd = GPIO_PuPd_UP;
		key1struct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOC,&key1struct);
}

//按键扫描函数
void Key_Scan(void)
{
	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
	{
			//消除抖动，二次判断
			delay(100);
			if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
			{
				while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4));//判断是否按键抬起
				BeepOn();
			}
	}
	else if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5))
	{
			//消除抖动，二次判断
			delay(100);
			if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5))
			{
				while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5));//判断是否按键抬起
				BeepOff();
			}
	}
	else if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6))
	{
			//消除抖动，二次判断
			delay(100);
			if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6))
			{
				while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6));//判断是否按键抬起
				LED_Flow();
			}
	}
	else if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
	{
			//消除抖动，二次判断
			delay(100);
			if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
			{
				while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13));//判断是否按键抬起
				LED_TurnOff(LED1);
				LED_TurnOff(LED2);
				LED_TurnOff(LED3);
			}
	}
}




