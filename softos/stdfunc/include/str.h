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
 * @�ļ�����: HDS_Intmac.h
 *
 * @�ļ�����: ��
 *
 * @�ļ�����: AhDun (mail: ahdunxx@163.com)
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




