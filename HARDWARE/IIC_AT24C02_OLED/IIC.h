
#ifndef __IIC_H__
#define __IIC_H__

#include "stdint.h"
 
//���������ݺ�ӻ�����ACK
#define NACK 1
#define ACK 0

//д ��λΪ0 �� ��λΪ1
#define WRITE_AT24OC02_ADDR 0xa0
#define READ_AT24OC02_ADDR  0xa1

//IIC��������
void IIC_Config(void);
void IIC_Start(void);
void IIC_End(void);
void IIC_SendByte(unsigned char data);
unsigned char IIC_GetByte(void);
unsigned char IIC_Get_Ack(void);
void IIC_SendAck(unsigned char ack);

//OLED��������
void OLed_ShowChina(uint8_t x,uint8_t y,uint8_t *buf);
void Oled_print(uint8_t x, uint8_t y,char *str);
void InitOLed(void);
void OLed_SetPos(unsigned char x, unsigned char y);
void OLed_Fill(unsigned char bmp_data);
void WriteOLedData(uint8_t data);
void WriteOLedCmd(uint8_t cmd);


//AT24C02��������
int AT24OC02_Init(void);
unsigned char AT24OC02_Wriet_Byte(unsigned char wordaddr,unsigned char data);
unsigned char AT24OC02_Read_Byte(unsigned char wordaddr);

#endif

