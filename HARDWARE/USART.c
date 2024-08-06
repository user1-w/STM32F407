#include"user.h"


#define USART_REC_LEN  			200  	//??????????????? 200
#define EN_USART1_RX 			1		//????1??/?????0??????1????
u8  USART_RX_BUF[USART_REC_LEN];
u16 USART_RX_STA;
//重定义fputc函数 
int fputc(int ch, FILE *f) 
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}




extern char temp[2]; //温度存储
extern char hum[2]; 
extern unsigned short int numguang;
extern char wendu[128];
extern char shidu[128];
extern char guangzhao[30];
extern char dianya[30];
extern char shujv[128];
extern void Oled_Temp(void);



extern int flg;//控制呼吸灯
extern int tp;//控制温湿度采集
extern int beepflag;
extern int tep;

void Usart_Config()
{
	//配置时钟 使能USART和A组
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//引脚复用 将PA9和PA10 配置为串口
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	//配置引脚为复用模式
	GPIO_InitTypeDef usart1_gpio1_struct;
	usart1_gpio1_struct.GPIO_Mode = GPIO_Mode_AF;
	usart1_gpio1_struct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	usart1_gpio1_struct.GPIO_PuPd = GPIO_PuPd_UP;
	usart1_gpio1_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&usart1_gpio1_struct);
	
	//配置串口
	USART_InitTypeDef usart1struct;
	//波特率
	usart1struct.USART_BaudRate = 115200;
	//硬件流 
	usart1struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//输入输出模式
	usart1struct.USART_Mode = USART_Mode_Rx| USART_Mode_Tx;
	//校验位 和 上位机一样
	usart1struct.USART_Parity = USART_Parity_No;
	//停止位
	usart1struct.USART_StopBits = USART_StopBits_1;
	//字长 数据位
	usart1struct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&usart1struct);
	
	//串口电路使能
	USART_Cmd(USART1,ENABLE);
	
	//配置中断控制器
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = USART1_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	//优先级
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
	//串口中断使能 接受数据非空执行中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
}


void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	unsigned char  res;
	char buff1[128];
	int i = 0;
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE))
	{ 

		res=USART_ReceiveData(USART1);
			
		switch(res)
		{
			//开启呼吸灯
			case 1:
				printf("打开呼吸灯\r\n");
				flg = 1;
			break;
			
			//关闭呼吸灯
			case 2:
				printf("关闭呼吸灯\r\n");
				flg = 0;
			break;
			
			//采集数据
			case 3:
				tp = 1;
			break;
			
			//关闭采集
			case 4:
				printf("关闭采集\r\n");
				tp = 0;
			break;
			
			//蜂鸣器警报
			case 5:
				Timer2_BEEP_PwmConfig();
				beepflag = 1;
				printf("蜂鸣器警报\r\n");
			break;
	
			case 6:
					beepflag = 0;
			printf("关闭蜂鸣器警报\r\n");
			break;
			
			
				
		//存入AT24OC02
		case 7:
			Temp_Light();
			while(AT24OC02_Init());
			for(i=0;i<strlen(shujv);i++)
			{	
					while(AT24OC02_Wriet_Byte(i+1,shujv[i]));
			}
			W25Q64_Write_Page(shujv,0,strlen(shujv));
			printf("采集成功\r\n");
		break;
			
			//取出AT24OC02中的数据
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
				printf("擦除中\n");
				W25Q64_Erase_allChip();
				printf("擦除成功\n");
		break;
			
		}
		}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}


