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
	_Signal *p1;

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

//	_Signal* timebz1;

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

	TaskHandle_Task1 = osTaskLogin(
	"RTC", 			                    //��������
	Task1_Func,			            //�����ַ
	Task1_Stack_size,		                    //����ջ����
	50,		                            //����ʱ����Ƭ
	-2,	                                    //�������ȼ�
	"Hello Task1\n",									//���񴫲�   
	Task_Set_Default);

	print("%s\n",osPostReadWait());


	TaskHandle_Task2 = osTaskLogin(    
	"TaskList", 			                    //��������
	Task2_Func,			            //�����ַ
	Task2_Stack_size,		                    //����ջ����
	50,		                            //����ʱ����Ƭ
	-1,	                                    //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default
	); 

	TaskHandle_Task3 = osTaskLogin( 
	"LED1", 			                        //��������
	Task3_Func,			                //�����ַ
	Task3_Stack_size,		                        //����ջ����
	50,		                                    //����ʱ����Ƭ
	-3,                                          //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default                                    
	);

	TaskHandle_Task4 = osTaskLogin( 
	"LED2", 			                        //��������
	Task4_Func,			                //�����ַ
	Task4_Stack_size,		                        //����ջ����
	50,		                                    //����ʱ����Ƭ
	-3,                                          //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default                                    
	);

	osTaskLogout(TaskHandle_Task4);

	while(1){
		osTaskDelayMs(10);
		for(_tr0 = 0;_tr0 < 100;_tr0++){
			osPostSend((u32*)"hello",TaskHandle_Main);
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

