/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：delay_Lib.c

 * 文件内容：软件延时

 * 文件版本：1.0.0

 * 文件作者：麦特实验室

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  加载头文件区
------------------------------------------------------------------------------------------------------------------------*/	

#include "main.h"//基本库
#include "delay_Lib.h"

/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：Dus

 * 函数功能：单位微秒延时

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void Dus()
{
	u8 e;
	_nop_();
	e = 5;
	while (--e);
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：Dms

 * 函数功能：单位毫秒延时

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void Dms()
{
 	u8 a = 29;
	u8 b = 183;
	do
	{
		while (--b);
	} while (--a);
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：delay_ms

 * 函数功能：毫秒级软件延时

 * 输入参数：ms_s(延时毫秒)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void delay_ms(u16 ms_s)
{	
	u16 x;
	for(x = ms_s; x > 0; x--)
	{
		Dms();
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：delay_us

 * 函数功能：微秒级软件延时

 * 输入参数：us_s(延时微秒)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void delay_us(u16 us_s)
{	
	u16 y;
	for(y = us_s; y > 0; y--)
	{
		Dus();
	}
}

/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/