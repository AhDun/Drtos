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

	osInit();

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

	//osTaskLogout(TaskHandle_Task4);

	while(1){
		osTaskDelayMs(1000);
		for(_tr0 = 0;_tr0 < 500;_tr0++){
			osPostSend((u32*)"hello",TaskHandle_Main);
		}
		osTaskDelayMs(1000);
		for(_tr0 = 0;_tr0 < 500;_tr0++){
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

