/*
                                                  FILE-START
*/
/*

 *@�ļ�����: HDS_Intmac.h

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

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

signed char CharComp(signed char *strs,signed char *strc);
signed char StrComp(signed char *strs,signed char *strc);
signed char StrCutComp(signed char *strs,signed char *strc,signed char cutchar);
unsigned int StrLoca(signed char *strs,signed char locachar);


#endif

/*
                                                  FILE-END
*/


