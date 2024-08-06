#include"user.h"

//��չ�ַ�����ķ���
//����



extern uint8_t HZ1[];
extern uint8_t HZ2[];
extern uint8_t HZ3[];
extern uint8_t HZ6[];
extern uint8_t HZ7[];
extern uint8_t dian[];
extern uint8_t ping[];



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
extern int tep;//���Ʋɼ�
extern int beepflag;//���Ʒ�����

//���ò��֣�
//PD5 6 ʱ��
void uart2init()
{
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
//1 ����ʱ������
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
//2 D��ʱ������
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    
//3���Ź�������
GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
    
//4.GPIO��ʼ��
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//������Ͳ�Ҫ����
GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOD, &GPIO_InitStructure);

//5.//���ڳ�ʼ��
USART_InitStructure.USART_BaudRate=115200;
USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
USART_InitStructure.USART_Parity=USART_Parity_No;
USART_InitStructure.USART_StopBits=USART_StopBits_1;
USART_InitStructure.USART_WordLength=USART_WordLength_8b;
USART_Init(USART2,&USART_InitStructure);

//6����1ʹ��
USART_Cmd(USART2,ENABLE);
//7�����ж�ʹ��
USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
//8�ж�����
NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
NVIC_Init(&NVIC_InitStructure);        
}



//�жϷ�����
void USART2_IRQHandler(void)
{
	unsigned char  res;
	char buff1[128];
	int i = 0;
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{ 

	res=USART_ReceiveData(USART2);
		
	switch(res)
	{
		
	//�����Ƶ���
	case 1:
		OLed_Fill(0);
		Oled_print(5,2,"OPEN BREATH_LED");
		flg = 1;
	break;
	
	//�ر�������
	case 2:OLed_Fill(0);
		Oled_print(16,2,"CLOSE LEDS");
		GPIO_SetBits(GPIOE,GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8);
		flg = 0;
	break;
	
		
	//�ɼ�������Oled��ʾ
	case 3:
		tep =1;
	break;
	
	//ֹͣ�ɼ�
	case 4:
		tep =0;
		Oled_print(0,2,"CLOSE Collection");
	break;
	
	//����������
	case 5:
		Timer2_BEEP_PwmConfig();
		OLed_Fill(0);
		Oled_print(0,2,"OPEN BEEP_ALARM");
		beepflag = 1;
	break;
	
	case 6:
		OLed_Fill(0);
		Oled_print(0,2,"CLOSE BEEP_ALARM");
		beepflag = 0;
	break;
	
	//����AT24OC02
	case 7:
		Temp_Light();
		OLed_Fill(0);
		Oled_print(6,2,"Data Collection");		
		while(AT24OC02_Init());
		for(i=0;i<strlen(shujv);i++)
		{	
				while(AT24OC02_Wriet_Byte(i+1,shujv[i]));
		}
		W25Q64_Write_Page(shujv,0,strlen(shujv));
		Oled_print(6,2,"Collection OK");
	break;
		
		//ȡ��AT24OC02�е�����
	case 8:
		for(i=0;i<strlen(shujv);i++)
				{
					buff1[i] = AT24OC02_Read_Byte(i+1);
				}
			OLed_Fill(0);
			OLed_ShowChina(1,0,HZ1);
			OLed_ShowChina(15,0,HZ2);
			OLed_ShowChina(1,2,HZ3);
			OLed_ShowChina(15,2,HZ2);
			OLed_ShowChina(1,4,HZ6);
			OLed_ShowChina(15,4,HZ7);
			OLed_ShowChina(1,6,dian);
			OLed_ShowChina(15,6,ping);
			Oled_print(34,0,strtok(buff1,"-"));
			Oled_print(34,2,strtok(NULL,"-"));
			Oled_print(34,4,strtok(NULL,"-"));
			Oled_print(34,6,strtok(NULL,"-"));
			W25Q64_Read_Data(0,buff1,strlen(shujv));
			Oled_print(74,0,strtok(buff1,"-"));
			Oled_print(74,2,strtok(NULL,"-"));
			Oled_print(74,4,strtok(NULL,"-"));
			Oled_print(74,6,strtok(NULL,"-"));
	break;
		case 9:
			OLed_Fill(0);
				Oled_print(6,2,"ERASEING");
				W25Q64_Erase_allChip();
				Oled_print(6,2,"ERASE OK");
		break;
			
			
	//�������
	//default: OLed_Fill(0);Oled_print(8,2,"INPUT ERROR!"); break;
}
}
USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}

