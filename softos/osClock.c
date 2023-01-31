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
#if (osPerformanceStatistics_Enable > 0)
_PerformanceStatistics PS;//����ͳ��
#endif
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
	uint32_t _tr0;//������ʼ��

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
        RunTaskHandle -> OccupyTime++;//����ռ��ʱ������
    }
    if(osTime. TSRT % TaskOccupyRatioSamplingTime == 0){//ϵͳÿ��һ��ʱ�����ͽ���ռ�ñ���ͳ��
        PS.CTO = 0;//CPUռ������Ϊ0
        for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//��ÿһ��������б���
            //TaskList[_tr0].TaskHandle -> OccupyRatio = TaskList[_tr0].TaskHandle -> OccupyTime / (TaskOccupyRatioSamplingTime / 100);//�����������ռ�ñ�
			TaskList[_tr0].TaskHandle -> OccupyRatio = TaskList[_tr0].TaskHandle -> OccupyTime;//�����������ռ�ñ�
			//���㹫ʽ��ռ�ñ� = ��λʱ���ڵ�ռ��ʱ�� / (��λʱ�� / 100)
            PS.CTO += (TaskList[_tr0].TaskHandle -> OccupyRatio / (TaskOccupyRatioSamplingTime / 100));//����CPUռ����
			//���㹫ʽ��CPUռ���� = CPUռ���� + ÿ�������ռ����
            TaskList[_tr0].TaskHandle -> OccupyTime = 0;//��յ�λʱ���ڵ�ռ��ʱ��
        }
		if(osTime.TISRRT > NULL){
			PS.CISRO = (osTime.TISRRT / (TaskOccupyRatioSamplingTime / 100));//����CPUռ����
			osTime.TISRRT = 0;
		}
		PS.CSO = ((PS.TSC * PS.TSSU) / (TaskOccupyRatioSamplingTime)) / 10;
		PS.TSCb = PS.TSC;
		PS.TSC = 0;
    }
	#endif
    /*----------------------------------��Ƭ---------------------------------------*/
    if(osTime.TTWM > 0 && TST.TSS == TaskSwitch_Ready && TST.TISRF == NULL){ //ʱ����Ƭ
	   //��ǰ�������е��������Ƭʱ�����0���ҵ���״̬Ϊδ����״̬
        osTime.TTWM--;//��ǰ�������е��������Ƭʱ���һ
        if(osTime.TTWM == 0){//��Ŀǰ�������е��������Ƭʱ��Ϊ��ʱ
            //RunTaskHandle -> Config &= TIT_Task_State_TC_RST;//����������е������״̬λ
            RunTaskHandle -> Config = Task_State_Up_TD;//���������е������״̬��Ϊλ��Ƭ����(����̬)
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
        if((TaskList[_tr0].TaskHandle -> Config) == Task_State_Up_DT){//�����������ʱ����(�ȴ�̬)���Ž���
            TaskList[_tr0].TaskHandle -> TimeFlag--;//���������ʱ���־�����ݼ�һ
            if(TaskList[_tr0].TaskHandle -> TimeFlag == 0){	//���������ʱ���־������Ϊ��ʱ
                if(TST.TSS != TaskSwitch_Ready){//����Ѿ����ڵ����У��Ͱ����������Ϊ��Ƭ����(����̬)
                    //TaskList[_tr0].TaskHandle  -> Config &= TIT_Task_State_TC_RST;//�����������״̬λ
                    TaskList[_tr0].TaskHandle  -> Config = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
                }
                else if(TaskList[_tr0].TaskHandle -> PriorityLevel <  RunTaskHandle -> PriorityLevel){//������������ڵ�ǰ�������������������ȼ�����ռ��
                    //TaskList[_tr0].TaskHandle -> Config &= TIT_Task_State_TC_RST;//�����������״̬λ
                    TaskList[_tr0].TaskHandle -> Config = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
                    //RunTaskHandle -> Config &= TIT_Task_State_TC_RST;//����������������״̬λ
                    RunTaskHandle -> Config = Task_State_Up_TD;//���������������״̬��Ϊ��Ƭ����(����̬)
                    if(TST.TSS == TaskSwitch_Ready){//��ѯ�Ƿ񼺱��������û�оʹ��������л�
                        TST. TDN = _tr0;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
                        osTaskSwitch_Enable(); //���������л�
                    }
                    else{//����Ѿ�������
                        TaskList[_tr0].TaskHandle -> TimeFlag = 1;//��ǰ�������е��������Ƭʱ����Ϊһ����ζ����Ƭʱ������Ƴ�һ��
                    }
                }
                else{//����֮�ϵ����
                        //TaskList[_tr0].TaskHandle -> Config &= TIT_Task_State_TC_RST;//�����������״̬λ
                        TaskList[_tr0].TaskHandle -> Config = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
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
