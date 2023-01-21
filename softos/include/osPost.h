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
#include "osMain.h"
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
	_PostBody*				PB;//�ʼ�����
	_uList					uList;//��������

}PostForm;
//}

/*
                                                  <����������>
*/
/*

 *@��������: osPostInit

 *@�����汾: 1.0.0

 *@��������: ��ʼ������

 *@�������: ��

 *@�� �� ֵ: �������󷵻�ֵ (0:��ʾ��ʼ���ɹ���-1:��ʾ��ʼ��ʧ��)

 *@ע   ��: ��

*/
extern osErrorValue osPostInit(void);
/*

 *@��������: osPostSend

 *@�����汾: 1.0.0

 *@��������: ��ʼ������

 *@�������: PB - �ʼ�����
			 TIT - Ŀ�������������ַ

 *@�� �� ֵ:  �������󷵻�ֵ (0:��ʾ��ʼ���ɹ���-1:��ʾ��ʼ��ʧ��)

 *@ע   ��: ��

*/
extern osErrorValue osPostSend(void* PB,TaskInfoTable* TIT);
/*

 *@��������: osPostRead

 *@�����汾: 1.0.0

 *@��������: ��ȡ�ʼ�

 *@�������: ��

 *@�� �� ֵ: �ʼ�����

 *@ע   ��: ��

*/
extern u32* osPostRead(void);
/*

 *@��������: osPostRead_Wait

 *@�����汾: 1.0.0

 *@��������: ����ʽ��ȡ�ʼ�

 *@�������: ��

 *@�� �� ֵ: �ʼ�����

 *@ע   ��: ��

*/
extern u32* osPostReadWait(void);

#endif
/*
                                                  FILE-END
*/


