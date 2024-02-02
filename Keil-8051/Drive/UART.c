/*------------------------------------------------------------------------------------------------------------------------
 * �ļ����ƣ�UART.c

 * �ļ����ݣ���������

 * �ļ��汾��1.0.0

 * �ļ����ߣ�����

 * ����������STC8A8K64S4A12@22.1184MHzоƬ & Keil uVision 5 

 * ע    �⣺
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����ͷ�ļ���
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//������
#include "UART.h"
#include "System_Uart.h"
#include "Power.h"
#include "System_Task.h"
/*------------------------------------------------------------------------------------------------------------------------
                                                  ������ʼ����
------------------------------------------------------------------------------------------------------------------------*/
u8 xdata TIBusy = 0;
#ifdef UART1_Enable
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�UART1Init

 * �������ܣ�����1��ʼ��

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void UART1Init()
{
	SCON = 0x50;//8λ����,�ɱ䲨����
	AUXR &= 0xBF;//��ʱ��1ʱ��ΪFosc/12,��12T
	AUXR &= 0xFE;//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0xFC;//�趨��ʱ��ֵ
	TH1 = 0xFF;//�趨��ʱ��ֵ
	ET1 = 0;//��ֹ��ʱ��1�ж�
	TR1 = 1;//������ʱ��1
	ES = 1;
	EA = 1;
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�UART1Interrupt

 * �������ܣ�����1�жϷ���

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void UART1Interrupt() interrupt 4
{
	if(RI)//�жϽ����Ƿ����
	{
		Systme_UART_Input();
		RI = 0;
	}
	else if(TI)//�жϷ����Ƿ����
	{
		TIBusy = 1;
		TI = 0;
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�OUT_UART1

 * �������ܣ�����1���

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void OUT_UART1(u8 sdata)
{
 	 TIBusy = TI = 0;
	 SBUF = sdata;//���������뷢�ͼĴ����У��Զ�����
	 while(1)
	 {
	  if(ES)
			if(TIBusy)
				break;
		if(!ES)
			if(TI)
				break;
	 }
	 TIBusy = TI = 0;
}
#endif
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�UART2Init

 * �������ܣ�����2��ʼ��

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
#ifdef UART2_Enable
void UART2Init()
{
	/*S2CON - ���� 2 ���ƼĴ���*/
	//bit7
	S2CON &= 0x7F;//�ɱ䲨����8λ���ݷ�ʽ
//	S2CON |= 0x80;//�ɱ䲨����9λ���ݷ�ʽ
	//bit5
	S2CON &= 0xDF;//�������� 3 ��ģʽ 1 ʱ�������ͨ�ſ���λ
//	S2CON |= 0x20;//�������� 3 ��ģʽ 1 ʱ�������ͨ�ſ���λ
	//bit4
//	S2CON &= 0xEF;//��ֹ���ڽ������� 
	S2CON |= 0x10;//�������ڽ�������
	//bit3
//	S2CON &= 0xF7;//������ 2 ʹ��ģʽ 1 ʱ��S2TB8 ΪҪ���͵ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ������Ҫ��������λ���� 0����ģʽ 0 �У���λ����
//	S2CON |= 0x08;//������ 2 ʹ��ģʽ 1 ʱ��S2TB8 ΪҪ���͵ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ������Ҫ��������λ���� 0����ģʽ 0 �У���λ����
	//bit2
//	S2CON &= 0xFB;//������ 2 ʹ��ģʽ 1 ʱ��S2RB8 Ϊ���յ��ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ����ģʽ 0 �У���λ����
//	S2CON |= 0x04;//������ 2 ʹ��ģʽ 1 ʱ��S2RB8 Ϊ���յ��ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ����ģʽ 0 �У���λ����
	//bit1
	S2CON &= 0xFD;//���� 2 �����ж������־λ
//	S2CON |= 0x02;//���� 2 �����ж������־λ 
	//bit0
	S2CON &= 0xFE;//���� 2 �����ж������־λ
//	S2CON |= 0x01;//���� 2 �����ж������־λ
	/*��ʱ��2���������ʷ�����*/
	T2L = 0x00;
	T2H = 0x00;
	/*IE2 - �ж�ʹ�ܼĴ��� 2*/
	//bit0
//	IE2 &= 0xFE;//��ֹ���п� 2 �ж�
	IE2 |= 0x01;//�������п� 2 �ж�
	/*IE - �ж�ʹ�ܼĴ��� */
	//bit7
//	IE2 &= 0x7F;//CPU �������е��ж�����
	IE2 |= 0x80;//CPU �����ж� 
	/*AUXR - �����Ĵ��� 1 */ 
	//bit2
	AUXR &= 0xFB;//��ʱ��2��12T�ٶ�����
	AUXR |= 0x04;//��ʱ��2��6T�ٶ�����
	//bit4
//	AUXR &= 0xEF;//�رն�ʱ��2
	AUXR |= 0x10;//������ʱ��2
}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�UART2Interrupt

 * �������ܣ�����2�жϷ���

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void UART2Interrupt() interrupt 8
{
	if(S2CON & 0x01)//�жϽ����Ƿ����
	{
		S2CON &= 0xFE;
	}
	else if(S2CON & 0x02)//�жϷ����Ƿ����
	{
		S2CON &= 0xFD;
	}
}
#endif
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�UART3Init

 * �������ܣ�����3��ʼ��

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
#ifdef UART3_Enable
void UART3Init()
{
	/*S3CON - ���� 2 ���ƼĴ���*/
	//bit7
	S3CON &= 0x7F;//�ɱ䲨����8λ���ݷ�ʽ
//	S3CON |= 0x80;//�ɱ䲨����9λ���ݷ�ʽ
	//bit6
	S3CON &= 0xBF;//ѡ��ʱ�� 2 Ϊ���� 3 �Ĳ����ʷ�����
//	S3CON |= 0x40;//ѡ��ʱ�� 3 Ϊ���� 3 �Ĳ����ʷ�����
	//bit5
	S3CON &= 0xDF;//�������� 3 ��ģʽ 1 ʱ�������ͨ�ſ���λ
//	S3CON |= 0x20;//�������� 3 ��ģʽ 1 ʱ�������ͨ�ſ���λ
	//bit4
//	S3CON &= 0xEF;//��ֹ���ڽ������� 
	S3CON |= 0x10;//�������ڽ�������
	//bit3
//	S3CON &= 0xF7;//������ 3 ʹ��ģʽ 1 ʱ��S2TB8 ΪҪ���͵ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ������Ҫ��������λ���� 0����ģʽ 0 �У���λ����
//	S3CON |= 0x08;//������ 3 ʹ��ģʽ 1 ʱ��S2TB8 ΪҪ���͵ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ������Ҫ��������λ���� 0����ģʽ 0 �У���λ����
	//bit2
//	S3CON &= 0xFB;//������ 3 ʹ��ģʽ 1 ʱ��S2RB8 Ϊ���յ��ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ����ģʽ 0 �У���λ����
//	S3CON |= 0x04;//������ 3 ʹ��ģʽ 1 ʱ��S2RB8 Ϊ���յ��ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ����ģʽ 0 �У���λ����
	//bit1
	S3CON &= 0xFD;//���� 3 �����ж������־λ
//	S3CON |= 0x02;//���� 3 �����ж������־λ 
	//bit0
	S3CON &= 0xFE;//���� 3 �����ж������־λ
//	S3CON |= 0x01;//���� 3 �����ж������־λ
	/*IE2 - �ж�ʹ�ܼĴ��� 2*/
	//bit3
//	IE2 &= 0xF7;//��ֹ���п� 3 �ж�

	IE2 |= 0x08;//�������п� 3 �ж�
	/*IE - �ж�ʹ�ܼĴ��� */
	//bit7
//	IE2 &= 0x7F;//CPU �������е��ж�����
	IE2 |= 0x80;//CPU �����ж� 
	
	/*��ʱ��2���������ʷ�����*/
	T2L = 0x00;
	T2H = 0x00;
	/*AUXR - �����Ĵ��� 1*/ 
	//bit2
	AUXR &= 0xFB;//��ʱ��2��12T�ٶ�����
	AUXR |= 0x04;//��ʱ��2��6T�ٶ�����
	//bit4
//	AUXR &= 0xEF;//�رն�ʱ��2
	AUXR |= 0x10;//������ʱ��2

/*��ʱ��3���������ʷ�����
	//T4T3M - ��ʱ�� 4/3 ���ƼĴ���
	//bit3
	T4T3M &= 0xF7;//��ʱ�� 3 ֹͣ����
	T4T3M |= 0x08;//��ʱ�� 3 ��ʼ����
*/


}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�UART3Interrupt

 * �������ܣ�����3�жϷ���

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
void UART3Interrupt() interrupt 17
{
	if(S3CON & 0x01)//�жϽ����Ƿ����
	{
		S3CON &= 0xFE;
	}
	else if(S3CON & 0x02)//�жϷ����Ƿ����
	{
		S3CON &= 0xFD;
	}
}
#endif
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�UART4Init

 * �������ܣ�����4��ʼ��

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
#ifdef UART4_Enable
void UART4Init()
{
	/*S4CON - ���� 2 ���ƼĴ���*/
	//bit7
	S4CON &= 0x7F;//�ɱ䲨����8λ���ݷ�ʽ
//	S4CON |= 0x80;//�ɱ䲨����9λ���ݷ�ʽ
	//bit6
	S4CON &= 0xBF;//ѡ��ʱ�� 2 Ϊ���� 3 �Ĳ����ʷ�����
//	S4CON |= 0x40;//ѡ��ʱ�� 4 Ϊ���� 3 �Ĳ����ʷ�����
	//bit5
	S4CON &= 0xDF;//�������� 3 ��ģʽ 1 ʱ�������ͨ�ſ���λ
//	S4CON |= 0x20;//�������� 3 ��ģʽ 1 ʱ�������ͨ�ſ���λ
	//bit4
//	S4CON &= 0xEF;//��ֹ���ڽ������� 
	S4CON |= 0x10;//�������ڽ�������
	//bit3
//	S4CON &= 0xF7;//������ 3 ʹ��ģʽ 1 ʱ��S2TB8 ΪҪ���͵ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ������Ҫ��������λ���� 0����ģʽ 0 �У���λ����
//	S4CON |= 0x08;//������ 3 ʹ��ģʽ 1 ʱ��S2TB8 ΪҪ���͵ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ������Ҫ��������λ���� 0����ģʽ 0 �У���λ����
	//bit2
//	S4CON &= 0xFB;//������ 3 ʹ��ģʽ 1 ʱ��S2RB8 Ϊ���յ��ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ����ģʽ 0 �У���λ����
//	S4CON |= 0x04;//������ 3 ʹ��ģʽ 1 ʱ��S2RB8 Ϊ���յ��ĵ� 9 λ���ݣ�һ������У��λ���ߵ�ַ֡/����֡��־λ����ģʽ 0 �У���λ����
	//bit1
	S4CON &= 0xFD;//���� 3 �����ж������־λ
//	S4CON |= 0x02;//���� 3 �����ж������־λ 
	//bit0
	S4CON &= 0xFE;//���� 3 �����ж������־λ
//	S4CON |= 0x01;//���� 3 �����ж������־λ
	/*IE2 - �ж�ʹ�ܼĴ��� 2*/
	//bit4
//	IE2 &= &= 0xEF;//��ֹ���п� 4 �ж�

	IE2 |= 0x10;//�������п� 4 �ж�
	/*IE - �ж�ʹ�ܼĴ��� */
	//bit7
//	IE2 &= 0x7F;//CPU �������е��ж�����
	IE2 |= 0x80;//CPU �����ж� 
	
	/*��ʱ��2���������ʷ�����*/
	T2L = 0x00;
	T2H = 0x00;
	/*AUXR - �����Ĵ��� 1*/ 
	//bit2
	AUXR &= 0xFB;//��ʱ��2��12T�ٶ�����
	AUXR |= 0x04;//��ʱ��2��6T�ٶ�����
	//bit4
//	AUXR &= 0xEF;//�رն�ʱ��2
	AUXR |= 0x10;//������ʱ��2

/*��ʱ��4���������ʷ�����
	//T4T3M - ��ʱ�� 4/3 ���ƼĴ���
	//bit3
	T4T3M &= 0x7F;//��ʱ�� 4 ֹͣ����
	T4T3M |= 0x80;//��ʱ�� 4 ��ʼ����
	//bit7
*/


}
/*------------------------------------------------------------------------------------------------------------------------
 * �������ƣ�UART4Interrupt

 * �������ܣ�����4�жϷ���

 * �����������

 * �����������

 * ע    �⣺��
------------------------------------------------------------------------------------------------------------------------*/
/********************************
��������:UART4Interrupt
��������:����4�жϷ���
�������:
��    ��:
�������:
��    ��:
********************************/
void UART4Interrupt() interrupt 18
{
	if(S4CON & 0x01)//�жϽ����Ƿ����
	{
		S4CON &= 0xFE;
	}
	else if(S4CON & 0x02)//�жϷ����Ƿ����
	{
		S4CON &= 0xFD;
	}
}
#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/