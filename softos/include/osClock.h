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
typedef uint32_t _TotalSystemRunningTime;//ϵͳ����ʱ��
typedef uint32_t _TaskISRRunningTime;//ϵͳ����ʱ��
#endif
typedef	uint32_t	_TaskTimeWheelMargin;//������Ƭʱ��
#if (osClockTimePeriod < osClockTimePeriodStandard)
typedef uint32_t _ClockTimePeriodValue; //ʱ�����ڼ���
#endif

//ϵͳʱ��{
typedef struct
{
	#if (os_TotalSystemRunningTime_Enable > 0)//������ϵͳ����ʱ��
	_TotalSystemRunningTime 	TSRT;//ϵͳ����ʱ��
	_TaskISRRunningTime			TISRRT;
	#endif
	_TaskTimeWheelMargin	   TTWM;//������Ƭʱ��
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	_ClockTimePeriodValue      CTPV;//ʱ�����ڼ���
	#endif
}osTIME;
//}

#if (osPerformanceStatistics_Enable > 0)
typedef  uint8_t  	_CPUTaskOccupy;//
typedef  uint8_t  	_CPUISROccupy;//
typedef	 uint8_t 	_CPUSwitchOccupy;
typedef		uint32_t		_TaskSwitchConut;//������ȴ���
typedef		uint8_t		_TaskSwitchSpeedUs;//�����л��ٶȲ���

//����ͳ��{
typedef struct
{
 
	_CPUTaskOccupy  	CTO;//
	_CPUISROccupy		CISRO;//
	_CPUSwitchOccupy	CSO;//
	_TaskSwitchConut	TSC;//������ȴ���
	_TaskSwitchConut	TSCb;//������ȴ���
	_TaskSwitchSpeedUs	TSSU;//�����л��ٶȲ���

}_PerformanceStatistics;
//}
#endif

extern _PerformanceStatistics PS;//����ͳ��
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

