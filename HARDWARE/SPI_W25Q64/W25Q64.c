

#include"user.h"



//����ָ����ֵ
#define W25X_ManufactDeviceID    0x90 
//����Ƭѡ����
#define W25X_ChipErase            0x60   //����h������
//��״̬�Ĵ���
#define W25X_ReadStatusReg        0x05
//������
#define W25X_ReadData            0x03
//дʹ��
#define W25X_WriteEnable        0x06
//д��ʹ��
#define W25X_WriteDisable        0x04 
//ҳ��� ����д����
#define W25X_PageProgram        0x02
//�����
#define W25X_BlockErase           0xD8 
//��������  
#define W25X_SectorErase        0x20

#define W25X_NULL               0x00

//ͨ��stm32 ��spi�豸��spiЭ�飩����ָ�� 0XA9 0XC2 - spi�豸��ִ�в�ͬ�Ķ���

//�豸��ʼ������
void W25Q64_Config()
{
	//1.SPI��ʼ��
	SPI_Config();
	//2.����lora  �͵�ƽѡ�� ���ߵ�ƽ��������
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
	//���ߵ�ƽ�Ȳ�ѡ��
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	
}


//��ȡ�豸id����
unsigned short int W25Q64_ReadID()
{
	//1.׼������
		unsigned short int id = 0;

	//2.Ƭѡ
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//3.��ʼд 4�� ��һ���ֽ��������豸id
		SPI1_Wriet_Read(W25X_ManufactDeviceID);
		SPI1_Wriet_Read(W25X_NULL);
		SPI1_Wriet_Read(W25X_NULL);
		SPI1_Wriet_Read(W25X_NULL);
	//4.��ʼ�� - 2���ֽ� ������͵������ֽ���id��
	//id��һ��16λ ���Զ���һ����Ҫ�����ڶ�
	id |= SPI1_Wriet_Read(W25X_NULL);
	id = id<<8;
	id |= SPI1_Wriet_Read(W25X_NULL);
	//ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//���ض�ȡ���Ľ�� Ҳ����id
	return id;
}


//д����ʹ�ܺ���
void W25Q64_Write_Enable()
{
	//Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//����ʹ������
	SPI1_Wriet_Read(W25X_WriteEnable);
	//ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
}


//���оƬ�Ƿ�busy����

unsigned char W25Q64_Check_busy()
{
	unsigned char stat = 0;
	do
	{
		//Ƭѡ
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		//�������� - ��ȡ��ؼĴ�����ȡ״̬
		SPI1_Wriet_Read(W25X_ReadStatusReg);
		//�� statΪ1����busy Ϊ0��busy
		stat = SPI1_Wriet_Read(W25X_NULL);
		//ȡ��Ƭѡ
		GPIO_SetBits(GPIOB,GPIO_Pin_2);
	}while(stat & 0x01);
	return 0;
}


//��������оƬ����
//��Ϊ���ܰ�1->0 ����оƬ����Ϊ1

void W25Q64_Erase_allChip()
{	
	W25Q64_Write_Enable();
	W25Q64_Check_busy();
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);

	//���Ͳ���оƬָ��
	SPI1_Wriet_Read(W25X_ChipErase);

	//ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	W25Q64_Check_busy();
}


// д�豸���� - д��ĳ��λ��

//һ��дһҳ 256�ֽ�
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



//���豸���� - ��ĳ��λ��
//�������Ǹ��ֽڶ������� �洢��ʲôλ�� ��Ҫ���೤ ����ֵ��������������
unsigned char W25Q64_Read_Data(unsigned int wordaddr,unsigned char buff[],unsigned char len)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	SPI1_Wriet_Read(W25X_ReadData);
	SPI1_Wriet_Read((wordaddr>>16)&0xff);
	SPI1_Wriet_Read((wordaddr>>8)&0xff);
	SPI1_Wriet_Read((wordaddr)&0xff);
	//������
	int i =0 ;
	for(i =0 ;i<len;i++)
	{
		buff[i] = SPI1_Wriet_Read(0x00);
	}
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	return i;
}


