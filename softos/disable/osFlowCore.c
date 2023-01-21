/*
                                                  FILE-START
*/
/*

 *@文件名称: DHS_FlowCore.c

 *@文件内容: 系统"Flow解释机内核"文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun

 *@开发环境: STM32F407ZGT6@168MHz芯片 & Keil uVision 5

 *@注    释: 无

*/


/*


page1{
lcd < r:1 < text:"哈哈" < flash:0.5 < num:@1; 
key > sw:1,#"cj page2",2,#"cj page3",3,#"cj func1";
}
func1{
	$printf  < str:"abcd" << num:@2
}


属性与数据  
输入 ->   处理    -> 输出
	 |
	\/
              控制

char 

gap -- 槽


char DHS_Intmac_Input()

uart<"hello world\n";



< 输出
> 输入

uart 方法
str   属性与数据
cj    命令



*/


/*
                                                  <引用文件区>
*/
#include "main.h"
#include "DHS_FlowCore.h"
#include "print.h"


/*
                                                  <数据初始区>
*/
s8* IntStrPer = NULL;
u32* Gap[GAP_SIZE] = {NULL};
u8  IOName[IOName_SIZE] = {NULL};
u8  WayName[WayName_SIZE] = {NULL};
u8  WayPter[WayPter_SIZE] = {NULL};
u32*	Gap_Read = NULL;
u8  WayPter_Mode  = NULL;

/*
                                                  <函数区>
*/
/*

 *@函数名称: 无

 *@函数版本: 1.0.0

 *@函数功能: 无

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
s8 DHS_Intmac_IONAME(u32 IONAME)
{
	switch(IONAME){
			case Intmac_case_3('e','n','d')://end方法
				return Intmac_End;
			case Intmac_case_4('u','a','r','t')://uart方法
				return DHS_Intmac_Uart();
			case Intmac_case_4('d','b','u','g')://dbug方法
				return DHS_Intmac_Uart();
	}
	return Intmac_IONAME_Error;
}

/*

 *@函数名称: 无

 *@函数版本: 1.0.0

 *@函数功能: 无

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
s8 DHS_Intmac_Uart(void)
{
	u8 _tr0;
	u8 err = Intmac_WayName_Error;
	s8 GetRE = DHS_Flow_GetWay();
	if(GetRE == Get_Error){ //出现异常
		return Get_Error;
	}
	while(1){
		err = Intmac_WayName_Error;
		switch(DHS_StrToSwitch(&WayName[0])){
			case Intmac_case_3('s','t','r'):
					if(WayPter_Mode){
						print("%s",*Gap_Read);
					}
					else{
						print("%s",&WayPter[0]);
					}
					err = 0;
					break;
			case Intmac_case_3('n','u','m'):
					if(WayPter_Mode){
						print("%d",*Gap_Read);
					}
					else{
						_tr0 = 0;
						while(1){
							if(WayPter[_tr0] == '\0'){
								break;
							}
							pchar(WayPter[_tr0]);
							_tr0++;
						}
					}
					err = 0;
					break;
		}
		if(err == Intmac_WayName_Error){//出现异常
			return Intmac_WayName_Error;
		}
		if(GetRE == Get_End){
			return Intmac_OK;
		}
		GetRE = DHS_Flow_GetWay();
		if(GetRE == Get_Error){//出现异常
			return Get_Error;
		}
//			printf("n=%s\n",&WayName[0]);
//			printf("p=%s\n",&WayPter[0]);
	}
		
}
/*

 *@函数名称: 无

 *@函数版本: 1.0.0

 *@函数功能: 无

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
s32 DHS_StrToNum(s8 *numstr)
{
	s32 result = 0;
	while(1){
		if(*numstr >= '0' && *numstr <= '9'){
			result = (result * 10) + ((*numstr) - '0');
		}
		else{
			return result;
		}
		numstr++;
	
	}
}
/*

 *@函数名称: 无

 *@函数版本: 1.0.0

 *@函数功能: 无

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
u32 DHS_StrToSwitch(u8 *numstr)
{
	u32 result = 0;
	u32  _tr0 = 0; 
#ifndef DHS_Intmac_AToa_Enable
	while(1){
		if(_tr0 % 2 == 0){
			if(*numstr >= 'A' && *numstr <= 'z'){
				result = result + *numstr;
			}
			else{
				return (u32)result;
			}
		}
		else{
			if(*numstr >= 'A' && *numstr <= 'z'){
				result = result - *numstr;
			}
			else{
				return (u32)result;
		}
		numstr++;
		_tr0++;
	}
#else
	while(1){
		if(_tr0 % 2 == 0){
			if(*numstr >= 'a' && *numstr <= 'z'){
				result = result + *numstr;
			}
			else if(*numstr >= 'A' && *numstr <= 'Z'){
				result = result + (*numstr	+ 32);
			}
			else{
				return (u32)result;
			}
		}
		else{
			if(*numstr >= 'a' && *numstr <= 'z'){
				result = result - *numstr;
			}
			else if(*numstr >= 'A' && *numstr <= 'Z'){
				result = result - (*numstr	+ 32);
			}
			else{
				return (u32)result;
			}
		}
		numstr++;
		_tr0++;
	}

#endif
}
/*

 *@函数名称: DHS_Intmac_GetWay

 *@函数版本: 1.0.0

 *@函数功能: 获取参数

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/

s8 DHS_Flow_GetWay(void)
{
	u32 _tr0;
	if(*IntStrPer == '<'){
		*IntStrPer++;
	}
	for(_tr0 = 0; _tr0 < WayName_SIZE ; _tr0++){
		if(*IntStrPer == ':'){
			WayPter_Mode = WayPter_Mode_WOK;
			WayPter[_tr0] = '\0';
			IntStrPer++;
			for(_tr0 = 0; _tr0 < WayPter_SIZE ; _tr0++){
				if(*IntStrPer == '<' || *IntStrPer == '>'){
					WayPter[_tr0] = '\0';
					return Get_OK;
				}else if(*IntStrPer == ';' || *IntStrPer == '\0'){
					WayPter[_tr0] = '\0';
					return Get_End;
				}
				WayPter[_tr0] = *IntStrPer;
				IntStrPer++;
			}
			return Get_Error;
		}
		else if(*IntStrPer == '@'){
			WayPter_Mode = WayPter_Mode_GOK;
			WayPter[_tr0] = '\0';
			IntStrPer++;
			for(_tr0 = 0; _tr0 < WayPter_SIZE ; _tr0++){
				if(*IntStrPer == '<' || *IntStrPer == '>'){
					WayPter[_tr0] = '\0';
					Gap_Read = Gap[DHS_StrToNum((s8*)&WayPter[0])];
					return Get_OK;
				}else if(*IntStrPer == ';' || *IntStrPer == '\0'){
					WayPter[_tr0] = '\0';
					Gap_Read = Gap[DHS_StrToNum((s8*)&WayPter[0])];
					return Get_End;
				}
				WayPter[_tr0] = *IntStrPer;
				IntStrPer++;
			}
			return Get_Error;
		}
//		else{
//			return Get_Error;
//		}
		WayName[_tr0] = *IntStrPer;
		IntStrPer++;
	}
	return Get_Error;
}





/*

 *@函数名称: DHS_Flow

 *@函数版本: 1.0.0

 *@函数功能: Flow入口

 *@输入参数: s8 *FlowStr(字符串)

 *@返 回 值: 无

 *@注    释: 无

*/

