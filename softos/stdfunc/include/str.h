/*
                                                  FILE-START
*/
/*

 *@文件名称: HDS_Intmac.h

 *@文件内容: 无

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注   释: 无

*/
#ifndef _HDS_Intmac_H_
#define _HDS_Intmac_H_

/*
                                                  <引用文件区>
*/


/*
                                                  <宏定义区>
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


