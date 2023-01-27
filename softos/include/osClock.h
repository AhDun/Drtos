/*
                                                  FILE-START
*/
#ifndef __osClockH_
#define __osClockH_

/*

 *@�ļ�����: osClock.h

 *@�ļ�����: 

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: 

*/

/*
                                                  <�����ļ���>
*/

/*
                                                  <�궨����>
*/

#define osClock_Enable 	//����ʱ�� ��������������ֶ����ã������Զ�����ļ����Զ���������


#define TaskOccupyRatioSamplingTime 		1000 //����ͳ��ʱ�䣬��λms

#define osClockGetTimePulse()	osTime. TSRT

/*
                                                  <����������>
*/

#if (os_TotalSystemRunningTime_Enable > 0)//������ϵͳ����ʱ��
typedef u32 _TotalSystemRunningTime;//ϵͳ����ʱ��
#endif
typedef	u32	_TaskTimeWheelMargin;//������Ƭʱ��
#if (osClockTimePeriod < osClockTimePeriodStandard)
typedef u32 _ClockTimePeriodValue; //ʱ�����ڼ���
#endif

//ϵͳʱ��{
typedef struct
{
	#if (os_TotalSystemRunningTime_Enable > 0)//������ϵͳ����ʱ��
	_TotalSystemRunningTime 	TSRT;//ϵͳ����ʱ��
	#endif
	_TaskTimeWheelMargin	   TTWM;//������Ƭʱ��
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	_ClockTimePeriodValue      CTPV;//ʱ�����ڼ���
	#endif
}osTIME;
//}


extern osTIME osTime;
/*
                                                  <����������>
*/
/*

 *@��������: osClockInit

 *@�����汾: 1.0.0

 *@��������: ϵͳʱ�ӳ�ʼ��

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osClockInit(void);
/*

 *@��������: osClockTimePulse

 *@�����汾: 1.0.0

 *@��������: ϵͳʱ�����崦��

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
void osClockTimePulse(void);


#endif
/*
                                                  FILE-END
*/

