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
 * @文件名称: HDS_Intmac.h
 *
 * @文件内容: 无
 *
 * @文件作者: AhDun (mail: ahdunxx@163.com)
 *
 * @注   释: 无
 *
 */
#ifndef _HDS_Intmac_H_
#define _HDS_Intmac_H_






#include "main.h"
/*
 *
 * @函数名称: osWordComp
 *
 * @函数功能: 字符比较
 *
 * @输入参数: 	1.strs		-原字符
				2.strc		-比较字符
	 *
 * @返 回 值: 	true		-相同
				false		-不相同
 *
 * @注    释: 无
 *
 */
signed char CharComp(signed char *strs,signed char *strc);

/*
 *
 * @函数名称: osStrComp
 *
 * @函数功能: 字符串比较
 *
 * @输入参数: int8_t *strs(原字符串),int8_t *strc(比较字符串)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */

signed char StrComp(signed char *strs,signed char *strc);
/*
 *
 * @函数名称: osStrComp
 *
 * @函数功能: 字符串比较
 *
 * @输入参数: int8_t *strs(原字符串),int8_t *strc(比较字符串)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
signed char StrCutComp(signed char *strs,signed char *strc,signed char cutchar);
/*
 *
 * @函数名称: osStrCutComp
 *
 * @函数功能: 截止式比较字符串
 *
 * @输入参数: int8_t *strs(原字符串),int8_t *strc(比较字符串),int8_t cutchar(截止字符)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
unsigned int StrLoca(signed char *strs,signed char locachar);


#endif




