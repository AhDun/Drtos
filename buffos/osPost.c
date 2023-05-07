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

#if (osPost_Config > 0)

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

	PostForm = osPostMemoryMalloc(sizeof(_Post));//申请内存
	if(PostForm == NULL){//如果返回为空,说明申请失败
		#if (osPostLog_Config > 0)
		osLogE("osPostSend","发送邮件时申请内存失败");
		#endif
		return (Error);//返回错误
	}else{
		PostForm -> Body = PB;
		PostForm -> DownAddr = NULL;

		uLinkListTailWrtie(&TaskHandle -> Arg1,(uint32_t*)PostForm);
	}
	if(TaskHandle -> Config == Task_State_Up_PT){
		if(TaskHandle -> Level <  osTaskGetRunTaskHandle() -> Level){//如果这个任务高于当前工作运行任务栏的优先级，就占用
			TaskHandle -> Config = Task_State_RE;//将这个任务的状态设为轮片挂起(挂起态)
			osTaskSwitchConfig(TaskHandle,osTaskGetRunTaskHandle(),Task_State_RE);//触发任务切换
		}else{
			TaskHandle -> Config = Task_State_RE;//将这个任务的状态设为轮片挂起(挂起态)
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

	if(osTaskGetRunTaskHandle() -> Arg1 != NULL){
		#if (osPostHead_Config > 0)
		PostForm = (_Post*)uLinkListHeadRead(&osTaskGetRunTaskHandle() -> Arg1);
		#else
		PostForm  =  (_Post*)uLinkListTailRead(&osTaskGetRunTaskHandle() -> Arg1);
		#endif
		Buf = PostForm -> Body;
		if(osPostMemoryFree(PostForm) != OK){
			#if (osPostLog_Config > 0)
			osLogE("osPostRead","读取邮件时释放内存失败\n");
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
	if(osTaskGetRunTaskHandle() -> Arg1 == 0){//没有邮件,进行等待
		osTaskSwitchConfig(OSCoreTaskHandle,osTaskGetRunTaskHandle(),Task_State_Up_PT);//触发异常,进行任务切换
	}
	return (osPostRead());//通过非阻塞式读取邮件
}

#endif


