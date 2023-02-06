/* *
 * @文件名称: main.h
 *
 * @文件内容: 基本库
 *
 * @注    释: 
*/

#ifndef __main_H_
#define __main_H_




//当前MUC库文件{
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "STM32xxGPIO.h"//GPIO寄存器操作文件
//}



#define ActionValue_Enable 	1	//操作值  1：启用 0：禁用

#define DataTypeSize_Enabled 0	//数据类型长度  1：启用 0：禁用
		/*如果使用标准的数据类型库，如:stdint.h，就无需启用此数据类型长度*/
#define DataType_Enabled 	0	//数据类型  1：启用 0：禁用
		/*如果使用标准的数据类型库，如:stdint.h，就无需启用此数据类型*/


#if (ActionValue_Enable > 0)
//操作值{
//布尔判断{
#define true 					  1u //真
#define false 					  0u //假
//}
//{锁控
#define Locking 				  1u //上锁
#define UnLock 	
//}				  0u //解锁
//{配置
#define Disable 				  0u //禁用
#define Enable 					  1u //使能
//}
//反馈{
#define Error  					  -1 //错误
#define Exception				  -1 //异常
#define ON 						  -1 //不正确
#define NReady					  -1 //未就绪
#define OK 						  0u //正确
#define YES						  0u //正确
#define Ready					  0u //已就绪
#define NULL 					  0u //空
#define Pass					  0u //通过
#define Unknown                   -1 //未知
#define Head					  0u  //首部
//}
//}
#endif


#if (DataType_Enabled > 0)
//数据类型{

//布尔型{
typedef bit 						bool;
typedef bit 						u2;
typedef bit 						U2;
typedef bit 						u2_t;
//}

//无符号字符型{
typedef unsigned char 				u8;
typedef unsigned char 				uchar;
typedef unsigned char 				UINT8;
typedef unsigned char 				uint8_t;
//}
//带符号字符型{
typedef signed char 				s8;
typedef signed char 				schar;
typedef signed char 				INT8;
typedef signed char 				int8_t;
//}
//无符号短整型与整型{
typedef unsigned short int  		u16;
typedef unsigned short int  		uint;
typedef unsigned short int  		UINT16;	
typedef unsigned short int  		uint16_t;	
//}
//带符号短整型与整型{
typedef signed  int  				s16;	
typedef signed  int  				sint;	
typedef signed  int  				INT16;
typedef signed  int  				int16_t;
//}
//无符号长整型{
typedef unsigned long int  			u32;	
typedef unsigned long int  			luint;
typedef unsigned long int  			UINT32;	
typedef unsigned long int  			uint32_t;
//}
//带符号长整型{
typedef signed long int  			s32;	
typedef signed long int  			lsint;	
typedef signed long int  			INT32;	
typedef signed long int  			int32_t;
//}
//单精度浮点型{
typedef float  						f32;
typedef float  						float_32;
typedef float  						F32;
typedef float  						f32_t;
//}
//双精度浮点型{
typedef double  					d64;
typedef double  					double_64;
typedef double  					D64;
typedef double  					d64_t;
//}
//}
#endif


#if (DataTypeSize_Enabled > 0)

//布尔型{
#define BOOL_MIN						0u
#define BOOL_MAX						1u
#define u2_MIN							0u
#define u2_MAX							1u
#define U2_MIN							0u
#define U2_MAX							1u
#define u2_t_MIN						0u
#define u2_t_MAX						1u
//}

//无符号字符型{
#define u8_MIN							0u
#define u8_MAX							255u
#define uchar_MIN						0u
#define uchar_MAX						255u
#define UINT8_MIN						0u
#define UINT8_MAX						255u
#define uint8_t_MIN						0u
#define uint8_t_MAX						255u
//}

//带符号字符型{
#define s8_MIN						 -128
#define s8_MAX						127
#define schar_MIN					-128
#define schar_MAX					127
#define INT8_MIN					-128
#define INT8_MAX					127
#define int8_t_MIN				 	-128
#define int8_t_MAX					127
//}
//无符号短整型与整型{
#define u16_MIN				 		0u
#define u16_MAX						65535u
#define uint_MIN				 	0u
#define uint_MAX					65535u
#define UINT16_MIN				 	0u
#define UINT16_MAX					65535u
#define uint16_t_MIN				0u
#define uint16_t_MAX				65535u
//}
//带符号短整型与整型{
#define s16_MIN				 		 -32768
#define s16_MAX						32767
#define sint_MIN				 	-32768
#define sint_MAX					32767
#define INT16_MIN				 	-32768
#define INT16_MAX					32767
#define int16_t_MIN				 	-32768
#define int16_t_MAX					32767
//}
//无符号长整型{
#define u32_MIN				 		0u
#define u32_MAX						4294967295u
#define luint_MIN				 	0u
#define luint_MAX					4294967295u
#define UINT32_MIN				 	0u
#define UINT32_MAX					4294967295u
#define uint32_t_MIN				0u
#define uint32_t_MAX				4294967295u
//}
//带符号长整型{
#define s32_MIN				 		-2147483648
#define s32_MAX						2147483647
#define lsint_MIN				 	-2147483648
#define lsint_MAX					2147483647
#define INT32_MIN				 	-2147483648
#define INT32_MAX					2147483647
#define int32_t_MIN				 	-2147483648
#define int32_t_MAX					2147483647
//}

//单精度浮点型{
#define f32_MIN				 		10e-37
#define f32_MAX						10e38
#define float_32_MIN				10e-37
#define float_32_MAX				10e38
#define F32_MIN					 	10e-37
#define F32_MAX						10e38
#define f32_t_MIN					10e-37
#define f32_t_MAX					10e38
//}


//双精度浮点型{
#define d64_MIN				 		10e-37
#define d64_MAX						10e308
#define double_64_MIN				10e-37
#define double_64_MAX				10e308
#define D64_MIN				 		10e-37
#define D64_MAX						10e308
#define d64_t_MIN				 	10e-37
#define d64_t_MAX					10e308
//}

#endif

#endif


