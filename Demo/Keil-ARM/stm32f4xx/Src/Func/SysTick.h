/*
 *@文件名称: SysTick.h

 *@文件内容: 

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 
*/
/*
                                                  防重复编译宏配置区
*/
#ifndef _SysTick_H
#define _SysTick_H
/*
                                                  <引用文件区>
*/
#include "main.h"
/*
                                                  <宏定义区>
*/
/*----------------------------------函数---------------------------------------*/
#define SysTick_us_Init_Test_Flag_OK() SysTick_us_Init_Test_Flag = OK;

/*
                                                  <数据声明区>
*/
extern s8 SysTick_us_Init_Test_Flag;

/*
                                                  <函数声明区>
*/
s8 SysTick_us_Init(u8 SysCLK,u16 ms);
void SysTick_us(u32 us);
#endif
/*
                                                  FILE-END
*/

