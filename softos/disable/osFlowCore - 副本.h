/*
                                                  FILE-START
*/
/*

 *@�ļ�����: HDS_Intmac.h

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun

 *@��������: STM32F407ZGT6@168MHzоƬ & Keil uVision 5

 *@ע   ��: ��

*/
#ifndef _HDS_Intmac_H_
#define _HDS_Intmac_H_

/*
                                                  <�����ļ���>
*/
#include "main.h"
/*
                                                  <�궨����>
*/

#define WayPter_Mode_WOK 0
#define WayPter_Mode_GOK 1

#define GAP_SIZE 		100
#define IOName_SIZE 	10
#define WayName_SIZE 	10
#define WayPter_SIZE 	50

#define Get_OK			1
#define Get_End 		2
#define Get_Error 		3


#define Intmac_OK				4
#define Intmac_End				5
#define Intmac_IONAME_Error		6
#define Intmac_WayName_Error	7



#define Intmac_case_1(a) 						(u32)(a)
#define Intmac_case_2(a,b) 						(u32)(a-b)
#define Intmac_case_3(a,b,c) 					(u32)(a-b+c)
#define Intmac_case_4(a,b,c,d) 					(u32)(a-b+c-d)
#define Intmac_case_5(a,b,c,d,e) 				(u32)(a-b+c-d+e)
#define Intmac_case_6(a,b,c,d,e,f) 				(u32)(a-b+c-d+e-f)
#define Intmac_case_7(a,b,c,d,e,f,g) 			(u32)(a-b+c-d+e-f+g)
#define Intmac_case_8(a,b,c,d,e,f,g,h) 			(u32)(a-b+c-d+e-f+g-h)
#define Intmac_case_9(a,b,c,d,e,f,g,h,k) 		(u32)(a-b+c-d+e-f+g-h+k)
#define Intmac_case_10(a,b,c,d,e,f,g,h,k,p) 	(u32)(a-b+c-d+e-f+g-h+k-p)



#define DHS_Intmac_ErrorOutput_Enable  //�����������
#define DHS_Intmac_AToa_Enable		   //���ô�дתСд


/*
                                                  <����������>
*/


extern s8* IntStrPer;
extern u32* Gap[GAP_SIZE];
extern u8  IOName[IOName_SIZE];
extern u8  WayName[WayName_SIZE];
extern u8  WayPter[WayPter_SIZE];
extern u32* Gap_Read;
extern u8  WayPter_Mode;


/*
                                                  <����������>
*/
s8 DHS_Flow(s8 *IntStr);
s8 DHS_Intmac_Uart(void);
s8 DHS_Intmac_IONAME(u32 IONAME);
u32 DHS_StrToSwitch(u8 *numstr);
s32 DHS_StrToNum(s8 *numstr);
s8 DHS_Flow_GetWay(void);
s8 DHS_CharComp(s8 *strs,s8 *strc);
s8 DHS_StrComp(s8 *strs,s8 *strc);
s8 DHS_StrCutComp(s8 *strs,s8 *strc,s8 cutchar);
u32 DHS_StrLoca(s8 *strs,s8 locachar);


#endif

/*
                                                  FILE-END
*/


