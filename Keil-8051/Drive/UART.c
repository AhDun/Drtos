/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：UART.c

 * 文件内容：串口配置

 * 文件版本：1.0.0

 * 文件作者：阿顿

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  加载头文件区
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//基本库
#include "UART.h"
#include "System_Uart.h"
#include "Power.h"
#include "System_Task.h"
/*------------------------------------------------------------------------------------------------------------------------
                                                  变量初始化区
------------------------------------------------------------------------------------------------------------------------*/
u8 xdata TIBusy = 0;
#ifdef UART1_Enable
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：UART1Init

 * 函数功能：串口1初始化

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void UART1Init()
{
	SCON = 0x50;//8位数据,可变波特率
	AUXR &= 0xBF;//定时器1时钟为Fosc/12,即12T
	AUXR &= 0xFE;//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;//设定定时器1为16位自动重装方式
	TL1 = 0xFC;//设定定时初值
	TH1 = 0xFF;//设定定时初值
	ET1 = 0;//禁止定时器1中断
	TR1 = 1;//启动定时器1
	ES = 1;
	EA = 1;
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：UART1Interrupt

 * 函数功能：串口1中断服务

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void UART1Interrupt() interrupt 4
{
	if(RI)//判断接收是否完成
	{
		Systme_UART_Input();
		RI = 0;
	}
	else if(TI)//判断发送是否完成
	{
		TIBusy = 1;
		TI = 0;
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：OUT_UART1

 * 函数功能：串口1输出

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void OUT_UART1(u8 sdata)
{
 	 TIBusy = TI = 0;
	 SBUF = sdata;//将数据送入发送寄存器中，自动发送
	 while(1)
	 {
	  if(ES)
			if(TIBusy)
				break;
		if(!ES)
			if(TI)
				break;
	 }
	 TIBusy = TI = 0;
}
#endif
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：UART2Init

 * 函数功能：串口2初始化

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
#ifdef UART2_Enable
void UART2Init()
{
	/*S2CON - 串口 2 控制寄存器*/
	//bit7
	S2CON &= 0x7F;//可变波特率8位数据方式
//	S2CON |= 0x80;//可变波特率9位数据方式
	//bit5
	S2CON &= 0xDF;//允许串口 3 在模式 1 时允许多机通信控制位
//	S2CON |= 0x20;//允许串口 3 在模式 1 时允许多机通信控制位
	//bit4
//	S2CON &= 0xEF;//禁止串口接收数据 
	S2CON |= 0x10;//允许串口接收数据
	//bit3
//	S2CON &= 0xF7;//当串口 2 使用模式 1 时，S2TB8 为要发送的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位，按需要由软件置位或清 0。在模式 0 中，该位不用
//	S2CON |= 0x08;//当串口 2 使用模式 1 时，S2TB8 为要发送的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位，按需要由软件置位或清 0。在模式 0 中，该位不用
	//bit2
//	S2CON &= 0xFB;//当串口 2 使用模式 1 时，S2RB8 为接收到的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位。在模式 0 中，该位不用
//	S2CON |= 0x04;//当串口 2 使用模式 1 时，S2RB8 为接收到的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位。在模式 0 中，该位不用
	//bit1
	S2CON &= 0xFD;//串口 2 发送中断请求标志位
//	S2CON |= 0x02;//串口 2 发送中断请求标志位 
	//bit0
	S2CON &= 0xFE;//串口 2 接收中断请求标志位
//	S2CON |= 0x01;//串口 2 接收中断请求标志位
	/*定时器2用作波特率发生器*/
	T2L = 0x00;
	T2H = 0x00;
	/*IE2 - 中断使能寄存器 2*/
	//bit0
//	IE2 &= 0xFE;//禁止串行口 2 中断
	IE2 |= 0x01;//允许串行口 2 中断
	/*IE - 中断使能寄存器 */
	//bit7
//	IE2 &= 0x7F;//CPU 屏蔽所有的中断申请
	IE2 |= 0x80;//CPU 开放中断 
	/*AUXR - 辅助寄存器 1 */ 
	//bit2
	AUXR &= 0xFB;//定时器2以12T速度运行
	AUXR |= 0x04;//定时器2以6T速度运行
	//bit4
//	AUXR &= 0xEF;//关闭定时器2
	AUXR |= 0x10;//开启定时器2
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：UART2Interrupt

 * 函数功能：串口2中断服务

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void UART2Interrupt() interrupt 8
{
	if(S2CON & 0x01)//判断接收是否完成
	{
		S2CON &= 0xFE;
	}
	else if(S2CON & 0x02)//判断发送是否完成
	{
		S2CON &= 0xFD;
	}
}
#endif
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：UART3Init

 * 函数功能：串口3初始化

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
#ifdef UART3_Enable
void UART3Init()
{
	/*S3CON - 串口 2 控制寄存器*/
	//bit7
	S3CON &= 0x7F;//可变波特率8位数据方式
//	S3CON |= 0x80;//可变波特率9位数据方式
	//bit6
	S3CON &= 0xBF;//选择定时器 2 为串口 3 的波特率发生器
//	S3CON |= 0x40;//选择定时器 3 为串口 3 的波特率发生器
	//bit5
	S3CON &= 0xDF;//允许串口 3 在模式 1 时允许多机通信控制位
//	S3CON |= 0x20;//允许串口 3 在模式 1 时允许多机通信控制位
	//bit4
//	S3CON &= 0xEF;//禁止串口接收数据 
	S3CON |= 0x10;//允许串口接收数据
	//bit3
//	S3CON &= 0xF7;//当串口 3 使用模式 1 时，S2TB8 为要发送的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位，按需要由软件置位或清 0。在模式 0 中，该位不用
//	S3CON |= 0x08;//当串口 3 使用模式 1 时，S2TB8 为要发送的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位，按需要由软件置位或清 0。在模式 0 中，该位不用
	//bit2
//	S3CON &= 0xFB;//当串口 3 使用模式 1 时，S2RB8 为接收到的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位。在模式 0 中，该位不用
//	S3CON |= 0x04;//当串口 3 使用模式 1 时，S2RB8 为接收到的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位。在模式 0 中，该位不用
	//bit1
	S3CON &= 0xFD;//串口 3 发送中断请求标志位
//	S3CON |= 0x02;//串口 3 发送中断请求标志位 
	//bit0
	S3CON &= 0xFE;//串口 3 接收中断请求标志位
//	S3CON |= 0x01;//串口 3 接收中断请求标志位
	/*IE2 - 中断使能寄存器 2*/
	//bit3
//	IE2 &= 0xF7;//禁止串行口 3 中断

	IE2 |= 0x08;//允许串行口 3 中断
	/*IE - 中断使能寄存器 */
	//bit7
//	IE2 &= 0x7F;//CPU 屏蔽所有的中断申请
	IE2 |= 0x80;//CPU 开放中断 
	
	/*定时器2用作波特率发生器*/
	T2L = 0x00;
	T2H = 0x00;
	/*AUXR - 辅助寄存器 1*/ 
	//bit2
	AUXR &= 0xFB;//定时器2以12T速度运行
	AUXR |= 0x04;//定时器2以6T速度运行
	//bit4
//	AUXR &= 0xEF;//关闭定时器2
	AUXR |= 0x10;//开启定时器2

/*定时器3用作波特率发生器
	//T4T3M - 定时器 4/3 控制寄存器
	//bit3
	T4T3M &= 0xF7;//定时器 3 停止计数
	T4T3M |= 0x08;//定时器 3 开始计数
*/


}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：UART3Interrupt

 * 函数功能：串口3中断服务

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void UART3Interrupt() interrupt 17
{
	if(S3CON & 0x01)//判断接收是否完成
	{
		S3CON &= 0xFE;
	}
	else if(S3CON & 0x02)//判断发送是否完成
	{
		S3CON &= 0xFD;
	}
}
#endif
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：UART4Init

 * 函数功能：串口4初始化

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
#ifdef UART4_Enable
void UART4Init()
{
	/*S4CON - 串口 2 控制寄存器*/
	//bit7
	S4CON &= 0x7F;//可变波特率8位数据方式
//	S4CON |= 0x80;//可变波特率9位数据方式
	//bit6
	S4CON &= 0xBF;//选择定时器 2 为串口 3 的波特率发生器
//	S4CON |= 0x40;//选择定时器 4 为串口 3 的波特率发生器
	//bit5
	S4CON &= 0xDF;//允许串口 3 在模式 1 时允许多机通信控制位
//	S4CON |= 0x20;//允许串口 3 在模式 1 时允许多机通信控制位
	//bit4
//	S4CON &= 0xEF;//禁止串口接收数据 
	S4CON |= 0x10;//允许串口接收数据
	//bit3
//	S4CON &= 0xF7;//当串口 3 使用模式 1 时，S2TB8 为要发送的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位，按需要由软件置位或清 0。在模式 0 中，该位不用
//	S4CON |= 0x08;//当串口 3 使用模式 1 时，S2TB8 为要发送的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位，按需要由软件置位或清 0。在模式 0 中，该位不用
	//bit2
//	S4CON &= 0xFB;//当串口 3 使用模式 1 时，S2RB8 为接收到的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位。在模式 0 中，该位不用
//	S4CON |= 0x04;//当串口 3 使用模式 1 时，S2RB8 为接收到的第 9 位数据，一般用作校验位或者地址帧/数据帧标志位。在模式 0 中，该位不用
	//bit1
	S4CON &= 0xFD;//串口 3 发送中断请求标志位
//	S4CON |= 0x02;//串口 3 发送中断请求标志位 
	//bit0
	S4CON &= 0xFE;//串口 3 接收中断请求标志位
//	S4CON |= 0x01;//串口 3 接收中断请求标志位
	/*IE2 - 中断使能寄存器 2*/
	//bit4
//	IE2 &= &= 0xEF;//禁止串行口 4 中断

	IE2 |= 0x10;//允许串行口 4 中断
	/*IE - 中断使能寄存器 */
	//bit7
//	IE2 &= 0x7F;//CPU 屏蔽所有的中断申请
	IE2 |= 0x80;//CPU 开放中断 
	
	/*定时器2用作波特率发生器*/
	T2L = 0x00;
	T2H = 0x00;
	/*AUXR - 辅助寄存器 1*/ 
	//bit2
	AUXR &= 0xFB;//定时器2以12T速度运行
	AUXR |= 0x04;//定时器2以6T速度运行
	//bit4
//	AUXR &= 0xEF;//关闭定时器2
	AUXR |= 0x10;//开启定时器2

/*定时器4用作波特率发生器
	//T4T3M - 定时器 4/3 控制寄存器
	//bit3
	T4T3M &= 0x7F;//定时器 4 停止计数
	T4T3M |= 0x80;//定时器 4 开始计数
	//bit7
*/


}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：UART4Interrupt

 * 函数功能：串口4中断服务

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
/********************************
函数名称:UART4Interrupt
函数功能:串口4中断服务
输入参数:
输    入:
输出参数:
输    出:
********************************/
void UART4Interrupt() interrupt 18
{
	if(S4CON & 0x01)//判断接收是否完成
	{
		S4CON &= 0xFE;
	}
	else if(S4CON & 0x02)//判断发送是否完成
	{
		S4CON &= 0xFD;
	}
}
#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/