/*
                                                  FILE-START
*/

/*

* softos�ں�

* ��Ȩ����(C) 2023 AhDun ��Ȩ����.

* ���������׼���κ���ʿȡ�ñ����ĸ���

* ���������ص��ĵ��ļ�(���¼�ơ������)�����ڴ���

* ������������ƣ������������Ƶ�Ȩ��

* ʹ�á����ơ��޸ġ��ϲ����������ַ���ת��ɺ�/�����۵ĸ�������������������ṩ���������������

* �������������:

* ������Ȩ���������������Ӧ����������

* ������ĸ�����󲿷֡�

* ����ǡ���ԭ�����ṩ�ģ�û���κ���ʽ�ı�֤����ʾ��

* ��ʾ�������������������ԡ������Եı�֤

* �����ض�Ŀ�ĺͲ���Ȩ�����κ�����£����߻�

* ��Ȩӵ������е��κ����������⳥���������Σ������Ƿ�

* �ں�ͬ����Ȩ�����������У��ɣ��ɻ���

* ���������ϵ��������ʹ�û��������ס�

*/

/*

 *@�ļ�����: osClock.c

 *@�ļ�����: ϵͳʱ���ļ�

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע    ��: 

*/

/*
                                                  <�����ļ���>
*/
#include "osConfig.h"
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

 *@��������: osClockTimePulse

 *@�����汾: 1.0.0

 *@��������: ϵͳʱ�����崦��

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
void osClockTimePulse(void)
{
	/*�����������ж���Ӧ����У���������������ĸ���*/
	u32 _tr0;//������ʼ��

	#if (osClockTimePeriod < osClockTimePeriodStandard) //
	if(++osTime.CTPV >= (osClockTimePeriodStandard /osClockTimePeriod)){
		osTime.CTPV = NULL;
	#endif
    /*----------------------------------��ʱ---------------------------------------*/
	#if (os_TotalSystemRunningTime_Enable > 0)//������ϵͳ����ʱ��
	#if (osClockTimePeriod > osClockTimePeriodStandard)
	osTime. TSRT += (osClockTimePeriod / osClockTimePeriodStandard);//ϵͳ����ʱ�����м�ʱ
	#else
	osTime. TSRT += 1;//ϵͳ����ʱ�����м�ʱ
	#endif
	#endif
     /*----------------------------------ͳ��---------------------------------------*/
	#if (osPerformanceStatistics_Enable > 0) //����������ͳ��
	if(TST.TISRF > NULL){
		osTime.TISRRT++;
	}
	else if(TST.TSS == TaskSwitch_Ready){//�������״̬Ϊδ���ȣ����м�ʱ
        RunTask_TIT -> TOT++;//����ռ��ʱ������
    }
    if(osTime. TSRT % TaskOccupyRatioSamplingTime == 0){//ϵͳÿ��һ��ʱ�����ͽ���ռ�ñ���ͳ��
        CPUS.CTO = 0;//CPUռ������Ϊ0
        for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//��ÿһ��������б���
            //TL[_tr0].TITA -> TOR = TL[_tr0].TITA -> TOT / (TaskOccupyRatioSamplingTime / 100);//�����������ռ�ñ�
			TL[_tr0].TITA -> TOR = TL[_tr0].TITA -> TOT;//�����������ռ�ñ�
			//���㹫ʽ��ռ�ñ� = ��λʱ���ڵ�ռ��ʱ�� / (��λʱ�� / 100)
            CPUS.CTO += (TL[_tr0].TITA -> TOR / (TaskOccupyRatioSamplingTime / 100));//����CPUռ����
			//���㹫ʽ��CPUռ���� = CPUռ���� + ÿ�������ռ����
            TL[_tr0].TITA -> TOT = 0;//��յ�λʱ���ڵ�ռ��ʱ��
        }
		if(osTime.TISRRT > NULL){
			CPUS.CISRO = (osTime.TISRRT / (TaskOccupyRatioSamplingTime / 100));//����CPUռ����
			osTime.TISRRT = 0;
		}
		
    }
	#endif
    /*----------------------------------��Ƭ---------------------------------------*/
    if(osTime.TTWM > 0 && TST.TSS == TaskSwitch_Ready && TST.TISRF == NULL){ //ʱ����Ƭ
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
