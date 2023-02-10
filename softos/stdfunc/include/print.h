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
 * @��������: vpchar
 *
 * @��������: pchar�������ϼ�����
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: 
 *
 */
static int vpchar(const char ch,int* s);
/*
 *
 * @��������: _print_num
 *
 * @��������: ����޷���ʮ������ֵ
 *
 * @�������: num	ʮ������ֵ
 * @�������: ctl	ǰ�������
 * @�������: s		spirnt����ָ��ش�
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
static void _print_num(unsigned int num,int ctl,int* s);
/*
 *
 * @��������: _print_d
 *
 * @��������: ����з���ʮ������ֵ
 *
 * @�������: num	ʮ������ֵ
 * @�������: ctl	ǰ�������
 * @�������: s		spirnt����ָ��ش�
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: 
 *
 */
static void _print_d(int num,int ctl,int* s);
/*
 *
 * @��������: _print_s
 *
 * @��������: ����ַ���
 *
 * @�������: p		�ַ�����ַ
 * @�������: s		spirnt����ָ��ش�
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: 
 *
 */
static void _print_s(int p,int* s);
/*
 *
 * @��������: _print_X
 *
 * @��������: �����д��ʮ��������
 *
 * @�������: num	ʮ��������ֵ
 * @�������: s		spirnt����ָ��ش�
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: 
 *
 */
static void _print16(int num,int c,int* s);
/*
 *
 * @��������: _print_o
 *
 * @��������: ����˽�����
 *
 * @�������: num	�˽�����ֵ
 * @�������: s		spirnt����ָ��ش�
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: 
 *
 */
static void _print8(int num,int* s);
/*
 *
 * @��������: _print_lu
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
static void _print_lu(unsigned int num,int* s);
/*
 *
 * @��������: _print_lf
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
static void _print_lf(double* num,char ctrl,int* s);
/*
 *
 * @��������: _pchar
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
static void _pchar(int p,int* s);
/*
 *
 * @��������: print
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
__asm void print(const char* s,...);
/*
 *
 * @��������: sprint
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
__asm void sprint(char* s,const char* c,...);
/*
 *
 * @��������: xprint
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
void xprint(int sp,int c);
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

