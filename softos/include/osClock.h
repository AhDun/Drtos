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
 * @ע    ��: 
 *
 */


#define osClock_Enable 	//����ʱ�� ��������������ֶ����ã������Զ�����ļ����Զ���������


#define TaskOccupyRatioSamplingTime 		1000 //����ͳ��ʱ�䣬��λms

#define STimeConfig_Restart		0x01
#define STimeConfig_NRestartL	0x02
#define STimeConfig_NRestart	0x03

#define osClockGetTimePulse()		osTime.TSRT//��ȡϵͳ��ʱ����


//ϵͳʱ��{
#if (os_TotalSystemRunningTime_Enable > 0)//������ϵͳ����ʱ��
typedef uint32_t _TotalSystemRunningTime;//ϵͳ����ʱ��
typedef uint32_t _TaskISRRunningTime;//ϵͳ����ʱ��
#endif
typedef	uint32_t	_TaskTimeWheelMargin;//������Ƭʱ��
#if (osClockTimePeriod < osClockTimePeriodStandard)
typedef uint32_t _ClockTimePeriodValue; //ʱ�����ڼ���
#endif
typedef struct
{
	#if (os_TotalSystemRunningTime_Enable > 0)//������ϵͳ����ʱ��
	_TotalSystemRunningTime 	TSRT;//ϵͳ����ʱ��
	_TaskISRRunningTime			TISRRT;//ϵͳ����ʱ��
	#endif
	_TaskTimeWheelMargin	   TTWM;//������Ƭʱ��
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	_ClockTimePeriodValue      CTPV;//ʱ�����ڼ���
	#endif
}osTIME;
//}

//����ͳ��{
#if (osPerformanceStatistics_Enable > 0)
typedef  uint8_t  	_CPUTaskOccupy;//����ռ�ñ�
typedef  uint8_t  	_CPUISROccupy;//�ж�ռ�ñ�
typedef	 uint8_t 	_CPUSwitchOccupy;//�л�ռ�ñ�
typedef	 uint32_t	_TaskSwitchConut;//������ȴ���
typedef	 uint8_t	_TaskSwitchSpeedUs;//�����л��ٶȲ���
typedef struct
{
 
	_CPUTaskOccupy  	CTO;//����ռ�ñ�
	_CPUISROccupy		CISRO;//�ж�ռ�ñ�
	_CPUSwitchOccupy	CSO;//�л�ռ�ñ�
	_TaskSwitchConut	TSC;//������ȴ���
	_TaskSwitchConut	TSCb;//������ȴ���
	_TaskSwitchSpeedUs	TSSU;//�����л��ٶȲ���

}_PerformanceStatistics;

//�����ʱ��{
typedef	 uint8_t		_STimeName;
typedef	 uint32_t		_STimeFlag;
typedef	 uint8_t		_STimeConfig;
typedef	 uint32_t		_STimeAddr;
typedef struct
{
	_NextAddr	  DownAddr;//��һ���ʼ��ĵ�ַ
	_STimeName* 	Name;
	_STimeConfig  	Config;
	_STimeAddr*	  	Addr;
	_STimeFlag		Flag;
}_STime;

typedef struct
{
	_NextAddr	  DownAddr;//��һ���ʼ��ĵ�ַ
	_STimeName* 	Name;
	_STimeConfig  	Config;
	_STimeAddr*	  	Addr;
	_STimeFlag		Flag;
	_STimeFlag		Flagb;
}_STimes;
//}
#endif

extern _PerformanceStatistics PS;//����ͳ��

extern _NextAddr STimeListHead;
extern _TaskHandle* TaskHandle_STime;

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


_STimes* osTimeLogin_Static(uint8_t* ListAddr,_STimeName* Name,_STimeFlag Flag,_STimeConfig Config,void* Addr);
_STimes* osTimeLogin(_STimeName* Name,_STimeFlag Flag,_STimeConfig Config,void* Addr);
osErrorValue osSTimeInit(void);
void osSTime(void);


#endif


