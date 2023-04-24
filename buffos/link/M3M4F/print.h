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

#ifndef __print_H_
#define __print_H_

/*
 *
 * @文件名称: print.h
 *
 * @文件内容: print系列函数
 *
 * @注   释: 无
 *
 */





#define _print_lf_retain	6 //小数精度
							  //这个数值决定了保留%f输出的小数点后几位



#define offsetUChar(a)  a + sizeof(unsigned char)
#define offsetChar(a)  a + sizeof(char)
#define offsetUInt(a)  a + sizeof(unsigned int)
#define offsetInt(a)  a + sizeof(signed int)
#define offsetFloat(a)  a + sizeof(float)
#define offsetDouble(a)  a + sizeof(double)

#define offsetUCharp(a)  a + sizeof(unsigned char*)
#define offsetCharp(a)  a + sizeof(char*)
#define offsetUIntp(a)  a + sizeof(unsigned int*)
#define offsetIntp(a)  a + sizeof(signed int*)
#define offsetFloatp(a)  a + sizeof(float*)
#define offsetDoublep(a)  a + sizeof(double*)






/*
 *
 * @函数名称: pchar
 *
 * @函数功能: 输出接口
 *
 * @输入参数: ch	字符
 *
 * @返 回 值: 无
 *
 * @注    释: 该函数可以用于重定向
 *
 */
int pchar(const char ch);
/*
 *
 * @函数名称: pchar
 *
 * @函数功能: sprint函数字符回流
 *
 * @输入参数: ch	字符
 * @输入参数: s		sprint函数回流数据
 *
 * @返 回 值: 无
 *
 * @注    释: 该函数可以用于重定向
 *
 */
static void _spchar(const char ch,int* s);
/*
 *
 * @函数名称: _printU10
 *
 * @输入参数: num	无符号十进制数
 * @输入参数: ctl	前置0个数
 * @输入参数: s		sprint函数回流数据
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void _printU10(unsigned int num,int ctl,int* s);
/*
 *
 * @函数名称: _printS10
 *
 * @函数功能: print内联输出有符号十进制数
 *
 * @输入参数: num	有符号十进制数
 * @输入参数: ctl	前置0个数
 * @输入参数: s		sprint函数回流数据
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _printS10(int num,int ctl,int* s);
/*
 *
 * @函数名称: _printSring
 *
 * @函数功能: print内联输出字符串
 *
 * @输入参数: p		字符串首地址
 * @输入参数: s		sprint函数回流数据
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void _printSring(int p,int* s);
/*
 *
 * @函数名称: _print16
 *
 * @函数功能: printf内联输出十六形式
 *
 * @输入参数: num	十六进制数值
 * @输入参数: c		ASCII码起始值
 * @输入参数: s		sprint函数回流数据
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print16(int num,int c,int* s);
/*
 *
 * @函数名称: _print8
 *
 * @函数功能: printf内联输出八进制
 *
 * @输入参数: num	八进制数值
 * @输入参数: s		sprint函数回流数据
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print8(int num,int* s);
/*
 *
 * @函数名称: _print_lf
 *
 * @函数功能: print内联输出双精度浮点数(64位)
 *
 * @输入参数: num	双精度浮点数
 * @输入参数: s		sprint函数回流数据
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print_lf(double* num,char ctrl,int* s);
/*
 *
 * @函数名称: xprint
 *
 * @函数功能: print函数子函数
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void xprint(int* s,char* con,int sp);








#endif

