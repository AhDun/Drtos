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
 * @函数名称: vpchar
 *
 * @函数功能: pchar函数的上级函数
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 
 *
 */
static int vpchar(const char ch,int* s);
/*
 *
 * @函数名称: _print_num
 *
 * @函数功能: 输出无符号十进制数值
 *
 * @输入参数: num	十进制数值
 * @输入参数: ctl	前补零个数
 * @输入参数: s		spirnt函数指针回传
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print_num(unsigned int num,int ctl,int* s);
/*
 *
 * @函数名称: _print_d
 *
 * @函数功能: 输出有符号十进制数值
 *
 * @输入参数: num	十进制数值
 * @输入参数: ctl	前补零个数
 * @输入参数: s		spirnt函数指针回传
 *
 * @返 回 值: 无
 *
 * @注    释: 
 *
 */
static void _print_d(int num,int ctl,int* s);
/*
 *
 * @函数名称: _print_s
 *
 * @函数功能: 输出字符串
 *
 * @输入参数: p		字符串地址
 * @输入参数: s		spirnt函数指针回传
 *
 * @返 回 值: 无
 *
 * @注    释: 
 *
 */
static void _print_s(int p,int* s);
/*
 *
 * @函数名称: _print_X
 *
 * @函数功能: 输出大写的十六进制数
 *
 * @输入参数: num	十六进制数值
 * @输入参数: s		spirnt函数指针回传
 *
 * @返 回 值: 无
 *
 * @注    释: 
 *
 */
static void _print16(int num,int c,int* s);
/*
 *
 * @函数名称: _print_o
 *
 * @函数功能: 输出八进制数
 *
 * @输入参数: num	八进制数值
 * @输入参数: s		spirnt函数指针回传
 *
 * @返 回 值: 无
 *
 * @注    释: 
 *
 */
static void _print8(int num,int* s);
/*
 *
 * @函数名称: _print_lu
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print_lu(unsigned int num,int* s);
/*
 *
 * @函数名称: _print_lf
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print_lf(double* num,char ctrl,int* s);
/*
 *
 * @函数名称: _pchar
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _pchar(int p,int* s);
/*
 *
 * @函数名称: print
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
__asm void print(const char* s,...);
/*
 *
 * @函数名称: sprint
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
__asm void sprint(char* s,const char* c,...);
/*
 *
 * @函数名称: xprint
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void xprint(int sp,int c);
/*
 *
 * @函数名称: tprint
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void tprint(const char* c,unsigned int s);



#endif

