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
 * @�ļ�����: str.c
 *
 * @�ļ�����: �ַ���
 *
 * @ע    ��: ��
 *
 */



#include "str.h"

/*
 *
 * @��������: osWordComp
 *
 * @��������: �ַ��Ƚ�
 *
 * @�������: 	1.strs		-ԭ�ַ�
				2.strc		-�Ƚ��ַ�
	 *
 * @�� �� ֵ: 	true		-��ͬ
				false		-����ͬ
 *
 * @ע    ��: ��
 *
 */
signed char CharComp(signed char *strs,signed char *strc)
{
	if(*strs == *strc){
		return true;
	}
	else{
		return false;
	}
}

/*
 *
 * @��������: osStrComp
 *
 * @��������: �ַ����Ƚ�
 *
 * @�������: int8_t *strs(ԭ�ַ���),int8_t *strc(�Ƚ��ַ���)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
signed char StrComp(signed char *strs,signed char *strc)
{
	for(;;){
		if(*strs != *strc){
			return false;
		}
		if(*strs == '\0'){
			return true;
		}
		strs++;
		strc++;
	}
}
/*
 *
 * @��������: osStrCutComp
 *
 * @��������: ��ֹʽ�Ƚ��ַ���
 *
 * @�������: int8_t *strs(ԭ�ַ���),int8_t *strc(�Ƚ��ַ���),int8_t cutchar(��ֹ�ַ�)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
signed char StrCutComp(signed char *strs,signed char *strc,signed char cutchar)
{
	for(;;){
		if(*strc == cutchar){
			return true;
		}
		if(*strs == '\0'){
			return true;
		}
		if(*strs != *strc){
			return false;
		}
		strs++;
		strc++;
	}
}
/*
 *
 * @��������: osStrLoca
 *
 * @��������: ���ַ�����λĳ���ַ���λ��
 *
 * @�������: int8_t *strs(�ַ���),int8_t locachar(�ַ�)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */

unsigned int StrLoca(signed char *strs,signed char locachar)
{
	unsigned int Locas = 0;
	for(;;){
		if(*strs == '\0'){
			return false;
		}
		if(*strs == locachar){
			return Locas;
		}
		strs++;
		Locas++;
	}
}
/*
 *
 * @��������: osStrLoca
 *
 * @��������: ���ַ�����λĳ���ַ���λ��
 *
 * @�������: int8_t *strs(�ַ���),int8_t locachar(�ַ�)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
unsigned int StrLength(signed char *strs)
{
	unsigned int Length = 0;
	for(;;){
		if(*strs == '\0'){
			return (Length);
		}else{
			Length++;
		}
	}
}

