 /*
 * Copyright (c) 2022-2023 AhDun
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */
/* *
 * @文件名称: SysTick.c
 *
 * @文件内容: 
 *
 * @注    释: 
*/


#include "SysTick.h"
#include "osConfig.h"


/*
                                                  变量初始化区
*/
s8 SysTick_us_Init_Test_Flag = Unknown;



/* *
 * @函数名称: SysTick_us_Init
 *
 * @函数功能: 以us级初始SysTick定时器
 *
 * @输入参数: SysCLK（主频），us（微秒）
 *
 * @返 回 值: 0: 成功，-1: 失败
 *
 * @注    释: 无
 *
 * 扩		 充: 
*/

s8 SysTick_us_Init(u8 SysCLK,u32 us)
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	 
	SysTick->LOAD = us * (SysCLK / 8) ; //时间加载	  		 
	SysTick->VAL = us * (SysCLK / 8) ;  //清空计数器
	SysTick->CTRL |= ( 0x01 | 0x02) ; //开始倒数
                //开始倒数  | 计数到0时，产生异常
	//while(osClockGetTimePulse() == 0);//如果SysTick定时器，未正常工作，则阻塞
	return (OK);
}

/* *
 * @函数名称: SysTick_Handler
 *
 * @函数功能: SysTick异常响应参数
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
//void SysTick_Handler(void)
//{
//	
//	osClockTimePulse();
//}

/* *
 * @函数名称: SysTick_us
 *
 * @函数功能: 微秒延时
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
void SysTick_us(u32 us)
{
	u32 VALs = SysTick->VAL - (us * (osCPU_Freq / 8));
	while(SysTick->VAL > VALs);
}



