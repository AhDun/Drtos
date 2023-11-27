/*********************************************************************************************************
* 文件名称：PWM.c
* 摘    要：
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
#include"PWM.h"
#include"Sdelay.h"

/********************************
函数名称:CPWM
函数功能:软件PWM调制
输入参数:x(频数)HzValue(刷新率)
输    入:
输出参数:高低电平
输    出:
********************************/
void CPWM(u16 x,u8 HzValue,u8 Spped)
{
	static u2 LHs;
	x *= Spped;
	if(LHs)
	{
		LHs = PWMOUT =  0;//低电平
		delay_us(x);//延时
	}
	else
	{
		LHs = PWMOUT =  1;//高电平
		delay_us(1000000 / HzValue - x);//延时
	}
}
/********************************
函数名称:PWMInit
函数功能:硬件PWM初始化
输入参数:
输    入:
输出参数:
输    出:
********************************/
void PWMInit()
{
	P_SW2 |= 0x80;
	/*PWMCFG - 增强型 PWM 配置寄存器*/
	//bit7
//	PWMCFG &= 0x7F;// 15 位的 PWM 计数器记满溢出归零时，硬件自动将此位置 1，并向 CPU 提出中断请求，此标志位需要软件清零
//	PWMCFG |= 0x80;// 15 位的 PWM 计数器记满溢出归零时，硬件自动将此位置 1，并向 CPU 提出中断请求，此标志位需要软件清零
	//bit6
	PWMCFG &= 0xBF;//PWM 与 ADC 不关联
//	PWMCFG |= 0x40;//：PWM 与 ADC 相关联。允许在 PWM 周期中某个时间点触发 A/D 转换。使用 TADCPH 和 TADCPL进行设置
	/*PWMIF - PWM 中断标志寄存器*/
	//Bit
	PWMIF = 0x00;//清空所有PWM的中断标志位
	/*PWMFDCR - PWM 异常检测控制寄存器*/
	//bit7
	PWMFDCR &= 0x7F;//比较器器结果由低变高为异常信号
//	PWMFDCR |= 0x80;//比较器器结果由高变低为异常信号
	//bit6
	PWMFDCR &= 0xBF;//外部端口 P3.5 信号由低变高为异常信号
//	PWMFDCR |= 0x40;//外部端口 P3.5 信号由高变低为异常信号
	//bit5
	PWMFDCR &= 0xDF;//关闭 PWM 外部异常检测功能
//	PWMFDCR |= 0x20;//使能 PWM 外部异常检测功能

	//bit4
	PWMFDCR &= 0xEF;//发生 WM 外部异常时，PWM 的输出口不作任何改变
//	PWMFDCR |= 0x10;//发生 WM 外部异常时，PWM 的输出口立即被设置为高阻输入模式。（注：只有 ENCnO=1 所对
	//bit3
	PWMFDCR &= 0xF7;//关闭 PWM 异常检测中断（FDIF 依然会被硬件置位）
//	PWMFDCR |= 0x08;//使能 PWM 异常检测中断

	//bit2
	PWMFDCR &= 0xFB;//比较器与 PWM 无关

//	PWMFDCR |= 0x04;//设定 PWM 异常检测源为比较器输出（异常类型有 INVCMP 设定）

	//bit1
	PWMFDCR &= 0xFD;//P3.5 口电平与 PWM 无关
//	PWMFDCR |= 0x02;//设定 PWM 异常检测源为 P3.5 口（异常类型有 INVIO 设定）

	//bit0
//	PWMFDCR &= 0xFE;//PWM 异常检测中断标志位
//	PWMFDCR |= 0x01;//PWM 异常检测中断标志位
	/*PWMCKS - PWM 时钟选择寄存器*/
	//bit4
	PWMCKS &= 0xEF;//PWM 时钟源为系统时钟经分频器分频之后的时钟
//	PWMCKS |= 0x10;//PWM 时钟源为定时器 2 的溢出脉冲
	//bit3 - bit0
	/*
	SELT2 PWM_PS[3:0] PWM 输入时钟源频率
		1 xxxx 定时器 2 的溢出脉冲
		0 0000 SYSclk/1
		0 0001 SYSclk/2
		0 0010 SYSclk/3
		… … …
		0 x SYSclk/(x+1)
		… … …
		0 1111 SYSclk/16 
	*/
	PWMCKS |= 0x00; 
	/*PWM 计数器寄存器*/
	//Bit
	PWMCH = 0x00;
	//Bit
	PWMCL = 0x00;
	/*PWMCR - PWM 控制寄存器*/
	//bit6
//	PWMCR &= 0xBF;//关闭 PWM 计数器归零中断（CBIF 依然会被硬件置位）
	PWMCR |= 0x40;//使能 PWM 计数器归零中断
	//bit7
//	PWMCR &= 0x7F;//关闭 PWM 波形发生器
	PWMCR |= 0x80;//使能 PWM 波形发生器，PWM 计数器开始计数

}
/********************************
函数名称:PWM0Init
函数功能:PWM0通道初始化
输入参数:
输    入:
输出参数:
输    出:
********************************/
void PWM0Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM0HLD - PWM 通道电平保持控制寄存器*/
	//bit1
	PWM0HLD &= 0xFD;//通道 PWM 正常输出
