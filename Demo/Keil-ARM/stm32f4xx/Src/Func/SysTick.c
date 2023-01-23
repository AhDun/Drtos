 /*
                                                  FILE-START
*/
/*
 *@�ļ�����: SysTick.c

 *@�ļ�����: 

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: 
*/

/*
                                                  <�����ļ���>
*/
#include "SysTick.h"
#include "osMain.h"


/*
                                                  ������ʼ����
*/
s8 SysTick_us_Init_Test_Flag = Unknown;

/*
                                                  <������>
*/

/*
 *@��������: SysTick_us_Init

 *@��������: ��us����ʼSysTick��ʱ��

 *@�������: SysCLK����Ƶ����us��΢�룩

 *@�� �� ֵ: 0: �ɹ���-1: ʧ��

 *@ע    ��: ��

 * ��		 ��: 
*/

s8 SysTick_us_Init(u8 SysCLK,u16 us)
{
	if(SysTick->CTRL & 0x01){
		return (Error); 
	}
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	 
	SysTick->LOAD = us * (SysCLK / 8) ; //ʱ�����	  		 
	SysTick->VAL = 0x00;        		//��ռ�����
	SysTick->CTRL |= ( 0x01 | 0x02) ; //��ʼ����
                //��ʼ����  | ������0ʱ�������쳣
	while(SysTick_us_Init_Test_Flag == Unknown);//���SysTick��ʱ����δ����������������
	return (OK);
}

/*
 *@��������: SysTick_Handler

 *@��������: SysTick�쳣��Ӧ����

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��
*/
void SysTick_Handler(void)
{
	SysTick_us_Init_Test_Flag_OK();
	osClockTimePulse();
}

/*
 *@��������: SysTick_us

 *@��������: ΢����ʱ

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��
*/
void SysTick_us(u32 us)
{
	u32 VALs = SysTick->VAL - (us * (osCPU_Freq / 8));
	while(SysTick->VAL > VALs);
}

/*
                                                  FILE-END
*/

