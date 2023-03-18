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
/*
 *
 * @�ļ�����: .c
 *
 * @�ļ�����: ��
 *
 * @ע    ��: ��
 *
 */
#include "osConfig.h"
#include "osTool.h"
 


/*
 *
 * @��������: ��
 *
 * @��������: ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */

OsErrorValue	osLog(uint8_t Class,char* FuncName,char* Text)
{
		switch(Class){
			case osLogClass_Fatal://���ؼ�
									osLogClassDebugOutput("[Fatal] %s - %s\n",FuncName,Text);
									break;
			case osLogClass_Error://����
									osLogClassDebugOutput("[Error] %s - %s\n",FuncName,Text);
									break;
			case osLogClass_Warn://���漶
									osLogClassDebugOutput("[Warn] %s - %s\n",FuncName,Text);
									break;
			case osLogClass_Info://��Ϣ��
									osLogClassDebugOutput("[Info] %s - %s\n",FuncName,Text);
									break;
			case osLogClass_Debug://���Լ�
									osLogClassDebugOutput("[Debug] %s - %s\n",FuncName,Text);
									break;
		}
		return (OK);
}

