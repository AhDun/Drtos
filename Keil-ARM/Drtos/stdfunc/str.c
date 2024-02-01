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
 * @file 称: str.c
 *
 * @brief 字符串
 *
 * @note : 无
 *
 */



#include "str.h"

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
 * @note : 无
 *
 */
signed char CharComp(signed char *strs,signed char *strc)
{
	if(*strs == *strc){
		return true;
	}
	else{
		return false;
	}
}

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
 * @note : 无
 *
 */
signed char StrComp(signed char *strs,signed char *strc)
{
	for(;;){
		if(*strs != *strc){
			return false;
		}
		if(*strs == '\0'){
			return true;
		}
		strs++;
		strc++;
	}
}
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
 * @note : 无
 *
 */
signed char StrCutComp(signed char *strs,signed char *strc,signed char cutchar)
{
	for(;;){
		if(*strc == cutchar){
			return true;
		}
		if(*strs == '\0'){
			return true;
		}
		if(*strs != *strc){
			return false;
		}
		strs++;
		strc++;
	}
}
/**
 *
 * @name osStrLoca
 *
 * @brief 在字符串定位某个字符的位置
 *
 * @param int8_t *strs(字符串),int8_t locachar(字符)
 *
 * @retval none
 *
 * @note : 无
 *
 */

unsigned int StrLoca(signed char *strs,signed char locachar)
{
	unsigned int Locas = 0;
	for(;;){
		if(*strs == '\0'){
			return false;
		}
		if(*strs == locachar){
			return Locas;
		}
		strs++;
		Locas++;
	}
}
/**
 *
 * @name osStrLoca
 *
 * @brief 在字符串定位某个字符的位置
 *
 * @param int8_t *strs(字符串),int8_t locachar(字符)
 *
 * @retval none
 *
 * @note : 无
 *
 */
unsigned int StrLength(signed char *strs)
{
	unsigned int Length = 0;
	for(;;){
		if(*strs == '\0'){
			return (Length);
		}else{
			Length++;
		}
	}
}

