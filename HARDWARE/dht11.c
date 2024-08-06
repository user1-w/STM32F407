#include"user.h"

unsigned int tnum = 0;

//DHT11配置
void dht11_Config()
{
	//PA3
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//配置引脚
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	//输出模式
	dht11struct.GPIO_Mode = GPIO_Mode_OUT;
	//开漏模式
	dht11struct.GPIO_OType = GPIO_OType_OD;
	//无需电阻
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&dht11struct);
	//输出模式要配置电平
	//因为起始信号为低 - 高，所以开始给一个高电平
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}
//DHT11输入模式
void dht11_Inmod()
{
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	dht11struct.GPIO_Mode = GPIO_Mode_IN;
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&dht11struct);
}
//DHT11输出模式
void dht11_Outmod()
{
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	//输出模式
	dht11struct.GPIO_Mode = GPIO_Mode_OUT;
	//开漏模式
	dht11struct.GPIO_OType = GPIO_OType_OD;
	//无需电阻
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&dht11struct);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}





//DHT11读字节
unsigned char dht11_ReadBytes()
{
	unsigned char resdata = 0;
	char i = 0;
	//一个字节八位，所以循环八次 每次得到每个位的只 0或1
	//并且从高位开始 '0'000 0000  
	for(i=0;i<8;i++)
	{
		//先移位
		resdata = resdata << 1;
		//跳过高电平 这是上次残余的
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		//跳过低电平 这样低电平都一样 所以只需要比较高电平
		while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
		{
			delay_us(30);
		}
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
		{
			resdata |= 0x01;
		}else
		{
			resdata &= 0xfe;
		}
	}
	return resdata;
}




char buff[5] = "";

//DHT11读数据
//参数是输出型参数
//返回值0为成功 失败1
unsigned char dht11_ReadData(char *humiz,char *humix,char *tempz,char *tempx)
{
	//时序
	//输出模式 - 低（20ms）+高（30us）
	dht11_Outmod();
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	delay_ms(20);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_us(30);
	//输入模式 读数据 传感器发送 低（45us）- 高（45us）
	dht11_Inmod();
	//自带上拉电阻，所以等待高电平结束
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	
	//也能由tnum测出时间
	//对面发送的是低电平 那么 cpu等待 等低电平过去
	while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
//	{
//		delay_us(1);
//		tnum++;
//		if(tnum > 60)
//			return 1;
//	}
	//tnum清
	//把高电平也越过
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
//	{
//		delay_us(1);
//		tnum++;
//		if(tnum > 60)
//			return 1;
//	}
	
	//真正的数据 五位
	int i = 0;
	
	for(i = 0;i<5;i++)
	{
		buff[i] = dht11_ReadBytes();
	}
	
	//在函数结束之前把引脚变为输出模式
	dht11_Outmod();
	if(buff[4] == buff[0] + buff[1] + buff[2] +buff[3])
	{
		*humiz = buff[0];
		*humix = buff[1];
		*tempz = buff[2];
		*tempx = buff[3];
		return 0;
	}
	else{
		return 1;
	}
}
