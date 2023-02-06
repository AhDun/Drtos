/*********************************************************************************************************
* 文件名称：LCD1602.c
* 摘    要：1602显示屏忙碌检测/1602显示屏命令发送/1602显示屏数据发送
* 当前版本：1.0.0
* 作    者：麦特实验室
* 完成日期：
* 内    容：
* 注    意：
* 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5                                                                 
**********************************************************************************************************
* 取代版本：
* 作    者：
* 完成日期：
* 修改内容：
* 修改文件：
*********************************************************************************************************/

#include"Basic.h"
#include"LCD1602.h"

u8 xdata DP1602 = 0;

/********************************
函数名称:delay_1602
函数功能:1602专用延时
输入参数:
输    入:
输出参数:
输    出:
********************************/
void delay_1602()
{
	_nop_();//大约延时474ns(1602最小延时时间:400ns)
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
void EN0()
{
	EN = 0;//1602使能
	delay_1602();//进行延时,让电平持续1us	
}
/********************************
函数名称:D1602_Read_Busy
函数功能:1602显示屏忙碌检测
输入参数:
输    入:
输出参数:
输    出:
********************************/
u2 D1602_Read_Busy() reentrant
{
	data1602IO = 0xFF;//清空
	delay_1602();//进行延时,让电平持续1us
	RS = 0;
	delay_1602();//进行延时,让电平持续1us
	RW = 1;
	delay_1602();//进行延时,让电平持续1us
 	EN = 1;//1602使能
	delay_1602();//进行延时,让电平持续1us
	if(data1602IO & 0x80)
		return 1;
	else
		return 0;
}
/********************************
函数名称:D1602_Write_Cmd
函数功能:1602显示屏发送命令
输入参数:cmd(1602命令)
输    入:
输出参数:
输    出:
********************************/
void D1602_Write_Cmd(u8 cmd)
{
	while(D1602_Read_Busy())//进行忙碌检测
	{
	 	 EN0();
		 if(cmd == 0x80 || cmd == 0x01 ||cmd == 0xA8)
			DP1602 = 0;
	}
	RS = 0;//RS = 0则为命令模式
    delay_1602();//进行延时,让电平持续1us
	RW = 0;
	delay_1602();//进行延时,让电平持续1us
	data1602IO = cmd;//发送命令
	delay_1602();//进行延时,让电平持续1us
	EN = 1;//1602使能
	delay_1602();//进行延时,让电平持续1us
	EN = 0;
	delay_1602();//进行延时,让电平持续1us
}
/********************************
函数名称:D1602_Write_Dat
函数功能:1602显示屏发送数据
输入参数:dat(1602数据)
输    入:
输出参数:
输    出:
********************************/
void D1602_Write_Dat(u8 dat)
{
  	while(D1602_Read_Busy())//进行忙碌检测
	{
	 	 EN0();
	}
	RS = 1;//RS = 1则为数据模式
	delay_1602();//进行延时,让电平持续1us
	RW = 0;
	delay_1602();//进行延时,让电平持续1us
	data1602IO = dat;//发送数据
	delay_1602();//进行延时,让电平持续1us
	EN = 1;//1602使能
	delay_1602();//进行延时,让电平持续1us
	EN = 0;
	delay_1602();//进行延时,让电平持续1us
	DP1602++;
}
//u8 D1602_Read_Dat()
//{
//	D1602_Read_Busy();//进行忙碌检测
//	RS = 1;//RS = 1则为数据模式
//	delay_1602();//进行延时,让电平持续1us
//	RW = 1;
//	delay_1602();//进行延时,让电平持续1us
//	EN = 1;//1602使能
//	delay_1602();//进行延时,让电平持续1us
//	return data1602IO;//数据
//}
