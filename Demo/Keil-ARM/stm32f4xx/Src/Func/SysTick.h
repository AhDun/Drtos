/**
 * @file SysTick.h
 *
 * @brief 
 *
 * @note 
*/
/*
                                                  ���ظ������������
*/
#ifndef _SysTick_H
#define _SysTick_H

#include "main.h"

/*----------------------------------����---------------------------------------*/
#define SysTick_us_Init_Test_Flag_OK() SysTick_us_Init_Test_Flag = OK;


extern s8 SysTick_us_Init_Test_Flag;


s8 SysTick_us_Init(u8 SysCLK,u32 ms);
s8 SysTick_us_load(u8 SysCLK,u32 us);
void SysTick_us(u32 us);
#endif


