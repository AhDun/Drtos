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

#define osPostDebugError_Enable 1 //�������DeBug  1:����Debug��� 0:�ر�Debug���

#define osPostDebugError	osDebugError 

/*
                                                  <����������>
*/

typedef		uint32_t		 _PostBody;//�ʼ�����
//�����{
typedef struct 
{
	_NextAddr	  DownAddr;//��һ���ʼ��ĵ�ַ
	_PostBody*	  Body;//�ʼ�����

}_Post;
//}

/*
                                                  <����������>
*/
/*

 *@��������: osPostSend

 *@�����汾: 1.0.0

 *@��������: ��ʼ������

 *@�������: PB - �ʼ�����
			 TaskHandle - Ŀ�������������ַ

 *@�� �� ֵ:  �������󷵻�ֵ (0:��ʾ��ʼ���ɹ���-1:��ʾ��ʼ��ʧ��)

 *@ע   ��: ��

*/
osErrorValue osPostSend(void* PB,_TaskHandle* TaskHandle);
/*

 *@��������: osPostRead

 *@�����汾: 1.0.0

 *@��������: ��ȡ�ʼ�

 *@�������: ��

 *@�� �� ֵ: �ʼ�����

 *@ע   ��: ��

*/
uint32_t* osPostRead(void);
/*

 *@��������: osPostRead_Wait

 *@�����汾: 1.0.0

 *@��������: ����ʽ��ȡ�ʼ�

 *@�������: ��

 *@�� �� ֵ: �ʼ�����

 *@ע   ��: ��

*/
uint32_t* osPostReadWait(void);

#endif
/*
                                                  FILE-END
*/


