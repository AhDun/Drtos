/*
                                                  FILE-START
*/

#ifndef __print_H_
#define __print_H_

/*
 *
 * @文件名称: print.h
 *
 * @文件内容: print系列函数
 *
 * @文件作者: AhDun (mail: ahdunxx@163.com)
 *
 * @注   释: 无
 *
 */

/*
                                                  <引用文件区>
*/

/*
                                                  <宏定义区>
*/

#define _print_lf_retain	6 //小数精度
							  //这个数值决定了保留%f输出的小数点后几位

/*
                                                  <数据声明区>
*/

/*
                                                  <函数声明区>
*/
/*
 *
 * @函数名称: pchar
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
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
			 ctl	前补零个数
			 s		spirnt函数指针回传
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
			 ctl	前补零个数
			 s		spirnt函数指针回传
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
			 s		spirnt函数指针回传
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
			 s		spirnt函数指针回传
 *
 * @返 回 值: 无
 *
 * @注    释: 
 *
 */
static void _print_X(int num,int* s);
/*
 *
 * @函数名称: _print_x
 *
 * @函数功能: 输出小写的十六进制数
 *
 * @输入参数: num	十六进制数值
			 s		spirnt函数指针回传
 *
 * @返 回 值: 无
 *
 * @注    释: 
 *
 */
static void _print_x(int num,int* s);
/*
 *
 * @函数名称: _print_o
 *
 * @函数功能: 输出八进制数
 *
 * @输入参数: num	八进制数值
			 s		spirnt函数指针回传
 *
 * @返 回 值: 无
 *
 * @注    释: 
 *
 */
static void _print_o(int num,int* s);
/*
 *
 * @函数名称: pchar
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 该函数可以用于重定向
 *
 */
static void _print_lu(unsigned int num,int* s);
/*
 *
 * @函数名称: pchar
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 该函数可以用于重定向
 *
 */
static void _print_lf(double* num,char ctrl,int* s);
/*
 *
 * @函数名称: pchar
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 该函数可以用于重定向
 *
 */
static void _pchar(int p,int* s);
/*
 *
 * @函数名称: pchar
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 该函数可以用于重定向
 *
 */
__asm void print(const char* s,...);
/*
 *
 * @函数名称: pchar
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 该函数可以用于重定向
 *
 */
__asm void sprint(char* s,const char* c,...);
/*
 *
 * @函数名称: pchar
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 该函数可以用于重定向
 *
 */
void xprint(int sp,int c);
/*
 *
 * @函数名称: pchar
 *
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 该函数可以用于重定向
 *
 */
void tprint(const char* c,unsigned int s);


/*
                                                  FILE-END
*/
#endif

