/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
 */
/*
 *
 * @�ļ�����: HDS_Intmac.h
 *
 * @�ļ�����: ��
 *
 * @ע   ��: ��
 *
 */
#ifndef _HDS_Intmac_H_
#define _HDS_Intmac_H_






#include "main.h"
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
signed char CharComp(signed char *strs,signed char *strc);

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

signed char StrComp(signed char *strs,signed char *strc);
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
signed char StrCutComp(signed char *strs,signed char *strc,signed char cutchar);
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
unsigned int StrLoca(signed char *strs,signed char locachar);


#endif




