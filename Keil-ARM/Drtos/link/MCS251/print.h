/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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

/**
 *
 * @file print.h
 *
 * @brief printϵ�к���
 *
 * @note none
 *
 */





#define _print_lf_retain	6 //С������
							  //�����ֵ�����˱���%f�����С�����λ


#define offsetUChar(a)  a - sizeof(unsigned char)
#define offsetChar(a)  a - sizeof(char)
#define offsetUInt(a)  a - sizeof(unsigned int)
#define offsetInt(a)  a - sizeof(signed int)
#define offsetFloat(a)  a - sizeof(float)
#define offsetDouble(a)  a - sizeof(double)

#define offsetUCharp(a)  a - sizeof(unsigned char*)
#define offsetCharp(a)  a - sizeof(char*)
#define offsetUIntp(a)  a - sizeof(unsigned int*)
#define offsetIntp(a)  a - sizeof(signed int*)
#define offsetFloatp(a)  a - sizeof(float*)
#define offsetDoublep(a)  a - sizeof(double*)






/**
 *
 * @name pchar
 *
 * @brief ����ӿ�
 *
 * @param ch	�ַ�
 *
 * @retval none
 *
 * @note �ú������������ض���
 *
 */
int pchar(const char ch);
/**
 *
 * @name pchar
 *
 * @brief sprint�����ַ�����
 *
 * @param ch	�ַ�
 * @param s		sprint������������
 *
 * @retval none
 *
 * @note �ú������������ض���
 *
 */
static void _spchar(const char ch,int* s);
/**
 *
 * @name _printU10
 *
 * @param num	�޷���ʮ������
 * @param ctl	ǰ��0����
 * @param s		sprint������������
 *
 * @retval none
 *
 * @note none
 *
 */
void _printU10(unsigned long int num,int ctl,int* s);
/**
 *
 * @name _printS10
 *
 * @brief print��������з���ʮ������
 *
 * @param num	�з���ʮ������
 * @param ctl	ǰ��0����
 * @param s		sprint������������
 *
 * @retval none
 *
 * @note none
 *
 */
static void _printS10(long int num,int ctl,int* s);
/**
 *
 * @name _printSring
 *
 * @brief print��������ַ���
 *
 * @param p		�ַ����׵�ַ
 * @param s		sprint������������
 *
 * @retval none
 *
 * @note none
 *
 */
void _printSring(long int p,int* s);
/**
 *
 * @name _print16
 *
 * @brief printf�������ʮ����ʽ
 *
 * @param num	ʮ��������ֵ
 * @param c		ASCII����ʼֵ
 * @param s		sprint������������
 *
 * @retval none
 *
 * @note none
 *
 */
static void _print16(long int num,int c,int* s);
/**
 *
 * @name _print8
 *
 * @brief printf��������˽���
 *
 * @param num	�˽�����ֵ
 * @param s		sprint������������
 *
 * @retval none
 *
 * @note none
 *
 */
static void _print8(long int num,int* s);
/**
 *
 * @name _print_lf
 *
 * @brief print�������˫���ȸ�����(64λ)
 *
 * @param num	˫���ȸ�����
 * @param s		sprint������������
 *
 * @retval none
 *
 * @note none
 *
 */
static void _print_lf(double* num,char ctrl,int* s);
/**
 *
 * @name xprint
 *
 * @brief print�����Ӻ���
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void xprint(int* s,char* con,int sp);








#endif