//	PWM0HLD |= 0x02;//通道 PWM 强制输出高电平 
	//bit0
	PWM0HLD &= 0xFE;//通道 PWM 正常输出
//	PWM0HLD |= 0x01;//通道 PWM 正常输出
	/*PWM0T1H - PWM0T1L - PWM0T2H  - PWM0T2L   PWM 翻转点设置计数值寄存器*/	
	PWM0T1H = 0x00;
	PWM0T1L = 0x00;
	PWM0T2H = 0x00;
	PWM0T2L = 0x00;
	/*PWM0CR - PWM0 通道控制寄存器*/
	//bit7
//	PWM0CR &= 0x7F;//相应 PWM 通道的端口为 GPIO 
	PWM0CR |= 0x80;//相应 PWM 通道的端口为 PWM 输出口，受 PWM 波形发生器控制
	//bit6
	PWM0CR &= 0xBF;//通道的 PWM 初始电平为低电平
//	PWM0CR |= 0x40;//通道的 PWM 初始电平为高电平
	//bit4 - bit3 PWM 输出功能脚切换选择，
	//bit2
//	PWM0CR &= 0xFB;//关闭通道的 PWM 中断
	PWM0CR |= 0x04;//使能通道的 PWM 中断
	//bit1
	PWM0CR &= 0xFD;//关闭通道的 PWM 在第 2 个翻转点中断
//	PWM0CR |= 0x02;//使能通道的 PWM 在第 2 个翻转点中断 
	//bit0
	PWM0CR &= 0xFE;//关闭通道的 PWM 在第 1 个翻转点中断
//	PWM0CR |= 0x01;//使能通道的 PWM 在第 1 个翻转点中断
}
/********************************
函数名称:PWM1Init
函数功能:PWM1通道初始化
输入参数:
输    入:
输出参数:
输    出:
********************************/
void PWM1Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM1HLD - PWM 通道电平保持控制寄存器*/
	//bit1
	PWM1HLD &= 0xFD;//通道 PWM 正常输出
//	PWM1HLD |= 0x02;//通道 PWM 强制输出高电平 
	//bit0
	PWM1HLD &= 0xFE;//通道 PWM 正常输出
//	PWM1HLD |= 0x01;//通道 PWM 正常输出
	/*PWM1T1H - PWM1T1L - PWM1T2H  - PWM1T2L   PWM 翻转点设置计数值寄存器*/	
	PWM1T1H = 0x00;
	PWM1T1L = 0x00;
	PWM1T2H = 0x00;
	PWM1T2L = 0x00;
	/*PWM1CR - PWM1 通道控制寄存器*/
	//bit7
//	PWM1CR &= 0x7F;//相应 PWM 通道的端口为 GPIO 
	PWM1CR |= 0x80;//相应 PWM 通道的端口为 PWM 输出口，受 PWM 波形发生器控制
	//bit6
	PWM1CR &= 0xBF;//通道的 PWM 初始电平为低电平
//	PWM1CR |= 0x40;//通道的 PWM 初始电平为高电平
	//bit4 - bit3 PWM 输出功能脚切换选择，
	//bit2
//	PWM1CR &= 0xFB;//关闭通道的 PWM 中断
	PWM1CR |= 0x04;//使能通道的 PWM 中断
	//bit1
	PWM1CR &= 0xFD;//关闭通道的 PWM 在第 2 个翻转点中断
//	PWM1CR |= 0x02;//使能通道的 PWM 在第 2 个翻转点中断 
	//bit0
	PWM1CR &= 0xFE;//关闭通道的 PWM 在第 1 个翻转点中断
