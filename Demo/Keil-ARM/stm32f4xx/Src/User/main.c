/*
                                                  FILE-START
*/

/*
 *@�ļ�����: main.c

 *@�ļ�����: 

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע    ��: 
*/


#include "main.h"
#include "SysTick.h"
#include "osConfig.h"
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

int main(void)
{
/*--------------------------------------demo---------------------------------------------------------*/
	u32 _tr0;
	SemaphoreTable *p1;

//	uint32_t p1 = 0;
//	osTIME p2;
//	uint32_t p3;
//	uint32_t p4;
//	uint32_t p5;
//	uint32_t p6;
//	uint32_t p7;
//	uint32_t p8;

//	uLinkListHeadWrtie(&p1,&p2);
//	uLinkListHeadWrtie(&p1,&p3);
//	uLinkListHeadWrtie(&p1,&p4);

//	p8 = uLinkListHeadRead(&p1);
//	p8 = uLinkListHeadRead(&p1);
//	p8 = uLinkListHeadRead(&p1);
//	p8 = uLinkListHeadRead(&p1);

//	SemaphoreTable* timebz1;

	osInit();

//	p1 = osSignalLogin(Signal_Binary);

//	osSignalUseWait(p1);
//	osSignalUseWait(p1);
//	osSignalUseWait(p1);
//	osSignalUseWait(p1);

//	osSignalFree(p1);
//	osSignalFree(p1);
//	osSignalFree(p1);
//	osSignalFree(p1);
//	osSignalFree(p1);



	//osMemoryMalloc(25000);

	print("%X\n",osTaskLogin(
	"RTC", 			                    //��������
	Task1_Func,			            //�����ַ
	Task1_Stack_size,		                    //����ջ����
	50,		                            //����ʱ����Ƭ
	-2,	                                    //�������ȼ�
	"Hello Task1\n",									//���񴫲�   
	Task_Set_Default));

	print("%s\n",osPostReadWait());


	osTaskLogin(    
	"TaskList", 			                    //��������
	Task2_Func,			            //�����ַ
	Task2_Stack_size,		                    //����ջ����
	50,		                            //����ʱ����Ƭ
	-1,	                                    //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default
	); 

	osTaskLogin( 
	"LED1", 			                        //��������
	Task3_Func,			                //�����ַ
	Task3_Stack_size,		                        //����ջ����
	50,		                                    //����ʱ����Ƭ
	-3,                                          //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default                                    
	);

	osTaskLogin( 
	"LED2", 			                        //��������
	Task4_Func,			                //�����ַ
	Task4_Stack_size,		                        //����ջ����
	50,		                                    //����ʱ����Ƭ
	-3,                                          //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default                                    
	);

	osTaskDelayMs(1000);
	//osTaskLogout("LED2");

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
//		print("������ʹ����:%d%% | ",PS.CO);
//		print("������ȴ���:%d | Ԥ�ƺ�ʱ:%dus\n",TST.TSC,TST.TSC*TST.TSSU);
//		TST.TSC = 0;
//		print("�ڴ�����:%d�ֽ� | �ڴ�����:%d�ֽ�\n",osMemoryAllSize(),osMemoryMaxMallocValue());
//		tprint("ϵͳ������: %d�� %hСʱ %m���� %s��\n",osTime. TSRT);
		osTaskDelayMs(1000);
		for(_tr0 = 0;_tr0 < 100;_tr0++){
			osPostSend((u32*)"hello",osTaskNameToTable("Main"));
		}
		for(_tr0 = 0;_tr0 < 100;_tr0++){
			osPostReadWait();
		}
//		for(_tr0 = 10;_tr0 < MemTank_Max;_tr0++){
//			MemoryPool[_tr0] = _tr0;
//			osTaskDelayMs(10);
//		}
	}
/*---------------------------------------------------------------------------------------------------*/
}


/*
                                                  FILE-END
*/

