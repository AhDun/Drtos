/*
                                                  FILE-START
*/

/*
 *@�ļ�����: main.c

 *@�ļ�����: 

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0 

 *@ע    ��: 
*/

/*
                             __ _            
                            / _| |           
                  ___  ___ | |_| |_ ___  ___ 
                 / __|/ _ \|  _| __/ _ \/ __|
                 \__ \ (_) | | | || (_) \__ \
                 |___/\___/|_|  \__\___/|___/
                            
						softos v1.0.0

*/
#include "main.h"
#include "SysTick.h"
#include "osMain.h"
#include "Demo.h"
#include "print.h"

/*
                                                  <������>
*/


/*
 *@��������: ��

 *@��������: ��

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/

int main(int argc, char *argv[])
{
/*--------------------------------------demo---------------------------------------------------------*/
	u32 _tr0;
	SemaphoreTable* timebz1;

//	char  a[100] = {"Hello World"};

//	u8* b;
//	u8*	c;
//	u8* d;

//	osIRQ_Init();
//	osUART_Init();
//	osMemoryInit();

////	print("%d\n",&MemoryPool[0]);

//	b = osMemoryMalloc(1);
//	print("%d\n",b);
//	//osMemoryFree(b);
//	c = osMemoryMalloc(2);
//	print("%d\n",c);
//	osMemoryFree(c);
//	d = osMemoryMalloc(2);
//	print("%d\n",d);
//	osMemoryFree(d);

//	print("%d\n",osMemoryGetPassValue());

//	d = osMemoryMalloc(2);
//	print("%d\n",d);
//	osMemoryFree(d);
//	//print("%d\n",MemoryNextAddr);


//	while(1);

//	PostForm F1;
//	PostForm F2;
//	PostForm F3;
//	PostForm F4;

//	//uLinkListAdd(&F1.DownAddr,&F2);
//	uLinkListAdd(&F1.DownAddr,&F3);
//	uLinkListAdd(&F1.DownAddr,&F4);
//	uLinkListHeadRemvoe(&F1.DownAddr);

//	uLinkListRemvoe(&F1.DownAddr,&F2);
//	uLinkListRemvoe(&F1.DownAddr,&F3);
//	uLinkListRemvoe(&F1.DownAddr,&F4);





	if(osInit() ==Error){//ϵͳ��ʼ��
		print("ϵͳ��ʼ��ʧ��");
	}

//	osMemoryMalloc(1);
	//osMemoryMalloc(25000+2310-150);

//	timebz1 = osSignalLogin(Signal_Binary);
//	osSignalApply_Wait(timebz1);
//	osSignalApply_Wait(timebz1);
//	osSignalApply_Wait(timebz1);
//	osSignalApply_Wait(timebz1);
//	osSignalFree(timebz1);
//	osSignalFree(timebz1);
//	osSignalFree(timebz1);
//	osSignalFree(timebz1);
//	osSignalFree(timebz1);

//		
//	osSignalApply_Wait(timebz1);
//	osSignalApply_Wait(timebz1);
//	RunTask_TIT -> TPL = -2;
//	osSignalApply_Wait(timebz1);
//	osSignalApply_Wait(timebz1);

	//osMainPrintFunc();



	//FPU->FPCCR = (0x00000001);

	//osTaskSwitch_Enable();
	//osTaskSet(0,Task_Set_Reboot);


////	b =  osMemoryMalloc(10);
////	printf("2:%d\n",b);
////	for(t = 1; t < 10;t++){
////		*(b + t) = t;
////	}
//	//printf("3:%d\n",osMemoryMalloc(995));
//	a = osMemoryMalloc(sizeof(TaskInfoTable));
//	printf("1:%d\n",a);
//	for(t = 1; t < 10;t++){
//		*(a + t) = t;
//	}
//	printf("4:%d\n",osMemoryExtend(a,20));
//	//osMemoryFree(b);
//	*(a - 2) = Memory_Occupy;
//	osMemoryFree(a + 1);
//	printf("5:%d\n",osMemoryMalloc(18));
//	while(1);
//	//Gap[1] = (u32*)&a;
//	//osIntmac_Input("uart<str:hello world\n<num:12;");
////	osIntmac("uart<str:hello world\n;\
////	uart<num@1<str:hello world\n");
	//print("%d,%f,%f,%f,%X,%f\n",223,56.78,89.7,89.6,0x023,33.445);
