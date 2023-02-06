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
 * @文件作者: AhDun (mail: ahdunxx@163.com)
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
 * @输入参数: 无
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
 * @函数功能: 输出接口
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 该函数可以用于重定向
 *
 */
static int vpchar(const char ch,int* s)
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
 * @函数名称: _print_num
 *
 * @函数功能: print内联输出数字
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print_num(unsigned int num,int ctl,int* s)
{
	int _FLAG = 0;
	//unsigned int _PLACE = 1000000000;
//	if((num / 10000000000) > 0){
//		vpchar((char)(num / 10000000000 + 48));
//	}
//	while(1)
//	{
//		if((num % (_PLACE * 10) / _PLACE) > 0 || _FLAG == 1){
//			vpchar((char)(num % (_PLACE * 10) / _PLACE + 48));
//			_FLAG = 1;
//		}
//		if(_PLACE == 1){
//			break;
//		}
//		_PLACE = _PLACE / 10;
//	}
	if((num / 10000000000) > 0 || ctl >= 11){
		vpchar((char)(num / 10000000000 + 48),s);
		_FLAG = 1;
	}
	if((num % 10000000000 / 1000000000) > 0 || _FLAG == 1 || ctl >= 10){
		vpchar((char)(num % 10000000000 / 1000000000 + 48),s);
		_FLAG = 1;
	}
	if((num % 1000000000 / 100000000) > 0 || _FLAG == 1 || ctl >= 9){
		vpchar((char)(num % 1000000000 / 100000000 + 48),s);
		_FLAG = 1;
	}
	if((num % 100000000 / 10000000) > 0 || _FLAG == 1 || ctl >= 8){
		vpchar((char)(num % 100000000 / 10000000 + 48),s);
		_FLAG = 1;
	}
	if((num % 10000000 / 1000000) > 0 || _FLAG == 1 || ctl >= 7){
		vpchar((char)(num % 10000000 / 1000000 + 48),s);
		_FLAG = 1;
	}
	if((num % 1000000 / 100000) > 0 || _FLAG == 1 || ctl >= 6){
		vpchar((char)(num % 1000000 / 100000 + 48),s);
		_FLAG = 1;
	}
	if((num % 100000 / 10000) > 0 || _FLAG == 1 || ctl >= 5){
		vpchar((char)(num % 100000 / 10000 + 48),s);
		_FLAG = 1;
	}
	if((num % 10000 / 1000) > 0 || _FLAG == 1 || ctl >= 4){
		vpchar((char)(num % 10000 / 1000 + 48),s);
		_FLAG = 1;
	}
	if((num % 1000 / 100) > 0 || _FLAG == 1 || ctl >= 3){
		vpchar((char)(num % 1000 / 100 + 48),s);	
		_FLAG = 1;
	}
	if((num % 100 / 10) > 0 || _FLAG == 1 || ctl >= 2){
		vpchar((char)(num % 100 / 10 + 48),s);
		_FLAG = 1;
	}
	vpchar((char)(num % 10+ 48),s);
}
/*
 *
 * @函数名称: _print_d
 *
 * @函数功能: print内联输出有符号整型数据
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print_d(int num,int ctl,int* s)
{
	if(num < 0){
		num = (~num) + 1;
		vpchar('-',s);
	}
	_print_num(num,ctl,s);
}
/*
 *
 * @函数名称: _pchar
 *
 * @函数功能: print内联输出字符
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _vpchar(int p,int* s)
{
	while(1){
		if((*(char*)p) != '\0'){
			vpchar((char)(*(char*)p),s);
		}
		else{
			break;
		}
		p++;
	}
} 
/*
 *
 * @函数名称: _print_X
 *
 * @函数功能: printf内联输出大写十六形式
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print_X(int num,int* s)
{
	int _FLAG = 28;
	int _BUF;
	vpchar('0',s);
	vpchar('x',s);
	if(num == 0x00){
		vpchar(0 + 48,s);
		vpchar(0 + 48,s);
	}else{
		while(1){
			_BUF = ((num >> _FLAG) & 0x0F);
			switch(_BUF){
				case 0: if(_FLAG & 0x80000000){vpchar(_BUF + 48,s);}break;
				case 10:vpchar('A',s);_FLAG = _FLAG | 0x80000000;break;
				case 11:vpchar('B',s);_FLAG = _FLAG | 0x80000000;break;
				case 12:vpchar('C',s);_FLAG = _FLAG | 0x80000000;break;
				case 13:vpchar('D',s);_FLAG = _FLAG | 0x80000000;break;
				case 14:vpchar('E',s);_FLAG = _FLAG | 0x80000000;break;
				case 15:vpchar('F',s);_FLAG = _FLAG | 0x80000000;break;
				default:vpchar(_BUF + 48,s);_FLAG = _FLAG | 0x80000000;break;
			}
			if((_FLAG & 0x7FFFFFFF) == 0){
				break;
			}
			_FLAG = _FLAG - 4;
		}
	}
}
/*
 *
 * @函数名称: _print_x
 *
 * @函数功能: printf内联输出小写十六形式
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print_x(int num,int* s)
{
	int _FLAG = 28;
	int _BUF;
	vpchar('0',s);
	vpchar('x',s);
	if(num == 0x00){
		vpchar(0 + 48,s);
		vpchar(0 + 48,s);
	}else{
		while(1){
			_BUF = ((num >> _FLAG) & 0x0F);
			switch(_BUF){
				case 0: if(_FLAG & 0x80000000){vpchar(_BUF + 48,s);}break;
				case 10:vpchar('a',s);_FLAG = _FLAG | 0x80000000;break;
				case 11:vpchar('b',s);_FLAG = _FLAG | 0x80000000;break;
				case 12:vpchar('c',s);_FLAG = _FLAG | 0x80000000;break;
				case 13:vpchar('d',s);_FLAG = _FLAG | 0x80000000;break;
				case 14:vpchar('e',s);_FLAG = _FLAG | 0x80000000;break;
				case 15:vpchar('f',s);_FLAG = _FLAG | 0x80000000;break;
				default:vpchar(_BUF + 48,s);_FLAG = _FLAG | 0x80000000;break;
			}
			if((_FLAG & 0x7FFFFFFF) == 0){
				break;
			}
			_FLAG = _FLAG - 4;
		}
	}
}
/*
 *
 * @函数名称: _print_o
 *
 * @函数功能: printf内联输出八进制
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
static void _print_o(int num,int* s)
{
	int _FLAG = 30;
	int _BUF;
	_BUF = (((num >> _FLAG) & 0x03));
	vpchar('0',s);
	if(_BUF > 0){
		vpchar(_BUF + 48,s);
		_FLAG = _FLAG | 0x80000000;
	}
	while(1){
		_BUF = ((num >> _FLAG) & 0x07);
		if(_BUF > 0 || (_FLAG & 0x80000000) > 0){
			vpchar(_BUF + 48,s);
			_FLAG = _FLAG | 0x80000000;
		}
		if((_FLAG & 0x7FFFFFFF) == 0){
			break;
		}
		_FLAG = _FLAG - 3;
	}
}
/*
 *
 * @函数名称: 无
 *
 * @函数功能: 无
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
/*static void _print_lu(unsigned int num)
{

}*/
/*
 *
 * @函数名称: _print_f
 *
 * @函数功能: print内联输出浮点数
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
/*static void _print_f(float num)
{
	int b = 0;
	int c = 0;
	int x = 0;
	int m = 10;
	for(x = 1; x < 7; x++){
		b = (unsigned int)(num * m);
		c = (c * 10) + (b % 10);
		m = m * 10;
	}
	m = m * 10;
	if((unsigned int)(num * m) % 10 > 4){
		c++;
	}
	while(1){
		if((c % 10) == 0){
			c = c / 10;
		}
		else{
			break;
		}
	}
	_print_d((int)num,0);
	vpchar('.');
	_print_num(c,0);
}*/
/*
 *
 * @函数名称: _print_f
 *
 * @函数功能: print内联输出双浮点数
 *
 * @输入参数: 无
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
	_print_d((int)numv,0,s);
	vpchar('.',s);
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
				_print_num(0,0,s);
			}
			break;
		}
	}
	
	_print_num(c,0,s);
	
	
}
/*
 *
 * @函数名称: print
 *
 * @函数功能: 格式打印函数
			print("hello");//打印hello
			控制字符
			print("%d",a);//将变量a以整型数据输出
			print("%f",a);//将变量a以浮点型数据输出
			print("%f",a);//将变量a以浮点型数据输出
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
	while(1)
	{
		switch(*_CONTROL){
			case '%':
						_CONTROL++;
						xprintc:
						switch(*_CONTROL){
							case 'd'://以十进制形式输出带符号整数(正数不输出符号)
									_print_d(*((int*)(_SP)),LeftValue,s1);
									_SP = _SP + 0x04;
									break;
							case 'u':
							case 'l'://输出32位无符号整数
									if(*(_CONTROL + 1) == 'u'){
										_CONTROL++;
										_print_num((*((unsigned int*)(_SP))),LeftValue,s1);
										_SP = _SP + 0x04;
									}
									else{
										vpchar((char)*_CONTROL,s1);
										break;
									}
									break;
							case 'p'://输出指针地址
									
									_print_num((int)(_SP),LeftValue,s1);
									_SP = _SP + 0x04;
									break;
							case 's'://输出字符串
									
									_vpchar(*((int*)(_SP)),s1);
									_SP = _SP + 0x04;
									break;
							case 'c'://输出单个字符
									
									vpchar((char)(*((int*)(_SP))),s1);
									_SP = _SP + 0x04;
									break;
							case 'X'://以十六进制大写形式输出无符号整数(输出前缀0x)
									
									_print_X(*((int*)(_SP)),s1);
									_SP = _SP + 0x04;
									break;
							case 'x'://以十六进制小写形式输出无符号整数(输出前缀0x)
									
									_print_x(*((int*)(_SP)),s1);
									_SP = _SP + 0x04;
									break;
							case 'o'://以八进制形式输出无符号整数(输出前缀0)
									
									_print_o(*((int*)(_SP)),s1);
									_SP = _SP + 0x04;
									break;
							case 'f'://输出双精度浮点
									if((_SP % 8) != 0){
										_SP = _SP + 0x04;
									}
									_print_lf((double*)(_SP),RightValue,s1);
									_SP = _SP + 0x08;
									break;
							case '.':
									_CONTROL++;
									RightValue = 0;
									while(*_CONTROL >= '0' && *_CONTROL <= '9'){
										RightValue = (RightValue * 10) + *_CONTROL - '0';
										_CONTROL++;
									}
									goto xprintc;
							default:
									if(*_CONTROL >= '0' && *_CONTROL <= '9'){
										LeftValue = 0;
										while(*_CONTROL >= '0' && *_CONTROL <= '9'){
											LeftValue = (LeftValue * 10) + *_CONTROL - '0';
											_CONTROL++;
										}
										if(*_CONTROL == '.'){
											_CONTROL++;
											RightValue = 0;
											while(*_CONTROL >= '0' && *_CONTROL <= '9'){
												RightValue = (RightValue * 10) + *_CONTROL - '0';
												_CONTROL++;
											}
											goto xprintc;
										}else{
											goto xprintc;
										}
									}else{
										vpchar((char)*_CONTROL,s1);
									}
									break;
								
						}
						break;
			case '\0'://结束符
						return;
			case '\n'://回车符
						vpchar('\n',s1);
						break;
			case '\b':
						break;
			case '\a':
						break;
			default:
						vpchar((char)*_CONTROL,s1);
						break;
		}
		_CONTROL++;
		LeftValue = 0;
		RightValue = 0;
	}
  
}
/*
 *
 * @函数名称: 无
 *
 * @函数功能: 无
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void tprint(const char* c,unsigned int s)
{
	while(1)
	{
		switch(*c){
			case '%':
					c++;
					switch(*c){
						case 'd':_print_d((s / 1000) /86400,0,0);break;//天			
						case 'h':_print_d(((s / 1000) /3600) % 24,0,0);break;//时
						case 'm':_print_d(((s / 1000) /60) % 60,0,0);break;//分
						case 's':_print_d((s / 1000) % 60,0,0);break;//秒
						case '%':vpchar('%',0);
					}
					break;
			case '\0':
					return;
			case '\n':
					vpchar('\n',0);
					break;
			default:
					vpchar((char)*c,0);
					break;
		}
		c++;
	}

}


__asm void print(const char* s,...)
{
	PRESERVE8
	extern  xprint
	
	PUSH	{R3}
	PUSH	{R2}
	PUSH	{R1}
	PUSH	{R0}
	MOV		R1,#0x00
	MOV		R0,SP
	PUSH 	{R4-R12,LR}
	LDR		R2,=xprint
    BLX     R2						//跳转到BX寄存器中所指向的值
	NOP
	NOP
	POP  	{R4-R12,LR}
	POP		{R0}
	POP		{R1}
	POP		{R2}
	POP		{R3}
	BX		LR
}
__asm void sprint(char* s,const char* c,...)
{
	PRESERVE8
	extern  xprint

	PUSH	{R3}
	PUSH	{R2}
	PUSH	{R1}
	PUSH	{R0}
	MOV		R1,#0x01
	MOV		R0,SP
	PUSH 	{R4-R12,LR}
	LDR		R2,=xprint
    BLX     R2						//跳转到BX寄存器中所指向的值
	NOP
	NOP
	POP  	{R4-R12,LR}
	POP		{R0}
	POP		{R1}
	POP		{R2}
	POP		{R3}
	BX		LR
}
	

