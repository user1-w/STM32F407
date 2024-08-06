

#include"user.h"

//PB2 CS --->设备层文件配置
//PB3 CLK--->协议层文件配置
//PB4 MISO 输入
//PB5 MOSI 输出


//1 SPI初始化函数

void SPI_Config()
{
	//1时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	//2引脚
	GPIO_InitTypeDef spistruct;
	spistruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	//复用模式
	spistruct.GPIO_Mode = GPIO_Mode_AF;
	spistruct.GPIO_OType = GPIO_OType_PP;
	spistruct.GPIO_Speed = GPIO_Fast_Speed;
	//上拉电阻
	spistruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&spistruct);
	
	
	//3.复用配置 GPIO复用为SPI接口
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);
	
	//4.SPI电路初始化
	SPI_InitTypeDef NEWSPISTRUCT;
	//全双工
	NEWSPISTRUCT.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//主机模式
	NEWSPISTRUCT.SPI_Mode = SPI_Mode_Master;
	//数据位大小
	NEWSPISTRUCT.SPI_DataSize = SPI_DataSize_8b;
	//时钟极性  空闲为低
	NEWSPISTRUCT.SPI_CPOL = SPI_CPOL_Low;
	//时钟相位   第一个上升沿数据被采样
	NEWSPISTRUCT.SPI_CPHA = SPI_CPHA_1Edge;
	//传输位 先低位还是先高位
	NEWSPISTRUCT.SPI_FirstBit = SPI_FirstBit_MSB;
	//片选 CS：软件片选
	NEWSPISTRUCT.SPI_NSS = SPI_NSS_Soft;
	//预分频系数 
	NEWSPISTRUCT.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	//校验数值
	NEWSPISTRUCT.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1,&NEWSPISTRUCT);
	//SPI使能
	SPI_Cmd(SPI1,ENABLE);
}

//2 spi读写函数
//返回值是读到的数据
//参数是写过去的数据
unsigned char SPI1_Wriet_Read(unsigned char data)
{
	//发送数据 关注一个标志位 发送完 变为1
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1,data);
	//接收数据 关注一个标志位 发送完 变为1
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}

