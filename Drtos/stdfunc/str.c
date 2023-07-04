/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
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

