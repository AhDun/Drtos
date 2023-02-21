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
NVIC_PendSV   		EQU     0xE000ED04;PendSV�Ĵ�����ַ   
NVIC_PendSV_SET   	EQU     0x10000000;PendSV�Ĵ����ں�����ʹ��ֵ

    PRESERVE8
    THUMB

    AREA CODE, CODE, READONLY
	;PRESERVE8 
		
	;AREA    |.text|, CODE, READONLY
    ;THUMB 


; ��������: CPU_SVC
;
; ��������: ʹ�ں�SVC����
;
; �������: ��
;
; �������: ��
;
; ע    ��: ��

ISR_Touch1

    CPSIE   I   ;ʹ�������жϣ�����û�������жϽ��ᴥ��HardFault_Handler
	SVC		0   ;����SVC����
    BX      LR	;�˳���������ת��BX�Ĵ���������ĵ�ַ

; ��������: CPU_PendSV
;
; ��������: ʹ�ں�PendSV����
;
; �������: ��
;
; �������: ��
;
; ע    ��: ��
ISR_Touch

	PUSH    {R0,R1,LR}						;���������ж�
    LDR     R0,     =NVIC_PendSV 	;��PendSV�Ĵ����ĵ�ַ���ص�R0�Ĵ�����
    LDR     R1,     =NVIC_PendSV_SET;��PendSV�Ĵ����ں�����ʹ��ֵ���ص�R1�Ĵ�����
    STR     R1, [R0]				;��PendSV�Ĵ����ں�����ʹ��д��R0�Ĵ�����ָ��ĵ�ַ
	POP     {R0,R1,PC}
;    BX      LR						;��ת��LR�Ĵ�������ָ���ֵ

	NOP
	END




	