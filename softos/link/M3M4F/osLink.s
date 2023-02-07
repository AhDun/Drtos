;
; Copyright (c) 2022-2023 AhDun
; 
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
; 
;     http://www.apache.org/licenses/LICENSE-2.0
; 
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.
; 
;


;	IMPORT  osTaskSwitch

;
	EXPORT  ISR_Touch
	EXPORT  ISR_Touch1
;
;
NVIC_PendSV   		EQU     0xE000ED04;PendSV寄存器地址   
NVIC_PendSV_SET   	EQU     0x10000000;PendSV寄存器内核悬起使能值

    PRESERVE8
    THUMB

    AREA CODE, CODE, READONLY
	;PRESERVE8 
		
	;AREA    |.text|, CODE, READONLY
    ;THUMB 


; 函数名称: CPU_SVC
;
; 函数功能: 使内核SVC悬起
;
; 输入参数: 无
;
; 输出参数: 无
;
; 注    释: 无

ISR_Touch1

    CPSIE   I   ;使能所有中断，如有没有启用中断将会触发HardFault_Handler
	SVC		0   ;触发SVC悬起
    BX      LR	;退出函数，跳转到BX寄存器中所存的地址

; 函数名称: CPU_PendSV
;
; 函数功能: 使内核PendSV悬起
;
; 输入参数: 无
;
; 输出参数: 无
;
; 注    释: 无
ISR_Touch

	PUSH    {R0,R1,LR}						;禁用所有中断
    LDR     R0,     =NVIC_PendSV 	;将PendSV寄存器的地址加载到R0寄存器中
    LDR     R1,     =NVIC_PendSV_SET;将PendSV寄存器内核悬起使能值加载到R1寄存器中
    STR     R1, [R0]				;将PendSV寄存器内核悬起使能写入R0寄存器所指向的地址
	POP     {R0,R1,PC}
;    BX      LR						;跳转到LR寄存器中所指向的值

	NOP
	END




	