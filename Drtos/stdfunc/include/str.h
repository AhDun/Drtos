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
/**
 *
 * @file HDS_Intmac.h
 *
 * @brief 无
 *
 * @note none 无
 *
 */
#ifndef _HDS_Intmac_H_
#define _HDS_Intmac_H_






#include "main.h"
/**
 *
 * @name osWordComp
 *
 * @brief 字符比较
 *
 * @param 	1.strs		-原字符
				2.strc		-比较字符
	 *
 * @retval 	true		-相同
				false		-不相同
 *
 * @note none
 *
 */
signed char CharComp(signed char *strs,signed char *strc);

/**
 *
 * @name osStrComp
 *
 * @brief 字符串比较
 *
 * @param int8_t *strs(原字符串),int8_t *strc(比较字符串)
 *
 * @retval none
 *
 * @note none
 *
 */

signed char StrComp(signed char *strs,signed char *strc);
/**
 *
 * @name osStrComp
 *
 * @brief 字符串比较
 *
 * @param int8_t *strs(原字符串),int8_t *strc(比较字符串)
 *
 * @retval none
 *
 * @note none
 *
 */
signed char StrCutComp(signed char *strs,signed char *strc,signed char cutchar);
/**
 *
 * @name osStrCutComp
 *
 * @brief 截止式比较字符串
 *
 * @param int8_t *strs(原字符串),int8_t *strc(比较字符串),int8_t cutchar(截止字符)
 *
 * @retval none
 *
 * @note none
 *
 */
unsigned int StrLoca(signed char *strs,signed char locachar);


#endif




