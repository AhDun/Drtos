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
                                                  ������ʼ����
*/
s8 SysTick_us_Init_Test_Flag = Unknown;



/**
 * @name SysTick_us_Init
 *
 * @brief ��us����ʼSysTick��ʱ��
 *
 * @param SysCLK����Ƶ����us��΢�룩
 *
 * @retval 0: �ɹ���-1: ʧ��
 *
 * @note none
 *
 * ��		 ��: 
*/

s8 SysTick_us_Init(u8 SysCLK,u32 us)
{
	if(SysTick->CTRL & 0x01){
		return (Error); 
	}
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	 
	SysTick->LOAD = us * (SysCLK / 8) ; //ʱ�����	  		 
	SysTick->VAL = us * (SysCLK / 8) ;  //��ռ�����
	SysTick->CTRL |= ( 0x01 | 0x02) ; //��ʼ����
                //��ʼ����  | ������0ʱ�������쳣
	//while(osClockGetTimePulse() == 0);//���SysTick��ʱ����δ����������������
	return (OK);
}

s8 SysTick_us_load(u8 SysCLK,u32 us)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	 
	SysTick->LOAD = us * (SysCLK / 8) ; //ʱ�����	  		 
	SysTick->CTRL |= ( 0x01 | 0x02) ; //��ʼ����
                //��ʼ����  | ������0ʱ�������쳣
	return (OK);
}

/**
 * @name SysTick_Handler
 *
 * @brief SysTick�쳣��Ӧ����
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
 * @brief ΢����ʱ
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



