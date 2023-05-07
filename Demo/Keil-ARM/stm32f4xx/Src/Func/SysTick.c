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
 * @�ļ�����: SysTick.c
 *
 * @�ļ�����: 
 *
 * @ע    ��: 
*/


#include "SysTick.h"
#include "osConfig.h"


/*
                                                  ������ʼ����
*/
s8 SysTick_us_Init_Test_Flag = Unknown;



/* *
 * @��������: SysTick_us_Init
 *
 * @��������: ��us����ʼSysTick��ʱ��
 *
 * @�������: SysCLK����Ƶ����us��΢�룩
 *
 * @�� �� ֵ: 0: �ɹ���-1: ʧ��
 *
 * @ע    ��: ��
 *
 * ��		 ��: 
*/

s8 SysTick_us_Init(u8 SysCLK,u32 us)
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	 
	SysTick->LOAD = us * (SysCLK / 8) ; //ʱ�����	  		 
	SysTick->VAL = us * (SysCLK / 8) ;  //��ռ�����
	SysTick->CTRL |= ( 0x01 | 0x02) ; //��ʼ����
                //��ʼ����  | ������0ʱ�������쳣
	//while(osClockGetTimePulse() == 0);//���SysTick��ʱ����δ����������������
	return (OK);
}

/* *
 * @��������: SysTick_Handler
 *
 * @��������: SysTick�쳣��Ӧ����
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
//void SysTick_Handler(void)
//{
//	
//	osClockTimePulse();
//}

/* *
 * @��������: SysTick_us
 *
 * @��������: ΢����ʱ
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
void SysTick_us(u32 us)
{
	u32 VALs = SysTick->VAL - (us * (osCPU_Freq / 8));
	while(SysTick->VAL > VALs);
}



