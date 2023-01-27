/*
                                                  FILE-START
*/
#ifndef _osPOST_H_
#define _osPOST_H_
/*

 *@�ļ�����: osPOST.h

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע   ��: ��

*/


/*
                                                  <�����ļ���>
*/
#include "main.h"
#include "osConfig.h"
#include "osTask.h"
/*
                                                  <�궨����>
*/
#define osPost_Enable 		//�������� ��������������ֶ����ã������Զ�����ļ����Զ���������

#define osPostHead		1	 //���ʼ�˳��  1������ 0������

/*
                                                  <����������>
*/

typedef		u32		 _PostBody;//�ʼ�����
//�����{
typedef struct 
{
	_NextAddr*  DownAddr;//��һ���ʼ��ĵ�ַ
	_PostBody*				PB;//�ʼ�����

}PostForm;
//}

/*
                                                  <����������>
*/
/*

 *@��������: osPostSend

 *@�����汾: 1.0.0

 *@��������: ��ʼ������

 *@�������: PB - �ʼ�����
			 TIT - Ŀ�������������ַ

 *@�� �� ֵ:  �������󷵻�ֵ (0:��ʾ��ʼ���ɹ���-1:��ʾ��ʼ��ʧ��)

 *@ע   ��: ��

*/
osErrorValue osPostSend(void* PB,TaskInfoTable* TIT);
/*

 *@��������: osPostRead

 *@�����汾: 1.0.0

 *@��������: ��ȡ�ʼ�

 *@�������: ��

 *@�� �� ֵ: �ʼ�����

 *@ע   ��: ��

*/
u32* osPostRead(void);
/*

 *@��������: osPostRead_Wait

 *@�����汾: 1.0.0

 *@��������: ����ʽ��ȡ�ʼ�

 *@�������: ��

 *@�� �� ֵ: �ʼ�����

 *@ע   ��: ��

*/
u32* osPostReadWait(void);

#endif
/*
                                                  FILE-END
*/


