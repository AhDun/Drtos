/* *
 * @文件名称: SysTick.h
 *
 * @文件内容: 
 *
 * @注    释: 
*/
/*
                                                  防重复编译宏配置区
*/
#ifndef _SysTick_H
#define _SysTick_H

#include "main.h"

/*----------------------------------函数---------------------------------------*/
#define SysTick_us_Init_Test_Flag_OK() SysTick_us_Init_Test_Flag = OK;


extern s8 SysTick_us_Init_Test_Flag;


s8 SysTick_us_Init(u8 SysCLK,u32 ms);
void SysTick_us(u32 us);
#endif


