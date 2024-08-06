

#include"user.h"



//常用指令数值
#define W25X_ManufactDeviceID    0x90 
//擦除片选命令
#define W25X_ChipErase            0x60   //或者h都可以
//读状态寄存器
#define W25X_ReadStatusReg        0x05
//读数据
#define W25X_ReadData            0x03
//写使能
#define W25X_WriteEnable        0x06
//写非使能
#define W25X_WriteDisable        0x04 
//页编程 就是写数据
#define W25X_PageProgram        0x02
//块擦除
#define W25X_BlockErase           0xD8 
//扇区擦除  
#define W25X_SectorErase        0x20

#define W25X_NULL               0x00

//通过stm32 给spi设备（spi协议）发送指令 0XA9 0XC2 - spi设备就执行不同的动作

//设备初始化函数
void W25Q64_Config()
{
	//1.SPI初始化
	SPI_Config();
	//2.屏蔽lora  低电平选中 给高电平就屏蔽了
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	GPIO_InitTypeDef lorastruct;
	lorastruct.GPIO_Pin = GPIO_Pin_1;
	lorastruct.GPIO_Mode = GPIO_Mode_OUT;
	lorastruct.GPIO_OType = GPIO_OType_PP;
	lorastruct.GPIO_Speed = GPIO_Fast_Speed;
	lorastruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&lorastruct);
	GPIO_SetBits(GPIOE,GPIO_Pin_1);
	
	
	GPIO_InitTypeDef w25qstruct;
	w25qstruct.GPIO_Pin = GPIO_Pin_2;
	w25qstruct.GPIO_Mode = GPIO_Mode_OUT;
	w25qstruct.GPIO_OType = GPIO_OType_PP;
	w25qstruct.GPIO_Speed = GPIO_Fast_Speed;
	w25qstruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&w25qstruct);
	//给高电平先不选中
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	
}


//读取设备id函数
unsigned short int W25Q64_ReadID()
{
	//1.准备变量
		unsigned short int id = 0;

	//2.片选
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//3.开始写 4个 第一个字节是请求设备id
		SPI1_Wriet_Read(W25X_ManufactDeviceID);
		SPI1_Wriet_Read(W25X_NULL);
		SPI1_Wriet_Read(W25X_NULL);
		SPI1_Wriet_Read(W25X_NULL);
	//4.开始读 - 2个字节 第五个和第六个字节是id号
	//id号一般16位 所以读到一个后要左移在读
	id |= SPI1_Wriet_Read(W25X_NULL);
	id = id<<8;
	id |= SPI1_Wriet_Read(W25X_NULL);
	//取消片选
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//返回读取到的结果 也就是id
	return id;
}


//写数据使能函数
void W25Q64_Write_Enable()
{
	//片选
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//发送使能命令
	SPI1_Wriet_Read(W25X_WriteEnable);
	//取消片选
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
}


//检测芯片是否busy函数

unsigned char W25Q64_Check_busy()
{
	unsigned char stat = 0;
	do
	{
		//片选
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		//发送命令 - 读取相关寄存器获取状态
		SPI1_Wriet_Read(W25X_ReadStatusReg);
		//读 stat为1就是busy 为0不busy
		stat = SPI1_Wriet_Read(W25X_NULL);
		//取消片选
		GPIO_SetBits(GPIOB,GPIO_Pin_2);
	}while(stat & 0x01);
	return 0;
}


//擦除整个芯片函数
//因为不能把1->0 整个芯片都变为1

void W25Q64_Erase_allChip()
{	
	W25Q64_Write_Enable();
	W25Q64_Check_busy();
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);

	//发送擦除芯片指令
	SPI1_Wriet_Read(W25X_ChipErase);

	//取消片选
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	W25Q64_Check_busy();
}


// 写设备函数 - 写到某个位置

//一次写一页 256字节
void W25Q64_Write_Page(unsigned char *pbuff,unsigned int writeaddr,unsigned short int numbytes)
{
	W25Q64_Write_Enable();
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	SPI1_Wriet_Read(W25X_PageProgram);
	SPI1_Wriet_Read((((u8)(writeaddr))>>16)&0xff);
	SPI1_Wriet_Read((((u8)(writeaddr))>>8)&0xff);
	SPI1_Wriet_Read((u8)(writeaddr));
	int i = 0;
	for(i =0;i<numbytes;i++)
	{
		SPI1_Wriet_Read(pbuff[i]);
	}
	
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	W25Q64_Check_busy();
}



//读设备函数 - 读某个位置
//参数从那个字节读出数据 存储到什么位置 想要读多长 返回值真正读到的数据
unsigned char W25Q64_Read_Data(unsigned int wordaddr,unsigned char buff[],unsigned char len)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	SPI1_Wriet_Read(W25X_ReadData);
	SPI1_Wriet_Read((wordaddr>>16)&0xff);
	SPI1_Wriet_Read((wordaddr>>8)&0xff);
	SPI1_Wriet_Read((wordaddr)&0xff);
	//读数据
	int i =0 ;
	for(i =0 ;i<len;i++)
	{
		buff[i] = SPI1_Wriet_Read(0x00);
	}
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	return i;
}


