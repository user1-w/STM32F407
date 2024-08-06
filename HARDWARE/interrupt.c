#include "user.h"


extern int flg;//���ƺ�����
extern int tep;//������ʪ�Ȳɼ�
extern int beepflag;

void INTERRUPT_KEY1_Config(void)//PE4
{
	//1.����ʱ��
	//ʱ��ʹ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//����PE4
		//��ʼ��
		GPIO_InitTypeDef keystruct;
		keystruct.GPIO_Mode = GPIO_Mode_IN;
		keystruct.GPIO_Pin = GPIO_Pin_4;
		keystruct.GPIO_PuPd = GPIO_PuPd_UP;
		keystruct.GPIO_Speed = GPIO_Low_Speed;
		GPIO_Init(GPIOE,&keystruct);
	//�ж�����-�ⲿ�ж�-4����
	//����IO��Ϊ�жϿ�
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	//�ⲿ�жϳ�ʼ��
		EXTI_InitTypeDef extistruct;
		extistruct.EXTI_Line = EXTI_Line4;
		extistruct.EXTI_LineCmd = ENABLE;
		extistruct.EXTI_Mode = EXTI_Mode_Interrupt;//�ж�ģʽIO�ж�
		extistruct.EXTI_Trigger = EXTI_Trigger_Falling;//�½��شӸߵ���
		EXTI_Init(&extistruct);
		//�����ж����ȼ�
		NVIC_InitTypeDef nvicstruct;
		nvicstruct.NVIC_IRQChannel =EXTI4_IRQn;
		nvicstruct.NVIC_IRQChannelCmd = ENABLE;
		nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
		nvicstruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&nvicstruct);
}

void INTERRUPT_KEY2_Config(void)//PE4
{
	//1.����ʱ��
	//ʱ��ʹ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//����PE4
		//��ʼ��
		GPIO_InitTypeDef keystruct;
		keystruct.GPIO_Mode = GPIO_Mode_IN;
		keystruct.GPIO_Pin = GPIO_Pin_5;
		keystruct.GPIO_PuPd = GPIO_PuPd_UP;
		keystruct.GPIO_Speed = GPIO_Low_Speed;
		GPIO_Init(GPIOE,&keystruct);
	//�ж�����-�ⲿ�ж�-4����
		//PE4���ó��ⲿ�ж�4��
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	//�ⲿ�жϳ�ʼ��
		EXTI_InitTypeDef extistruct;
		extistruct.EXTI_Line = EXTI_Line5;
		extistruct.EXTI_LineCmd = ENABLE;
		extistruct.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
		extistruct.EXTI_Trigger = EXTI_Trigger_Falling;//�½��شӸߵ���
		EXTI_Init(&extistruct);
		//�����ж����ȼ�
		NVIC_InitTypeDef nvicstruct;
		nvicstruct.NVIC_IRQChannel =EXTI9_5_IRQn;
		nvicstruct.NVIC_IRQChannelCmd = ENABLE;
		nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
		nvicstruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&nvicstruct);
}



void INTERRUPT_KEY3_Config(void)//PE4
{
	//1.����ʱ��
	//ʱ��ʹ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//����PE4
		//��ʼ��
		GPIO_InitTypeDef keystruct;
		keystruct.GPIO_Mode = GPIO_Mode_IN;
		keystruct.GPIO_Pin = GPIO_Pin_6;
		keystruct.GPIO_PuPd = GPIO_PuPd_UP;
		keystruct.GPIO_Speed = GPIO_Low_Speed;
		GPIO_Init(GPIOE,&keystruct);
	//�ж�����-�ⲿ�ж�-4����
		//PE4���ó��ⲿ�ж�4��
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
	//�ⲿ�жϳ�ʼ��
		EXTI_InitTypeDef extistruct;
		extistruct.EXTI_Line = EXTI_Line6;
		extistruct.EXTI_LineCmd = ENABLE;
		extistruct.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
		extistruct.EXTI_Trigger = EXTI_Trigger_Falling;//�½��شӸߵ���
		EXTI_Init(&extistruct);
		//�����ж����ȼ�
		NVIC_InitTypeDef nvicstruct;
		nvicstruct.NVIC_IRQChannel =EXTI9_5_IRQn;
		nvicstruct.NVIC_IRQChannelCmd = ENABLE;
		nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
		nvicstruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&nvicstruct);
}



void INTERRUPT_KEY4_Config(void)//PC13
{
	//1.����ʱ��
	//ʱ��ʹ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//����PE4
		//��ʼ��
		GPIO_InitTypeDef keystruct;
		keystruct.GPIO_Mode = GPIO_Mode_IN;
		keystruct.GPIO_Pin = GPIO_Pin_13;
		keystruct.GPIO_PuPd = GPIO_PuPd_UP;
		keystruct.GPIO_Speed = GPIO_Low_Speed;
		GPIO_Init(GPIOC,&keystruct);
	//�ж�����-�ⲿ�ж�-4����
		//PE4���ó��ⲿ�ж�4��
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
	//�ⲿ�жϳ�ʼ��
		EXTI_InitTypeDef extistruct;
		extistruct.EXTI_Line = EXTI_Line13;
		extistruct.EXTI_LineCmd = ENABLE;
		extistruct.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
		extistruct.EXTI_Trigger = EXTI_Trigger_Falling;//�½��شӸߵ���
		EXTI_Init(&extistruct);
		//�����ж����ȼ�
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
	
	
	
	
