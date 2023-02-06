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

#ifndef __osCPU_H_
#define __osCPU_H_

/*
 *
 * @文件名称: osCPU.h
 *
 * @文件内容: 
 *
 * @注    释: 
 *
 */



#include "main.h"



#define xPSR_INIT_VALUE 0x01000000//xPSR寄存器初始化变量
#if (osFPU_Enable > 0) //启用了FPU
#define LR_INIT_VALUE 0xFFFFFFED//xPSR寄存器初始化变量
#else
#define LR_INIT_VALUE 0xFFFFFFFD//xPSR寄存器初始化变量
#endif










/*
 *
 * @函数名称: INTX_DISABLE
 *
 * @函数功能: 关闭所有中断
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void INTX_DISABLE(void);
/*
 *
 * @函数名称: INTX_ENABLE
 *
 * @函数功能: 开启所有中断
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void INTX_ENABLE(void);
/*
 *
 * @函数名称: Jump
 *
 * @函数功能: 跳转到指定位置
 *
 * @输入参数: addr 	地址
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void Jump(uint32_t* addr);
/*
 *
 * @函数名称: INTX_ENABLE
 *
 * @函数功能: 开启所有中断
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osTASK_Stack_Init(uint32_t* tpp,uint32_t* tsa,uint32_t* eca,uint32_t* tsas);
/*
 *
 * @函数名称: INTX_ENABLE
 *
 * @函数功能: 开启所有中断
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osTASK_START(uint32_t* tsas);
/*
 *
 * @函数名称: 使内核SVC悬起
 *
 * @函数功能: CPU_PendSV
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void CPU_PendSV(void);
/*
 *
 * @函数名称: CPU_SVC
 *
 * @函数功能: 使内核SVC悬起
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void CPU_SVC(void);





#endif



