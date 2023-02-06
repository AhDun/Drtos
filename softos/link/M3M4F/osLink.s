;
;                                                  FILE-START
;
; 文件名称: osCPUa.asm
;
; 文件内容: 系统"CPU内核操作汇编"文件
;
; 文件版本: 1.0.0
;
; 文件作者: AhDun (mail: ahdunxx@163.com)
;
; 注    释: 无
;
;
;
;
;                                                  <声明区>
;

;	IMPORT  osTaskSwitch
;
;                                                  <全局标号>
;
	EXPORT  CPU_PendSV
	EXPORT  CPU_SVC
;
;                                                  <常量标号定义>
;
NVIC_PendSV   		EQU     0xE000ED04;PendSV寄存器地址   
NVIC_PendSV_SET   	EQU     0x10000000;PendSV寄存器内核悬起使能值
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


CPU_SVC

    CPSIE   I   ;使能所有中断，如有没有启用中断将会触发HardFault_Handler
	SVC		0   ;触发SVC悬起
    BX      LR	;退出函数，跳转到BX寄存器中所存的地址
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
;CPU_PendSV_STATE

	;LDR     R4,     =NVIC_PendSV	;将PendSV寄存器的地址加载到R4寄存器中
    ;NOP								;空指令,作用屏蔽warning: A1581W警告
    ;LDR     R4, [R4]				;将R4寄存器的值做为指针取值到R4中
    ;AND     R4, R4,#NVIC_PendSV_SET	;将R4寄存器的值与0x10000000进行相与运算
    ;BX      LR						;跳转到LR寄存器中所指向的值
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
CPU_PendSV

	PUSH    {R0,R1,LR}						;禁用所有中断
    LDR     R0,     =NVIC_PendSV 	;将PendSV寄存器的地址加载到R0寄存器中
    LDR     R1,     =NVIC_PendSV_SET;将PendSV寄存器内核悬起使能值加载到R1寄存器中
    STR     R1, [R0]				;将PendSV寄存器内核悬起使能写入R0寄存器所指向的地址
	POP     {R0,R1,PC}
;    BX      LR						;跳转到LR寄存器中所指向的值







;PendSV_Handler
	

;	CPSID   I
;	LDR	  R0,	=UPTask_TRS
;	LDR   R0,   [R0]
;	MOV   R2,   SP
;	MRS	  R3,	  PSP
;	MOV   SP,   R3
;	TaskSwitchState		LR, #0x10
;	IT		EQ
;	VSTMDBEQ SP!,{S16-S31}
;	PUSH	{R4-R11}
;	STR   SP,   [R0]

;	LDR   R0,	=STTask_TRS
;	LDR   R0, [R0]
;	LDR   SP,   [R0]
;	POP 	{R4-R11}
;	TaskSwitchState		LR, #0x10
;	IT		EQ
;	VLDMIAEQ SP!, {S16-S31} 
;	MOV   R1,   SP
;	MSR   PSP,  R1
;	;STR   R1,   [R0]
;	MOV   SP,   R2
;	CPSIE   I
;	BX     LR
	NOP
	END
;
;                                                 END
;



	