;
;                                                  FILE-START
;
; �ļ�����: print.asm
;
; �ļ�����: print������sprint��ת
;
; �ļ��汾: 1.0.0
;
; �ļ�����: AhDun (mail: ahdunxx@163.com)
;
; ��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0
;
; ע    ��: ��
;
;
;
;
;                                                  <������>
;
	IMPORT  xprint
;
;                                                  <ȫ�ֱ��>
;
	EXPORT  print
	EXPORT  sprint
;
;                                                  <������Ŷ���>
;
;
;
;                                                  <������>
;
    PRESERVE8
    THUMB

    AREA CODE, CODE, READONLY
	;PRESERVE8 
		
	;AREA    |.text|, CODE, READONLY
    ;THUMB 
;
;
; ��������: CPU_PendSV_STATE
;
; �����汾: 1.0.0
;
; ��������: ��ѯ�ں��Ƿ��Ѿ�������
;
; �������: ��
;
; �������: ��
;
; ע    ��: ��
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
    BLX     R2						;��ת��BX�Ĵ�������ָ���ֵ
	NOP
	NOP
	POP  	{R4-R12,LR}
	POP		{R0}
	POP		{R1}
	POP		{R2}
	POP		{R3}
	BX		LR
;
; ��������: CPU_PendSV
;
; �����汾: 1.0.0
;
; ��������: ʹ�ں�PendSV����
;
; �������: ��
;
; �������: ��
;
; ע    ��: ��
sprint
	PUSH	{R3}
	PUSH	{R2}
	PUSH	{R1}
	PUSH	{R0}
	MOV		R1,#0x01
	MOV		R0,SP
	PUSH 	{R4-R12,LR}
	LDR		R2,=xprint
    BLX     R2						;��ת��BX�Ĵ�������ָ���ֵ
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



	


	