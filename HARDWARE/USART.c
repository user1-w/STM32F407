#include"user.h"


#define USART_REC_LEN  			200  	//??????????????? 200
#define EN_USART1_RX 			1		//????1??/?????0??????1????
u8  USART_RX_BUF[USART_REC_LEN];
u16 USART_RX_STA;
//�ض���fputc���� 
int fputc(int ch, FILE *f) 
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}




extern char temp[2]; //�¶ȴ洢
extern char hum[2]; 
extern unsigned short int numguang;
extern char wendu[128];
extern char shidu[128];
extern char guangzhao[30];
extern char dianya[30];
extern char shujv[128];
extern void Oled_Temp(void);



extern int flg;//���ƺ�����
extern int tp;//������ʪ�Ȳɼ�
extern int beepflag;
extern int tep;

void Usart_Config()
{
	//����ʱ�� ʹ��USART��A��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//���Ÿ��� ��PA9��PA10 ����Ϊ����
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	//��������Ϊ����ģʽ
	GPIO_InitTypeDef usart1_gpio1_struct;
	usart1_gpio1_struct.GPIO_Mode = GPIO_Mode_AF;
	usart1_gpio1_struct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	usart1_gpio1_struct.GPIO_PuPd = GPIO_PuPd_UP;
	usart1_gpio1_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&usart1_gpio1_struct);
	
	//���ô���
	USART_InitTypeDef usart1struct;
	//������
	usart1struct.USART_BaudRate = 115200;
	//Ӳ���� 
	usart1struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//�������ģʽ
	usart1struct.USART_Mode = USART_Mode_Rx| USART_Mode_Tx;
	//У��λ �� ��λ��һ��
	usart1struct.USART_Parity = USART_Parity_No;
	//ֹͣλ
	usart1struct.USART_StopBits = USART_StopBits_1;
	//�ֳ� ����λ
	usart1struct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&usart1struct);
	
	//���ڵ�·ʹ��
	USART_Cmd(USART1,ENABLE);
	
	//�����жϿ�����
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = USART1_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	//���ȼ�
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
	//�����ж�ʹ�� �������ݷǿ�ִ���ж�
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
}


void USART1_IRQHandler(void)                	//����1�жϷ������
{
	unsigned char  res;
	char buff1[128];
	int i = 0;
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE))
	{ 

		res=USART_ReceiveData(USART1);
			
		switch(res)
		{
			//����������
			case 1:
				printf("�򿪺�����\r\n");
				flg = 1;
			break;
			
			//�رպ�����
			case 2:
				printf("�رպ�����\r\n");
				flg = 0;
			break;
			
			//�ɼ�����
			case 3:
				tp = 1;
			break;
			
			//�رղɼ�
			case 4:
				printf("�رղɼ�\r\n");
				tp = 0;
			break;
			
			//����������
			case 5:
				Timer2_BEEP_PwmConfig();
				beepflag = 1;
				printf("����������\r\n");
			break;
	
			case 6:
					beepflag = 0;
			printf("�رշ���������\r\n");
			break;
			
			
				
		//����AT24OC02
		case 7:
			Temp_Light();
			while(AT24OC02_Init());
			for(i=0;i<strlen(shujv);i++)
			{	
					while(AT24OC02_Wriet_Byte(i+1,shujv[i]));
			}
			W25Q64_Write_Page(shujv,0,strlen(shujv));
			printf("�ɼ��ɹ�\r\n");
		break;
			
			//ȡ��AT24OC02�е�����
		case 8:
			for(i=0;i<strlen(shujv);i++)
				{
					buff1[i] = AT24OC02_Read_Byte(i+1);
				}
				printf("AT24OC02-DATA\r\n");
				for(i=0;i<strlen(shujv);i++)
				{
					printf("%c",buff1[i]);
				}
				printf("\r\n");
				W25Q64_Read_Data(0,buff1,strlen(shujv));
				printf("W25Q64-DATA\r\n");
				for(i=0;i<strlen(shujv);i++)
				{
					printf("%c",buff1[i]);
				}
		break;
		case 9:
				printf("������\n");
				W25Q64_Erase_allChip();
				printf("�����ɹ�\n");
		break;
			
		}
		}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}


