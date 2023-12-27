/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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

/**
 *
 * @file osClock.h
 *
 * @brief 
 *
 * @note 
 *
 */




//��ʱ������{
#define STimeConfig_Restart		0x01 // �ظ�
#define STimeConfig_NRestartL	0x02 // һ�β�ɾ��
#define STimeConfig_NRestart	0x03 // һ��
//}



/**
 *
 * @name osClockGetOsRTC
 *
 * @brief ��ȡOSRTC
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockGetOsRTC()		OsTimeSystemRunTime		
/**
 *
 * @name osClockGetOsRTCD
 *
 * @brief ��ȡOSRTC����
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockGetOsRTCD()	(osClockGetOsRTC() / 1000) /86400
/**
 *
 * @name osClockRTCGetH
 *
 * @brief ��ȡOSRTCСʱ��
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockGetOsRTCH()		((osClockGetOsRTC() / 1000) /3600) % 24
/**
 *
 * @name osClockRTCGetH
 *
 * @brief ��ȡOSRTC������
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockGetOsRTCM()	((osClockGetOsRTC() / 1000) /60) % 60
/**
 *
 * @name osClockRTCGetH
 *
 * @brief ��ȡOSRTC����
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockGetOsRTCS()	(osClockGetOsRTC() / 1000) % 60


/**
 *
 * @name osClockGetTimePulse
 *
 * @brief ��ȡϵͳ��ʱ����
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define OsTimeGetSystemRunTime()		OsTimeSystemRunTime
/**
 *
 * @name osClockGetTimePulse
 *
 * @brief ��ȡϵͳ��ʱ����
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define OsTimeGetTaskISRTime()			OsTimeTaskISRTime

/**
 *
 * @name osClockGetTimePulse
 *
 * @brief ������Ƭʱ��
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define OsTimeGetTaskTimeWheel()			OsTimeTaskTimeWheel
/**
 *
 * @name osClockGetTimePulse
 *
 * @brief ��ȡϵͳ��ʱ����
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define OsTimeGetPeriodValue()			OsTimePeriodValue


//ϵͳʱ��{
#if (osRunTime_Config > 0)//������ϵͳ����ʱ��
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
typedef	uint16_t			_OsTimePeriod;
extern _OsTimePeriod		OsTimePeriod;


//����ͳ��{
#if (osPerf_Config > 0)
typedef  uint8_t  	_CPUTaskOccupy;//����ռ�ñ�
typedef  uint8_t  	_CPUISROccupy;//�ж�ռ�ñ�
typedef	 uint8_t 	_CPUSwitchOccupy;//�л�ռ�ñ�
typedef	 uint32_t	_TaskSwitchConut;//������ȴ���
typedef	 double		_TaskSwitchSpeedUs;//�����л��ٶȲ���
typedef struct
{
	_TaskSwitchConut	TSC;//������ȴ���
	_CPUTaskOccupy  	CTO;//����ռ�ñ�
	_CPUISROccupy		CISRO;//�ж�ռ�ñ�
	_CPUSwitchOccupy	CSO;//�л�ռ�ñ�
	_TaskSwitchConut	TSCb;//������ȴ���
	_TaskSwitchSpeedUs	TSSU;//�����л��ٶȲ���

}_OSRecord;
extern _OSRecord OSRecord;//����ͳ��

//}
#endif

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
}_STimer;//������




/**
 *
 * @name osClockInit
 *
 * @brief ϵͳʱ�ӳ�ʼ��
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osClockInit(void);
/**
 *
 * @name osClockTimePulse
 *
 * @brief ϵͳʱ�����崦��
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void osClockTimePulse(void);

/**
 *
 * @name osTimeLoginStatic
 *
 * @brief ��ʱ��ע��
 *
 * @param ListAddr	��ʱ�������ַ
 * @param Name	��ʱ������
 * @param Flag	��ʱ�����ͱ�־
 * @param Config	��ʱ���������
 * @param Addr	�ص�������ַ
 *
 * @retval none
 *
 * @note none
 *
 */
_STimer* osTimerLoginStatic(uint8_t* ListAddr,_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr);
/**
 *
 * @name osSTimeLogout
 *
 * @brief ��ʱ��ע��
 *
 * @param STimer	��ʱ����ַ
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osSTimerLogout(_STimer* STimer);
/**
 *
 * @name osTimeLogin
 *
 * @brief ��ʱ��ע��
 *
 * @param Name	��ʱ������
 * @param Flag	��ʱ�����ͱ�־
 * @param Config	��ʱ���������
 * @param Addr	�ص�������ַ
 *
 * @retval none
 *
 * @note none
 *
 */

_STimer* osTimerLogin(_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr);
/**
 *
 * @name osSTimeInit
 *
 * @brief ��ʱ����ʼ��
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osSTimerInit(void);
/**
 *
 * @name osSTime
 *
 * @brief ��ʱ����Ӧ����
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void osSTimer(void);


#endif



