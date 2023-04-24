/*
 * Copyright (c) 2022-2023 AhDun
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

/* *
 * @�ļ�����: main.c
 *
 * @�ļ�����: 
 *
 * @ע    ��: 
*/



#include "main.h"
//#include "SysTick.h"
#include "osConfig.h"
#include "STC32G_UART.h"
#include "STC32G_GPIO.h"
#include "STC32G_ADC.h"
#include "STC32G_Exti.h"
#include "STC32G_I2C.h"
#include "STC32G_SPI.h"
#include "STC32G_Timer.h"
#include "STC32G_UART.h"
#include "STC32G_Compare.h"
#include "STC32G_Delay.h"
#include "STC32G_Switch.h"
#include "STC32G_WDT.h"
#include "STC32G_NVIC.h"


uint8_t CCRAM[MemTank_Max];

_MemoryInfo  Memory_CCRAM = {&CCRAM[0],&CCRAM[0],&CCRAM[MemTank_Max]};

void func()
{
	P1 = 0x00;
}


void MCUInit()
{
	WTST = 0;     //���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
    EAXFR = 1;    //��չ�Ĵ���(XFR)����ʹ��
    CKCON = 0;    //��߷���XRAM�ٶ�


	P0_MODE_IO_PU(GPIO_Pin_All);		//P0 ����Ϊ׼˫���
	P1_MODE_IO_PU(GPIO_Pin_All);		//P1 ����Ϊ׼˫���
//	P1_MODE_IN_HIZ(GPIO_Pin_LOW);		//P1.0~P1.3 ����Ϊ��������
//	P1_MODE_OUT_OD(GPIO_Pin_4 | GPIO_Pin_5); //P1.4,P1.5 ����Ϊ©����·
	P2_MODE_IO_PU(GPIO_Pin_All);		//P2 ����Ϊ׼˫���
	P3_MODE_IO_PU(GPIO_Pin_All);		//P3 ����Ϊ׼˫���
	P4_MODE_IO_PU(GPIO_Pin_All);		//P4 ����Ϊ׼˫���
	P5_MODE_IO_PU(GPIO_Pin_All);		//P5 ����Ϊ׼˫���
	P6_MODE_IO_PU(GPIO_Pin_All);		//P6 ����Ϊ׼˫���
	P7_MODE_IO_PU(GPIO_Pin_All);		//P7 ����Ϊ׼˫���
	
	P1_PULL_UP_ENABLE(GPIO_Pin_4 | GPIO_Pin_5);	//P1.4,P1.5 �����ڲ�����
}


/* *
 * @��������: ��
 *
 * @��������: ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */

void main(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	TIM_InitTypeDef		TIM_InitStructure;
	_TaskHandle* TaskHandleListBuf = osTaskGetTaskHandleListHead();
	//osLinkJump(func);
	MCUInit();
	osIRQ_Init();
	//ES = 1;

//	TIM_InitStructure.TIM_Mode = TIM_16BitAutoReload;
//	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T; 
//	TIM_InitStructure.TIM_ClkOut = DISABLE;
//	TIM_InitStructure.TIM_Value = 0;
//	TIM_InitStructure.TIM_Run = ENABLE;
//	Timer_Inilize(Timer0,&TIM_InitStructure);
//	ET0 = 1;
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2, ���Բ���ѡ��)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		    //��ʼ������2 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_3);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	//osInit();
	osMemoryInstall(osMemoryInit(&Memory_CCRAM));
	osIRQ_Init();
		osTaskLogin(MainName_Config,func,MainStackSize_Config,MainTimeWheel_Config,MainPriorityLevel_Config,MainPass_Config,MainSet_Config); 
	
	ISR_Touch();



//	print("�з���������:%d\n",-123456);
//	print("�޷���������:%lu\n",-123456);
//	print("�������:%f\n",1234.5678);
//	print("��дʮ�����Ʋ���:%X\n",0x1234ABCD);
//	print("Сдʮ�����Ʋ���:%x\n",0x1234ABCD);
//	print("�˽��Ʋ���:%o\n",0123456);
//	print("�ַ�����:%c\n",'a');
//	print("�ַ�������:%s\n","Hello World");
//	print("%3d\n",1);
//	print("�������:%.1f\n",1234.5678); 
	//print("%d\n",osMemoryGetFreeValue());

	do{
		print("����<%s>\n",TaskHandleListBuf -> Name);
		TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
	}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());
	while(1);
//osInit();

}




