#include"user.h"



//����ģʽ
void IIC_INMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOB,&iicstruct);
}

//���ģʽ
void IIC_OUTMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	iicstruct.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOB,&iicstruct);
}



//PB6:sck  PB7:sda
//1��ʼ������
void IIC_Config()
{
	//1.ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//2.����
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	
	//�ⲿ����������
	iicstruct.GPIO_OType = GPIO_OType_OD;
	iicstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	iicstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&iicstruct);
}
//2��ʼ�ź�
void IIC_Start()
{
	//ʱ���߸� �����߸ߵ���
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//ʱ����Ϊ�ߵ�ƽʱ �����߻�ɼ����ݣ����Ժ�������Ҫ��ʱ��������
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);

}
//3��ֹ�ź�
void IIC_End()
{
	//ʱ���߸ߣ������ߵ͵��ߣ��ȶ����
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	GPIO_SetBits(GPIOB,GPIO_Pin_6);//ʱ����Ϊ��
	delay_us(2);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);//�����߱��
	delay_us(2);
	
	//��Ϊ������ֹ�ź����Բ���Ҫ��ʱ��������
}
//4����һ���ֽں���
void IIC_SendByte(unsigned char data)
{
	//һλһλ�Ĵ���data>>1 & 0x01
	unsigned char i = 0;
	for(i = 0;i<8;i++)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);//ʱ���ߵͣ��������ݿ��Ըı�
		delay_us(1);
		
		
		if((data>>(7-i)) & 0x01)//���Ϊ1 ��֤����һλ��ֵΪ1  ����Ҫ�������ߵĵ�ƽ��Ϊ��
			GPIO_SetBits(GPIOB,GPIO_Pin_7);//��Ϊ�ߵ�ƽ��������������ܸı�
		else
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		delay_us(2);
		GPIO_SetBits(GPIOB,GPIO_Pin_6);//ʱ���ߵ�ƽ��߿��Զ�ȡ
		delay_us(4);//�������ϵĵ�ƽ�ȴ�����ȡ
	}
	
	//ʱ����Ϊ�ߵ�ƽʱ �����߻�ɼ����ݣ�����Ҫ��ʱ��������
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	
}



//5��ȡһ���ֽں���
unsigned char IIC_GetByte()
{
	IIC_INMODE();
	unsigned char dat = 0;
	unsigned char i = 0;
	for(i =0;i<8;i++)
	{
		dat = dat << 1;
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);//ʱ���������� 
		delay_us(1);
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
		delay_us(1);
		GPIO_SetBits(GPIOB,GPIO_Pin_6);//ʱ�������� ��ȡ�õ��������ߵĵ�ƽ
		delay_us(1);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
		{
			dat |= 0x01;
		}
		else
		{
			dat &= 0xfe;
		}
			//ʱ����Ϊ�ߵ�ƽʱ �����߻�ɼ����ݣ�����Ҫ��ʱ��������
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(4);
	}
	IIC_OUTMODE();                  
	return dat;
}




//6��ȡACK�ź� Ϊ0�ɹ� 1ʧ��
unsigned char IIC_Get_Ack()
{
	IIC_INMODE();
	//ʱ�����ȱ�� �Ȳ����������ϵ�����
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(1);
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	//ʱ���������������ݣ�������������Ǹߵģ�����������Ǹ߾�û�ɹ�
	delay_us(1);
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
	{
		return 1;
	}
	else
	{
		//ʱ����Ϊ�ߵ�ƽʱ �����߻�ɼ����ݣ�����Ҫ��ʱ��������
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		IIC_OUTMODE();
		return	0;
	}
}


//7����ACK�ź� 
void IIC_SendAck(unsigned char ack)
{

	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	if(ack == NACK)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	}
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_us(4);
	//ʱ����Ϊ�ߵ�ƽʱ �����߻�ɼ����ݣ�����Ҫ��ʱ��������
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
}


