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
#ifndef __osClockH_
#define __osClockH_

/*
 *
 * @�ļ�����: osClock.h
 *
 * @�ļ�����: 
 *
 * @�ļ�����: AhDun (mail: ahdunxx@163.com)
 *
 * @ע    ��: 
 *
 */





#define osClock_Enable 	//����ʱ�� ��������������ֶ����ã������Զ�����ļ����Զ���������


#define TaskOccupyRatioSamplingTime 		1000 //����ͳ��ʱ�䣬��λms

#define osClockGetTimePulse()		osTime.TSRT



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
typedef  uint8_t  	_CPUTaskOccupy;//����ռ�ñ�
typedef  uint8_t  	_CPUISROccupy;//�ж�ռ�ñ�
typedef	 uint8_t 	_CPUSwitchOccupy;//�л�ռ�ñ�
typedef	 uint32_t	_TaskSwitchConut;//������ȴ���
typedef	 uint8_t	_TaskSwitchSpeedUs;//�����л��ٶȲ���
//����ͳ��{
typedef struct
{
 
	_CPUTaskOccupy  	CTO;//����ռ�ñ�
	_CPUISROccupy		CISRO;//�ж�ռ�ñ�
	_CPUSwitchOccupy	CSO;//�л�ռ�ñ�
	_TaskSwitchConut	TSC;//������ȴ���
	_TaskSwitchConut	TSCb;//������ȴ���
	_TaskSwitchSpeedUs	TSSU;//�����л��ٶȲ���

}_PerformanceStatistics;
//}
#endif

extern _PerformanceStatistics PS;//����ͳ��

extern osTIME osTime;

/*
 *
 * @��������: osClockInit
 *
 * @��������: ϵͳʱ�ӳ�ʼ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
osErrorValue osClockInit(void);
/*
 *
 * @��������: osClockTimePulse
 *
 * @��������: ϵͳʱ�����崦��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osClockTimePulse(void);


#endif