//	sprint(&a[0],"%f,%s,%f,%X",12.3,"Hello",89.98,0x123);
//	print("%s",&a[0]);
//	while(1);

//	for(_tr0 = 0; _tr0 < 2000; _tr0++){
//		print("send:%d",_tr0);
//		osPostSend((u32*)_tr0,0);
//	}
//	for(_tr0 = 0; _tr0 < 2000; _tr0++){
//		print("%d\n",osPostRead());
//	}
//	for(_tr0 = 0; _tr0 < 2000; _tr0++){
//		print("send:%d",_tr0);
//		osPostSend((u32*)_tr0,0);
//	}
//	for(_tr0 = 0; _tr0 < 2000; _tr0++){
//		print("%d\n",osPostRead());
//	}
//	while(1);

	print("%d",osTaskLogin(
	"RTC", 			                    //��������
	Task1_Func,			            //�����ַ
	Task1_Stack_size,		                    //����ջ����
	50,		                            //����ʱ����Ƭ
	0,	                                    //�������ȼ�
	"Hello Task1\n",									//���񴫲�   
	Task_Set_Default));

	print("%s\n",osPostReadWait());


	osTaskLogin(    
	"TaskList", 			                    //��������
	Task2_Func,			            //�����ַ
	Task2_Stack_size,		                    //����ջ����
	50,		                            //����ʱ����Ƭ
	1,	                                    //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default
	); 

	osTaskLogin( 
	"LED1", 			                        //��������
	Task3_Func,			                //�����ַ
	Task3_Stack_size,		                        //����ջ����
	50,		                                    //����ʱ����Ƭ
	-2,                                          //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default                                    
	);

	osTaskLogin( 
	"LED2", 			                        //��������
	Task4_Func,			                //�����ַ
	Task4_Stack_size,		                        //����ջ����
	50,		                                    //����ʱ����Ƭ
	-2,                                          //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default                                    
	);




//	osTaskLogout("Task2");



//	osTaskLogin(    
//	"Task2", 			                    //��������
//	Task2_Func,			            //�����ַ
//	Task2_Stack_size,		                    //����ջ����
//	50,		                            //����ʱ����Ƭ
//	1,	                                    //�������ȼ�
//	"Hello",
//	TaskConfig_Default
//	); 

	while(1){
//		for(_tr0 = 0;_tr0 < TST.TLMA;_tr0++){
//			print("����<%s>��ʹ����Ϊ:ռ��ʱ��:%dms | �������ȼ�:%d | ����״̬:",TL[_tr0].TITA -> TN,TL[_tr0].TITA -> TOT,TL[_tr0].TITA -> TPL);
//			if(TL[_tr0].TITA != RunTask_TIT || TST.TSS != TaskSwitch_Ready){
//				switch(TL[_tr0].TITA -> TC){
//					case Task_State_Up_TD:print("��Ƭ����\n");break;
//					case Task_State_Up_IN:print("��������\n");break;
//					case Task_State_Up_DT:print("��ʱ����\n");break;
//					case Task_State_Up_SI:print("�źŹ���\n");break;
//					case Task_State_Up_PT:print("�ʼ�����\n");break;
//					case Task_State_DI:print("����̬\n");break;
//					case Task_State_ST:print("��ֹ̬\n");break;
//					case Task_State_RB:print("����̬\n");break;
//					case Task_State_OP:print("����̬\n");break;
//					case Task_State_Up:print("����̬\n");break;
//				}
//			}
//			else{
//				print("��������\n");
//			}	
//		}
//		print("������ʹ����:%d%% | ",CPUS.CO);
//		print("������ȴ���:%d | Ԥ�ƺ�ʱ:%dus\n",TST.TSC,TST.TSC*TST.TSSU);
//		TST.TSC = 0;
//		print("�ڴ�����:%d�ֽ� | �ڴ�����:%d�ֽ�\n",osMemoryAllSize(),osMemoryMaxMallocValue());
//		tprint("ϵͳ������: %d�� %hСʱ %m���� %s��\n",osTime. TSRT);
		osTaskDelayMs(3000);
//		for(_tr0 = 580;_tr0 < MemTank_Max;_tr0++){
//			MemoryPool[_tr0] = _tr0;
//			osTaskDelayMs(10);
//		}
	}
/*---------------------------------------------------------------------------------------------------*/
}


/*
                                                  FILE-END
*/

