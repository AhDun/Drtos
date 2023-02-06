;
;                                                  FILE-START
;
; �ļ�����: osCPUa.asm
;
; �ļ�����: ϵͳ"CPU�ں˲������"�ļ�
;
; �ļ��汾: 1.0.0
;
; �ļ�����: AhDun (mail: ahdunxx@163.com)
;
; ע    ��: ��
;
;
;
;
;                                                  <������>
;

;	IMPORT  osTaskSwitch
;
;                                                  <ȫ�ֱ��>
;
	EXPORT  CPU_PendSV
	EXPORT  CPU_SVC
;
;                                                  <������Ŷ���>
;
NVIC_PendSV   		EQU     0xE000ED04;PendSV�Ĵ�����ַ   
NVIC_PendSV_SET   	EQU     0x10000000;PendSV�Ĵ����ں�����ʹ��ֵ
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


CPU_SVC

    CPSIE   I   ;ʹ�������жϣ�����û�������жϽ��ᴥ��HardFault_Handler
	SVC		0   ;����SVC����
    BX      LR	;�˳���������ת��BX�Ĵ���������ĵ�ַ
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
;CPU_PendSV_STATE

	;LDR     R4,     =NVIC_PendSV	;��PendSV�Ĵ����ĵ�ַ���ص�R4�Ĵ�����
    ;NOP								;��ָ��,��������warning: A1581W����
    ;LDR     R4, [R4]				;��R4�Ĵ�����ֵ��Ϊָ��ȡֵ��R4��
    ;AND     R4, R4,#NVIC_PendSV_SET	;��R4�Ĵ�����ֵ��0x10000000������������
    ;BX      LR						;��ת��LR�Ĵ�������ָ���ֵ
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
CPU_PendSV

	PUSH    {R0,R1,LR}						;���������ж�
    LDR     R0,     =NVIC_PendSV 	;��PendSV�Ĵ����ĵ�ַ���ص�R0�Ĵ�����
    LDR     R1,     =NVIC_PendSV_SET;��PendSV�Ĵ����ں�����ʹ��ֵ���ص�R1�Ĵ�����
    STR     R1, [R0]				;��PendSV�Ĵ����ں�����ʹ��д��R0�Ĵ�����ָ��ĵ�ַ
	POP     {R0,R1,PC}
;    BX      LR						;��ת��LR�Ĵ�������ָ���ֵ







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



	