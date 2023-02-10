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
 * @�ļ�����: print.h
 *
 * @�ļ�����: printϵ�к���
 *
 * @ע   ��: ��
 *
 */





#define _print_lf_retain	6 //С������
							  //�����ֵ�����˱���%f�����С�����λ




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
int pchar(const char ch);
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
static int _spchar(const char ch,int* s);
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
static void _printU10(unsigned int num,int ctl,int* s);
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
static void _printS10(int num,int ctl,int* s);
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
static void _printSring(int p,int* s);
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
static void _print16(int num,int c,int* s);
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
static void _print8(int num,int* s);
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
static void _print_lf(double* num,char ctrl,int* s);
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
void xprint(int sp,int c);


/*
 *
 * @��������: print
 *
 * @��������: ��printf����һ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
__asm void print(const char* s,...);
/*
 *
 * @��������: sprint
 *
 * @��������: ��sprintf����һ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
__asm void sprint(char* s,const char* c,...);


/*
 *
 * @��������: tprint
 *
 * @��������: ����ӿ�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void tprint(const char* c,unsigned int s);



#endif

