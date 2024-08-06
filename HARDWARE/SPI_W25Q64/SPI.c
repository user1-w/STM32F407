

#include"user.h"

//PB2 CS --->�豸���ļ�����
//PB3 CLK--->Э����ļ�����
//PB4 MISO ����
//PB5 MOSI ���


//1 SPI��ʼ������

void SPI_Config()
{
	//1ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	//2����
	GPIO_InitTypeDef spistruct;
	spistruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	//����ģʽ
	spistruct.GPIO_Mode = GPIO_Mode_AF;
	spistruct.GPIO_OType = GPIO_OType_PP;
	spistruct.GPIO_Speed = GPIO_Fast_Speed;
	//��������
	spistruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&spistruct);
	
	
	//3.�������� GPIO����ΪSPI�ӿ�
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);
	
	//4.SPI��·��ʼ��
	SPI_InitTypeDef NEWSPISTRUCT;
	//ȫ˫��
	NEWSPISTRUCT.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//����ģʽ
	NEWSPISTRUCT.SPI_Mode = SPI_Mode_Master;
	//����λ��С
	NEWSPISTRUCT.SPI_DataSize = SPI_DataSize_8b;
	//ʱ�Ӽ���  ����Ϊ��
	NEWSPISTRUCT.SPI_CPOL = SPI_CPOL_Low;
	//ʱ����λ   ��һ�����������ݱ�����
	NEWSPISTRUCT.SPI_CPHA = SPI_CPHA_1Edge;
	//����λ �ȵ�λ�����ȸ�λ
	NEWSPISTRUCT.SPI_FirstBit = SPI_FirstBit_MSB;
	//Ƭѡ CS�����Ƭѡ
	NEWSPISTRUCT.SPI_NSS = SPI_NSS_Soft;
	//Ԥ��Ƶϵ�� 
	NEWSPISTRUCT.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	//У����ֵ
	NEWSPISTRUCT.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1,&NEWSPISTRUCT);
	//SPIʹ��
	SPI_Cmd(SPI1,ENABLE);
}

//2 spi��д����
//����ֵ�Ƕ���������
//������д��ȥ������
unsigned char SPI1_Wriet_Read(unsigned char data)
{
	//�������� ��עһ����־λ ������ ��Ϊ1
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1,data);
	//�������� ��עһ����־λ ������ ��Ϊ1
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}