s8 DHS_Flow(s8 *FlowStr)
{
	u8 _tr0;
	u32 row = 0;
	IntStrPer = FlowStr;
	while(1){
		row++;
		for(_tr0 = 0; _tr0 < IOName_SIZE;_tr0++){
			if(*IntStrPer == '<'){
				IOName[_tr0] = '\0';
				break;
			}
			IOName[_tr0] = *IntStrPer;
			IntStrPer++;
		}
		switch(DHS_Intmac_IONAME(DHS_StrToSwitch(&IOName[0]))){
#ifdef DHS_Intmac_ErrorOutput_Enable//启用输出错误 
			case Intmac_IONAME_Error:
					print("\n发生错误: 第%d行,找不到 <%s> 命令",row,&IOName[0]);
					return OK;
			case Intmac_WayName_Error:
					print("\n发生错误: 第%d行,找不到 <%s> 属性",row,&WayName[0]);
					return OK;
			case Get_Error:
					print("\n发生错误: 第%d行,在读取属性与数据时错误",row);
					return OK;
#endif
			case Intmac_End:
					return OK;
		}
		//printf("\np=%c\n",*IntStrPer);
		if(*IntStrPer == '\0'){
			break;
		}
		if(*IntStrPer == ';'){
			if(*(IntStrPer + 1) == 9){
				IntStrPer++;
			}
		}
		IntStrPer++;
	}
	return (OK);
}


/*

 *@函数名称: DHS_WordComp

 *@函数版本: 1.0.0

 *@函数功能: 字符比较

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
s8 DHS_CharComp(s8 *strs,s8 *strc)
{
	if(*strs == *strc){
		return true;
	}
	else{
		return false;
	}
}

/*

 *@函数名称: DHS_StrComp

 *@函数版本: 1.0.0

 *@函数功能: 字符串比较

 *@输入参数: s8 *strs(原字符串),s8 *strc(比较字符串)

 *@返 回 值: 无

 *@注    释: 无

*/
s8 DHS_StrComp(s8 *strs,s8 *strc)
{
	while(1){
		if(*strs != *strc){
			return false;
		}
		if(*strs == '\0'){
			return true;
		}
		strs++;
		strc++;
	}
}
/*

 *@函数名称: DHS_StrCutComp

 *@函数版本: 1.0.0

 *@函数功能: 截止式比较字符串

 *@输入参数: s8 *strs(原字符串),s8 *strc(比较字符串),s8 cutchar(截止字符)

 *@返 回 值: 无

 *@注    释: 无

*/
s8 DHS_StrCutComp(s8 *strs,s8 *strc,s8 cutchar)
{
	while(1){
		if(*strc == cutchar){
			return true;
		}
		if(*strs == '\0'){
			return true;
		}
		if(*strs != *strc){
			return false;
		}
		strs++;
		strc++;
	}
}
/*

 *@函数名称: DHS_StrLoca

 *@函数版本: 1.0.0

 *@函数功能: 在字符串定位某个字符的位置

 *@输入参数: s8 *strs(字符串),s8 locachar(字符)

 *@返 回 值: 无

 *@注    释: 无

*/

u32 DHS_StrLoca(s8 *strs,s8 locachar)
{
	u32 Locas = 0;
	while(1){
		if(*strs == '\0'){
			return false;
		}
		if(*strs == locachar){
			return Locas;
		}
		strs++;
		Locas++;
	}
}
/*
                                                  FILE-END
*/
