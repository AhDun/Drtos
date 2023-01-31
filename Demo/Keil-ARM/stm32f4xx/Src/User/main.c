/*
                                                  FILE-START
*/

/*
 *@文件名称: main.c

 *@文件内容: 

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@注    释: 
*/


#include "main.h"
#include "SysTick.h"
#include "osConfig.h"
#include "Demo.h"
#include "print.h"

/*
                                                  <函数区>
*/


/*
 *@函数名称: 无

 *@函数功能: 无

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

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
	"RTC", 			                    //任务名称
	Task1_Func,			            //任务地址
	Task1_Stack_size,		                    //任务栈长度
	50,		                            //任务时间轮片
	-2,	                                    //任务优先级
	"Hello Task1\n",									//任务传参   
	Task_Set_Default);

	print("%s\n",osPostReadWait());


	TaskHandle_Task2 = osTaskLogin(    
	"TaskList", 			                    //任务名称
	Task2_Func,			            //任务地址
	Task2_Stack_size,		                    //任务栈长度
	50,		                            //任务时间轮片
	-1,	                                    //任务优先级
	"Hello",									//任务传参
	Task_Set_Default
	); 

	TaskHandle_Task3 = osTaskLogin( 
	"LED1", 			                        //任务名称
	Task3_Func,			                //任务地址
	Task3_Stack_size,		                        //任务栈长度
	50,		                                    //任务时间轮片
	-3,                                          //任务优先级
	"Hello",									//任务传参
	Task_Set_Default                                    
	);

	TaskHandle_Task4 = osTaskLogin( 
	"LED2", 			                        //任务名称
	Task4_Func,			                //任务地址
	Task4_Stack_size,		                        //任务栈长度
	50,		                                    //任务时间轮片
	-3,                                          //任务优先级
	"Hello",									//任务传参
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