//	PWM1CR |= 0x01;//使能通道的 PWM 在第 1 个翻转点中断
}
/********************************
函数名称:PWM2Init
函数功能:PWM2通道初始化
输入参数:
输    入:
输出参数:
输    出:
********************************/
void PWM2Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM2HLD - PWM 通道电平保持控制寄存器*/
	//bit1
	PWM2HLD &= 0xFD;//通道 PWM 正常输出
//	PWM2HLD |= 0x02;//通道 PWM 强制输出高电平 
	//bit0
	PWM2HLD &= 0xFE;//通道 PWM 正常输出
//	PWM2HLD |= 0x01;//通道 PWM 正常输出
	/*PWM2T1H - PWM2T1L - PWM2T2H  - PWM2T2L   PWM 翻转点设置计数值寄存器*/	
	PWM2T1H = 0x00;
	PWM2T1L = 0x00;
	PWM2T2H = 0x00;
	PWM2T2L = 0x00;
	/*PWM2CR - PWM2 通道控制寄存器*/
	//bit7
//	PWM2CR &= 0x7F;//相应 PWM 通道的端口为 GPIO 
	PWM2CR |= 0x80;//相应 PWM 通道的端口为 PWM 输出口，受 PWM 波形发生器控制
	//bit6
	PWM2CR &= 0xBF;//通道的 PWM 初始电平为低电平
//	PWM2CR |= 0x40;//通道的 PWM 初始电平为高电平
	//bit4 - bit3 PWM 输出功能脚切换选择，
	//bit2
//	PWM2CR &= 0xFB;//关闭通道的 PWM 中断
	PWM2CR |= 0x04;//使能通道的 PWM 中断
	//bit1
	PWM2CR &= 0xFD;//关闭通道的 PWM 在第 2 个翻转点中断
//	PWM2CR |= 0x02;//使能通道的 PWM 在第 2 个翻转点中断 
	//bit0
	PWM2CR &= 0xFE;//关闭通道的 PWM 在第 1 个翻转点中断
//	PWM2CR |= 0x01;//使能通道的 PWM 在第 1 个翻转点中断
}
/********************************
函数名称:PWM3Init
函数功能:PWM3通道初始化
输入参数:
输    入:
输出参数:
输    出:
********************************/
void PWM3Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM3HLD - PWM 通道电平保持控制寄存器*/
	//bit1
	PWM3HLD &= 0xFD;//通道 PWM 正常输出
//	PWM3HLD |= 0x02;//通道 PWM 强制输出高电平 
	//bit0
	PWM3HLD &= 0xFE;//通道 PWM 正常输出
//	PWM3HLD |= 0x01;//通道 PWM 正常输出
	/*PWM3T1H - PWM3T1L - PWM3T2H  - PWM3T2L   PWM 翻转点设置计数值寄存器*/	
	PWM3T1H = 0x00;
	PWM3T1L = 0x00;
	PWM3T2H = 0x00;
	PWM3T2L = 0x00;
	/*PWM3CR - PWM3 通道控制寄存器*/
	//bit7
//	PWM3CR &= 0x7F;//相应 PWM 通道的端口为 GPIO 
	PWM3CR |= 0x80;//相应 PWM 通道的端口为 PWM 输出口，受 PWM 波形发生器控制
	//bit6
	PWM3CR &= 0xBF;//通道的 PWM 初始电平为低电平
//	PWM3CR |= 0x40;//通道的 PWM 初始电平为高电平
	//bit4 - bit3 PWM 输出功能脚切换选择，
	//bit2
//	PWM3CR &= 0xFB;//关闭通道的 PWM 中断
	PWM3CR |= 0x04;//使能通道的 PWM 中断
	//bit1
	PWM3CR &= 0xFD;//关闭通道的 PWM 在第 2 个翻转点中断
//	PWM3CR |= 0x02;//使能通道的 PWM 在第 2 个翻转点中断 
	//bit0
	PWM3CR &= 0xFE;//关闭通道的 PWM 在第 1 个翻转点中断
//	PWM3CR |= 0x01;//使能通道的 PWM 在第 1 个翻转点中断
}
/********************************
函数名称:PWM4Init
函数功能:PWM4通道初始化
输入参数:
输    入:
输出参数:
输    出:
********************************/
void PWM4Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM4HLD - PWM 通道电平保持控制寄存器*/
	//bit1
	PWM4HLD &= 0xFD;//通道 PWM 正常输出
