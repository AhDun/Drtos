/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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

#ifndef __osLink_H_
#define __osLink_H_

/**
 *
 * @file osCPU.h
 *
 * @brief 
 *
 * @note 
 *
 */



#include "main.h"


#define xPSR_INIT_VALUE 0x01000000//xPSR寄存器初始化变量
#if (osTaskUseStack_Config > 0)
#if (osFPU_Config > 0) //启用了FPU
#define LR_INIT_VALUE 0xFFFFFFED//xPSR寄存器初始化变量
#else
#define LR_INIT_VALUE 0xFFFFFFFD//xPSR寄存器初始化变量
#endif
#else
#if (osFPU_Config > 0) //启用了FPU
#define LR_INIT_VALUE 0xFFFFFFE9//xPSR寄存器初始化变量
#else
#define LR_INIT_VALUE 0xFFFFFFF9//xPSR寄存器初始化变量
#endif
#endif




/**
 *
 * @name osLinkISRDisable
 *
 * @brief 关闭所有中断
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void osLinkISRDisable(void);
/**
 *
 * @name osLinkISREnable
 *
 * @brief 开启所有中断
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void osLinkISREnable(void);
/**
 *
 * @name Jump
 *
 * @brief 跳转到指定位置
 *
 * @param addr 	地址
 *
 * @retval none
 *
 * @note none
 *
 */
void osLinkJump(uint32_t* addr);
/**
 *
 * @name osLinkTaskStackInit
 *
 * @brief 任务栈初始化
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void osLinkTaskStackInit(uint32_t* tpp,uint32_t* tsa,uint32_t* eca,uint32_t* tsas);
/**
 *
 * @name INTX_ENABLE
 *
 * @brief 开启所有中断
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
__asm void osLinkUseEnable(void);
/**
 *
 * @name ISR_Touch
 *
 * @brief 触发中断
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void ISR_Touch(void);
/**
 * 
 * @name ISR_Touch1
 *
 * @brief 触发中断
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void ISR_Touch1(void);
/**
 * 
 * @name osTaskErrorHardFault
 *
 * @brief 任务发生错误
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */

OsErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp);
/**
 * 
 * @name osTaskSpeedTest
 *
 * @brief 任务上下文切换速度测试
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */

OsErrorValue osTaskSpeedTest(void);

/**
 * 
 * @name osTaskMonitor
 *
 * @brief 任务监视器
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osTaskMonitor(void);


/**
 *
 * @name print
 *
 * @brief print函数入口
 *
 * @param c 控制字符串
 *			  ... 其他传参
 *
 * @retval none
 *
 * @note none
 *
 */


__asm void print(const char* c,...);
/**
 *
 * @name sprint
 *
 * @brief sprint函数入口
 *
 * @param s 输出地址
 *  		  c 控制字符串
 *			  ... 其他传参
 *
 * @retval none
 *
 * @note none
 *
 */

__asm void sprint(char* s,const char* c,...);



#endif



