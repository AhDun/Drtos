/*------------------------------------------------------------------------------------------------------------------------
 * �ļ����ƣ�System_Clock.h

 * �ļ����ݣ�

 * �ļ��汾��1.0.0

 * �ļ����ߣ�����ʵ����

 * ����������STC8A8K64S4A12@22.1184MHzоƬ & Keil uVision 5 

 * ע    �⣺
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  ���ظ������������
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __System_Clock_h_
#define __System_Clock_h_
/*------------------------------------------------------------------------------------------------------------------------
                                                  �궨����
------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------��ֵ---------------------------------------*/
/*ʱ������*/
#define timer_msnMax 16 //�����ʱ������
#define System_Timer_Reload 0xF8CD //ϵͳ��ʱ����װֵ 

#define Timer_Touch 0 		// ��ʱ���������
#define Task_Touch 1			// ���񴥷�
#define Task_End_Touch 2	// �����Զ���������
#define Task_API_Touch 3	// ����API����
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����������
------------------------------------------------------------------------------------------------------------------------*/
extern u8 xdata AppRunTimer;//Ӧ������ʱ��
extern u16 xdata SystemTime;//ϵͳʱ��
extern u32 xdata RUNTime;//��������ʱ��
extern u16 xdata Task0Time;//����0������ʱ��
extern u16 xdata ProTime;//���񱣻�ʱ��
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����������
------------------------------------------------------------------------------------------------------------------------*/
extern void TaskDelayMs(u16 TimeMs);//Ӳ����ʱ
extern void HeavyLoadSystemTimer();//��װϵͳ��ʱ��
extern void SystemClock();//ϵͳʱ��


#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/