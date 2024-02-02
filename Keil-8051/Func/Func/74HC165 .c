/*********************************************************************************************************
* �ļ����ƣ�74HC165.c
* ժ    Ҫ��
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
#include"74HC165.h"

/********************************
��������:delay_74HC165
��������:74HC165ר����ʱ
�������:
��    ��:
�������:
��    ��:
********************************/
void delay_74HC165()
{
   _nop_(); 
   _nop_();
   _nop_();
   _nop_();	
}
/********************************
��������:Read74HC165
��������:��74HC165
�������:
��    ��:
�������:74HC165������
��    ��:
********************************/
u8 Read74HC165()
{  
   u8 i ,dat = 0;
   LD_74HC165 = 0;
   delay_74HC165();//������ʱ ����һ�����ȵ�����
   LD_74HC165 = 1;//���ⲿ�ź�ȫ��������������
   delay_74HC165();
   for(i=0; i<8; i++)
    { 
	  dat = dat << 1;//����һλ
	  CLK_74HC165  = 0;//ʱ����0	 
      _nop_();
	  dat |= QH_74HC165;
      CLK_74HC165  = 1;//ʱ����1	  
	} 
   
   return dat;	 
}