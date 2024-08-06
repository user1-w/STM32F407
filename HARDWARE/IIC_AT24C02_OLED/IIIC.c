#include"user.h"



//输入模式
void IIC_INMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOB,&iicstruct);
}

//输出模式
void IIC_OUTMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	iicstruct.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOB,&iicstruct);
}



//PB6:sck  PB7:sda
//1初始化函数
void IIC_Config()
{
	//1.时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//2.引脚
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	
	//外部有上拉电阻
	iicstruct.GPIO_OType = GPIO_OType_OD;
	iicstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	iicstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&iicstruct);
}
//2起始信号
void IIC_Start()
{
	//时钟线高 数据线高到低
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//时钟线为高电平时 数据线会采集数据，所以函数结束要把时钟线拉低
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);

}
//3终止信号
void IIC_End()
{
	//时钟线高，数据线低到高，先都变低
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	GPIO_SetBits(GPIOB,GPIO_Pin_6);//时钟线为高
	delay_us(2);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);//数据线变高
	delay_us(2);
	
	//因为这是终止信号所以不需要把时钟线拉低
}
//4发送一个字节函数
void IIC_SendByte(unsigned char data)
{
	//一位一位的传，data>>1 & 0x01
	unsigned char i = 0;
	for(i = 0;i<8;i++)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);//时钟线低，所以数据可以改变
		delay_us(1);
		
		
		if((data>>(7-i)) & 0x01)//如果为1 就证明这一位的值为1  所以要把数据线的电平变为高
			GPIO_SetBits(GPIOB,GPIO_Pin_7);//变为高电平，这就是数据线能改变
		else
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		delay_us(2);
		GPIO_SetBits(GPIOB,GPIO_Pin_6);//时钟线电平变高可以读取
		delay_us(4);//数据线上的电平等待被读取
	}
	
	//时钟线为高电平时 数据线会采集数据，所以要把时钟线拉低
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	
}



//5读取一个字节函数
unsigned char IIC_GetByte()
{
	IIC_INMODE();
	unsigned char dat = 0;
	unsigned char i = 0;
	for(i =0;i<8;i++)
	{
		dat = dat << 1;
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);//时钟线先拉低 
		delay_us(1);
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
		delay_us(1);
		GPIO_SetBits(GPIOB,GPIO_Pin_6);//时钟线拉高 读取得到的数据线的电平
		delay_us(1);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
		{
			dat |= 0x01;
		}
		else
		{
			dat &= 0xfe;
		}
			//时钟线为高电平时 数据线会采集数据，所以要把时钟线拉低
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(4);
	}
	IIC_OUTMODE();                  
	return dat;
}




//6获取ACK信号 为0成功 1失败
unsigned char IIC_Get_Ack()
{
	IIC_INMODE();
	//时钟线先变低 先不读数据线上的数据
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(1);
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	//时钟线拉高来读数据，上面的数据线是高的，如果读到的是高就没成功
	delay_us(1);
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
	{
		return 1;
	}
	else
	{
		//时钟线为高电平时 数据线会采集数据，所以要把时钟线拉低
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		IIC_OUTMODE();
		return	0;
	}
}


//7发送ACK信号 
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
	//时钟线为高电平时 数据线会采集数据，所以要把时钟线拉低
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
}


