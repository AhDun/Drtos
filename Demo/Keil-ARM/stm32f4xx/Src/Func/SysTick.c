 /*
                                                  FILE-START
*/
/*
 *@文件名称: SysTick.c

 *@文件内容: 

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 
*/

/*
                                                  <引用文件区>
*/
#include "SysTick.h"
#include "osMain.h"


/*
                                                  变量初始化区
*/
s8 SysTick_us_Init_Test_Flag = Unknown;

/*
                                                  <函数区>
*/

/*
 *@函数名称: SysTick_us_Init

 *@函数功能: 以us级初始SysTick定时器

 *@输入参数: SysCLK（主频），us（微秒）

 *@返 回 值: 0: 成功，-1: 失败

 *@注    释: 无

 * 扩		 充: 
*/

s8 SysTick_us_Init(u8 SysCLK,u16 us)
{
	if(SysTick->CTRL & 0x01){
		return (Error); 
	}
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	 
	SysTick->LOAD = us * (SysCLK / 8) ; //时间加载	  		 
	SysTick->VAL = 0x00;        		//清空计数器
	SysTick->CTRL |= ( 0x01 | 0x02) ; //开始倒数
                //开始倒数  | 计数到0时，产生异常
	while(SysTick_us_Init_Test_Flag == Unknown);//如果SysTick定时器，未正常工作，则阻塞
	return (OK);
}

/*
 *@函数名称: SysTick_Handler

 *@函数功能: SysTick异常响应参数

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无
*/
void SysTick_Handler(void)
{
	SysTick_us_Init_Test_Flag_OK();
	osClockTimePulse();
}

/*
 *@函数名称: SysTick_us

 *@函数功能: 微秒延时

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无
*/
void SysTick_us(u32 us)
{
	u32 VALs = SysTick->VAL - (us * (osCPU_Freq / 8));
	while(SysTick->VAL > VALs);
}

/*
                                                  FILE-END
*/

