/*********************************************************************************************************
* �ļ����ƣ�ADApp.h
* ժ    Ҫ����ȡAD��ֵ/��ȡ��Ƭ����ADC��ֵ
* ��ǰ�汾��1.0.0
* ��    �ߣ�����
* ������ڣ�
* ��    �ݣ�
* ע    �⣺
* ����������STC8A8K64S4A12@22.1184MHzоƬ & Keil uVision 5                                                                 
**********************************************************************************************************
* ȡ���汾��
* ��    �ߣ�
* ������ڣ�
* �޸����ݣ�
* �޸��ļ���
*********************************************************************************************************/
#ifndef __ADApp_h_
#define __ADApp_h_

#define SPIIFCON 0 //Ӳ��SPI
//#define SPIFCON 1//����SPI

/*
0x94//   AIN0 ��λ��
0xD4//   AIN1 ��������
0xA4//   AIN2 ��������
0xE4//   AIN3 �ⲿ����
*/
void delay_AD();
u16 in_AD(u8 cmd);
u16 SAD_Read(u8 ADCType);

#endif