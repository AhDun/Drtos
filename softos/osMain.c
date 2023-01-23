/*
                                                  FILE-START
*/

/*

 *@�ļ�����: osMain.c

 *@�ļ�����: ϵͳ"��Ҫ"�ļ�

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: 

*/

/*
                                                  <�����ļ���>
*/
#include "osMain.h"


/*
                                                  <������>
*/

/*

 *@��������: osInit

 *@�����汾: 1.0.0

 *@��������: ϵͳ��ʼ��

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osInit(void)
{
	/*if(*/osIRQ_Init() /*== Error){//ϵͳ�жϳ�ʼ��
		return (Error)*/;//��������,���ش���
	/*}*/
	/*if(*/osDebug_Init()/* == Error){//ϵͳ���ڳ�ʼ��
		return (Error)*/;//��������,���ش���
	/*}*/
	if(osMemoryInit() == Error){
		#if (osMainDebug_Enable > 0)
		osMainDebug("�ڴ��ʼ������");
		#endif
		return (Error);//��������,���ش���
	}
	if(osPostInit() == Error){//�����ʼ��
		#if (osMainDebug_Enable > 0)
		osMainDebug("�����ʼ������");
		#endif
		return (Error);//��������,���ش���
	}
	if(osTaskInit() == Error){//����ϵͳ��ʼ��
		#if (osMainDebug_Enable > 0)
		osMainDebug("����ϵͳ��ʼ������");
		#endif
		return (Error);//��������,���ش���
	}
	if(osClockInit() == Error){//ϵͳʱ�ӳ�ʼ��
		#if (osMainDebug_Enable > 0)
		osMainDebug("ϵͳʱ�ӳ�ʼ������");
		#endif
		return (Error);//��������,���ش���
	} 
	osMainPrintInfo();
	osMainSpeedTest();
	return (OK);//��ʼ���ɹ�,����OK
}
/*

 *@��������: osPrintDebug

 *@�����汾: 1.0.0

 *@��������: ����Debug

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osMainPrintFunc(void)
{
	osMainDebugInfo("ϵͳ�������\n",0);
	osMainDebugInfo("������ [�ѱ���]\n",0);
	osMainDebugInfo("ʱ�� [�ѱ���]\n",0);
	#ifdef osSignal_Enable
		osMainDebugInfo("�ź��� \n",0);
		#ifdef osSignalMutual_Enable
		osMainDebugInfo("|-  �����ź���[�ѱ���]\n",0);
		#else
		osMainDebugInfo("|-  �����ź���[δ����]\n",0);
		#endif
		#ifdef osSignalBinary_Enable
		osMainDebugInfo("|-  ��ֵ�ź���[�ѱ���]\n",0);
		#else
		osMainDebugInfo("|-  ��ֵ�ź���[δ����]\n",0);
		#endif
		#ifdef osSignalCount_Enable
		osMainDebugInfo("|-  �����ź���[�ѱ���]\n",0);
		#else
		osMainDebugInfo("|-  �����ź���[δ����]\n",0);
		#endif
	#else
		osMainDebugInfo("�ź��� [δ����]\n",0);
	#endif
	#ifdef osMemory_Enable
	osMainDebugInfo("�ڴ���� [�ѱ���]\n",0);
	#else
		osMainDebugInfo("�ڴ���� [δ����]\n",0);
	#endif
	#ifdef osPost_Enable
	osMainDebugInfo("���� [�ѱ���]\n",0);
	#else
	osMainDebugInfo("���� [δ����]\n",0);
	#endif
	return (OK);
}
/*

 *@��������: osPrintDebug

 *@�����汾: 1.0.0

 *@��������: ����Debug

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osMainSpeedTest(void)
{
	u32 t0,t1;
	RunTask_TIT -> TC = Task_State_Up_IN;
	t0 = SysTick->VAL;
	osTaskSwitch_Enable();//���������л�
	t1 = SysTick->VAL;
	#if (osTaskUsePrint  > 0)
	TST.TSSU = (t0 - t1) / (osCPU_Freq / 8);
	#endif
	print("�����л��ٶȲ���\nt0=%d\nt1=%d\n�л��ٶ�=%fus\n",t0,t1,((t0 - t1) / (osCPU_Freq / 8))*1.0);
	return (OK);
}

/*
                                                  FILE-END
*/


