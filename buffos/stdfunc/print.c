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
 * @�������: ch	�ַ�
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
 * @��������: sprint�����ַ�����
 *
 * @�������: ch	�ַ�
 * @�������: s		sprint������������
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: �ú������������ض���
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
 * @��������: _printU10
 *
 * @�������: num	�޷���ʮ������
 * @�������: ctl	ǰ��0����
 * @�������: s		sprint������������
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
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
 * @��������: _printS10
 *
 * @��������: print��������з���ʮ������
 *
 * @�������: num	�з���ʮ������
 * @�������: ctl	ǰ��0����
 * @�������: s		sprint������������
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
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
 * @��������: _printSring
 *
 * @��������: print��������ַ���
 *
 * @�������: p		�ַ����׵�ַ
 * @�������: s		sprint������������
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
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
 * @��������: _print16
 *
 * @��������: printf�������ʮ����ʽ
 *
 * @�������: num	ʮ��������ֵ
 * @�������: c		ASCII����ʼֵ
 * @�������: s		sprint������������
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
 * @��������: _print8
 *
 * @��������: printf��������˽���
 *
 * @�������: num	�˽�����ֵ
 * @�������: s		sprint������������
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
 * @��������: _print_lf
 *
 * @��������: print�������˫���ȸ�����(64λ)
 *
 * @�������: num	˫���ȸ�����
 * @�������: s		sprint������������
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
 * @��������: xprint
 *
 * @��������: print�����Ӻ���
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
	for(;;)
	{
		switch(*_CONTROL){
			case '%':
						_CONTROL++;
						xprintc:
						switch(*_CONTROL){
							case 'd'://��ʮ������ʽ�������������(�������������)
									_printS10(*((int*)(_SP)),LeftValue,s1);
									_SP = _SP + 0x04;
									break;
							case 'l'://���32λ�޷�������
									if(*(_CONTROL + 1) != 'u'){
										_spchar((char)*_CONTROL,s1);
										break;
									}
							case 'u'://���32λ�޷�������
									_CONTROL++;
									_printU10((*((unsigned int*)(_SP))),LeftValue,s1);
									_SP = _SP + 0x04;
									break;									
							case 'p'://���ָ���ַ
									
									_printU10((int)(_SP),LeftValue,s1);
									_SP = _SP + 0x04;
									break;
							case 's'://����ַ���
									
									_printSring(*((int*)(_SP)),s1);
									_SP = _SP + 0x04;
									break;
							case 'c'://��������ַ�
									
									_spchar((char)(*((int*)(_SP))),s1);
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
							case '.'://��ֵ
									_CONTROL++;
									RightValue = 0;
									while(*_CONTROL >= '0' && *_CONTROL <= '9'){
										RightValue = (RightValue * 10) + *_CONTROL - '0';
										_CONTROL++;
									}
									goto xprintc;
							default:
									if(*_CONTROL >= '0' && *_CONTROL <= '9'){//��ֵ
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
			case '\0'://������
						return;
			case '\n'://�س���
						_spchar('\n',s1);
						break;
			case '\b'://�Զ���
						break;
			case '\a'://�Զ���
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




	

