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

//#define xPSR_INIT_VALUE 0x01000000//xPSR寄存器初始化变量
//#if (osTaskUseStack_Config > 0)
//#if (osFPU_Config > 0) //启用了FPU
//#define LR_INIT_VALUE 0xFFFFFFED//xPSR寄存器初始化变量
//#else
//#define LR_INIT_VALUE 0xFFFFFFFD//xPSR寄存器初始化变量
//#endif
//#else
//#if (osFPU_Config > 0) //启用了FPU
//#define LR_INIT_VALUE 0xFFFFFFE9//xPSR寄存器初始化变量
//#else
//#define LR_INIT_VALUE 0xFFFFFFF9//xPSR寄存器初始化变量
//#endif
//#endif




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
//void osLinkISRDisable(void);
#define osLinkISRDisable() 	EA = 0
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
//void osLinkISREnable(void);
#define osLinkISREnable() 	EA = 1
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
void osLinkUseEnable(void);
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
//void ISR_Touch(void);
#define ISR_Touch() IE0 = 1
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
 * @name print
 *
 * @brief 与printf函数一致
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void print(const char* c,...);
/**
 *
 * @name sprint
 *
 * @brief 与sprintf函数一致
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void sprint(char* s,const char* c,...);





#endif



