/*
                                                  FILE-START
*/

#ifndef __print_H_
#define __print_H_

/*

 *@�ļ�����: .h

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע   ��: ��

*/

/*
                                                  <�����ļ���>
*/

/*
                                                  <�궨����>
*/

#define _print_lf_retain	6 //С������


/*
                                                  <����������>
*/

/*
                                                  <����������>
*/

int pchar(const char ch);
static int vpchar(const char ch,int* s);
static void _print_num(unsigned int num,int ctl,int* s);
static void _print_d(int num,int ctl,int* s);
static void _print_s(int p,int* s);
static void _print_X(int num,int* s);
static void _print_x(int num,int* s);
static void _print_o(int num,int* s);
static void _print_lu(unsigned int num,int* s);
static void _print_lf(double* num,char ctrl,int* s);
static void _pchar(int p,int* s);

__asm void print(const char* s,...);
__asm void sprint(char* s,const char* c,...);

void xprint(int sp,int c);
void tprint(const char* c,unsigned int s);


/*
                                                  FILE-END
*/
#endif

