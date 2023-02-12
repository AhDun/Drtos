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
/*
 *
 * @文件名称: osPost.c
 *
 * @文件内容: 系统"队列与邮箱"文件
 *
 * @注    释: 无
 *
 */


#include "osPost.h"






/*
 *
 * @函数名称: osPostSend
 *
 * @函数功能: 发送邮件
 *
 * @输入参数: 无
 *
 * @返 回 值: -1:发生错误 / 0:发送成功
 *
 * @注   释: 无
 *
 */
OsErrorValue osPostSend(void* PB,_TaskHandle* TaskHandle)
{
	_Post* PostForm;

	PostForm = osMemoryMalloc(sizeof(_Post));//申请内存
	if(PostForm == NULL){//如果返回为空,说明申请失败
		#if (osPostDebugError_Enable > 0)
		osPostDebugError("发送邮件时申请内存失败 %s\n",osTaskGetRunTaskHandle() -> Name);
		#endif
		return (Error);//返回错误
	}else{
		PostForm -> Body = PB;
		PostForm -> DownAddr = NULL;

		uLinkListTailWrtie(&TaskHandle -> PF,(uint32_t*)PostForm);
	}
	if(TaskHandle -> Config == Task_State_Up_PT){
		if(TaskHandle -> PriorityLevel <  osTaskGetRunTaskHandle() -> PriorityLevel){//如果这个任务高于当前工作运行任务栏的优先级，就占用
			TaskHandle -> Config = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
			osTaskGetRunTaskHandle() -> Config = Task_State_Up_TD;//将正在运行任务的状态设为轮片挂起(挂起态)
			if(osTaskGetSwitchState() == TaskSwitch_Ready){
				osTaskGetNextTaskHandle() = TaskHandle;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
				osTaskSwitch_Enable();//触发任务切换
			} 
		}else{
			TaskHandle -> Config = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
		}
	}
	return (OK);//发送成功，返回OK
}


/*
 *
 * @函数名称: osPostRead
 *
 * @函数功能: 读取邮件
 *
 * @输入参数: uint8_t* ResiduePost(邮箱指针)
 *
 * @返 回 值: 邮件内容
 *
 * @注   释: 无
 *
 */
uint32_t* osPostRead(void)
{
	_Post* PostForm;
	uint32_t*	Buf;

	if(osTaskGetRunTaskHandle() -> PF != NULL){
		#if (osPostHead > 0)
		PostForm = (_Post*)uLinkListHeadRead(&osTaskGetRunTaskHandle() -> PF);
		#else
		PostForm  =  (_Post*)uLinkListTailRead(&osTaskGetRunTaskHandle() -> PF);
		#endif
		Buf = PostForm -> Body;
		if(osMemoryFree(PostForm) != OK){
			#if (osPostDebugError_Enable > 0)
			osPostDebugError("读取邮件时释放内存失败 %s\n",osTaskGetRunTaskHandle() -> Name);
			#endif
			return (Buf);
		}
		return (Buf);
		
	}else{
		return (NULL);//没有邮件，返回空
	}
}
/*
 *
 * @函数名称: osPostRead_Wait
 *
 * @函数功能: 阻塞式读取邮件
 *
 * @输入参数: 无
 *
 * @返 回 值: 邮件内容
 *
 * @注   释: 无
 *
 */
uint32_t* osPostReadWait(void)
{
	if(osTaskGetRunTaskHandle() -> PF == 0){//没有邮件,进行等待
		while(osTaskGetSwitchState() != TaskSwitch_Ready);//查询任务可切换态,如果是不可切换,无限循环,直到可切换态
		osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_Up_PT);//触发异常,进行任务切换
	}
	return (osPostRead());//通过非阻塞式读取邮件
}


