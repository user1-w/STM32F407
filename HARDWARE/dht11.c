#include"user.h"

unsigned int tnum = 0;

//DHT11����
void dht11_Config()
{
	//PA3
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//��������
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	//���ģʽ
	dht11struct.GPIO_Mode = GPIO_Mode_OUT;
	//��©ģʽ
	dht11struct.GPIO_OType = GPIO_OType_OD;
	//�������
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&dht11struct);
	//���ģʽҪ���õ�ƽ
	//��Ϊ��ʼ�ź�Ϊ�� - �ߣ����Կ�ʼ��һ���ߵ�ƽ
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}
//DHT11����ģʽ
void dht11_Inmod()
{
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	dht11struct.GPIO_Mode = GPIO_Mode_IN;
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&dht11struct);
}
//DHT11���ģʽ
void dht11_Outmod()
{
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	//���ģʽ
	dht11struct.GPIO_Mode = GPIO_Mode_OUT;
	//��©ģʽ
	dht11struct.GPIO_OType = GPIO_OType_OD;
	//�������
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&dht11struct);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}





//DHT11���ֽ�
unsigned char dht11_ReadBytes()
{
	unsigned char resdata = 0;
	char i = 0;
	//һ���ֽڰ�λ������ѭ���˴� ÿ�εõ�ÿ��λ��ֻ 0��1
	//���ҴӸ�λ��ʼ '0'000 0000  
	for(i=0;i<8;i++)
	{
		//����λ
		resdata = resdata << 1;
		//�����ߵ�ƽ �����ϴβ����
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		//�����͵�ƽ �����͵�ƽ��һ�� ����ֻ��Ҫ�Ƚϸߵ�ƽ
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

//DHT11������
//����������Ͳ���
//����ֵ0Ϊ�ɹ� ʧ��1
unsigned char dht11_ReadData(char *humiz,char *humix,char *tempz,char *tempx)
{
	//ʱ��
	//���ģʽ - �ͣ�20ms��+�ߣ�30us��
	dht11_Outmod();
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	delay_ms(20);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_us(30);
	//����ģʽ ������ ���������� �ͣ�45us��- �ߣ�45us��
	dht11_Inmod();
	//�Դ��������裬���Եȴ��ߵ�ƽ����
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	
	//Ҳ����tnum���ʱ��
	//���淢�͵��ǵ͵�ƽ ��ô cpu�ȴ� �ȵ͵�ƽ��ȥ
	while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
//	{
//		delay_us(1);
//		tnum++;
//		if(tnum > 60)
//			return 1;
//	}
	//tnum��
	//�Ѹߵ�ƽҲԽ��
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
//	{
//		delay_us(1);
//		tnum++;
//		if(tnum > 60)
//			return 1;
//	}
	
	//���������� ��λ
	int i = 0;
	
	for(i = 0;i<5;i++)
	{
		buff[i] = dht11_ReadBytes();
	}
	
	//�ں�������֮ǰ�����ű�Ϊ���ģʽ
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
