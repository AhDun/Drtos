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




//��ʱ������{
#define STimeConfig_Restart		0x01 // �ظ�
#define STimeConfig_NRestartL	0x02 // һ�β�ɾ��
#define STimeConfig_NRestart	0x03 // һ��
//}



/*
 *
 * @��������: osClockGetOsRTC
 *
 * @��������: ��ȡOSRTC
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osClockGetOsRTC()		OsTimeSystemRunTime		
/*
 *
 * @��������: osClockGetOsRTCD
 *
 * @��������: ��ȡOSRTC����
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osClockGetOsRTCD()	(osClockGetOsRTC() / 1000) /86400
/*
 *
 * @��������: osClockRTCGetH
 *
 * @��������: ��ȡOSRTCСʱ��
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osClockGetOsRTCH()		((osClockGetOsRTC() / 1000) /3600) % 24
/*
 *
 * @��������: osClockRTCGetH
 *
 * @��������: ��ȡOSRTC������
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osClockGetOsRTCM()	((osClockGetOsRTC() / 1000) /60) % 60
/*
 *
 * @��������: osClockRTCGetH
 *
 * @��������: ��ȡOSRTC����
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osClockGetOsRTCS()	(osClockGetOsRTC() / 1000) % 60


/*
 *
 * @��������: osClockGetTimePulse
 *
 * @��������: ��ȡϵͳ��ʱ����
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define OsTimeGetSystemRunTime()		OsTimeSystemRunTime
/*
 *
 * @��������: osClockGetTimePulse
 *
 * @��������: ��ȡϵͳ��ʱ����
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define OsTimeGetTaskISRTime()			OsTimeTaskISRTime

/*
 *
 * @��������: osClockGetTimePulse
 *
 * @��������: ��ȡϵͳ��ʱ����
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define OsTimeGetTaskTimeWheel()			OsTimeTaskTimeWheel
/*
 *
 * @��������: osClockGetTimePulse
 *
 * @��������: ��ȡϵͳ��ʱ����
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define OsTimeGetPeriodValue()			OsTimePeriodValue


//ϵͳʱ��{
#if (os_TotalSystemRunningTime_Config > 0)//������ϵͳ����ʱ��
typedef uint32_t _SystemRunningTime;//ϵͳ����ʱ��
extern _SystemRunningTime 		OsTimeSystemRunTime;//ϵͳ����ʱ��
typedef uint32_t _TaskISRRunningTime;//ϵͳ����ʱ��
extern _TaskISRRunningTime		OsTimeTaskISRTime;//ϵͳ����ʱ��
#endif
typedef	uint32_t	_TaskWheelMargin;//������Ƭʱ��
extern _TaskWheelMargin	   OsTimeTaskTimeWheel;//������Ƭʱ��
#if (osClockTimePeriod < osClockTimePeriodStandard)
typedef uint32_t _ClockTimePeriodValue; //ʱ�����ڼ���
extern _ClockTimePeriodValue      OsTimePeriodValue;//ʱ�����ڼ���
#endif


//����ͳ��{
#if (osPerformanceStatistics_Config > 0)
typedef  uint8_t  	_CPUTaskOccupy;//����ռ�ñ�
typedef  uint8_t  	_CPUISROccupy;//�ж�ռ�ñ�
typedef	 uint8_t 	_CPUSwitchOccupy;//�л�ռ�ñ�
typedef	 uint32_t	_TaskSwitchConut;//������ȴ���
typedef	 double		_TaskSwitchSpeedUs;//�����л��ٶȲ���
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
typedef	 uint32_t		_STaskDelay;
typedef	 uint8_t		_STimeConfig;
typedef	 uint32_t		_STimeAddr;
typedef struct
{
	_NextAddr	  DownAddr;//��һ���ʼ��ĵ�ַ
	_STimeName* 	Name;
	_STimeConfig  	Config;
	_STimeAddr*	  	Addr;
	_STaskDelay		Flag;
}_STime;//��������

typedef struct
{
	_NextAddr	  DownAddr;//��һ���ʼ��ĵ�ַ
	_STimeName* 	Name;
	_STimeConfig  	Config;
	_STimeAddr*	  	Addr;
	_STaskDelay		Flag;
	_STaskDelay		Flagb;
}_STimes;//������
//}
#endif

extern _PerformanceStatistics PS;//����ͳ��

extern _NextAddr STimeListHead;

extern _TaskHandle* TaskHandle_STime;



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
OsErrorValue osClockInit(void);
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

/*
 *
 * @��������: osTimeLogin_Static
 *
 * @��������: ��ʱ��ע��
 *
 * @�������: ListAddr	��ʱ�������ַ
 * @�������: Name	��ʱ������
 * @�������: Flag	��ʱ�����ͱ�־
 * @�������: Config	��ʱ���������
 * @�������: Addr	�ص�������ַ
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
_STimes* osTimeLogin_Static(uint8_t* ListAddr,_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr);
/*
 *
 * @��������: osSTimeLogout
 *
 * @��������: ��ʱ��ע��
 *
 * @�������: STimes	��ʱ����ַ
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSTimeLogout(_STimes* STimes);
/*
 *
 * @��������: osTimeLogin
 *
 * @��������: ��ʱ��ע��
 *
 * @�������: Name	��ʱ������
 * @�������: Flag	��ʱ�����ͱ�־
 * @�������: Config	��ʱ���������
 * @�������: Addr	�ص�������ַ
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */

_STimes* osTimeLogin(_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr);
/*
 *
 * @��������: osSTimeInit
 *
 * @��������: ��ʱ����ʼ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSTimeInit(void);
/*
 *
 * @��������: osSTime
 *
 * @��������: ��ʱ����Ӧ����
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osSTime(void);


#endif



