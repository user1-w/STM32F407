#ifndef __USER_H__

#define __USER_H__

#include<stm32f4xx.h>
#include "delay.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "IIC.h"

#define LED1  1
#define LED2  2
#define LED3  3


//�ӳٺ���
void delay(unsigned int nCount);


//LED����ģ��
void LED_Config(void);
void LED_TurnOn(unsigned int LEDNUM);
void LED_TurnOff(unsigned int LEDNUM);
void LED_Shine(void);
void LED_Flow(void);
//Beep����ģ��
void BeepConfig(void);
void BeepOn(void);
void BeepOff(void);
void BeepAlarm(void);
//key����ģ��
void Key1_2_3_Config(void);
void Key_4_Config(void);
void  Key_Scan(void);

//�ж�����ģ��
void INTERRUPT_KEY1_Config(void);
void INTERRUPT_KEY2_Config(void);
void INTERRUPT_KEY3_Config(void);
void INTERRUPT_KEY4_Config(void);


//��ʱ������
void systick_delay(unsigned int n);
void systick_config(void);


//������������
void Usart_Config(void);


//��ʱ������
void Timer4_Config(unsigned short int psc,unsigned short int period);

//����PWM����
void Timer12_Ch2_PwmConfig(void);
void pwm_ledconfig(void);
void Fan_Off(void);
void Fan_On(void);
void Fan_Control(unsigned int value);


//������
void Led_Control(unsigned int value);
void Led_Breath(void);


//������PWM
void Timer2_BEEP_PwmConfig(void);
void Beep_Control(unsigned int value);
void Pwm_Alarm(void);

//DHT11����
void dht11_Config(void);
void dht11_Inmod(void);
void dht11_Outmod(void);
unsigned char dht11_ReadBytes(void);
unsigned  char dht11_ReadData(char *humiz,char *humix,char *tempz,char *tempx);
//extern ֻ������ ���ÿռ�
extern unsigned int tnum;

//SPI��W25Q64����
void SPI_Config(void);
unsigned char SPI1_Wriet_Read(unsigned char data);
void W25Q64_Config(void);
unsigned short int W25Q64_ReadID(void);
void W25Q64_Write_Enable(void);
unsigned char W25Q64_Check_busy(void);
void W25Q64_Erase_allChip(void);
void W25Q64_Write_Page(unsigned char *pbuff,unsigned int writeaddr,unsigned short int numbytes);
unsigned char W25Q64_Read_Data(unsigned int wordaddr,unsigned char buff[],unsigned char len);


//ADCģ������
void ADC_GUANG_Config(void);
unsigned short int Get_AdcChannel(unsigned int channel);
unsigned short int get_ADCaverage(unsigned int channel,char times);

//esp8266
void uart2init(void);


//��λ
void ADC_DianWei_Config(void);
unsigned short int Get_ADC_dianwei_Channel(unsigned int channel);
unsigned short int get_DianWei_ADCaverage(unsigned int channel,char times);


//���ݲɼ�
void Temp_Light(void);
void Oled_Temp(void);
#endif
