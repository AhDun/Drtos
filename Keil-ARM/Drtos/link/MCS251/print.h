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

#ifndef __print_H_
#define __print_H_

/**
 *
 * @file print.h
 *
 * @brief print系列函数
 *
 * @note none
 *
 */





#define _print_lf_retain	6 //小数精度
							  //这个数值决定了保留%f输出的小数点后几位


#define offsetUChar(a)  a - sizeof(unsigned char)
#define offsetChar(a)  a - sizeof(char)
#define offsetUInt(a)  a - sizeof(unsigned int)
#define offsetInt(a)  a - sizeof(signed int)
#define offsetFloat(a)  a - sizeof(float)
#define offsetDouble(a)  a - sizeof(double)

#define offsetUCharp(a)  a - sizeof(unsigned char*)
#define offsetCharp(a)  a - sizeof(char*)
#define offsetUIntp(a)  a - sizeof(unsigned int*)
#define offsetIntp(a)  a - sizeof(signed int*)
#define offsetFloatp(a)  a - sizeof(float*)
#define offsetDoublep(a)  a - sizeof(double*)






/**
 *
 * @name pchar
 *
 * @brief 输出接口
 *
 * @param ch	字符
 *
 * @retval none
 *
 * @note 该函数可以用于重定向
 *
 */
int pchar(const char ch);
/**
 *
 * @name pchar
 *
 * @brief sprint函数字符回流
 *
 * @param ch	字符
 * @param s		sprint函数回流数据
 *
 * @retval none
 *
 * @note 该函数可以用于重定向
 *
 */
static void _spchar(const char ch,int* s);
/**
 *
 * @name _printU10
 *
 * @param num	无符号十进制数
 * @param ctl	前置0个数
 * @param s		sprint函数回流数据
 *
 * @retval none
 *
 * @note none
 *
 */
void _printU10(unsigned long int num,int ctl,int* s);
/**
 *
 * @name _printS10
 *
 * @brief print内联输出有符号十进制数
 *
 * @param num	有符号十进制数
 * @param ctl	前置0个数
 * @param s		sprint函数回流数据
 *
 * @retval none
 *
 * @note none
 *
 */
static void _printS10(long int num,int ctl,int* s);
/**
 *
 * @name _printSring
 *
 * @brief print内联输出字符串
 *
 * @param p		字符串首地址
 * @param s		sprint函数回流数据
 *
 * @retval none
 *
 * @note none
 *
 */
void _printSring(long int p,int* s);
/**
 *
 * @name _print16
 *
 * @brief printf内联输出十六形式
 *
 * @param num	十六进制数值
 * @param c		ASCII码起始值
 * @param s		sprint函数回流数据
 *
 * @retval none
 *
 * @note none
 *
 */
static void _print16(long int num,int c,int* s);
/**
 *
 * @name _print8
 *
 * @brief printf内联输出八进制
 *
 * @param num	八进制数值
 * @param s		sprint函数回流数据
 *
 * @retval none
 *
 * @note none
 *
 */
static void _print8(long int num,int* s);
/**
 *
 * @name _print_lf
 *
 * @brief print内联输出双精度浮点数(64位)
 *
 * @param num	双精度浮点数
 * @param s		sprint函数回流数据
 *
 * @retval none
 *
 * @note none
 *
 */
static void _print_lf(double* num,char ctrl,int* s);
/**
 *
 * @name xprint
 *
 * @brief print函数子函数
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void xprint(int* s,char* con,int sp);








#endif

