/*
                                                  FILE-START
*/
/*

 *@�ļ�����: osCPU.c

 *@�ļ�����: ϵͳ"CPU�ں˲���"�ļ�

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע    ��: 

*/

/*
                                                  <�����ļ���>
*/
#include "osConfig.h"
#include "osCPU.h"



/*
                                                  ������ʼ����
*/

/*
                                                  <������>
*/

//const uint32_t NVIC_PendSV = 0xE000ED04;//PendSV
//const uint32_t NVIC_PendSV_SET = 0x10000000;


__asm void Jump(uint32_t* addr)
{
	PUSH {R0}
	POP	{PC}
}

/*

 *@��������: osTASK_Stack_Init

 *@�����汾: 1.0.0

 *@��������: ����ջ��ʼ��

 *@�������: uint32_t tta(���񴫲�) ,uint32_t *tsa(����ʼ��ַ),uint32_t *eca(��������ص���ַ),uint32_t *tsas(����ջ��ַ)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
__asm void osTASK_Stack_Init(uint32_t* tpp,uint32_t* tsa,uint32_t* eca,uint32_t* tsas)
						  //R0      ,R1      ,R2      ,R3
						  //C�����������������ζ�Ӧ�ļĴ���
{	
	PUSH{R4-R5}

	MOV   R4,   SP		//��SP�Ĵ������ݵ�R4�Ĵ�����
	LDR   SP,   [R3]		//��R3�Ĵ����е�ֵ��Ϊָ�룬ȡֵ��SP�Ĵ�����
		
	#if (osFPU_Enable > 0) //������FPU
	MOV   R5,   #0x00		//��0x00����R5�Ĵ���
	PUSH  {R5}			//FPSCR
	SUB   SP,    SP,#0x40	//SP�Ĵ����е�ֵ��ȥ0x40

	#endif

	LDR    R5,   =xPSR_INIT_VALUE //xPSR�Ĵ�����ʼ���������ص�R5�Ĵ�����
	//|ָ��|�Ĵ���|��ջʱ���ڵļĴ���  
	PUSH   {R5}  					//xPSR(xPSR_INIT_VALUE)
	PUSH   {R1}  					//PC(����ʼ��ַ)
	PUSH   {R2}  					//LR(��������ص���ַ)
	MOV    R2,#0x00				//��0x00ֵ���ص�R2�Ĵ�����
	PUSH   {R2}  	//R12(0x00)
	PUSH   {R2}  	//R3(0x00)
	PUSH   {R2}	//R2(0x00)
	PUSH   {R2}	//R1(0x00)
	PUSH   {R0}	//R0(0x00)


	#if (osFPU_Enable > 0) //������FPU
	SUB   SP,    SP,#0x40	//SP�Ĵ����е�ֵ��ȥ0x40

	#endif

	LDR		R5,	=LR_INIT_VALUE
	PUSH   {R5}//R11
	MOV   R5,   #0x00		//��0x00����R5�Ĵ���
	PUSH   {R5}//R4
	PUSH   {R5}//R5
	PUSH   {R5}//R6
	PUSH   {R5}//R7
	PUSH   {R5}//R8
	PUSH   {R5}//R9
	PUSH   {R5}//R10
	PUSH   {R5}//R11


	STR	  SP,	[R3]
	MOV   SP,   R4				//��R4�Ĵ����е�ֵ���ص�SP�Ĵ����У��ϰ벿�ֳ��򱸷ݵ�SPֵ
	POP{R4-R5}

	BX	  LR
}
/*

 *@��������: osTASK_FIRST_START

 *@�����汾: 1.0.0

 *@��������: ������һ������

 *@�������: uint32_t *tsas(����ջ��ַ)

 *@�� �� ֵ: ��

 *@ע   ��: ��

*/
__asm void osTASK_START(uint32_t* tsas)
								//R0
								//C�����������������ζ�Ӧ�ļĴ���
{
  MOV	R1,	  SP
  MSR   PSP,  R1		//ͨ��MSR���R0�Ĵ����е�����д��PSP������ջ���Ĵ�����
  LDR   R0,     [R0]	//��R3�Ĵ����е�ֵ��Ϊָ�룬ȡֵ��SP�Ĵ�����
  MSR   MSP,  R0		//ͨ��MSR���R0�Ĵ����е�����д��PSP������ջ���Ĵ�����
 /*ʹ�ܽ���ջ{*/
  MRS	R0,		CONTROL 	//ͨ��MRS�����ȡ���ƼĴ�����R0�Ĵ���
  ORR	R0,		R0,#0x02	//R0�Ĵ�����0x02���л����㣬ʹ��bit1λ ��1
  MSR	CONTROL,R0			//��ͨ��MSR���R0�Ĵ����е�����д�ؿ��ƼĴ�����
  /*}*/

  BX    LR	//�˳���������ת��BX�Ĵ���������ĵ�ַ
}



__asm void HardFault_Handler(void)
{
	extern osTaskErrorHardFault
	
	PUSH	{R4,LR}

	MRS	  	R1,		PSP		//ͨ��MRS���PSP������ջ���Ĵ����е����ݶ���R1�Ĵ�����
	LDR		R0,		[R1,#0x14]
	MRS	  	R1,		PSP		//ͨ��MRS���PSP������ջ���Ĵ����е����ݶ���R1�Ĵ�����
	
	BL.W	osTaskErrorHardFault

	POP		{R4,PC}
}

__asm void SysTick_Handler(void)
{
	extern osClockTimePulse
	
	PUSH	{R4,LR}

	BL.W	osClockTimePulse

	POP		{R4,PC}

	NOP
}

__asm void PendSV_Handler(void)
{
	PRESERVE8

	extern RunTaskHandle
	extern osTaskNext

	CPSID   I			//���������ж�
 
	MRS	  R1,	PSP		//ͨ��MRS���PSP������ջ���Ĵ����е����ݶ���R1�Ĵ�����
#if (osFPU_Enable > 0) //������FPU
    TST		LR, #0x10
    IT		EQ
    VSTMDBEQ R1!,{S16-S31}
#endif

    STMDB R1!,	{R4-R11,LR}	//ѹջR4-R11

	LDR   R0,	=RunTaskHandle
	LDR	  R0,	[R0]
    STR   R1,   [R0]	
	

	CPSIE   I

	BL.W	osTaskNext

	CPSID   I			//���������ж�

	LDR   R0,	=RunTaskHandle
	LDR	  R0,	[R0]
	LDR   R1,   [R0]	

	LDMIA R1! ,{R4-R11,LR}	//��ջR4-R11
#if (osFPU_Enable > 0) //������FPU
	TST		LR, #0x10
    IT		EQ
    VLDMIAEQ R1!,{S16-S31}
#endif

	MSR   PSP,  R1		//ͨ��MSR���R0�Ĵ����е�����д��PSP������ջ���Ĵ�����

	CPSIE   I			//���������ж�
    BX	  LR
	NOP
	NOP
}

/*
                                                  FILE-END
*/