//	PWM4HLD |= 0x02;//通道 PWM 强制输出高电平 
	//bit0
	PWM4HLD &= 0xFE;//通道 PWM 正常输出
//	PWM4HLD |= 0x01;//通道 PWM 正常输出
	/*PWM4T1H - PWM4T1L - PWM4T2H  - PWM4T2L   PWM 翻转点设置计数值寄存器*/	
	PWM4T1H = 0x00;
	PWM4T1L = 0x00;
	PWM4T2H = 0x00;
	PWM4T2L = 0x00;
	/*PWM4CR - PWM4 通道控制寄存器*/
	//bit7
//	PWM4CR &= 0x7F;//相应 PWM 通道的端口为 GPIO 
	PWM4CR |= 0x80;//相应 PWM 通道的端口为 PWM 输出口，受 PWM 波形发生器控制
	//bit6
	PWM4CR &= 0xBF;//通道的 PWM 初始电平为低电平
//	PWM4CR |= 0x40;//通道的 PWM 初始电平为高电平
	//bit4 - bit3 PWM 输出功能脚切换选择，
	//bit2
//	PWM4CR &= 0xFB;//关闭通道的 PWM 中断
	PWM4CR |= 0x04;//使能通道的 PWM 中断
	//bit1
	PWM4CR &= 0xFD;//关闭通道的 PWM 在第 2 个翻转点中断
//	PWM4CR |= 0x02;//使能通道的 PWM 在第 2 个翻转点中断 
	//bit0
	PWM4CR &= 0xFE;//关闭通道的 PWM 在第 1 个翻转点中断
//	PWM4CR |= 0x01;//使能通道的 PWM 在第 1 个翻转点中断
}
/********************************
函数名称:PWM5Init
函数功能:PWM5通道初始化
输入参数:
输    入:
输出参数:
输    出:
********************************/
void PWM5Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM5HLD - PWM 通道电平保持控制寄存器*/
	//bit1
	PWM5HLD &= 0xFD;//通道 PWM 正常输出
//	PWM5HLD |= 0x02;//通道 PWM 强制输出高电平 
	//bit0
	PWM5HLD &= 0xFE;//通道 PWM 正常输出
//	PWM5HLD |= 0x01;//通道 PWM 正常输出
	/*PWM5T1H - PWM5T1L - PWM5T2H  - PWM5T2L   PWM 翻转点设置计数值寄存器*/	
	PWM5T1H = 0x00;
	PWM5T1L = 0x00;
	PWM5T2H = 0x00;
	PWM5T2L = 0x00;
	/*PWM5CR - PWM5 通道控制寄存器*/
	//bit7
//	PWM5CR &= 0x7F;//相应 PWM 通道的端口为 GPIO 
	PWM5CR |= 0x80;//相应 PWM 通道的端口为 PWM 输出口，受 PWM 波形发生器控制
	//bit6
	PWM5CR &= 0xBF;//通道的 PWM 初始电平为低电平
//	PWM5CR |= 0x40;//通道的 PWM 初始电平为高电平
	//bit4 - bit3 PWM 输出功能脚切换选择，
	//bit2
//	PWM5CR &= 0xFB;//关闭通道的 PWM 中断
	PWM5CR |= 0x04;//使能通道的 PWM 中断
	//bit1
	PWM5CR &= 0xFD;//关闭通道的 PWM 在第 2 个翻转点中断
//	PWM5CR |= 0x02;//使能通道的 PWM 在第 2 个翻转点中断 
	//bit0
	PWM5CR &= 0xFE;//关闭通道的 PWM 在第 1 个翻转点中断
//	PWM5CR |= 0x01;//使能通道的 PWM 在第 1 个翻转点中断
}
/********************************
函数名称:PWM6Init
函数功能:PWM6通道初始化
输入参数:
输    入:
输出参数:
输    出:
********************************/
void PWM6Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM6HLD - PWM 通道电平保持控制寄存器*/
	//bit1
	PWM6HLD &= 0xFD;//通道 PWM 正常输出
//	PWM6HLD |= 0x02;//通道 PWM 强制输出高电平 
	//bit0
	PWM6HLD &= 0xFE;//通道 PWM 正常输出
