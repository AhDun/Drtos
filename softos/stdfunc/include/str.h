/*
                                                  FILE-START
*/
/*

 *@�ļ�����: HDS_Intmac.h

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע   ��: ��

*/
#ifndef _HDS_Intmac_H_
#define _HDS_Intmac_H_

/*
                                                  <�����ļ���>
*/


/*
                                                  <�궨����>
*/

#include "main.h"
/*

 *@��������: osWordComp

 *@�����汾: 1.0.0

 *@��������: �ַ��Ƚ�

 *@�������: 	1.strs		-ԭ�ַ�
				2.strc		-�Ƚ��ַ�
	
 *@�� �� ֵ: 	true		-��ͬ
				false		-����ͬ

 *@ע    ��: ��

*/
signed char CharComp(signed char *strs,signed char *strc);

/*

 *@��������: osStrComp

 *@�����汾: 1.0.0

 *@��������: �ַ����Ƚ�

 *@�������: s8 *strs(ԭ�ַ���),s8 *strc(�Ƚ��ַ���)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/

signed char StrComp(signed char *strs,signed char *strc);
/*

 *@��������: osStrComp

 *@�����汾: 1.0.0

 *@��������: �ַ����Ƚ�

 *@�������: s8 *strs(ԭ�ַ���),s8 *strc(�Ƚ��ַ���)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
signed char StrCutComp(signed char *strs,signed char *strc,signed char cutchar);
/*

 *@��������: osStrCutComp

 *@�����汾: 1.0.0

 *@��������: ��ֹʽ�Ƚ��ַ���

 *@�������: s8 *strs(ԭ�ַ���),s8 *strc(�Ƚ��ַ���),s8 cutchar(��ֹ�ַ�)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
unsigned int StrLoca(signed char *strs,signed char locachar);


#endif

/*
                                                  FILE-END
*/


