/*
                                                  FILE-START
*/
/*

 *@文件名称: HDS_Intmac.h

 *@文件内容: 无

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@注   释: 无

*/
#ifndef _HDS_Intmac_H_
#define _HDS_Intmac_H_

/*
                                                  <引用文件区>
*/


/*
                                                  <宏定义区>
*/

#include "main.h"
/*

 *@函数名称: osWordComp

 *@函数版本: 1.0.0

 *@函数功能: 字符比较

 *@输入参数: 	1.strs		-原字符
				2.strc		-比较字符
	
 *@返 回 值: 	true		-相同
				false		-不相同

 *@注    释: 无

*/
signed char CharComp(signed char *strs,signed char *strc);

/*

 *@函数名称: osStrComp

 *@函数版本: 1.0.0

 *@函数功能: 字符串比较

 *@输入参数: s8 *strs(原字符串),s8 *strc(比较字符串)

 *@返 回 值: 无

 *@注    释: 无

*/

signed char StrComp(signed char *strs,signed char *strc);
/*

 *@函数名称: osStrComp

 *@函数版本: 1.0.0

 *@函数功能: 字符串比较

 *@输入参数: s8 *strs(原字符串),s8 *strc(比较字符串)

 *@返 回 值: 无

 *@注    释: 无

*/
signed char StrCutComp(signed char *strs,signed char *strc,signed char cutchar);
/*

 *@函数名称: osStrCutComp

 *@函数版本: 1.0.0

 *@函数功能: 截止式比较字符串

 *@输入参数: s8 *strs(原字符串),s8 *strc(比较字符串),s8 cutchar(截止字符)

 *@返 回 值: 无

 *@注    释: 无

*/
unsigned int StrLoca(signed char *strs,signed char locachar);


#endif

/*
                                                  FILE-END
*/


