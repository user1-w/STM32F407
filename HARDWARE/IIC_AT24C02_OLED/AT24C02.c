#include"user.h"




//1.�豸��ʼ�� ����豸�Ƿ����
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
//2.���д ����
//��ĳ���豸��ĳ����ַд����
//�������ֽڵ�ַ������
unsigned char AT24OC02_Wriet_Byte(unsigned char wordaddr,unsigned char data)
{
	//1.��ʼ�ź�
	IIC_Start();
	
	//2.�����豸��ַ
	IIC_SendByte(WRITE_AT24OC02_ADDR);
	
	//3.��ȡack�ź�
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	//4.�����ֽڵ�ַ
	IIC_SendByte(wordaddr);
	//5.��ȡack�ź�
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	
	//6.��������
	IIC_SendByte(data);
	
	//7.��ȡack�ź�
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	
	//8.�����ź�
	IIC_End();
	
	return	0;
}

//3.���������
//����ֵ�����ݱ���
unsigned char AT24OC02_Read_Byte(unsigned char wordaddr)
{
	unsigned char ret = 0;
	//1.��ʼ�ź�
	IIC_Start();
	//2 �����豸��ַ��д��
	IIC_SendByte(WRITE_AT24OC02_ADDR);
	//3 ��ȡack
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	//4 �����ֽڵ�ַ
	IIC_SendByte(wordaddr);
	//5 ��ȡack
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	//6 ��ʼ�ź�
	IIC_Start();
	//7 �����豸��ַ������
	IIC_SendByte(READ_AT24OC02_ADDR);
	//8 ��ȡack
	if(IIC_Get_Ack())
	{
		IIC_End();
		return 1;
	}
	//9 ��������
	ret = IIC_GetByte();
	//10 ����nack
	IIC_SendAck(NACK);
	//11 �����ź�
	IIC_End();
	return ret;
}	



