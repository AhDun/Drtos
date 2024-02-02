/*********************************************************************************************************
* �ļ����ƣ�DS1302App.c
* ժ    Ҫ��DS1302��ʼ��/��ȡDS130
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

#include"Basic.h"
#include"DS1302App.h"
#include"DS1302.h"

/********************************
��������:Ds1302_Init
��������:DS1302��ʼ��
�������:
��    ��:
�������:
��    ��:
********************************/
void Ds1302_Init()
{
	u8 n;
	Ds1302Write(0x8E,0x00);//��ֹд���������ǹر�д��������
	for (n = 0; n < 7; n++)//д��7���ֽڵ�ʱ���źţ�����ʱ��������
		Ds1302Write(WriteRtcAddr[n],RtcTime[n]);	
	Ds1302Write(0x8E,0x80);//��д��������
}
/********************************
��������:Ds1302_Read
��������:��ȡDS1302
�������:
��    ��:
�������:
��    ��:
********************************/
void in_Ds1302()
{
	u8 n;
	for (n = 0; n < 7; n++)//��ȡ7���ֽڵ�ʱ���źţ�����ʱ��������
		RtcTime[n] = Ds1302Read(ReadRtcAddr[n]);
}