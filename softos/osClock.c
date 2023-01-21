/*
                                                  FILE-START
*/
/*

 *@�ļ�����: osClock.c

 *@�ļ�����: ϵͳ"ʱ��"ϵ�ļ�

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: 

*/

/*
                                                  <�����ļ���>
*/
#include "osMain.h"
#include "osClock.h"

/*
                                                  ������ʼ����
*/
osTIME osTime;//ϵͳʱ��
/*
                                                  <������>
*/
/*

 *@��������: osClockInit

 *@�����汾: 1.0.0

 *@��������: ϵͳʱ�ӳ�ʼ��

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osClockInit(void)
{
	if(osClock_Init() == Error){//���ʱ�ӳ�ʼ������
		return (Error);//��ʾʱ�ӳ�ʼ��ʱ��������,���ش���
	}
	return (OK);//����OK
}
/*

 *@��������: osTime_Handler

 *@�����汾: 1.0.0

 *@��������: ϵͳʱ�Ӵ���

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
void osClockTimePulse(void)
{
	/*�����������ж���Ӧ����У���������������ĸ���*/
	u32 _tr0;//������ʼ��

	#if (osClockTimePeriod < osClockTimePeriodStandard) //
	if(++osTime.CTPV >= (osClockTimePeriodStandard /osClockTimePeriod))
	{
		osTime.CTPV = NULL;
	#endif
    /*----------------------------------��ʱ---------------------------------------*/
	#if (os_TotalSystemRunningTime_Enable > 0)//������ϵͳ����ʱ��
	#if (osClockTimePeriod > osClockTimePeriodStandard)
	osTime. TSRT = osTime. TSRT + (osClockTimePeriod / osClockTimePeriodStandard);//ϵͳ����ʱ�����м�ʱ
	#else
	osTime. TSRT = osTime. TSRT + 1;//ϵͳ����ʱ�����м�ʱ
	#endif
	#endif
     /*----------------------------------ͳ��---------------------------------------*/
	#if (osPerformanceStatistics_Enable > 0) //����������ͳ��
    if(TST.TSS == TaskSwitch_Ready){//�������״̬Ϊδ���ȣ����м�ʱ
        RunTask_TIT -> TOT++;//����ռ��ʱ������
    }
    if(osTime. TSRT % TaskOccupyRatioSamplingTime == 0){//ϵͳÿ��һ��ʱ�����ͽ���ռ�ñ���ͳ��
        CPUS.CO = 0;//CPUռ������Ϊ0
        for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//��ÿһ��������б���
            //TL[_tr0].TITA -> TOR = TL[_tr0].TITA -> TOT / (TaskOccupyRatioSamplingTime / 100);//�����������ռ�ñ�
			TL[_tr0].TITA -> TOR = TL[_tr0].TITA -> TOT;//�����������ռ�ñ�
			//���㹫ʽ��ռ�ñ� = ��λʱ���ڵ�ռ��ʱ�� / (��λʱ�� / 100)
            CPUS.CO = CPUS.CO + (TL[_tr0].TITA -> TOR / (TaskOccupyRatioSamplingTime / 100));//����CPUռ����
			//���㹫ʽ��CPUռ���� = CPUռ���� + ÿ�������ռ����
			#if (osTaskUsePrint  > 0)
			#if (osTaskUsePrintClock > 0)
			print("����<%s>��ʹ����Ϊ:ռ��ʱ��:%dms | �������ȼ�:%d | ����״̬:",TL[_tr0].TITA -> TN,TL[_tr0].TITA -> TOT,TL[_tr0].TITA -> TPL);
			if(TL[_tr0].TITA != RunTask_TIT || TST.TSS != TaskSwitch_Ready){
				switch(TL[_tr0].TITA -> TC){
					case Task_State_Up_TD:print("��Ƭ����\n");break;
					case Task_State_Up_IN:print("��������\n");break;
					case Task_State_Up_DT:print("��ʱ����\n");break;
					case Task_State_Up_SI:print("�źŹ���\n");break;
					case Task_State_Up_PT:print("�ʼ�����\n");break;
					case Task_State_DI:print("����̬\n");break;
					case Task_State_ST:print("��ֹ̬\n");break;
					case Task_State_RB:print("����̬\n");break;
					case Task_State_OP:print("����̬\n");break;
					case Task_State_Up:print("����̬\n");break;
				}
			}
			else{
				print("��������\n");
			}
			#endif
			#endif

            TL[_tr0].TITA -> TOT = 0;//��յ�λʱ���ڵ�ռ��ʱ��
        }
		#if (osTaskUsePrint  > 0)
		#if (osTaskUsePrintClock > 0)
		print("������ʹ����:%d%% | ",CPUS.CO);
		if(TST.TSC*TST.TSSU > 1000){
			print("������ȴ���:%d | Ԥ�ƺ�ʱ:%d.%dms\n",TST.TSC,TST.TSC*TST.TSSU / 1000,TST.TSC*TST.TSSU % 1000 / 100);
		}else{
			print("������ȴ���:%d | Ԥ�ƺ�ʱ:%dus\n",TST.TSC,TST.TSC*TST.TSSU);
		}
		TST.TSC = 0;
		print("�ڴ�����:%d�ֽ� | �ڴ�����:%d�ֽ� | �ɷ���:%d�ֽ�\n",osMemoryAllSize(),osMemoryMarginSize(),osMemoryMaxMallocValue());
		tprint("ϵͳ������: %d�� %hСʱ %m���� %s��\n",osTime. TSRT);
		#endif
		#endif
    }
	#endif
    /*----------------------------------��Ƭ---------------------------------------*/
    if(osTime.TTWM > 0 && TST.TSS == TaskSwitch_Ready){ //ʱ����Ƭ
	   //��ǰ�������е��������Ƭʱ�����0���ҵ���״̬Ϊδ����״̬
        osTime.TTWM--;//��ǰ�������е��������Ƭʱ���һ
        if(osTime.TTWM == 0){//��Ŀǰ�������е��������Ƭʱ��Ϊ��ʱ
            //RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//����������е������״̬λ
            RunTask_TIT -> TC = Task_State_Up_TD;//���������е������״̬��Ϊλ��Ƭ����(����̬)
            if(TST.TSS == TaskSwitch_Ready){//��ѯ�Ƿ񼺱��������û�оʹ��������л�
                osTaskSwitch_Enable();//���������л�
            }
            else{//����Ѿ�������
                osTime.TTWM = 1;//��ǰ�������е��������Ƭʱ����Ϊһ����ζ����Ƭʱ������Ƴ�һ��
            }
             
        }
    }
    for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//������������������б���
		/*----------------------------------��ʱ---------------------------------------*/
        if((TL[_tr0].TITA -> TC) == Task_State_Up_DT){//�����������ʱ����(�ȴ�̬)���Ž���
            TL[_tr0].TITA -> TTF--;//���������ʱ���־�����ݼ�һ
            if(TL[_tr0].TITA -> TTF == 0){	//���������ʱ���־������Ϊ��ʱ
                if(TST.TSS != TaskSwitch_Ready){//����Ѿ����ڵ����У��Ͱ����������Ϊ��Ƭ����(����̬)
                    //TL[_tr0].TITA  -> TC &= TIT_Task_State_TC_RST;//�����������״̬λ
                    TL[_tr0].TITA  -> TC = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
                }
                else if(TL[_tr0].TITA -> TPL <  RunTask_TIT -> TPL){//������������ڵ�ǰ�������������������ȼ�����ռ��
                    //TL[_tr0].TITA -> TC &= TIT_Task_State_TC_RST;//�����������״̬λ
                    TL[_tr0].TITA -> TC = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
                    //RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//����������������״̬λ
                    RunTask_TIT -> TC = Task_State_Up_TD;//���������������״̬��Ϊ��Ƭ����(����̬)
                    if(TST.TSS == TaskSwitch_Ready){//��ѯ�Ƿ񼺱��������û�оʹ��������л�
                        TST. TDN = _tr0;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
                        osTaskSwitch_Enable(); //���������л�
                    }
                    else{//����Ѿ�������
                        TL[_tr0].TITA -> TTF = 1;//��ǰ�������е��������Ƭʱ����Ϊһ����ζ����Ƭʱ������Ƴ�һ��
                    }
                }
                else{//����֮�ϵ����
                        //TL[_tr0].TITA -> TC &= TIT_Task_State_TC_RST;//�����������״̬λ
                        TL[_tr0].TITA -> TC = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
                }
            }
        }
    }
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	}
	#endif
}

/*
                                                  FILE-END
*/
