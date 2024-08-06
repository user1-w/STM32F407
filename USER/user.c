#include"user.h"

extern uint8_t HZ1[];
extern uint8_t HZ2[];
extern uint8_t HZ3[];
extern uint8_t HZ6[];
extern uint8_t HZ7[];
extern uint8_t dian[];
extern uint8_t ping[];

char temp[2] = ""; //�¶ȴ洢
char hum[2] = "";  //ʪ�ȴ洢

char shidu[128];
char wendu[128];
char guangzhao[30];
char dianya[30];
char shujv[128];
unsigned short int numguang;
float numdian;
unsigned short int chipid;

int flag = 0;

extern int flg;//���ƺ�����
extern int beepflag;
int tep;//������ʪ�Ȳɼ�
int tp = 0;

unsigned char buffer[128];
void Temp_Light()
{
		dht11_ReadData(hum,hum+1,temp,temp+1);
		numguang = Get_AdcChannel(0);
		numdian = Get_ADC_dianwei_Channel(10);
		numdian = (numdian/4096)*3.3;
	
		sprintf(wendu,":%d.%d",temp[0],temp[1]);
		sprintf(shidu,":%d.%d",hum[0],hum[1]);
		sprintf(guangzhao,":%d",numguang);
		sprintf(dianya,":%.3f",numdian);
		sprintf(shujv,"%d.%d-%d.%d-%d-%.3f",temp[0],temp[1],hum[0],hum[1],numguang,numdian);
		delay_ms(100);
		if(temp[0]>=30)
		{
			int i = 3;
			Fan_Control(600);
			if(flag == 0)
			{
				BeepConfig();
				while(i--)
				{
					BeepAlarm();
				}
				flag =1;
			}
		}
		else
		{
			Fan_Control(0);
			flag = 0;
		}
}


void Oled_Temp()
{
	OLed_Fill(0);
	OLed_ShowChina(1,0,HZ1);
	OLed_ShowChina(15,0,HZ2);
	OLed_ShowChina(1,2,HZ3);
	OLed_ShowChina(15,2,HZ2);
	OLed_ShowChina(1,4,HZ6);
	OLed_ShowChina(15,4,HZ7);
	OLed_ShowChina(1,6,dian);
	OLed_ShowChina(15,6,ping);
	Oled_print(34,0,wendu);
	Oled_print(34,2,shidu);
	Oled_print(36,4,guangzhao);
	Oled_print(35,6,dianya);
	delay_ms(1000);
	OLed_Fill(0);
}

void live_collect()
{
	if(tep)
	{
		Temp_Light();
		Oled_Temp();
	}
}

void USART_Cllect()
{
	if(tp)
	{
		Temp_Light();
		printf("�¶ȣ�%s\r\n",wendu);
		printf("ʪ�ȣ�%s\r\n",shidu);
		printf("���գ�%s\r\n",guangzhao);
		printf("��ѹ��%s\r\n",dianya);
		delay_ms(900);
	}
}



int  main(void)
{

	//�ӳٺ�����ʼ��
	delay_init(168);
	//���ڳ�ʼ��
	Usart_Config();	
	//�жϷ��麯��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart2init();
	//LED��ʼ��
	LED_Config();
	//������ʼ��
	Key1_2_3_Config();
	Key_4_Config();
	//�жϳ�ʼ������
	INTERRUPT_KEY1_Config();
	INTERRUPT_KEY2_Config();
	INTERRUPT_KEY3_Config();
	INTERRUPT_KEY4_Config();
	//���ٷ���
	Timer12_Ch2_PwmConfig();
	//������
	pwm_ledconfig();
	//SPI�豸�ӿ�
	W25Q64_Config();
	
	//IICЭ��
	IIC_Config();
	//DHT11��ʼ��
	dht11_Config();
	//OLED��ʼ��
	InitOLed();
	//ADCת�����պ͵�λ��
	ADC_GUANG_Config();
	ADC_DianWei_Config();
	Temp_Light();
	//IIC�ӿ��豸
	while(AT24OC02_Init());
	
	while(1)
	{	
		Led_Breath();
		live_collect();
		Pwm_Alarm();
		USART_Cllect();
	}
}

