/*
                                                  FILE-START
*/
/*

 *@文件名称: osPost.c

 *@文件内容: 系统"队列与邮箱"文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@注    释: 无

*/

/*
                                                  <引用文件区>
*/
#include "osPost.h"

/*
                                                  <数据初始区>
*/
/*
                                                  <函数区>
*/



/*

 *@函数名称: osPostSend

 *@函数版本: 1.0.0

 *@函数功能: 发送邮件

 *@输入参数: 无

 *@返 回 值: -1:发生错误 / 0:发送成功

 *@注   释: 无

*/
osErrorValue osPostSend(void* PB,TaskInfoTable* TIT)
{
	PostForm* PF;

	if(TIT -> TI >= TST.TLMA){//如果写入任务ID不能大于任务活动量,否则返回错误
		return (Error);//出现错误,返回Error
	}else{
		PF = osMemoryMalloc(sizeof(PostForm));//申请内存
		if(PF == NULL){//如果返回为空,说明申请失败
			#if (osPostDebugError_Enable > 0)
			osPostDebugError("发送邮件时申请内存失败 %s\n",RunTask_TIT -> TN);
			#endif
			return (Error);//返回错误
		}else{
			PF -> PB = PB;
			PF -> DownAddr = NULL;

			uLinkListAdd(&TIT -> PF,&PF -> DownAddr);
		}
		if(TIT -> TPL <  RunTask_TIT -> TPL && TIT -> TC == Task_State_Up_PT){//如果这个任务高于当前工作运行任务栏的优先级，就占用
			//TL[_tr0].TITA -> TC &= TIT_Task_State_TC_RST;//清除这个任务的状态位
			TIT -> TC = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
			//RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//清除正在运行任务的状态位
			RunTask_TIT -> TC = Task_State_Up_TD;//将正在运行任务的状态设为轮片挂起(挂起态)
			if(TST.TSS == TaskSwitch_Ready){
				TST. TDN = TIT -> TI;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
				osTaskSwitch_Enable();//触发任务切换
			} 
		}else if(TIT -> TC == Task_State_Up_PT){
			TIT -> TC = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
		}
	}
	//TIT -> TC = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
	return (OK);//发送成功，返回OK
}


/*

 *@函数名称: osPostRead

 *@函数版本: 1.0.0

 *@函数功能: 读取邮件

 *@输入参数: uint8_t* ResiduePost(邮箱指针)

 *@返 回 值: 邮件内容

 *@注   释: 无

*/
uint32_t* osPostRead(void)
{
	PostForm* PF;
	uint32_t*	Buf;

	if(RunTask_TIT -> PF != NULL){
		#if (osPostHead > 0)
		PF = (PostForm*)RunTask_TIT -> PF;
		Buf = PF -> PB;
		RunTask_TIT -> PF = PF -> DownAddr;
		#else
		PF  =  uLinkListReadEndAndRemvoe(&RunTask_TIT -> PF);
		Buf = PF -> PB;
		#endif
		if(osMemoryFree(PF) == Error){
			#if (osPostDebugError_Enable > 0)
			osPostDebugError("读取邮件时释放内存失败 %s\n",RunTask_TIT -> TN);
			#endif
			return (Buf);
		}
		return (Buf);
		
	}else{
		return (NULL);//没有邮件，返回空
	}
}
/*

 *@函数名称: osPostRead_Wait

 *@函数版本: 1.0.0

 *@函数功能: 阻塞式读取邮件

 *@输入参数: 无

 *@返 回 值: 邮件内容

 *@注   释: 无

*/
uint32_t* osPostReadWait(void)
{
	if(RunTask_TIT -> PF == 0){//没有邮件,进行等待
		while(TST.TSS != TaskSwitch_Ready);//查询任务可切换态,如果是不可切换,无限循环,直到可切换态
		//RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//任务的状态位复位
		RunTask_TIT -> TC = Task_State_Up_PT;//修改为邮件挂起(等待态)
		osTaskSwitch_Enable();//触发异常,进行任务切换
	}
	return (osPostRead());//通过非阻塞式读取邮件
}

/*
                                                  FILE-END
*/
