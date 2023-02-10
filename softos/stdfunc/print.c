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
 * @�ļ�����: print.c
 *
 * @�ļ�����: print��������printf�÷�����
 *
 * @ע    ��: ��
 *
 */


#include "main.h"
#include "print.h"
#include "usart.h"	

/*
                                                  ������ʼ����
*/

/*
 *
 * @��������: pchar
 *
 * @��������: ����ӿ�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: �ú������������ض���
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
 * @��������: pchar
 *
 * @��������: ����ӿ�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: �ú������������ض���
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
 * @��������: _print_num
 *
 * @��������: print�����������
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
static void _print_num(unsigned int num,int ctl,int* s)
{
	int _FLAG = 100000000;
	char _FLAG1 = 0;
	if((num / 1000000000) % 10 > 0){
		vpchar((char)(num / 1000000000) % 10 + 48,s);
		_FLAG1 = 1;
	}
	ctl = 10  - ctl;
	while(_FLAG > 1){
		if(((num / _FLAG) % 10) > 0 || _FLAG1 == 1 || ctl == 0){
			vpchar((char)((num / _FLAG) % 10) + 48,s);
			_FLAG1 = 1;
		}
		_FLAG /= 10;
		if(ctl > 0){
			ctl -= 1;
		}
	}
	vpchar((num % 10) + 48,s);
}
/*
 *
 * @��������: _print_d
 *
 * @��������: print��������з�����������
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
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
 * @��������: _pchar
 *
 * @��������: print��������ַ�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
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
 * @��������: _print_x
 *
 * @��������: printf�������Сдʮ����ʽ
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
static void _print16(int num,int c,int* s)
{
	char _FLAG = 28;
	char _FLAG1 = 0;
	char _BUF;
	vpchar('0',s);
	vpchar('x',s);
	if(num == 0x00){
		vpchar(0 + 48,s);
		vpchar(0 + 48,s);
	}else{
		while(1){
			_BUF = ((num >> _FLAG) & 0x0F);
			if(_BUF > 0 || _FLAG1 > 0){
				vpchar(c + (_BUF - 10),s);
				_FLAG1 = 1;
			}
			else if(_BUF >= 10){
				vpchar(c + (_BUF - 10),s);
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
 * @��������: _print_o
 *
 * @��������: printf��������˽���
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
static void _print8(int num,int* s)
{
	char _FLAG = 30;
	char _FLAG1 = 0;
	char _BUF;
	_BUF = ((num >> _FLAG) & 0x03);
	vpchar('0',s);
	if(_BUF > 0){
		vpchar(_BUF + 48,s);
		_FLAG1 = 1;
	}
	while(1){
		_BUF = ((num >> _FLAG) & 0x07);
		if(_BUF > 0 || _FLAG1 > 0){
			vpchar(_BUF + 48,s);
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
 * @��������: _print_f
 *
 * @��������: print�������������
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
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
 * @��������: _print_f
 *
 * @��������: print�������˫������
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
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
				vpchar('0',s);
			}
			break;
		}
	}
	
	_print_num(c,0,s);
	
	
}
/*
 *
 * @��������: print
 *
 * @��������: ��ʽ��ӡ����
			print("hello");//��ӡhello
			�����ַ�
			print("%d",a);//������a�������������
			print("%f",a);//������a�Ը������������
			print("%f",a);//������a�Ը������������
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
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
							case 'd'://��ʮ������ʽ�������������(�������������)
									_print_d(*((int*)(_SP)),LeftValue,s1);
									_SP = _SP + 0x04;
									break;
							case 'l'://���32λ�޷�������
									if(*(_CONTROL + 1) != 'u'){
										vpchar((char)*_CONTROL,s1);
										break;
									}
							case 'u'://���32λ�޷�������
									_CONTROL++;
									_print_num((*((unsigned int*)(_SP))),LeftValue,s1);
									_SP = _SP + 0x04;
									break;									
							case 'p'://���ָ���ַ
									
									_print_num((int)(_SP),LeftValue,s1);
									_SP = _SP + 0x04;
									break;
							case 's'://����ַ���
									
									_vpchar(*((int*)(_SP)),s1);
									_SP = _SP + 0x04;
									break;
							case 'c'://��������ַ�
									
									vpchar((char)(*((int*)(_SP))),s1);
									_SP = _SP + 0x04;
									break;
							case 'X'://��ʮ�����ƴ�д��ʽ����޷�������(���ǰ׺0x)
									
									_print16(*((int*)(_SP)),'A',s1);
									_SP = _SP + 0x04;
									break;
							case 'x'://��ʮ������Сд��ʽ����޷�������(���ǰ׺0x)
									
									_print16(*((int*)(_SP)),'a',s1);
									_SP = _SP + 0x04;
									break;
							case 'o'://�԰˽�����ʽ����޷�������(���ǰ׺0)
									
									_print8(*((int*)(_SP)),s1);
									_SP = _SP + 0x04;
									break;
							case 'f'://���˫���ȸ���
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
			case '\0'://������
						return;
			case '\n'://�س���
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
 * @��������: ��
 *
 * @��������: ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
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
						case 'd':_print_d((s / 1000) /86400,0,0);break;//��			
						case 'h':_print_d(((s / 1000) /3600) % 24,0,0);break;//ʱ
						case 'm':_print_d(((s / 1000) /60) % 60,0,0);break;//��
						case 's':_print_d((s / 1000) % 60,0,0);break;//��
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



	

