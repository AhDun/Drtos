/*********************************************************************************************************
* 文件名称：STC.h
* 摘    要：
* 当前版本：1.0.0
* 作    者：阿顿
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
#include"STC.h"
/********************************
函数名称:BandgapV
函数功能:从RAM中读取Bandgap电压值
输入参数:
输入:
输出参数:Bandgap电压值
输出:
********************************/
u16 BandgapV()
{
 	return (*(int idata *)0xEF);
}
/********************************
函数名称:MCUID
函数功能:从RAM中读取取单片机ID
输入参数:
输    入:
输出参数:单片机ID
输    出:
********************************/
u8 MCUID()
{
 	return (*(char idata *)0xF1);
}
/********************************
函数名称:IRC32K
函数功能:从RAM中读取32K掉电唤醒定时器的频率
输入参数:
输    入:
输出参数:32K掉电唤醒定时器的频率
输    出:
********************************/
u8 IRC32K()
{
 	return(*(int idata *)0xF8); 
}
/********************************
函数名称:IRC22M
函数功能:从RAM中读取22.1184Mz的IRC参数
输入参数:
输    入:
输出参数:22.1184Mz的IRC参数
输    出:
********************************/
u8 IRC22M()
{
	return(*(char idata *)0xFA);
}
/********************************
函数名称:IRC24M
函数功能:从RAM中读取24Mz的IRC参数
输入参数:
输    入:
输出参数:24Mz的IRC参数
输    出:
********************************/
u8 IRC24M()
{
   return(*(char idata *)0xFB);
}
