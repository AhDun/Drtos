/*********************************************************************************************************
* 文件名称：IRApp.c
* 摘    要：红外初始化/红外码值处理函数/红外键值散转程序/获取红外数值
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
#include"IRApp.h"
#include"PCA.h"

u8 xdata irpro_ok = 0,irok = 0,startflag = 0;
u8 xdata IR_DATA_SP = 0;
u8 xdata IRcord[4] = {0};//红外解码后数据
u8 xdata irdata[33] = {0};//红外数据

/********************************
函数名称:IRInit
函数功能:红外初始化
输入参数:
输    入:
输出参数:
输    出:
********************************/
void IRInit()
{
	PCA0Init();
} 
/********************************
函数名称:EX0Interrupts
函数功能:红外外部中断0服务函数
输入参数:
输    入:
输出参数:
输    出:
********************************/
void IREX()
{
	length[0] /=  250;
	if(startflag)                         
	{
		if(length[0] < 63 && length[0] >= 33)//引导码 TC9012的头码，9ms+4.5ms
        	IR_DATA_SP = 0;
    	irdata[IR_DATA_SP++] = length[0];//存储每个电平的持续时间，用于以后判断是0还是1
    	length[0]  = 0;
		if(IR_DATA_SP == 33)//33位数据
  		{
  			irok = 1;//接收完成标志位
			IR_DATA_SP = startflag = 0;
  		}
	}
	else//记录初始化
	{
		length[0] = 0;//清空
		startflag = 1;//下次开始接收
	}
}
/********************************
函数名称:Ircordpro
函数功能:红外码值处理函数
输入参数:
输    入:
输出参数:
输    出:
********************************/
void Ircordpro()
{ 
	u8 i, j, k,value;
	for(i = 0 ,k = 1;i < 4; i++)      //处理4个字节
	{
		for(j = 1;j <= 8; j++) //处理1个字节8位
		{
			if(irdata[k++] > 5)//大于某值为1，这个和晶振有绝对关系，这里使用12M计算，此值可以有一定误差
				value = value | 0x80;//高位写1
			if(j < 8)
				value >>= 1;//高位写0
		}
		IRcord[i] = value;
		value = 0;     
	} 
	irpro_ok = 1;//处理完毕标志位置1
}
/********************************
函数名称:Ir_work
函数功能:红外键值散转程序
输入参数:
输    入:
输出参数:红外散转后的数值
输    出:
********************************/
u8 Ir_work()
{
	switch(IRcord[2])//判断第三个数码值
	{
		case 0x16:return 0;//0 
		case 0x0c:return 1;//1 
		case 0x18:return 2;//2
		case 0x5e:return 3;//3
		case 0x08:return 4;//4
		case 0x1c:return 5;//5
		case 0x5a:return 6;//6
		case 0x42:return 7;//7
		case 0x52:return 8;//8
		case 0x4a:return 9;//9
		case 0x45:return 10;//10 
		case 0x46:return 11;//11
		case 0x47:return 12;//12
		case 0x44:return 13;//13
		case 0x40:return 14;//14
		case 0x43:return 15;//15
		case 0x07:return 16;//16
		case 0x15:return 17;//17
		case 0x09:return 18;//18
		case 0x19:return 19;//19
		case 0x0d:return 20;//20
	}
	return 0xFF;
}
/********************************
函数名称:TRkeyvalue
函数功能:获取红外数值
输入参数:
输    入:
输出参数:红外散转后的数值
输    出:
********************************/
u8 in_IRkv()
{
	if(!CR)//检测是否开启运行,如果关闭，为其打开
		IRInit();//红外初始化
	if(irok)//如果接收好了进行红外处理
	{   
		irok = 0;
		Ircordpro();
	}
	if(irpro_ok)//如果处理好后进行工作处理，如按对应的按键后显示对应的数字等
	{
		irpro_ok = 0;
		return Ir_work();//通过散转，通过获取数值
	}
	return 0xFF;
}
