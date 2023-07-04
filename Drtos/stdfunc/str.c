/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
 */
/*
 *
 * @文件名称: str.c
 *
 * @文件内容: 字符串
 *
 * @注    释: 无
 *
 */



#include "str.h"

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
signed char CharComp(signed char *strs,signed char *strc)
{
	if(*strs == *strc){
		return true;
	}
	else{
		return false;
	}
}

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
/*
 *
 * @函数名称: osStrLoca
 *
 * @函数功能: 在字符串定位某个字符的位置
 *
 * @输入参数: int8_t *strs(字符串),int8_t locachar(字符)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
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
/*
 *
 * @函数名称: osStrLoca
 *
 * @函数功能: 在字符串定位某个字符的位置
 *
 * @输入参数: int8_t *strs(字符串),int8_t locachar(字符)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
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

