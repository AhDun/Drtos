/*
                                                  FILE-START
*/
/*

 *@�ļ�����: str.c

 *@�ļ�����: �ַ���

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע    ��: ��

*/


/*
                                                  <�����ļ���>
*/
#include "str.h"

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

 *@��������: osStrComp

 *@�����汾: 1.0.0

 *@��������: �ַ����Ƚ�

 *@�������: s8 *strs(ԭ�ַ���),s8 *strc(�Ƚ��ַ���)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
signed char StrComp(signed char *strs,signed char *strc)
{
	while(1){
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

 *@��������: osStrCutComp

 *@�����汾: 1.0.0

 *@��������: ��ֹʽ�Ƚ��ַ���

 *@�������: s8 *strs(ԭ�ַ���),s8 *strc(�Ƚ��ַ���),s8 cutchar(��ֹ�ַ�)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
signed char StrCutComp(signed char *strs,signed char *strc,signed char cutchar)
{
	while(1){
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

 *@��������: osStrLoca

 *@�����汾: 1.0.0

 *@��������: ���ַ�����λĳ���ַ���λ��

 *@�������: s8 *strs(�ַ���),s8 locachar(�ַ�)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/

unsigned int StrLoca(signed char *strs,signed char locachar)
{
	unsigned int Locas = 0;
	while(1){
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

 *@��������: osStrLoca

 *@�����汾: 1.0.0

 *@��������: ���ַ�����λĳ���ַ���λ��

 *@�������: s8 *strs(�ַ���),s8 locachar(�ַ�)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
unsigned int StrLength(signed char *strs)
{
	unsigned int Length = 0;
	while(1){
		if(*strs == '\0'){
			return (Length);
		}else{
			Length++;
		}
	}
}
/*
                                                  FILE-END
*/
