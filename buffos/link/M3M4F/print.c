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


/*
                                                  变量初始化区
*/

///*
// *
// * @函数名称: pchar
// *
// * @函数功能: 输出接口
// *
// * @输入参数: ch	字符
// *
// * @返 回 值: 无
// *
// * @注    释: 该函数可以用于重定向
// *
// */
//int pchar(const char ch)
//{
////	USART_SendData(USART1,ch);//发送到串口
////	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
////	return (ch);
//}
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
static void _spchar(const char ch,int* s)
{
	if(s){//如果s传参不为零,就表明有输出地址
		*((char*)*s) = ch;//将字符写入到回流地址中
		*s = (int)*s + 1;//将回流地址向后移一位
	}
	else{
		pchar(ch);//直接输出
	}
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
void _printU10(unsigned int num,int ctl,int* s)
{
	int _FLAG = 100000000;//初始化第十位除数
	char _FLAG1 = 0;//用于表示前一位是否有输出
	if((num / 1000000000) % 10 > 0){//如果第十位数大于零,就输出第十位
		_spchar((char)(num / 1000000000) % 10 + 48,s);
		_FLAG1 = 1;//标记位曾输出数值
	}
	ctl = 9  - ctl;
	while(_FLAG > 1){
		if(((num / _FLAG) % 10) > 0 || _FLAG1 == 1 || ctl == 0){
			_spchar((char)((num / _FLAG) % 10) + 48,s);
			_FLAG1 = 1;//标记位曾输出数值
		}
		_FLAG /= 10;
		if(ctl > 0){
			ctl -= 1;
		}
	}
	_spchar(num % 10 + 48,s);//输出最后一位
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
	if(num < 0){//是否为负值
		num = (~num) + 1;//取绝对值
		_spchar('-',s);//输出负号
	}
	_printU10(num,ctl,s);//无使用号十进制数输出
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
void _printSring(int p,int* s)
{
	while(*(char*)p != '\0'){//遇到结束符时结束循环
		_spchar(*(char*)p++,s);//逐个输出字符
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
	char _Bit = 28;//初始化当前位数
	char _Flag = 0;//用于表示前一位是否有输出
	char _Buf;//用于数值缓存
	_spchar('0',s);//输出0
	_spchar('x',s);//输出x
	if(num == 0x00){//如果数值为零,直接输出00
		_spchar(0 + 48,s);//输出0
		_spchar(0 + 48,s);//输出0
	}else{
		for(;;){
			_Buf = ((num >> _Bit) & 0x0F);//取当前位数
			/*
				例如 num = 0x12345678
				num 右移28位并只取最后八位,得 0x12
			*/
			if(_Buf >= 10){//当数值大于等于十时
				_spchar(c + (_Buf - 10),s);
				_Flag = 1;//标记位曾输出数值
			}else if(_Buf > 0 || _Flag > 0){//当数值或前一位是有输出时才输出
				_spchar(_Buf + 48,s);
				_Flag = 1;//标记位曾输出数值
			}
			if(_Bit <= 0){//当前位数为零时,退出函数
				return;
			}
			_Bit -= 4;//位数减四
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
	char _Bit = 30;//初始化当前位数
	char _Flag = 0;//用于表示前一位是否有输出
	char _Buf;//用于数值缓存
	_Buf = ((num >> _Bit) & 0x03);//取当前位数
	_spchar('0',s);//输出0
	if(_Buf > 0){//
		_spchar(_Buf + 48,s);
		_Flag = 1;//标记位曾输出数值
	}
	for(;;){
		_Buf = ((num >> _Bit) & 0x07);//取当前位数
		/*
			例如 num = 02215053170
			num 右移30位并只取最后三位,得 02
		*/
		if(_Buf > 0 || _Flag > 0){
			_spchar(_Buf + 48,s);//当数值或前一位是有输出时才输出
			_Flag = 1;//标记位曾输出数值
		}
		if(_Bit <= 0){//当前位数为零时,退出函数
			return;
		}
		_Bit = _Bit - 3;//位数减三
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
	int _Value = 0;//
	int m;//倍数
	char _Count;//
	int _Zero = 0;//
	double _Buf;//浮点缓冲
	char p;//精度

	if(ctrl > 0){//如果对输出精度有要求
		p =  ctrl;//使用指定精度
	}else{//如果对输出精度有要求
		p = _print_lf_retain;//使用默认精度
	}

	_Buf = *num;
	m = 10;
	_printS10((int)_Buf,0,s);//输出整数部分
	_spchar('.',s);//输出小数点
	for(_Count = 1; _Count < (p + 1); _Count++){//将小数部分转换成整数
		/*
			例如: 1.2345 转换后为: 2345
		*/
		_Value = (_Value * 10) + ((unsigned int)(_Buf * m) % 10);
		if(_Value == 0){//如果为零,则记录下来
			_Zero = _Zero + 1;
		}
		m = m * 10;
	}
	for(_Count = 1; _Count < 20;_Count++){//检测小数部分是否为空值
		if((_Value % 10) == 0){//如果小数部分是空值,继续向后搜索
			_Value = _Value / 10;
		}else{//如果小数部分不是空值,就需要步零
			for(;_Zero > 0;_Zero--){
				_spchar('0',s);
			}
			break;
		}
	}
	
	_printU10(_Value,0,s);//输出小数部分
	
	
}
/*
 *
 * @函数名称: xprint
 *
 * @函数功能: print函数子函数
 *
 * @输入参数: s 回写地址
 * 			  con 控制字符串地址
 *			  sp 栈指针
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void xprint(int* s,char* con,int sp)
{	
	
	char LeftValue = 0;//左值,表示小数点前面的数值
	char RightValue = 0;//右值,表示小数点后面的数值

	for(;;)
	{
		switch(*con){
			case '%':
						con++;
						xprintc:
						switch(*con){
							case 'M'://切换控制字符
									con = (char*)*((int*)(sp));
									con --;
									sp = offsetCharp(sp);//指向下一个传参
									break;
							case 'd'://以十进制形式输出带符号整数(正数不输出符号)
									_printS10(*((int*)(sp)),LeftValue,s);
									sp = offsetUInt(sp);//指向下一个传参
									break;
							case 'l'://输出无符号整数
									if(*(con + 1) != 'u'){
										_spchar((char)*con,s);
										break;
									}
									con++;
							case 'u'://输出无符号整数
									_printU10((*((unsigned int*)(sp))),LeftValue,s);
									sp = offsetUInt(sp);//指向下一个传参
									break;									
							case 'p'://输出指针地址
									
									_printU10((int)(sp),LeftValue,s);
									sp = offsetIntp(sp);//指向下一个传参
									break;
							case 's'://输出字符串
									
									_printSring(*((int*)(sp)),s);
									sp = offsetCharp(sp);//指向下一个传参
									break;
							case 'c'://输出单个字符
									
									_spchar((char)(*((int*)(sp))),s);
									sp = offsetCharp(sp);//指向下一个传参
									break;
							case 'X'://以十六进制大写形式输出无符号整数(输出前缀0x)
									
									_print16(*((int*)(sp)),'A',s);
									sp = offsetUInt(sp);//指向下一个传参
									break;
							case 'x'://以十六进制小写形式输出无符号整数(输出前缀0x)
									
									_print16(*((int*)(sp)),'a',s);
									sp = offsetUInt(sp);//指向下一个传参
									break;
							case 'o'://以八进制形式输出无符号整数(输出前缀0)
									
									_print8(*((int*)(sp)),s);
									sp = offsetUInt(sp);//指向下一个传参
									break;
							case 'f'://输出双精度浮点
									if((sp % 8) != 0){//检查指针是否8位对齐,如果没有对齐将偏移
										sp = offsetUInt(sp);//指向下一个传参
									}
									_print_lf((double*)(sp),RightValue,s);
									sp = offsetDouble(sp);//指向下一个传参
									
									break;
							case '.'://右值
									con++;//向后移动,指向ASCII数字
									RightValue = 0;//清空右值
									while(*con >= '0' && *con <= '9'){//在ASCII数字范围
										RightValue = (RightValue * 10) + *con - '0';//将ASCII码的表示的数字转换成十进制
										con++;//向后
									}
									goto xprintc;//结束转换
							default:
									if(*con >= '0' && *con <= '9'){//左值
										LeftValue = 0;
										while(*con >= '0' && *con <= '9'){//在ASCII数字范围
											LeftValue = (LeftValue * 10) + *con - '0';//将ASCII码的表示的数字转换成十进制
											con++;//向后
										}
										goto xprintc;//结束转换
									}else{//非右值,进行输出
										_spchar((char)*con,s);//直接将字符打印
									}
									break;
								
						}
						break;
			case '\0'://结束符
						return;
			case '\n'://回车符
						_spchar('\n',s);
						break;
			case '\b'://自定义
						break;
			case '\a'://自定义
						break;
			default:  //其他情况
						_spchar((char)*con,s);//直接将字符打印
						break;
		}
		con++;//控制字符串指针后移
		LeftValue = 0;//清空左值
		RightValue = 0;//清空右值
	}
  
}




	

