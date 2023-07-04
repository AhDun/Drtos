/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
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


void delay(unsigned long t)
{
	unsigned long i;
	while(t--){
		_nop_();
		i = 5528UL;
		while (i) i--;
	}

}

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
uint32_t s = 0x123;

void main(void)
{
	char i = 0;
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	TIM_InitTypeDef		TIM_InitStructure;
	_TaskHandle* TaskHandleListBuf = osTaskGetTaskHandleListHead();
	_TaskHandle* a;

	MCUInit();

	P0 = 0x00;
	P1 = 0x00;
	P2 = 0x00;
	P3 = 0x00;
	P4 = 0x00;
	P5 = 0x00;
	P6 = 0x00;
	P7 = 0x00;
//	while(1){
//		delay(100);
//		P34 = P33 = 0;
//		delay(100);
//		P34 = P33 = 1;
//	}
	P3 = 0x00;

//	WKTCL	= 4095 & 0xFF;
//	WKTCH	= (4095 >> 8) & 0xFF | 0x80;
	while(1){

		if(i < 1){
			WKTCL	= 4095 & 0xFF;
			WKTCH	= (4095 >> 8) & 0xFF | 0x80;
			PCON	|= 0x02;
			P3 = 0xFF;
		}else{
			WKTCL	= 99 & 0xFF;
			WKTCH	= (99 >> 8) & 0xFF | 0x80;
			PCON	|= 0x02;
			P3 = 0x00 ;
		}
		i++;
		if(i > 2){
			i = 0;
		}
	}
		OsTaskRunTaskHandle = &s;
	osLinkTaskStackInit((uint32_t*)0,(uint32_t*)func,(uint32_t*)34,&s);
	//osLinkJump(func);
	
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


	a = osTaskLogin(MainName_Config,func,MainStackSize_Config,MainTimeWheel_Config,MainPriorityLevel_Config,MainPass_Config,MainSet_Config); 
	osTaskGetNextTaskHandle() = a; 
	osTaskGetRunTaskHandle() = a;//���������е�������Ϣ���ָ�봫�͸�������������� 
	//osTaskGetNextTaskHandle() -> Config = Task_State_RE;//����������״̬��Ϊ��Ƭ����(����̬)
	OsTimeGetTaskTimeWheel() = osTaskGetRunTaskHandle() -> TaskWheel;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
	//print("����<%s>\n",TaskHandleListBuf -> Name);
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
	TaskHandleListBuf = osTaskGetTaskHandleListHead();
	do{
		print("����<%s>\n",TaskHandleListBuf -> Name);
		TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
	}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());
	while(1);
//osInit();

}





