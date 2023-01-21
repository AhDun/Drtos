/*
 *@�ļ�����: SysTick.h

 *@�ļ�����: 

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: 
*/
/*
                                                  ���ظ������������
*/
#ifndef _SysTick_H
#define _SysTick_H
/*
                                                  <�����ļ���>
*/
#include "main.h"
/*
                                                  <�궨����>
*/
/*----------------------------------����---------------------------------------*/
#define SysTick_us_Init_Test_Flag_OK() SysTick_us_Init_Test_Flag = OK;

/*
                                                  <����������>
*/
extern s8 SysTick_us_Init_Test_Flag;

/*
                                                  <����������>
*/
s8 SysTick_us_Init(u8 SysCLK,u16 ms);
void SysTick_us(u32 us);
#endif
/*
                                                  FILE-END
*/

