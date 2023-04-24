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
/*
 *
 * @文件名称: osLink.c
 *
 * @文件内容: 链接(衔接)文件
 *
 * @注    释: 
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

/*
 *
 * @函数名称: osLinkTaskStackInit
 *
 * @函数功能: 任务栈初始化
 *
 * @输入参数: uint32_t tta(任务传参) ,uint32_t *tsa(任务开始地址),uint32_t *eca(任务结束回调地址),uint32_t *tsas(任务栈地址)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osLinkTaskStackInit(uint32_t* tpp,uint32_t* tsa,uint32_t* eca,uint32_t* tsas)
						  //R0      ,R1      ,R2      ,R3
						  //C编译器函数各个传参对应的寄存器
{	

}
/*
 *
 * @函数名称: osLinkUseEnable
 *
 * @函数功能: 启用进程栈
 *
 * @输入参数: uint32_t *tsas(任务栈地址)
 *
 * @返 回 值: 无
 *
 * @注   释: 无
 *
 */
void osLinkUseEnable(void)
{

}


 
/*
 *
 * @函数名称: PendSV_Handler
 *
 * @函数功能: 启动第一个任务
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注   释: 无
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
	__asm   { PUSH  DR56    }               
    __asm   { PUSH  DR28    }               
    __asm   { PUSH  DR24    }               
    __asm   { PUSH  DR20    }               
    __asm   { PUSH  DR16    }               
    __asm   { PUSH  DR12    }               
    __asm   { PUSH  DR8     }               
    __asm   { PUSH  DR4     }               
    __asm   { PUSH  DR0     }               
    __asm   { PUSH  PSW     }
    __asm   { MOV   DR0,DR60}           
    __asm   { MOV   DR4,OsTaskRunTaskHandle}   
    __asm   { MOV   @WR6,WR2} 
	__asm   { SETB  EA    } 
	osTaskNext(); 
	__asm   { CLR	EA      }
	__asm   { MOV   DR4,OsTaskRunTaskHandle}   
    __asm   { MOV   WR2,@WR6    }   
    __asm   { XRL   WR0,WR0     }           
    __asm   { MOV   DR60,DR0    }           
	__asm   { POP   PSW     }               
    __asm   { POP   DR0     }               
    __asm   { POP   DR4     }               
    __asm   { POP   DR8     }               
    __asm   { POP   DR12    }               
    __asm   { POP   DR16    }               
    __asm   { POP   DR20    }               
    __asm   { POP   DR24    }               
    __asm   { POP   DR28    }               
    __asm   { POP   DR56    }  
    __asm   { SETB  EA    	} 
	OsTaskRunTaskHandle;
}

#endif

int pchar(const char ch)
{
	SBUF = ch;
	while(!TI);
	TI = 0;
	return (ch);
}

/*
 *
 * @函数名称: print
 *
 * @函数功能: print函数入口
 *
 * @输入参数: c 控制字符串
 *			  ... 其他传参
 *
 * @返 回 值: 无
 *
 * @注   释: 无
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
/*
 *
 * @函数名称: sprint
 *
 * @函数功能: sprint函数入口
 *
 * @输入参数: s 输出地址
 *  		  c 控制字符串
 *			  ... 其他传参
 *
 * @返 回 值: 无
 *
 * @注   释: 无
 *
 */

void sprint(char* s,const char* c,...)
{
	
}



