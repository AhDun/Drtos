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
 * @�ļ�����: osLink.c
 *
 * @�ļ�����: ����(�ν�)�ļ�
 *
 * @ע    ��: 
 *
 */


#include "osConfig.h"
#include "osLink.h"

/*
                                                  ������ʼ����
*/



//const uint32_t NVIC_PendSV = 0xE000ED04;//PendSV
//const uint32_t NVIC_PendSV_SET = 0x10000000;


__asm void osLinkJump(uint32_t* addr)
{
	PUSH {R0}
	POP	{PC}
}

__asm void osLinkISRDisable(void)
{

	CPSID   I	//���������ж�
	BX      LR	//�˳���������ת��BX�Ĵ���������ĵ�ַ
}

__asm void osLinkISREnable(void)
{

	CPSIE   I	//���������ж�
	BX      LR  //�˳���������ת��BX�Ĵ���������ĵ�ַ
}

/*
 *
 * @��������: osLinkTaskStackInit
 *
 * @��������: ����ջ��ʼ��
 *
 * @�������: uint32_t tta(���񴫲�) ,uint32_t *tsa(����ʼ��ַ),uint32_t *eca(��������ص���ַ),uint32_t *tsas(����ջ��ַ)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
__asm void osLinkTaskStackInit(uint32_t* tpp,uint32_t* tsa,uint32_t* eca,uint32_t* tsas)
						  //R0      ,R1      ,R2      ,R3
						  //C�����������������ζ�Ӧ�ļĴ���
{	
	PUSH{R4-R5}

	MOV   R4,   SP//��SP�Ĵ������ݵ�R4�Ĵ�����
	LDR   SP,   [R3]//��R3�Ĵ����е�ֵ��Ϊָ�룬ȡֵ��SP�Ĵ�����
		
	#if (osFPU_Config > 0)//������FPU
	MOV   R5,   #0x00//��0x00����R5�Ĵ���
	PUSH  {R5}//FPSCR
	SUB   SP,    SP,#0x40//SP�Ĵ����е�ֵ��ȥ0x40

	#endif

	LDR    R5,   =xPSR_INIT_VALUE //xPSR�Ĵ�����ʼ���������ص�R5�Ĵ�����
	//|ָ��|�Ĵ���|��ջʱ���ڵļĴ���  
	PUSH   {R5}//xPSR(xPSR_INIT_VALUE)
	PUSH   {R1}//PC(����ʼ��ַ)
	PUSH   {R2}//LR(��������ص���ַ)
	MOV    R2,#0x00//��0x00ֵ���ص�R2�Ĵ�����
	PUSH   {R2}//R12(0x00)
	PUSH   {R2}//R3(0x00)
	PUSH   {R2}//R2(0x00)
	PUSH   {R2}//R1(0x00)
	PUSH   {R0}//R0(0x00)


	#if (osFPU_Config > 0)//������FPU
	SUB   SP,    SP,#0x40//SP�Ĵ����е�ֵ��ȥ0x40

	#endif

	LDR		R5,	=LR_INIT_VALUE
	PUSH   {R5}//R11
	MOV   R5,   #0x00//��0x00����R5�Ĵ���
	PUSH   {R5}//R4
	PUSH   {R5}//R5
	PUSH   {R5}//R6
	PUSH   {R5}//R7
	PUSH   {R5}//R8
	PUSH   {R5}//R9
	PUSH   {R5}//R10
	PUSH   {R5}//R11


	STR	  SP,	[R3]
	MOV   SP,   R4//��R4�Ĵ����е�ֵ���ص�SP�Ĵ����У��ϰ벿�ֳ��򱸷ݵ�SPֵ
	POP{R4-R5}

	BX	  LR
}
/*
 *
 * @��������: osLinkUseEnable
 *
 * @��������: ���ý���ջ
 *
 * @�������: uint32_t *tsas(����ջ��ַ)
 *
 * @�� �� ֵ: ��
 *
 * @ע   ��: ��
 *
 */