//	PWM6HLD |= 0x01;//通道 PWM 正常输出
	/*PWM6T1H - PWM6T1L - PWM6T2H  - PWM6T2L   PWM 翻转点设置计数值寄存器*/	
	PWM6T1H = 0x00;
	PWM6T1L = 0x00;
	PWM6T2H = 0x00;
	PWM6T2L = 0x00;
	/*PWM6CR - PWM6 通道控制寄存器*/
	//bit7
//	PWM6CR &= 0x7F;//相应 PWM 通道的端口为 GPIO 
	PWM6CR |= 0x80;//相应 PWM 通道的端口为 PWM 输出口，受 PWM 波形发生器控制
	//bit6
	PWM6CR &= 0xBF;//通道的 PWM 初始电平为低电平
//	PWM6CR |= 0x40;//通道的 PWM 初始电平为高电平
	//bit4 - bit3 PWM 输出功能脚切换选择，
	//bit2
//	PWM6CR &= 0xFB;//关闭通道的 PWM 中断
	PWM6CR |= 0x04;//使能通道的 PWM 中断
	//bit1
	PWM6CR &= 0xFD;//关闭通道的 PWM 在第 2 个翻转点中断
//	PWM6CR |= 0x02;//使能通道的 PWM 在第 2 个翻转点中断 
	//bit0
	PWM6CR &= 0xFE;//关闭通道的 PWM 在第 1 个翻转点中断
//	PWM6CR |= 0x01;//使能通道的 PWM 在第 1 个翻转点中断
}
/********************************
函数名称:PWM7Init
函数功能:PWM7通道初始化
输入参数:
输    入:
输出参数:
输    出:
********************************/
void PWM7Init()
{
	P_SW2 = 0x80;
	if((PWMCR & 0x80) == 0)
		PWMInit();
	
	/*PWM7HLD - PWM 通道电平保持控制寄存器*/
	//bit1
	PWM7HLD &= 0xFD;//通道 PWM 正常输出
//	PWM7HLD |= 0x02;//通道 PWM 强制输出高电平 
	//bit0
	PWM7HLD &= 0xFE;//通道 PWM 正常输出
//	PWM7HLD |= 0x01;//通道 PWM 正常输出
	/*PWM7T1H - PWM7T1L - PWM7T2H  - PWM7T2L   PWM 翻转点设置计数值寄存器*/	
	PWM7T1H = 0x00;
	PWM7T1L = 0x00;
	PWM7T2H = 0x00;
	PWM7T2L = 0x00;
	/*PWM7CR - PWM7 通道控制寄存器*/
	//bit7
//	PWM7CR &= 0x7F;//相应 PWM 通道的端口为 GPIO 
	PWM7CR |= 0x80;//相应 PWM 通道的端口为 PWM 输出口，受 PWM 波形发生器控制
	//bit6
	PWM7CR &= 0xBF;//通道的 PWM 初始电平为低电平
//	PWM7CR |= 0x40;//通道的 PWM 初始电平为高电平
	//bit4 - bit3 PWM 输出功能脚切换选择，
	//bit2
//	PWM7CR &= 0xFB;//关闭通道的 PWM 中断
	PWM7CR |= 0x04;//使能通道的 PWM 中断
	//bit1
	PWM7CR &= 0xFD;//关闭通道的 PWM 在第 2 个翻转点中断
//	PWM7CR |= 0x02;//使能通道的 PWM 在第 2 个翻转点中断 
	//bit0
	PWM7CR &= 0xFE;//关闭通道的 PWM 在第 1 个翻转点中断
//	PWM7CR |= 0x01;//使能通道的 PWM 在第 1 个翻转点中断
}
void PWMInterrupt() interrupt 22
{
 	if(PWMCFG & 0x80)
	{
	   PWMCFG &= 0x7F;
	}
	if(PWMIF & 0x01)
	{
	   PWMIF &= 0xFE;
	}
	if(PWMIF & 0x02)
	{
	   PWMIF &= 0xFD;
	}
	if(PWMIF & 0x04)
	{
	   PWMIF &= 0xFB;
	}
	if(PWMIF & 0x08)
	{
	   PWMIF &= 0xF7;
	}
	if(PWMIF & 0x10)
	{
	   PWMIF &= 0xEF;
	}
	if(PWMIF & 0x20)
	{
	   PWMIF &= 0xDF;
	}
	if(PWMIF & 0x40)
	{
	   PWMIF &= 0xBF;
	}
	if(PWMIF & 0x80)
	{
	   PWMIF &= 0x7F;
	}
}
void PWMFDInterrupt() interrupt 23
{
}
