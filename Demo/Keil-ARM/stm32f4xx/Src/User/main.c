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
#include "SysTick.h"
#include "osConfig.h"
#include "Demo.h"
#include "print.h"

uint8_t CCRAM[MemTank_Max] __attribute__((at(0x10000000)));
uint32_t RAM[1000];

_MemoryInfo  Memory_CCRAM = {&CCRAM[0],&CCRAM[0],&CCRAM[MemTank_Max]};
_MemoryInfoStatic  Memory_RAM = {&RAM[0],&RAM[999],1,2};





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

int main(void)
{
/*--------------------------------------demo---------------------------------------------------------*/
	u32 _tr0;
	//_SignalHandle* a;
	//_TaskHandle t;
	osInit();
	osMemoryInstallStatic(osMemoryInitStatic(&Memory_RAM));
	print("static memory:%d\n",osMemoryStaticGetPassValue());
//	a = osSignalLogin(Signal_AndGroup);
//	osSignalSetGroup(a,2,2,1);
//	osSignalSetGroup(a,2,1,1);
//	print("\n\n\n\n\n\n");
//	print("�з�����������:%d\n",-123456);
//	print("�޷�����������:%lu\n",-123456);
//	print("����������:%f\n",1234.5678);
//	print("��дʮ�����Ʋ���:%X\n",0x1234ABCD);
//	print("Сдʮ�����Ʋ���:%x\n",0x1234ABCD);
//	print("�˽��Ʋ���:%o\n",0123456);
//	print("�ַ�����:%c\n",'a');
//	print("�ַ�������:%s\n","Hello World");
//	print("��������:%3d\n",99);
//	print("����������:%.2f\n",1234.5678);
//	print("\n\n\n\n\n\n");
	//print("%M","%d\n",10);
	//osLogF("ad","A:%d",100);
	//osMemoryMalloc(25000);
//	_tr0 = -2;
	//print("%d\n\n",MemoryStructLength);
	//print("%f %d %f %d %f %s\n",123.456,123,12.123,456,456.789,"very");



//	t.Name = "RTC";
//	t.Addr = (void*)Task1_Func;
//	t.Length = Task1_Stack_size;
//	t.Wheel = 50;
//	t.Level = -2;
//	t.Arg = (void*)"Hello Task1\n";

//	osTaskLoad(&t,Load_Create);

	TaskHandle_Task1 = osTaskLogin(
	Task1_Func,			            //�����ַ
	Task1_Stack_size,		                    //����ջ����
	-2,	                                    //�������ȼ�
	50,		                            //����ʱ����Ƭ
	"Hello Task1\n",									//���񴫲�   
	"RTC", 			                    //��������
	Task_Set_Default);

	//print("%s\n",osPostReadWait());


	TaskHandle_Task2 = osTaskLogin(    
	Task2_Func,			            //�����ַ
	Task2_Stack_size,		                    //����ջ����
	-1,	                                    //�������ȼ�
	50,		                            //����ʱ����Ƭ
	"Hello",									//���񴫲�
	"TaskList", 			                    //��������
	Task_Set_Default
	); 

	TaskHandle_Task3 = osTaskLogin( 
	Task3_Func,			                //�����ַ
	Task3_Stack_size,		                        //����ջ����
	-3,                                          //�������ȼ�
	50,		                                    //����ʱ����Ƭ
	"Hello",									//���񴫲�
	"LED1", 			                        //��������
	Task_Set_Default                                    
	);

	TaskHandle_Task4 = osTaskLogin( 
	Task4_Func,			                //�����ַ
	Task4_Stack_size,		                        //����ջ����
	-3,                                          //�������ȼ�
	50,		                                    //����ʱ����Ƭ
	"Hello",									//���񴫲�
	"LED2", 			                        //��������
	Task_Set_Default                                    
	);
	OSCoreTaskHandle -> Config = Task_Set_OSCore; 


	//osTaskLogout(TaskHandle_Task3);
	osTaskStart();
//	for(;;){
//		for(_tr0 = 0;_tr0 < 500;_tr0++){
//			osPostReadWait();
//		}
////		for(_tr0 = 10;_tr0 < MemTank_Max;_tr0++){
////			MemoryPool[_tr0] = _tr0;
////			osTaskDelayMs(10);
////		}
//	}
/*---------------------------------------------------------------------------------------------------*/
}




