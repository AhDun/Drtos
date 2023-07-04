/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
 */

#ifndef __osLink_H_
#define __osLink_H_

/*
 *
 * @�ļ�����: osCPU.h
 *
 * @�ļ�����: 
 *
 * @ע    ��: 
 *
 */



#include "main.h"

//#define xPSR_INIT_VALUE 0x01000000//xPSR�Ĵ�����ʼ������
//#if (osTaskUseStack_Config > 0)
//#if (osFPU_Config > 0) //������FPU
//#define LR_INIT_VALUE 0xFFFFFFED//xPSR�Ĵ�����ʼ������
//#else
//#define LR_INIT_VALUE 0xFFFFFFFD//xPSR�Ĵ�����ʼ������
//#endif
//#else
//#if (osFPU_Config > 0) //������FPU
//#define LR_INIT_VALUE 0xFFFFFFE9//xPSR�Ĵ�����ʼ������
//#else
//#define LR_INIT_VALUE 0xFFFFFFF9//xPSR�Ĵ�����ʼ������
//#endif
//#endif




/*
 *
 * @��������: osLinkISRDisable
 *
 * @��������: �ر������ж�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
//void osLinkISRDisable(void);
#define osLinkISRDisable() 	EA = 0
/*
 *
 * @��������: osLinkISREnable
 *
 * @��������: ���������ж�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
//void osLinkISREnable(void);
#define osLinkISREnable() 	EA = 1
/*
 *
 * @��������: Jump
 *
 * @��������: ��ת��ָ��λ��
 *
 * @�������: addr 	��ַ
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osLinkJump(uint32_t* addr);
/*
 *
 * @��������: osLinkTaskStackInit
 *
 * @��������: ����ջ��ʼ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osLinkTaskStackInit(uint32_t* tpp,uint32_t* tsa,uint32_t* eca,uint32_t* tsas);
/*
 *
 * @��������: INTX_ENABLE
 *
 * @��������: ���������ж�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osLinkUseEnable(void);
/*
 *
 * @��������: ISR_Touch
 *
 * @��������: �����ж�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
//void ISR_Touch(void);
#define ISR_Touch() IE0 = 1
/*
 * 
 * @��������: ISR_Touch1
 *
 * @��������: �����ж�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void ISR_Touch1(void);


/*
 *
 * @��������: print
 *
 * @��������: ��printf����һ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void print(const char* c,...);
/*
 *
 * @��������: sprint
 *
 * @��������: ��sprintf����һ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void sprint(char* s,const char* c,...);





#endif