__asm void osLinkUseEnable(void)
{
#if (osTaskUseStack_Config > 0)
  MOV	R1,	  SP
  MSR   PSP,  R1//ͨ��MSR���R0�Ĵ����е�����д��PSP������ջ���Ĵ�����
  LDR	R0,	  =osTaskGetRunTaskHandle()
  LDR	R0,	  [R0]
  LDR	R0,	  [R0]
  MSR   MSP,  R0//ͨ��MSR���R0�Ĵ����е�����д��PSP������ջ���Ĵ�����
 /*ʹ�ܽ���ջ{*/
  MRS	R0,		CONTROL//ͨ��MRS�����ȡ���ƼĴ�����R0�Ĵ���
  ORR	R0,		R0,#0x02//R0�Ĵ�����0x02���л����㣬ʹ��bit1λ ��1
  MSR	CONTROL,R0//��ͨ��MSR���R0�Ĵ����е�����д�ؿ��ƼĴ�����
  /*}*/
#endif
  BX    LR//�˳���������ת��BX�Ĵ���������ĵ�ַ
  NOP
}


/*
 *
 * @��������: HardFault_Handler
 *
 * @��������: ����������
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע   ��: ��
 *
 */
__asm void HardFault_Handler(void)
{
	extern osTaskErrorHardFault
	
	PUSH	{LR}

	MRS	  	R1,		PSP		//ͨ��MRS���PSP������ջ���Ĵ����е����ݶ���R1�Ĵ�����
	LDR		R0,		[R1,#0x14]
	MRS	  	R1,		PSP		//ͨ��MRS���PSP������ջ���Ĵ����е����ݶ���R1�Ĵ�����
	
	BL.W	osTaskErrorHardFault

	POP		{PC}
}
/*
 *
 * @��������: SysTick_Handler
 *
 * @��������: ϵͳʱ�����
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע   ��: ��
 *
 */
__asm void SysTick_Handler(void)
{
	extern osClockTimePulse
	
	PUSH	{LR}

	BL.W	osClockTimePulse

	POP		{PC}

	NOP
}
/*
 *
 * @��������: PendSV_Handler
 *
 * @��������: ������һ������
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע   ��: ��
 *
 */
#if (osTaskUseStack_Config > 0)
__asm void PendSV_Handler(void)
{
	PRESERVE8

	extern osTaskGetRunTaskHandle()
	extern osTaskNext

	CPSID   I			//���������ж�
 
	MRS	  R1,	PSP		//ͨ��MRS���PSP������ջ���Ĵ����е����ݶ���R1�Ĵ�����
#if (osFPU_Config > 0) //������FPU
    TST		LR, #0x10
    IT		EQ
    VSTMDBEQ R1!,{S16-S31}
#endif

    STMDB R1!,	{R4-R11,LR}	//ѹջR4-R11

	LDR   R0,	=osTaskGetRunTaskHandle()
	LDR	  R0,	[R0]
    STR   R1,   [R0]	
	

	CPSIE   I

	BL.W	osTaskNext

	CPSID   I			//���������ж�

	LDR   R0,	=osTaskGetRunTaskHandle()
	LDR	  R0,	[R0]
	LDR   R1,   [R0]	

	LDMIA R1! ,{R4-R11,LR}	//��ջR4-R11
#if (osFPU_Config > 0) //������FPU
	TST		LR, #0x10
    IT		EQ
    VLDMIAEQ R1!,{S16-S31}
#endif

	MSR   PSP,  R1		//ͨ��MSR���R0�Ĵ����е�����д��PSP������ջ���Ĵ�����

	CPSIE   I			//���������ж�
    BX	  LR
	NOP
#if (osFPU_Config > 0) //������FPU
	NOP
#endif
}
#else
__asm void PendSV_Handler(void)
{
	PRESERVE8

	extern osTaskGetRunTaskHandle()
	extern osTaskNext

	CPSID   I			//���������ж�
 
#if (osFPU_Config > 0) //������FPU
    TST		LR, #0x10
    IT		EQ
    VSTMDBEQ SP!,{S16-S31}
#endif

    STMDB SP!,	{R4-R11,LR}	//ѹջR4-R11

	LDR   R0,	=osTaskGetRunTaskHandle()
	LDR	  R0,	[R0]
    STR   SP,   [R0]	
	

	CPSIE   I

	BL.W	osTaskNext

	CPSID   I			//���������ж�

	LDR   R0,	=osTaskGetRunTaskHandle()
	LDR	  R0,	[R0]
	LDR   SP,   [R0]	

	LDMIA SP! ,{R4-R11,LR}	//��ջR4-R11
#if (osFPU_Config > 0) //������FPU
	TST		LR, #0x10
    IT		EQ
    VLDMIAEQ SP!,{S16-S31}
#endif

	CPSIE   I			//���������ж�
    BX	  LR
	NOP
	NOP
#if (osFPU_Config > 0) //������FPU
	NOP
#endif
}
#endif



OsErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp)
{
	#if (osTaskRunError_Config > 0)
	uint8_t Count = 1;
	osTaskEnterIRQ();
	while(Count--){
		#if (osTaskName_Config > 0)
		print("\n\n\n����Ϊ%s����������Ӳ�������쳣!!!\n",osTaskGetRunTaskHandle() -> Name);
		#endif
		print("�������ȼ�:%d\n",osTaskGetRunTaskHandle() -> Level);
		print("����ǰʹ����:%d%%\n",osTaskGetRunTaskHandle() -> OccupyRatio);
		print("������ʱʣ��ʱ��:%d%ms\n���񵥴��������ʱ��:%dms\n",osTaskGetRunTaskHandle() -> Delay,osTaskGetRunTaskHandle() -> Wheel);
		print("������һ��״̬:",0,0);
		switch(osTaskGetRunTaskHandle() -> Config){
			case Task_State_Up_DT:print("��ʱ����\n");break;
			case Task_State_Up_SI:print("�źŹ���\n");break;
			case Task_State_Up_PT:print("�ʼ�����\n");break;
			case Task_State_DI:print("����̬\n");break;
			case Task_State_ST:print("��ֹ̬\n");break;
			case Task_State_RB:print("����̬\n");break;
			case Task_State_OP:print("����̬\n");break;
			case Task_State_RE:print("����̬\n");break;
		}
		print("��������״̬:");
		if(osTaskGetRunTaskHandle() -> Arg1 == NULL){
			print("�յ�\n");
		}
		else{
			print("�ǿ�\n");
		}
		print("����ջ�ܴ�С:%d�ֽ�\n����ջʣ��:%d�ֽ�\n",(uint32_t)osTaskGetRunTaskHandle() -> Length - (uint32_t)osTaskGetRunTaskHandle() -  sizeof(_TaskHandle),psp - ((uint32_t)osTaskGetRunTaskHandle() +  sizeof(_TaskHandle)));
		print("�����쳣��:%X\n",pc);
		print("�ڴ�����:%d�ֽ�\n�ڴ�����:%d�ֽ�",osMemoryGetAllValue(),osMemoryGetFreeValue());
	}
	#endif
	#if (osTaskErrorSet == 1)
	osTaskSet(NULL,Task_Set_Reboot);
	#elif(osTaskErrorSet == 0)
	osTaskSet(NULL,Task_Set_Pause);
	#endif
	osTaskExitIRQ();
	return (OK);
}
/*
 *
 * @��������: osTaskSpeedTest
 *
 * @��������: �����л��ٶȲ���
 *
 * @�������: ��	
 *
 * @�� �� ֵ: -1:��������0: �����ɹ�
 *
 * @ע    ��: ��
 *
 */

