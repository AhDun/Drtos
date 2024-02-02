/*********************************************************************************************************
* 文件名称：FlasdApp.c
* 摘    要：Flash写字符串/Flash读字符串/Flash续写字符串
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
#include"FlashApp.h"
#include"Flash.h"

/********************************
函数名称:outs_Flash
函数功能:Flash写字符串
输入参数:Flash_p(Flash指针),*fp(数据指针),n(长度)
输    入:
输出参数:
输    出:
********************************/
void outs_Flash(u16 Flash_p,u8 *fp,u8 n)
{
	Flash_erase(Flash_p);
	while(n > 0)//当长度小于等于0,退出运行
	{
		Flash_write(Flash_p,*fp++);//通过Flash_read函数写入到Flash
		n--;//长度减一
		Flash_p++;//Flash指针加一
	}
}
/********************************
函数名称:ins_Flash
函数功能:Flash读字符串
输入参数:Flash_p(Flash指针),*fp(数据指针),n(长度)
输    入:
输出参数:
输    出:
********************************/
void ins_Flash(u16 Flash_p,u8 *fp,u8 n)
{
	while(n > 0)//当长度小于等于0,退出运行
	{
		*fp++ = Flash_read(Flash_p);//通过Flash_read函数读取Flash
		n--;//长度减一
		Flash_p++;//Flash指针加一
	}
}
/********************************
函数名称:outsa_Flash
函数功能:Flash续写字符串
输入参数:Flash_p(Flash指针),*fp(数据指针),n(长度)
输    入:
输出参数:
输    出:
********************************/
void outsa_Flash(u16 Flash_p,u8 *fp,u8 n)
{
 	while(Flash_read(Flash_p) != 0xFF)
		Flash_p++;//Flash指针加一
	while(n > 0)//当长度小于等于0,退出运行
	{
		Flash_write(Flash_p,*fp++);
		n--;//长度减一
		Flash_p++;//Flash指针加一
	}
}
/********************************
函数名称:inchar_Flash
函数功能:Flash读字符
输入参数:Flash_p(Flash指针)
输    入:
输出参数:字符
输    出:
********************************/
u8 inchar_Flash(u16 Flash_p)
{
	return Flash_read(Flash_p);
}
/********************************
函数名称:outchar_Flash
函数功能:Flash写字符
输入参数:Flash_p(Flash指针),sdata(数据)
输    入:
输出参数:
输    出:
********************************/
void outchar_Flash(u16 Flash_p,u8 sdata)
{
	Flash_write(Flash_p,sdata);
}
/********************************
函数名称:DelErase_Flash
函数功能:擦除扇区
输入参数:
输    入:
输出参数:
输    出:
********************************/
void DelErase_Flash(u16 Flash_p)
{
	Flash_erase(Flash_p);
}

