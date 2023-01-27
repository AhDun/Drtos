/*
                                                  FILE-START
*/

/*
 *@文件名称: main.c

 *@文件内容: 

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0 

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

int main(int argc, char *argv[])
{
/*--------------------------------------demo---------------------------------------------------------*/
	u32 _tr0;
//	SemaphoreTable* timebz1;

	osInit();


	//osMemoryMalloc(25000);

	print("%d",osTaskLogin(
	"RTC", 			                    //任务名称
	Task1_Func,			            //任务地址
	Task1_Stack_size,		                    //任务栈长度
	50,		                            //任务时间轮片
	-2,	                                    //任务优先级
	"Hello Task1\n",									//任务传参   
	Task_Set_Default));

	print("%s\n",osPostReadWait());


	osTaskLogin(    
	"TaskList", 			                    //任务名称
	Task2_Func,			            //任务地址
	Task2_Stack_size,		                    //任务栈长度
	50,		                            //任务时间轮片
	-1,	                                    //任务优先级
	"Hello",									//任务传参
	Task_Set_Default
	); 

	osTaskLogin( 
	"LED1", 			                        //任务名称
	Task3_Func,			                //任务地址
	Task3_Stack_size,		                        //任务栈长度
	50,		                                    //任务时间轮片
	-3,                                          //任务优先级
	"Hello",									//任务传参
	Task_Set_Default                                    
	);

	osTaskLogin( 
	"LED2", 			                        //任务名称
	Task4_Func,			                //任务地址
	Task4_Stack_size,		                        //任务栈长度
	50,		                                    //任务时间轮片
	-3,                                          //任务优先级
	"Hello",									//任务传参
	Task_Set_Default                                    
	);



	while(1){
//		for(_tr0 = 0;_tr0 < TST.TLMA;_tr0++){
//			print("任务<%s>的使用量为:占用时长:%dms | 任务优先级:%d | 任务状态:",TL[_tr0].TITA -> TN,TL[_tr0].TITA -> TOT,TL[_tr0].TITA -> TPL);
//			if(TL[_tr0].TITA != RunTask_TIT || TST.TSS != TaskSwitch_Ready){
//				switch(TL[_tr0].TITA -> TC){
//					case Task_State_Up_TD:print("轮片挂起\n");break;
//					case Task_State_Up_IN:print("主动挂起\n");break;
//					case Task_State_Up_DT:print("延时挂起\n");break;
//					case Task_State_Up_SI:print("信号挂起\n");break;
//					case Task_State_Up_PT:print("邮件挂起\n");break;
//					case Task_State_DI:print("禁用态\n");break;
//					case Task_State_ST:print("终止态\n");break;
//					case Task_State_RB:print("重启态\n");break;
//					case Task_State_OP:print("运行态\n");break;
//					case Task_State_Up:print("挂起态\n");break;
//				}
//			}
//			else{
//				print("正在运行\n");
//			}	
//		}
//		print("任务总使用量:%d%% | ",CPUS.CO);
//		print("任务调度次数:%d | 预计耗时:%dus\n",TST.TSC,TST.TSC*TST.TSSU);
//		TST.TSC = 0;
//		print("内存总量:%d字节 | 内存余量:%d字节\n",osMemoryAllSize(),osMemoryMaxMallocValue());
//		tprint("系统已运行: %d天 %h小时 %m分钟 %s秒\n",osTime. TSRT);
		osTaskDelayMs(10);
		osPostSend((u32*)"hello Main",osTaskNameToTable("Main"));
		osPostReadWait();
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

