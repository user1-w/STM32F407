#include"user.h"


void BeepConfig(void)
{
	//����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//���ýӿ�
	GPIO_InitTypeDef beepstruct;
	beepstruct.GPIO_Pin = GPIO_Pin_10;
	beepstruct.GPIO_Mode = GPIO_Mode_OUT;
	beepstruct.GPIO_OType = GPIO_OType_PP;
	beepstruct.GPIO_Speed = GPIO_Fast_Speed;
	beepstruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB,&beepstruct);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	
}

void BeepOn(void)
{
	//����������Ϊ�߻��ǵ�
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_SET);
	
}

void BeepOff(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);
	
}

void BeepAlarm(void)
{
	//�Զ���ת
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_SET);
	delay_ms(500);
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);
	delay_ms(500);
}
