;
;                                                  FILE-START
;
; 文件名称: print.asm
;
; 文件内容: print函数与sprint跳转
;
; 文件版本: 1.0.0
;
; 文件作者: AhDun (mail: ahdunxx@163.com)
;
; 开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0
;
; 注    释: 无
;
;
;
;
;                                                  <声明区>
;
	IMPORT  xprint
;
;                                                  <全局标号>
;
	EXPORT  print
	EXPORT  sprint
;
;                                                  <常量标号定义>
;
;
;
;                                                  <代码区>
;
    PRESERVE8
    THUMB

    AREA CODE, CODE, READONLY
	;PRESERVE8 
		
	;AREA    |.text|, CODE, READONLY
    ;THUMB 
;
;
; 函数名称: CPU_PendSV_STATE
;
; 函数版本: 1.0.0
;
; 函数功能: 查询内核是否已经被悬起
;
; 输入参数: 无
;
; 输出参数: 无
;
; 注    释: 无
;
print
	PUSH	{R3}
	PUSH	{R2}
	PUSH	{R1}
	PUSH	{R0}
	MOV		R1,#0x00
	MOV		R0,SP
	PUSH 	{R4-R12,LR}
	LDR		R2,=xprint
    BLX     R2						;跳转到BX寄存器中所指向的值
	NOP
	NOP
	POP  	{R4-R12,LR}
	POP		{R0}
	POP		{R1}
	POP		{R2}
	POP		{R3}
	BX		LR
;
; 函数名称: CPU_PendSV
;
; 函数版本: 1.0.0
;
; 函数功能: 使内核PendSV悬起
;
; 输入参数: 无
;
; 输出参数: 无
;
; 注    释: 无
sprint
	PUSH	{R3}
	PUSH	{R2}
	PUSH	{R1}
	PUSH	{R0}
	MOV		R1,#0x01
	MOV		R0,SP
	PUSH 	{R4-R12,LR}
	LDR		R2,=xprint
    BLX     R2						;跳转到BX寄存器中所指向的值
	NOP
	NOP
	POP  	{R4-R12,LR}
	POP		{R0}
	POP		{R1}
	POP		{R2}
	POP		{R3}
	BX		LR


	END
;
;                                                 END
;



	


	