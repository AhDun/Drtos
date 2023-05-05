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
#ifndef __osPOST_H_
#define __osPOST_H_
/*
 *
 * @文件名称: osPOST.h
 *
 * @文件内容: 无
 *
 * @注   释: 无
 *
 */





#include "main.h"
#include "osConfig.h"
#include "osTask.h"


#if (osPost_Config > 0)

typedef		uint32_t		 _PostBody;//邮件主体
//邮箱表单{
typedef struct 
{
	_NextAddr	  DownAddr;//下一个邮件的地址
	_PostBody*	  Body;//邮件主体

}_Post;
//}


/*
 *
 * @函数名称: osPostSend
 *
 * @函数功能: 初始化邮箱
 *
 * @输入参数: PB - 邮件内容
			 TaskHandle - 目标任务的任务句柄地址
 *
 * @返 回 值:  函数错误返回值 (0:表示初始化成功，-1:表示初始化失败)
 *
 * @注   释: 无
 *
 */
OsErrorValue osPostSend(void* PB,_TaskHandle* TaskHandle);
/*
 *
 * @函数名称: osPostRead
 *
 * @函数功能: 读取邮件
 *
 * @输入参数: 无
 *
 * @返 回 值: 邮件内容
 *
 * @注   释: 无
 *
 */
uint32_t* osPostRead(void);
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
uint32_t* osPostReadWait(void);

#endif

#endif