OsErrorValue osTaskSpeedTest(void)
{
	uint32_t t0,t1;
	osTaskGetRunTaskHandle() -> Config = Task_State_RE;
	t0 = SysTick->VAL;
	osTaskSwitch();//���������л�
	t1 = SysTick->VAL;
	#if (osPerf_Config > 0)
	PerformanceStatistics.TSSU = (osCPU_Period*(t0 - t1)*8)/osCPU_Period_Times;
	#endif
	#if (osTaskLog_Config > 0)
	print("�����л��ٶȲ���: t0 %d - t1 %d = %d��ʱ������(%fus)\n",t0,t1,(t0 - t1)*8,(osCPU_Period*(t0 - t1)*8)/osCPU_Period_Times);
	#endif
	return (OK);
}

OsErrorValue osTaskMonitor(void)

{
	_TaskHandle* TaskHandleListBuf = osTaskGetTaskHandleListHead();;
	do{
		print("����<%s>ռ��ʱ��:%dms | �������ȼ�:%d | ����״̬:",TaskHandleListBuf -> Name,TaskHandleListBuf -> OccupyRatio,TaskHandleListBuf -> Level);
		if(TaskHandleListBuf != osTaskGetRunTaskHandle() || osTaskGetSwitchQueue()){
			switch(TaskHandleListBuf -> Config){
				case Task_State_Up_DT:print("��ʱ����\n");break;
				case Task_State_Up_SI:print("�źŹ���\n");break;
				case Task_State_Up_PT:print("�ʼ�����\n");break;
				case Task_State_DI:print("����̬\n");break;
				case Task_State_ST:print("��ֹ̬\n");break;
				case Task_State_RB:print("����̬\n");break;
				case Task_State_OP:print("����̬\n");break;
				case Task_State_RE:print("����̬\n");break;
			}
		}
		else{
			print("��������\n");
		}
		TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
	}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());

	
	print("CPU��ʹ����:%d%% = ���� %d%% + �ж�%d%% + ����%d%%\n",PerformanceStatistics.CTO + PerformanceStatistics.CISRO + PerformanceStatistics.CSO,PerformanceStatistics.CTO,PerformanceStatistics.CISRO,PerformanceStatistics.CSO);

	print("������ȴ���:%d | Ԥ�ƺ�ʱ:%fus(%fms)\n",PerformanceStatistics.TSCb,PerformanceStatistics.TSCb*PerformanceStatistics.TSSU,(PerformanceStatistics.TSCb*PerformanceStatistics.TSSU) / 1000);

	print("�ڴ� ����:%d�ֽ� | ����:%d�ֽ� | �ɷ���:%d�ֽ� | ����:%d\n",osMemoryGetAllValue(),osMemoryGetFreeValue(),osMemoryGetPassValue(),osMemorySum());
	print("ϵͳ������: %d�� %dСʱ %d���� %d��\n",osClockGetOsRTCD(),osClockGetOsRTCH(),osClockGetOsRTCM(),osClockGetOsRTCS());
	
	return (OK);
}




