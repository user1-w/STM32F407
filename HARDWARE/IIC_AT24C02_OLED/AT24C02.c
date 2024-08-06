#include"user.h"




//1.设备初始化 检测设备是否存在
int AT24OC02_Init()
{
	IIC_Config();
	IIC_Start();
	IIC_SendByte(WRITE_AT24OC02_ADDR);
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	else
	{
		return	0;
	}
}
//2.随机写 函数
//向某个设备的某个地址写数据
//参数是字节地址，数据
unsigned char AT24OC02_Wriet_Byte(unsigned char wordaddr,unsigned char data)
{
	//1.起始信号
	IIC_Start();
	
	//2.发送设备地址
	IIC_SendByte(WRITE_AT24OC02_ADDR);
	
	//3.获取ack信号
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	//4.发送字节地址
	IIC_SendByte(wordaddr);
	//5.获取ack信号
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	
	//6.发送数据
	IIC_SendByte(data);
	
	//7.获取ack信号
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	
	//8.结束信号
	IIC_End();
	
	return	0;
}

//3.随机读函数
//返回值是数据本身
unsigned char AT24OC02_Read_Byte(unsigned char wordaddr)
{
	unsigned char ret = 0;
	//1.起始信号
	IIC_Start();
	//2 发送设备地址（写）
	IIC_SendByte(WRITE_AT24OC02_ADDR);
	//3 获取ack
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	//4 发送字节地址
	IIC_SendByte(wordaddr);
	//5 获取ack
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	//6 起始信号
	IIC_Start();
	//7 发送设备地址（读）
	IIC_SendByte(READ_AT24OC02_ADDR);
	//8 获取ack
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	//9 读出数据
	ret = IIC_GetByte();
	//10 发送nack
	IIC_SendAck(NACK);
	//11 结束信号
	IIC_End();
	return ret;
}	



