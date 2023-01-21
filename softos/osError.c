/*
                                                  FILE-START
*/
/*

 *@�ļ�����: .c

 *@�ļ�����: ϵͳ"������"�ļ�

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: ��

*/

/*
                                                  <�����ļ���>
*/

#include "main.h"
#include "osError.h"
#include "osMain.h"
#include "print.h"

/*
                                                  <���ݳ�ʼ��>
*/
/*
                                                  <������>
*/
/*

 *@��������: osError

 *@�����汾: 1.0.0

 *@��������: Ӳ���������쳣����

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
void osTaskError_HardFault(void)
{
	u8 _v1;
	for(_v1 = 0; _v1 < 3; _v1++){
		osErrorDebug("\n\n\nHardFault:����Ϊ%s����������Ӳ�������쳣!!!\n",RunTask_TIT -> TN,0);
		osErrorDebug("�������ȼ�:%d\n",RunTask_TIT -> TPL,0);
		osErrorDebug("����ǰʹ����:%d%%\n",RunTask_TIT -> TOR,0);
		osErrorDebug("������ʱʣ��ʱ��:%d%ms\n���񵥴��������ʱ��:%dms\n",RunTask_TIT -> TTF,RunTask_TIT -> TTW);
		osErrorDebug("������һ��״̬:",0,0);
		switch(RunTask_TIT -> TC){
			case Task_State_Up_TD:osErrorDebug("��Ƭ����\n",0,0);break;
			case Task_State_Up_IN:osErrorDebug("��������\n",0,0);break;
			case Task_State_Up_DT:osErrorDebug("��ʱ����\n",0,0);break;
			case Task_State_Up_SI:osErrorDebug("�źŹ���\n",0,0);break;
			case Task_State_Up_PT:osErrorDebug("�ʼ�����\n",0,0);break;
			case Task_State_DI:osErrorDebug("����̬\n",0,0);break;
			case Task_State_ST:osErrorDebug("��ֹ̬\n",0,0);break;
			case Task_State_RB:osErrorDebug("����̬\n",0,0);break;
			case Task_State_OP:osErrorDebug("����̬\n",0,0);break;
			case Task_State_Up:osErrorDebug("����̬\n",0,0);break;
		}
		osErrorDebug("��������״̬:",0,0);
		if(RunTask_TIT -> PF == NULL){
			osErrorDebug("�յ�\n",0,0);
		}
		else{
			osErrorDebug("�ǿ�\n",0,0);
		}
		osErrorDebug("����ջ�ܴ�С:%d�ֽ�\n����ջʣ��:%d�ֽ�\n",(RunTask_TIT -> TSS - 1),Read_PSP() - ((u32)RunTask_TIT -> TH - ((RunTask_TIT -> TSS - 1))));
		osErrorDebug("�����쳣��:%X\n",Read_PC(),0);
		osErrorDebug("�ڴ�����:%d�ֽ�\n�ڴ�����:%d�ֽ�",osMemoryGetAllValue(),osMemoryGetFreeValue());
	}
	osTaskSet(0,Task_Set_Pause);

	
}

/*
                                                  FILE-END
*/
