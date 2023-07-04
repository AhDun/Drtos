/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
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


/*
                                                  ������ʼ����
*/

///*
// *
// * @��������: pchar
// *
// * @��������: ����ӿ�
// *
// * @�������: ch	�ַ�
// *
// * @�� �� ֵ: ��
// *
// * @ע    ��: �ú������������ض���
// *
// */
//int pchar(const char ch)
//{
////	USART_SendData(USART1,ch);//���͵�����
////	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
////	return (ch);
//}
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
static void _spchar(const char ch,int* s)
{
	if(s){//���s���β�Ϊ��,�ͱ����������ַ
		*((char*)*s) = ch;//���ַ�д�뵽������ַ��
		*s = (int)*s + 1;//��������ַ�����һλ
	}
	else{
		pchar(ch);//ֱ�����
	}
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
void _printU10(unsigned long int num,int ctl,int* s)
{
	long int _FLAG = 100000000;//��ʼ����ʮλ����
	char _FLAG1 = 0;//���ڱ�ʾǰһλ�Ƿ������
	if((num / 1000000000) % 10 > 0){//�����ʮλ��������,�������ʮλ
		_spchar((char)(num / 1000000000) % 10 + 48,s);
		_FLAG1 = 1;//���λ�������ֵ
	}
	ctl = 9  - ctl;
	while(_FLAG > 1){
		if(((num / _FLAG) % 10) > 0 || _FLAG1 == 1 || ctl == 0){
			_spchar((char)((num / _FLAG) % 10) + 48,s);
			_FLAG1 = 1;//���λ�������ֵ
		}
		_FLAG /= 10;
		if(ctl > 0){
			ctl -= 1;
		}
	}
	_spchar(num % 10 + 48,s);//������һλ
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
static void _printS10(long int num,int ctl,int* s)
{

	if(num < 0){//�Ƿ�Ϊ��ֵ
		num = (~num) + 1;//ȡ����ֵ
		_spchar('-',s);//�������
	}
	_printU10(num,ctl,s);//��ʹ�ú�ʮ���������
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
void _printSring(long int p,int* s)
{
	while(*(char*)p != '\0'){//����������ʱ����ѭ��
		_spchar(*(char*)p++,s);//�������ַ�
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
static void _print16(long int num,int c,int* s)
{
	char _Bit = 28;//��ʼ����ǰλ��
	char _Flag = 0;//���ڱ�ʾǰһλ�Ƿ������
	char _Buf;//������ֵ����
	_spchar('0',s);//���0
	_spchar('x',s);//���x
	if(num == 0x00){//�����ֵΪ��,ֱ�����00
		_spchar(0 + 48,s);//���0
		_spchar(0 + 48,s);//���0
	}else{
		for(;;){
			_Buf = ((num >> _Bit) & 0x0F);//ȡ��ǰλ��
			/*
				���� num = 0x12345678
				num ����28λ��ֻȡ����λ,�� 0x12
			*/
			if(_Buf >= 10){//����ֵ���ڵ���ʮʱ
				_spchar(c + (_Buf - 10),s);
				_Flag = 1;//���λ�������ֵ
			}else if(_Buf > 0 || _Flag > 0){//����ֵ��ǰһλ�������ʱ�����
				_spchar(_Buf + 48,s);
				_Flag = 1;//���λ�������ֵ
			}
			if(_Bit <= 0){//��ǰλ��Ϊ��ʱ,�˳�����
				return;
			}
			_Bit -= 4;//λ������
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
static void _print8(long int num,int* s)
{
	char _Bit = 30;//��ʼ����ǰλ��
	char _Flag = 0;//���ڱ�ʾǰһλ�Ƿ������
	char _Buf;//������ֵ����
	_Buf = ((num >> _Bit) & 0x03);//ȡ��ǰλ��
	_spchar('0',s);//���0
	if(_Buf > 0){//
		_spchar(_Buf + 48,s);
		_Flag = 1;//���λ�������ֵ
	}
	for(;;){
		_Buf = ((num >> _Bit) & 0x07);//ȡ��ǰλ��
		/*
			���� num = 02215053170
			num ����30λ��ֻȡ�����λ,�� 02
		*/
		if(_Buf > 0 || _Flag > 0){
			_spchar(_Buf + 48,s);//����ֵ��ǰһλ�������ʱ�����
			_Flag = 1;//���λ�������ֵ
		}
		if(_Bit <= 0){//��ǰλ��Ϊ��ʱ,�˳�����
			return;
		}
		_Bit = _Bit - 3;//λ������
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
	int _Value = 0;//
	int m;//����
	char _Count;//
	int _Zero = 0;//
	double _Buf;//���㻺��
	char p;//����

	if(ctrl > 0){//��������������Ҫ��
		p =  ctrl;//ʹ��ָ������
	}else{//��������������Ҫ��
		p = _print_lf_retain;//ʹ��Ĭ�Ͼ���
	}

	_Buf = *num;
	m = 10;
	_printS10((int)_Buf,0,s);//�����������
	_spchar('.',s);//���С����
	for(_Count = 1; _Count < (p + 1); _Count++){//��С������ת��������
		/*
			����: 1.2345 ת����Ϊ: 2345
		*/
		_Value = (_Value * 10) + ((unsigned int)(_Buf * m) % 10);
		if(_Value == 0){//���Ϊ��,���¼����
			_Zero = _Zero + 1;
		}
		m = m * 10;
	}
	for(_Count = 1; _Count < 20;_Count++){//���С�������Ƿ�Ϊ��ֵ
		if((_Value % 10) == 0){//���С�������ǿ�ֵ,�����������
			_Value = _Value / 10;
		}else{//���С�����ֲ��ǿ�ֵ,����Ҫ����
			for(;_Zero > 0;_Zero--){
				_spchar('0',s);
			}
			break;
		}
	}
	
	_printU10(_Value,0,s);//���С������
	
	
}
/*
 *
 * @��������: xprint
 *
 * @��������: print�����Ӻ���
 *
 * @�������: s ��д��ַ
 * 			  con �����ַ�����ַ
 *			  sp ջָ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void xprint(int* s,char* con,int sp)
{	
	
	char LeftValue = 0;//��ֵ,��ʾС����ǰ�����ֵ
	char RightValue = 0;//��ֵ,��ʾС����������ֵ

	for(;;)
	{
		switch(*con){
			case '%':
						con++;
						sp -= 2;
						xprintc:
						switch(*con){
							case 'M'://�л������ַ�
									con = (char*)*((int*)(sp));
									con --;
									sp = offsetCharp(sp);//ָ����һ������
									break;
							case 'd'://��ʮ������ʽ�������������(�������������)
									_printS10((*((long int*)(sp))) & 0x0000FFFF,LeftValue,s);
									sp = offsetUInt(sp);//ָ����һ������
									break;
							case 'l'://����޷�������
									if(*(con + 1) != 'u'){
										_spchar((char)*con,s);
										break;
									}
									con++;
							case 'u'://����޷�������
									_printU10((*((unsigned long int*)(sp))),LeftValue,s);
									sp = offsetUInt(sp);//ָ����һ������
									break;									
							case 'p'://���ָ���ַ
									_printU10((long int)(sp),LeftValue,s);
									sp = offsetIntp(sp);//ָ����һ������
									break;
							case 's'://����ַ���
									_printSring(*((long int*)(sp)),s);
									sp = offsetCharp(sp);//ָ����һ������
									break;
							case 'c'://��������ַ�
									_spchar((char)(*((long int*)(sp))),s);
									sp = offsetCharp(sp);//ָ����һ������
									break;
							case 'X'://��ʮ�����ƴ�д��ʽ����޷�������(���ǰ׺0x)
									_print16(*((long int*)(sp)),'A',s);
									sp = offsetUInt(sp);//ָ����һ������
									break;
							case 'x'://��ʮ������Сд��ʽ����޷�������(���ǰ׺0x)
									_print16(*((long int*)(sp)),'a',s);
									sp = offsetUInt(sp);//ָ����һ������
									break;
							case 'o'://�԰˽�����ʽ����޷�������(���ǰ׺0)
									_print8(*((long int*)(sp)),s);
									sp = offsetUInt(sp);//ָ����һ������
									break;
							case 'f'://���˫���ȸ���
									_print_lf((double*)(sp),RightValue,s);
									sp = offsetUInt(sp);//ָ����һ������
									break;
							case '.'://��ֵ
									con++;//����ƶ�,ָ��ASCII����
									RightValue = 0;//�����ֵ
									while(*con >= '0' && *con <= '9'){//��ASCII���ַ�Χ
										RightValue = (RightValue * 10) + *con - '0';//��ASCII��ı�ʾ������ת����ʮ����
										con++;//���
									}
									goto xprintc;//����ת��
							default:
									if(*con >= '0' && *con <= '9'){//��ֵ
										LeftValue = 0;
										while(*con >= '0' && *con <= '9'){//��ASCII���ַ�Χ
											LeftValue = (LeftValue * 10) + *con - '0';//��ASCII��ı�ʾ������ת����ʮ����
											con++;//���
										}
										goto xprintc;//����ת��
									}else{//����ֵ,�������
										_spchar((char)*con,s);//ֱ�ӽ��ַ���ӡ
									}
									break;
								
						}
						break;
			case '\0'://������
						return;
			case '\n'://�س���
						_spchar('\n',s);
						break;
			case '\b'://�Զ���
						break;
			case '\a'://�Զ���
						break;
			default:  //�������
						_spchar((char)*con,s);//ֱ�ӽ��ַ���ӡ
						break;
		}
		con++;//�����ַ���ָ�����
		LeftValue = 0;//�����ֵ
		RightValue = 0;//�����ֵ
	}
  
}




	

