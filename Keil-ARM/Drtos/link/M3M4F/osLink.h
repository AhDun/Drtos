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


#define xPSR_INIT_VALUE 0x01000000//xPSR�Ĵ�����ʼ������
#if (osTaskUseStack_Config > 0)
#if (osFPU_Config > 0) //������FPU
#define LR_INIT_VALUE 0xFFFFFFED//xPSR�Ĵ�����ʼ������
#else
#define LR_INIT_VALUE 0xFFFFFFFD//xPSR�Ĵ�����ʼ������
#endif
#else
#if (osFPU_Config > 0) //������FPU
#define LR_INIT_VALUE 0xFFFFFFE9//xPSR�Ĵ�����ʼ������
#else
#define LR_INIT_VALUE 0xFFFFFFF9//xPSR�Ĵ�����ʼ������
#endif
#endif




/**
 *
 * @name osLinkISRDisable
 *
 * @brief �ر������ж�
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
 * @brief ���������ж�
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
 * @brief ��ת��ָ��λ��
 *
 * @param addr 	��ַ
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
 * @brief ����ջ��ʼ��
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
 * @brief ���������ж�
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
 * @brief �����ж�
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
 * @brief �����ж�
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
 * @brief ����������
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
 * @brief �����������л��ٶȲ���
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
 * @brief ���������
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
 * @brief print�������
 *
 * @param c �����ַ���
 *			  ... ��������
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
 * @brief sprint�������
 *
 * @param s �����ַ
 *  		  c �����ַ���
 *			  ... ��������
 *
 * @retval none
 *
 * @note none
 *
 */

__asm void sprint(char* s,const char* c,...);



#endif



