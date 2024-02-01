/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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
/**
 *
 * @file osPOST.h
 *
 * @brief 无
 *
 * @note none
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


/**
 *
 * @name osPostSend
 *
 * @brief 初始化邮箱
 *
 * @param PB - 邮件内容
			 TaskHandle - 目标任务的任务句柄地址
 *
 * @retval  函数错误返回值 (0:表示初始化成功，-1:表示初始化失败)
 *
 * @note none
 *
 */
OsErrorValue osPostSend(void* PB,_TaskHandle* TaskHandle);
/**
 *
 * @name osPostRead
 *
 * @brief 读取邮件
 *
 * @param none
 *
 * @retval 邮件内容
 *
 * @note none
 *
 */
uint32_t* osPostRead(void);
/**
 *
 * @name osPostRead_Wait
 *
 * @brief 阻塞式读取邮件
 *
 * @param none
 *
 * @retval 邮件内容
 *
 * @note none
 *
 */
uint32_t* osPostReadWait(void);

#endif

#endif



