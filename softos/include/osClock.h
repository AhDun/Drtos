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

#define osClockTimePeriod 					1000 //ϵͳʱ�����ڣ���λus
#define osClockTimePeriodStandard			1000 //ϵͳʱ���׼���ڣ���λus


#define TaskOccupyRatioSamplingTime 		1000 //����ͳ��ʱ�䣬��λms

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
typedef struct
{
#if (os_TotalSystemRunningTime_Enable > 0)//������ϵͳ����ʱ��
	_TotalSystemRunningTime TSRT;//ϵͳ����ʱ��
#endif
	_TaskTimeWheelMargin	   TTWM;//������Ƭʱ��
#if (osClockTimePeriod < osClockTimePeriodStandard)
	_ClockTimePeriodValue      CTPV;//ʱ�����ڼ���
#endif
}osTIME;//ϵͳʱ��

extern osTIME osTime;
/*
                                                  <����������>
*/
extern osErrorValue osClockInit(void);

extern void osClockTimePulse(void);


#endif
/*
                                                  FILE-END
*/

