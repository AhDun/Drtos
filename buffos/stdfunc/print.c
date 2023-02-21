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
 * @文件名称: print.c
 *
 * @文件内容: print函数，与printf用法无异
 *
 * @注    释: 无
 *
 */


#include "main.h"
#include "print.h"
#include "usart.h"	

/*
                                                  变量初始化区
*/

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
int pchar(const char ch)
{
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return (ch);
}
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
static int _spchar(const char ch,int* s)
{
	if(s == 0){
		pchar(ch);
	}
	else{
		*((char*)*s) = ch;
		*s = (int)*s + 1;
	}
	return ch;
}
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
static void _printU10(unsigned int num,int ctl,int* s)
{
	int _FLAG = 100000000;
	char _FLAG1 = 0;
	if((num / 1000000000) % 10 > 0){
		_spchar((char)(num / 1000000000) % 10 + 48,s);
		_FLAG1 = 1;
	}
	ctl = 9  - ctl;
	while(_FLAG > 1){
		if(((num / _FLAG) % 10) > 0 || _FLAG1 == 1 || ctl == 0){
			_spchar((char)((num / _FLAG) % 10) + 48,s);
			_FLAG1 = 1;
		}
		_FLAG /= 10;
		if(ctl > 0){
			ctl -= 1;
		}
	}
	_spchar(num % 10 + 48,s);
}
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
static void _printS10(int num,int ctl,int* s)
{
	if(num < 0){
		num = (~num) + 1;
		_spchar('-',s);
	}
	_printU10(num,ctl,s);
}
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
static void _printSring(int p,int* s)
{
	for(;;){
		if(*(char*)p != '\0'){
			_spchar(*(char*)p,s);
		}
		else{
			return;
		}
		p++;
	}
} 
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
static void _print16(int num,int c,int* s)
{
	char _FLAG = 28;
	char _FLAG1 = 0;
	char _BUF;
	_spchar('0',s);
	_spchar('x',s);
	if(num == 0x00){
		_spchar(0 + 48,s);
		_spchar(0 + 48,s);
	}else{
		for(;;){
			_BUF = ((num >> _FLAG) & 0x0F);
			if(_BUF >= 10){
				_spchar(c + (_BUF - 10),s);
				_FLAG1 = 1;
			}else if(_BUF > 0 || _FLAG1 > 0){
				_spchar(_BUF + 48,s);
				_FLAG1 = 1;
			}
			if(_FLAG <= 0){
				return;
			}
			_FLAG -= 4;
		}
	}
}
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
static void _print8(int num,int* s)
{
	char _FLAG = 30;
	char _FLAG1 = 0;
	char _BUF;
	_BUF = ((num >> _FLAG) & 0x03);
	_spchar('0',s);
	if(_BUF > 0){
		_spchar(_BUF + 48,s);
		_FLAG1 = 1;
	}
	for(;;){
		_BUF = ((num >> _FLAG) & 0x07);
		if(_BUF > 0 || _FLAG1 > 0){
			_spchar(_BUF + 48,s);
			_FLAG1 = 1;
		}
		if(_FLAG <= 0){
			return;
		}
		_FLAG = _FLAG - 3;
	}
}
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
static void _print_lf(double* num,char ctrl,int* s)
{
	int c = 0;
	int m;
	char x;
	int k = 0;
	double numv;
	char p;
	
	m = 10;

	if(ctrl > 0){
		p =  ctrl;
	}else{
		p = _print_lf_retain;
	}

	numv = *num;
	_printS10((int)numv,0,s);
	_spchar('.',s);
	for(x = 1; x < (p + 1); x++){
		c = (c * 10) + ((unsigned int)(numv * m) % 10);
		if(c == 0){
			k = k + 1;
		}
		m = m * 10;
	}
	for(x = 1; x < 20;x++){
		if((c % 10) == 0){
			c = c / 10;
		}else{
			for(;k > 0;k--){
				_spchar('0',s);
			}
			break;
		}
	}
	
	_printU10(c,0,s);
	
	
}
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
void xprint(int sp,int c)
{	
	int _SP;
    char* _CONTROL;
	int* s1;
	
	char LeftValue = 0;
	char RightValue = 0;

	_SP = sp;
	if(c != 0){
		s1 = (int*)(_SP);
		_CONTROL = (char*)(*((int*)(_SP + 0x04)));
		_SP = _SP + 0x08;
	}else{
		_CONTROL = (char*)(*((int*)(_SP)));
		_SP = _SP + 0x04;
		s1 = 0;
	}
	for(;;)
	{
		switch(*_CONTROL){
			case '%':
						_CONTROL++;
						xprintc:
						switch(*_CONTROL){
							case 'd'://以十进制形式输出带符号整数(正数不输出符号)
									_printS10(*((int*)(_SP)),LeftValue,s1);
									_SP = _SP + 0x04;
									break;
							case 'l'://输出32位无符号整数
									if(*(_CONTROL + 1) != 'u'){
										_spchar((char)*_CONTROL,s1);
										break;
									}
							case 'u'://输出32位无符号整数
									_CONTROL++;
									_printU10((*((unsigned int*)(_SP))),LeftValue,s1);
									_SP = _SP + 0x04;
									break;									
							case 'p'://输出指针地址
									
									_printU10((int)(_SP),LeftValue,s1);
									_SP = _SP + 0x04;
									break;
							case 's'://输出字符串
									
									_printSring(*((int*)(_SP)),s1);
									_SP = _SP + 0x04;
									break;
							case 'c'://输出单个字符
									
									_spchar((char)(*((int*)(_SP))),s1);
									_SP = _SP + 0x04;
									break;
							case 'X'://以十六进制大写形式输出无符号整数(输出前缀0x)
									
									_print16(*((int*)(_SP)),'A',s1);
									_SP = _SP + 0x04;
									break;
							case 'x'://以十六进制小写形式输出无符号整数(输出前缀0x)
									
									_print16(*((int*)(_SP)),'a',s1);
									_SP = _SP + 0x04;
									break;
							case 'o'://以八进制形式输出无符号整数(输出前缀0)
									
									_print8(*((int*)(_SP)),s1);
									_SP = _SP + 0x04;
									break;
							case 'f'://输出双精度浮点
									if((_SP % 8) != 0){
										_SP = _SP + 0x04;
									}
									_print_lf((double*)(_SP),RightValue,s1);
									_SP = _SP + 0x08;
									break;
							case '.'://右值
									_CONTROL++;
									RightValue = 0;
									while(*_CONTROL >= '0' && *_CONTROL <= '9'){
										RightValue = (RightValue * 10) + *_CONTROL - '0';
										_CONTROL++;
									}
									goto xprintc;
							default:
									if(*_CONTROL >= '0' && *_CONTROL <= '9'){//左值
										LeftValue = 0;
										while(*_CONTROL >= '0' && *_CONTROL <= '9'){
											LeftValue = (LeftValue * 10) + *_CONTROL - '0';
											_CONTROL++;
										}
										goto xprintc;
									}else{
										_spchar((char)*_CONTROL,s1);
									}
									break;
								
						}
						break;
			case '\0'://结束符
						return;
			case '\n'://回车符
						_spchar('\n',s1);
						break;
			case '\b'://自定义
						break;
			case '\a'://自定义
						break;
			default:
						_spchar((char)*_CONTROL,s1);
						break;
		}
		_CONTROL++;
		LeftValue = 0;
		RightValue = 0;
	}
  
}




	