/*
 *
 * @��������: pchar
 *
 * @��������: ����ӿ�
 *
 * @�������: ch	�ַ�
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: �ú������������ض���
 *
 */
int pchar(const char ch)
{
	USART_SendData(USART1,ch);//���͵�����
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return (ch);
}

/*
 *
 * @��������: print
 *
 * @��������: print�������
 *
 * @�������: c �����ַ���
 *			  ... ��������
 *
 * @�� �� ֵ: ��
 *
 * @ע   ��: ��
 *
 */
__asm void print(const char* c,...)
{
	PRESERVE8
	extern  xprint
	
	PUSH	{R3}//������ѹ��ջ��
	PUSH	{R2}//������ѹ��ջ��
	PUSH	{R1}//������ѹ��ջ��
    MOV		R1,R0//�������ַ���ָ�봫��R1,�൱����xprint������con���� (�����ַ���ָ��)
	MOV		R2,SP//��ջָ�봫��R2,�൱����xprint������sp���� (ջָ��)
    MOV		R0,#0x00//��0x00����R0,�൱����xprint������s���� (��д��ַ)
	PUSH 	{LR}//ѹ�뷵�ص�ַ

	BL.W	xprint//����xprint����
					
	POP  	{LR}//�������ص�ַ
	ADD		SP,#0x0C//�ͷ�ջ
	BX		LR//����LR�Ĵ����еĵ�ַ,������һ������
}
/*
 *
 * @��������: sprint
 *
 * @��������: sprint�������
 *
 * @�������: s �����ַ
 *  		  c �����ַ���
 *			  ... ��������
 *
 * @�� �� ֵ: ��
 *
 * @ע   ��: ��
 *
 */

__asm void sprint(char* s,const char* c,...)
{
	PRESERVE8
	extern  xprint
	
	PUSH	{R3}//������ѹ��ջ��
	PUSH	{R2}//������ѹ��ջ��
	PUSH	{R0}//�������ַѹ��ջ��
	ADD		R2,SP,#0x04//��ջָ�봫��R2,�൱����xprint������sp���� (ջָ��)
	MOV		R0,SP//��ջָ�봫��R0,�൱����xprint������s���� (��д��ַ)
	PUSH 	{LR}//ѹ�뷵�ص�ַ

	BL.W	xprint//����xprint����
					
	POP  	{LR}//�������ص�ַ
	ADD		SP,#0x0C//�ͷ�ջ
	BX		LR//����LR�Ĵ����еĵ�ַ,������һ������
}



