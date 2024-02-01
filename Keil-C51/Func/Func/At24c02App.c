/*********************************************************************************************************
* 文件名称：At24c02App.c
* 摘    要：写AT24c02/读AT24c02/AT24c02读字符串/AT24c02写字符串/删除AT24c02所有数据
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
#include"At24c02App.h"
#include"Sdelay.h"
#include"I2C.h"

/********************************
函数名称:delay_At24c02
函数功能:At24c02专用延时
输入参数:
输    入:
输出参数:
输    出:
********************************/
void delay_At24c02()
{
 	delay_ms(5);//软件延时5ms
}
/********************************
函数名称:At24c02Write
函数功能:写AT24c02
输入参数:addr(地址),dat(数据)
输    入:
输出参数:
输    出:
********************************/
void At24c02Write(u8 addr,u8 dat)
{
	#if	I2CIFCON == 0
	if((I2CCFG & 0x80) == 0)
		SI2CInit();
	#endif
	Start();//产生起始信号
	SendByte(At24c02Address + 0);//发送写器件地址
	SendByte(addr);//发送要写入内存地址
	SendByte(dat);//发送数据
	Stop();//产生结束信号
}
/********************************
函数名称:At24c02Read
函数功能:读AT24c02
输入参数:addr(地址)
输    入:
输出参数:数据
输    出:
********************************/
u8 At24c02Read(u8 addr)
{
	#if	I2CIFCON == 0
	if((I2CCFG & 0x80) == 0)
		SI2CInit();
	#endif
	Start();//产生起始信号
	SendByte(At24c02Address + 0); //发送写器件地址
	SendByte(addr); //发送要读取的地址
	Start();//产生起始信号
	SendByte(At24c02Address + 1); //发送读器件地址
	addr = ReadByte(); //读取数据
	Stop();//产生结束信号
	return addr;//返回数据	
}
/********************************
函数名称:outs_At24c02
函数功能:AT24c02写字符串
输入参数:Flash_p(Flash指针),*fp(数据指针),n(长度)
输    入:
输出参数:
输    出:
********************************/
void outs_At24c02(u8 Flash_p,u8 *fp,u8 n)
{
	#if	I2CIFCON == 0
	if((I2CCFG & 0x80) == 0)
		SI2CInit();
	#endif
	while(n > 0)
	{
		At24c02Write(Flash_p,*fp++);//通过At24c02Write函数写入到At24c02EEPROM
		delay_At24c02();//软件延时10ms
		n--;//长度减一
		Flash_p++;//EEPROM指针加一
	}
}
/********************************
函数名称:ins_At24c02
函数功能:AT24c02读字符串
输入参数:Flash_p(Flash指针),*fp(数据指针),n(长度)
输    入:
输出参数:
输    出:
********************************/
void ins_At24c02(u8 Flash_p,u8 *fp,u8 n)
{
	#if	I2CIFCON == 0
	if((I2CCFG & 0x80) == 0)
		SI2CInit();
	#endif
	Start();//产生起始信号
	SendByte(At24c02Address + 0); //发送写器件地址
	SendByte(Flash_p); //发送要读取的地址
	Start();//产生起始信号
	SendByte(At24c02Address + 1); //发送读器件地址
	while(n > 0)
	{
		*fp++ = ReadByte();//通过At24c02Read函数读取At24c02EEPROM
		SendOk();//发送应答信号
		n--;//长度减一
	}
	Stop();//产生结束信号
}
/********************************
函数名称:Del_At24c02
函数功能:删除AT24c02所有数据
输入参数:
输    入:
输出参数:
输    出:
********************************/
void Del_AT24c02()
{
 	u8 a;
	#if	I2CIFCON == 0
	if((I2CCFG & 0x80) == 0)
		SI2CInit();
	#endif
	for(a = 1; a > 0; a++)//使用for进行遍历,当a值溢出后for停止循环
	{
	 	if(a == 1)
		{
			At24c02Write(0,0xFF);//通过At24c02Write函数将0xFF写入到At24c02EEPROM
			delay_At24c02();//软件延时10ms
		}
		At24c02Write(a,0xFF);//通过At24c02Write函数将0xFF写入到At24c02EEPROM
		delay_At24c02();//软件延时10ms	
	}
}

