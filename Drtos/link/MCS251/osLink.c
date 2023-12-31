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
/**
 *
 * @file osLink.c
 *
 * @brief 链接(衔接)文件
 *
 * @note 
 *
 */


#include "osConfig.h"
#include "osLink.h"
#include "STC32G_UART.h"
#include "STC32G_Exti.h"
/*
                                                  变量初始化区
*/



//const uint32_t NVIC_PendSV = 0xE000ED04;//PendSV
//const uint32_t NVIC_PendSV_SET = 0x10000000;

//void ISR_Touch(void)
//{

//}

void osLinkJump(uint32_t* addr)
{
	__asm {LJMP	@WR2}
}

//void osLinkISRDisable(void)
//{

//}

//void osLinkISREnable(void)
//{


//}

/**
 *
 * @name osLinkTaskStackInit
 *
 * @brief 任务栈初始化
 *
 * @param uint32_t tta(任务传参) ,uint32_t *tsa(任务开始地址),uint32_t *eca(任务结束回调地址),uint32_t *tsas(任务栈地址)
 *
 * @retval none
 *
 * @note none
 *
 */
void osLinkTaskStackInit(uint32_t* tpp,uint32_t* tsa,uint32_t* eca,uint32_t* tsas)
{	
	__asm	{ MOV		DR8,DR60}
	__asm	{ MOV		DR12,DR60}
	__asm	{ SUB		DR12,#0x07}
	__asm	{ MOV		WR14,@DR12}
	__asm	{ ADD		WR14,#0x02}
	__asm	{ MOV		WR14,@WR14}
	__asm	{ MOV		DR60,DR12}


	__asm	{ MOV		DR12,DR8}
	__asm	{ SUB		DR12,#0x03}
	__asm	{ MOV		WR14,@DR12}
	__asm   { PUSH  	WR14}
	//__asm   { PUSH  	WR6}
		__asm	{PUSH		R6}
	__asm	{PUSH		R7}

	__asm   { PUSH     DR28 }
	__asm   { PUSH     DR24 }
	__asm   { PUSH     DR20 }
	__asm   { PUSH     DR16 }
	__asm   { PUSH     DR8 }
	__asm   { PUSH     DR4 }
	__asm   { PUSH     DR0 }
	__asm   { PUSH     PSW }
	__asm   { PUSH     DPH }
	__asm   { PUSH     DPL }

	__asm	{ MOV		DR12,DR8}
	__asm	{ SUB		DR12,#0x07}
	__asm	{ MOV		WR14,@DR12}
	__asm	{ ADD		WR14,#0x02}
	__asm	{ MOV		DR4,DR60}
	__asm	{ MOV		@WR14,WR6}

	__asm   { CLR	EA      }
	__asm   { MOV   DR4,#OsTaskRunTaskHandle}   
	__asm	{ ADD	WR6,#0x02}
    __asm   { MOV   WR6,@WR6    }
	__asm	{ ADD	WR6,#0x02}
	__asm   { MOV   WR2,@WR6    }
    __asm   { XRL   WR0,WR0     }           
    __asm   { MOV   DR60,DR0    }                                      
    __asm   { SETB  EA    	}

	#pragma asm
        POP      DPL                            ; WORD0(DR56)=DPTR
        POP      DPH                            ; WORD0(DR56)=DPTR
        POP      PSW
        POP      DR0
        POP      DR4
        POP      DR8
        POP      DR16
        POP      DR20
        POP      DR24
        POP      DR28
        RETI  
	#pragma endasm

	OsTaskRunTaskHandle;

	//__asm	{MOV	   DR60,DR8}
}
/**
 *
 * @name osLinkUseEnable
 *
 * @brief 启用进程栈
 *
 * @param uint32_t *tsas(任务栈地址)
 *
 * @retval none
 *
 * @note none
 *
 */
void osLinkUseEnable(void)
{

}



 
/**
 *
 * @name PendSV_Handler
 *
 * @brief 启动第一个任务
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
#if (osTaskUseStack_Config > 0)
void INT0_ISR_Handler (void) interrupt INT0_VECTOR		
{

}
#else
void INT0_ISR_Handler (void) interrupt INT0_VECTOR	
{
	__asm   { CLR	EA      }                   
    __asm   { MOV   DR0,DR60}           
    __asm   { MOV   DR4,#OsTaskRunTaskHandle}   
    __asm   { MOV   @WR6,WR2} 
	__asm   { SETB  EA    } 
	osTaskNext(); 
	__asm   { CLR	EA      }
	__asm   { MOV   DR4,#OsTaskRunTaskHandle}   
    __asm   { MOV   WR2,@WR6    }   
    __asm   { XRL   WR0,WR0     }           
    __asm   { MOV   DR60,DR0    }                                      
    __asm   { SETB  EA    	} 

	
}

#endif

int pchar(const char ch)
{
	SBUF = ch;
	while(!TI);
	TI = 0;
	return (ch);
}

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

//(int* s,char* con,int sp)
void print(const char* c,...)
{
	__asm {MOV DR4, DR0}
	__asm {MOV DR0, DR60}
	__asm {SUB DR0, #0x03}
	__asm {PUSH DR0}
	__asm {MOV DR0,#0x00}
	xprint();
	__asm {POP DR0}
}
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

void sprint(char* s,const char* c,...)
{
	
}



