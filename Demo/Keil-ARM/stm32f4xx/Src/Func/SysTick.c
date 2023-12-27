 /**
 * Copyright 2022-2023 AhDun. All rights reserved.
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
/**
 * @file SysTick.c
 *
 * @brief 
 *
 * @note 
*/


#include "SysTick.h"
#include "osConfig.h"


/*
                                                  变量初始化区
*/
s8 SysTick_us_Init_Test_Flag = Unknown;



/**
 * @name SysTick_us_Init
 *
 * @brief 以us级初始SysTick定时器
 *
 * @param SysCLK（主频），us（微秒）
 *
 * @retval 0: 成功，-1: 失败
 *
 * @note none
 *
 * 扩		 充: 
*/

s8 SysTick_us_Init(u8 SysCLK,u32 us)
{
	if(SysTick->CTRL & 0x01){
		return (Error); 
	}
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	 
	SysTick->LOAD = us * (SysCLK / 8) ; //时间加载	  		 
	SysTick->VAL = us * (SysCLK / 8) ;  //清空计数器
	SysTick->CTRL |= ( 0x01 | 0x02) ; //开始倒数
                //开始倒数  | 计数到0时，产生异常
	//while(osClockGetTimePulse() == 0);//如果SysTick定时器，未正常工作，则阻塞
	return (OK);
}

s8 SysTick_us_load(u8 SysCLK,u32 us)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	 
	SysTick->LOAD = us * (SysCLK / 8) ; //时间加载	  		 
	SysTick->CTRL |= ( 0x01 | 0x02) ; //开始倒数
                //开始倒数  | 计数到0时，产生异常
	return (OK);
}

/**
 * @name SysTick_Handler
 *
 * @brief SysTick异常响应参数
 *
 * @param none
 *
 * @retval none
 *
 * @note none
*/
//void SysTick_Handler(void)
//{
//	
//	osClockTimePulse();
//}

/**
 * @name SysTick_us
 *
 * @brief 微秒延时
 *
 * @param none
 *
 * @retval none
 *
 * @note none
*/
void SysTick_us(u32 us)
{
	u32 VALs = SysTick->VAL - (us * (osCPU_Freq / 8));
	while(SysTick->VAL > VALs);
}



