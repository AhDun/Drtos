/*********************************************************************************************************
* 文件名称：GPIO.c
* 摘    要：
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
#include"GPIO.h"

#define PIO 0x00
#define PSIO 0x01
#define XIO 0x02
#define OIO 0x03

#define P0S 100
#define P1S 110
#define P2S 120
#define P3S 130

#define UART1IO 0x06
#define CCPIO 0x04
#define SPIIO 0x02
#define I2CIO 0x14
#define CMPOIO 0x13
#define UART4IO 0x12
#define UART3IO 0x11
#define UART2IO 0x10
#define MCLKOIO 0x23
#define PWM0IO 0x33
#define PWM1IO 0x43
#define PWM2IO 0x53
#define PWM3IO 0x63
#define PWM4IO 0x73
#define PWM5IO 0x83
#define PWM6IO 0x93
#define PWM7IO 0xA3
/********************************
函数名称:IOSW
函数功能:IO口调整
输入参数:
输    入:
输出参数:
输    出:
********************************/
void IOSW(u8 IOm,u8 Mode)
{
	P_SW2 |= 0x80;
	switch(IOm >> 4)
	{
		case 0:
				switch(Mode)
				{
					case 0:P_SW1 &= ~(0x01 << ((IOm & 0x0F) + 1));P_SW1 &= ~(0x01 << (IOm & 0x0F));break;
					case 1:P_SW1 &= ~(0x01 << ((IOm & 0x0F) + 1));P_SW1 |= (0x01 << (IOm & 0x0F));break;
					case 2:P_SW1 |= (0x01 << ((IOm & 0x0F) + 1));P_SW1 &= ~(0x01 << (IOm & 0x0F));break;
					case 3:P_SW1 |= (0x01 << ((IOm & 0x0F) + 1));P_SW1 |= (0x01 << (IOm & 0x0F));break;  
				}
				break;	
		case 1:
				switch((IOm & 0x0F)  & 0x0F)
				{
					case 4:
							switch(Mode)
							{
								case 0:P_SW2 &= ~(0x01 << ((IOm & 0x0F) + 1));P_SW2 &= ~(0x01 << (IOm & 0x0F));break;
								case 1:P_SW2 &= ~(0x01 << ((IOm & 0x0F) + 1));P_SW2 |= (0x01 << (IOm & 0x0F));break;
								case 2:P_SW2 |= (0x01 << ((IOm & 0x0F) + 1));P_SW2 &= ~(0x01 << (IOm & 0x0F));break;
								case 3:P_SW2 |= (0x01 << ((IOm & 0x0F) + 1));P_SW2 |= (0x01 << (IOm & 0x0F));break;  
							}
							break;
					case 3:
							switch(Mode)
							{
							 	case 0:P_SW2 &= ~(0x01 << (IOm & 0x0F));break;
								case 1:P_SW2 |= (0x01 << (IOm & 0x0F));break;
							}
							break;
					case 2:
							switch(Mode)
							{
							 	case 0:P_SW2 &= ~(0x01 << (IOm & 0x0F));break;
								case 1:P_SW2 |= (0x01 << (IOm & 0x0F));break;
							}
							break;
					case 1:
							switch(Mode)
							{
							 	case 0:P_SW2 &= ~(0x01 << (IOm & 0x0F));break;
								case 1:P_SW2 |= (0x01 << (IOm & 0x0F));break;
							}
							break;
					case 0:
							switch(Mode)
							{
							 	case 0:P_SW2 &= ~(0x01 << (IOm & 0x0F));break;
								case 1:P_SW2 |= (0x01 << (IOm & 0x0F));break;
							}
							break;		
				}
				break;
		case 2:
				switch(Mode)
				{
				 	case 0:CKSEL &= ~(0x01 << (IOm & 0x0F));break;
					case 1:CKSEL |= (0x01 << (IOm & 0x0F));break;
				}
				break;	
		case 3:
				switch(Mode)
				{
					case 0:PWM0CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM0CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 1:PWM0CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM0CR  |= (0x01 << (IOm & 0x0F));break;
					case 2:PWM0CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM0CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 3:PWM0CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM0CR  |= (0x01 << (IOm & 0x0F));break;  
				}
				break;	
		case 4:
				switch(Mode)
				{
					case 0:PWM1CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM1CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 1:PWM1CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM1CR  |= (0x01 << (IOm & 0x0F));break;
					case 2:PWM1CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM1CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 3:PWM1CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM1CR  |= (0x01 << (IOm & 0x0F));break;  
				}
				break;		
		case 5:
				switch(Mode)
				{
					case 0:PWM2CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM2CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 1:PWM2CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM2CR  |= (0x01 << (IOm & 0x0F));break;
					case 2:PWM2CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM2CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 3:PWM2CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM2CR  |= (0x01 << (IOm & 0x0F));break;  
				}
				break;
		case 6:
				switch(Mode)
				{
					case 0:PWM3CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM3CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 1:PWM3CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM3CR  |= (0x01 << (IOm & 0x0F));break;
					case 2:PWM3CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM3CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 3:PWM3CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM3CR  |= (0x01 << (IOm & 0x0F));break;  
				}
				break;
		case 7:
				switch(Mode)
				{
					case 0:PWM4CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM4CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 1:PWM4CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM4CR  |= (0x01 << (IOm & 0x0F));break;
					case 2:PWM4CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM4CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 3:PWM4CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM4CR  |= (0x01 << (IOm & 0x0F));break;  
				}
				break;
		case 8:
				switch(Mode)
				{
					case 0:PWM5CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM5CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 1:PWM5CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM5CR  |= (0x01 << (IOm & 0x0F));break;
					case 2:PWM5CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM5CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 3:PWM5CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM5CR  |= (0x01 << (IOm & 0x0F));break;  
				}
				break;
		case 9:
				switch(Mode)
				{
					case 0:PWM6CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM6CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 1:PWM6CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM6CR  |= (0x01 << (IOm & 0x0F));break;
					case 2:PWM6CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM6CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 3:PWM6CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM6CR  |= (0x01 << (IOm & 0x0F));break;  
				}
				break;
		case 10:
				switch(Mode)
				{
					case 0:PWM7CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM7CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 1:PWM7CR  &= ~(0x01 << ((IOm & 0x0F) + 1));PWM7CR  |= (0x01 << (IOm & 0x0F));break;
					case 2:PWM7CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM7CR  &= ~(0x01 << (IOm & 0x0F));break;
					case 3:PWM7CR  |= (0x01 << ((IOm & 0x0F) + 1));PWM7CR  |= (0x01 << (IOm & 0x0F));break;  
				}
				break;	
	}	
}
/********************************
函数名称:IOMode
函数功能:IO口模式配置
输入参数:
输    入:
输出参数:
输    出:
********************************/
void IOMode(u8 IOm,u8 Mode)
{
 	 if(IOm >= 100)
	 {
		switch(IOm)
		{
		 	case 100:
					switch(Mode)
					{
					 	case 0: P0M1 = 0x00;P0M0 = 0x00;break;
						case 1: P0M1 = 0x00;P0M0 = 0xFF;break;
						case 2: P0M1 = 0xFF;P0M0 = 0x00;break;
						case 3: P0M1 = 0xFF;P0M0 = 0xFF;break;
					}
					break;
			case 110:
					switch(Mode)
					{
					 	case 0: P1M1 = 0x00;P1M0 = 0x00;break;
						case 1: P1M1 = 0x00;P1M0 = 0xFF;break;
						case 2: P1M1 = 0xFF;P1M0 = 0x00;break;
						case 3: P1M1 = 0xFF;P1M0 = 0xFF;break;
					}
					break;
			case 120:
					switch(Mode)
					{
					 	case 0: P2M1 = 0x00;P2M0 = 0x00;break;
						case 1: P2M1 = 0x00;P2M0 = 0xFF;break;
						case 2: P2M1 = 0xFF;P2M0 = 0x00;break;
						case 3: P2M1 = 0xFF;P2M0 = 0xFF;break;
					}
					break;
			case 130:
					switch(Mode)
					{
					 	case 0: P3M1 = 0x00;P3M0 = 0x00;break;
						case 1: P3M1 = 0x00;P3M0 = 0xFF;break;
						case 2: P3M1 = 0xFF;P3M0 = 0x00;break;
						case 3: P3M1 = 0xFF;P3M0 = 0xFF;break;
					}
					break;
		}
	 }
	 else if(IOm >= 30)
	 {
	  	switch(Mode)
		{
			case 0:P3M1 &= ~(0x01 << (IOm - 30));P3M0 &= ~(0x01 << (IOm - 30));break;
			case 1:P3M1 &= ~(0x01 << (IOm - 30));P3M0 |= (0x01 << (IOm - 30));break;
			case 2:P3M1 |= (0x01 << (IOm - 30));P3M0 &= ~(0x01 << (IOm - 30));break;
			case 3:P3M1 |= (0x01 << (IOm - 30));P3M0 |= (0x01 << (IOm - 30));break;  
		}
	 }
	 else if(IOm >= 20)
	 {
		switch(Mode)
		{
			case 0:P2M1 &= ~(0x01 << (IOm - 20));P2M0 &= ~(0x01 << (IOm - 20));break;
			case 1:P2M1 &= ~(0x01 << (IOm - 20));P2M0 |= (0x01 << (IOm - 20));break;
			case 2:P2M1 |= (0x01 << (IOm - 20));P2M0 &= ~(0x01 << (IOm - 20));break;
			case 3:P2M1 |= (0x01 << (IOm - 20));P2M0 |= (0x01 << (IOm - 20));break;  
		}
	 }
	 else if(IOm >= 10)
	 {
	  	switch(Mode)
		{
			case 0:P1M1 &= ~(0x01 << (IOm - 10));P1M0 &= ~(0x01 << (IOm - 10));break;
			case 1:P1M1 &= ~(0x01 << (IOm - 10));P1M0 |= (0x01 << (IOm - 10));break;
			case 2:P1M1 |= (0x01 << (IOm - 10));P1M0 &= ~(0x01 << (IOm - 10));break;
			case 3:P1M1 |= (0x01 << (IOm - 10));P1M0 |= (0x01 << (IOm - 10));break;  
		}
	 }
	 else if(IOm >= 0)
	 {
	  	switch(Mode)
		{
			case 0:P0M1 &= ~(0x01 << IOm);P0M0 &= ~(0x01 << IOm);break;
			case 1:P0M1 &= ~(0x01 << IOm);P0M0 |= (0x01 << IOm);break;
			case 2:P0M1 |= (0x01 << IOm);P0M0 &= ~(0x01 << IOm);break;
			case 3:P0M1 |= (0x01 << IOm);P0M0 |= (0x01 << IOm);break;  
		}
	 }
	 	
}
/********************************
函数名称:IOPU
函数功能:IO口内部上接电阻配置
输入参数:
输    入:
输出参数:
输    出:
********************************/
void IOPU(u8 IOm,u8 Mode)
{
	if(IOm >= 100)
	 {
		switch(IOm)
		{
		 	case 100:
					switch(Mode)
					{
					 	case 0: P0PU = 0x00;break;
						case 1: P0PU = 0xFF;break;
					}
					break;
			case 110:
					switch(Mode)
					{
					 	case 0: P1PU = 0x00;break;
						case 1: P1PU = 0xFF;break;
					}
					break;
			case 120:
					switch(Mode)
					{
					 	case 0: P2PU = 0x00;break;
						case 1: P2PU = 0xFF;break;
					}
					break;
			case 130:
					switch(Mode)
					{
					 	case 0: P3PU = 0x00;break;
						case 1: P3PU = 0xFF;break;
					}
					break;
		}
	 }
	 else if(IOm >= 30)
	 {
	  	switch(Mode)
		{
			case 0:P0PU &= ~(0x01 << (IOm - 30));break;
			case 1:P0PU |= (0x01 << (IOm - 30));break;
		}
	 }
	 else if(IOm >= 20)
	 {
		switch(Mode)
		{
			case 0:P1PU &= ~(0x01 << (IOm - 20));break;
			case 1:P1PU |= (0x01 << (IOm - 20));break;  
		}
	 }
	 else if(IOm >= 10)
	 {
	  	switch(Mode)
		{
			case 0:P2PU &= ~(0x01 << (IOm - 10));break;
			case 1:P2PU |= (0x01 << (IOm - 10));break;  
		}
	 }
	 else if(IOm >= 0)
	 {
	  	switch(Mode)
		{
			case 0:P3PU &= ~(0x01 << IOm);break;
			case 1:P3PU |= (0x01 << IOm);break;  
		}
	 }		
}
/********************************
函数名称:IONCS
函数功能:IO口施密特触发配置
输入参数:
输    入:
输出参数:
输    出:
********************************/
void IONCS(u8 IOm,u8 Mode)
{
	if(IOm >= 100)
	 {
		switch(IOm)
		{
		 	case 100:
					switch(Mode)
					{
					 	case 0: P0NCS = 0x00;break;
						case 1: P0NCS = 0xFF;break;
					}
					break;
			case 110:
					switch(Mode)
					{
					 	case 0: P1NCS = 0x00;break;
						case 1: P1NCS = 0xFF;break;
					}
					break;
			case 120:
					switch(Mode)
					{
					 	case 0: P2NCS = 0x00;break;
						case 1: P2NCS = 0xFF;break;
					}
					break;
			case 130:
					switch(Mode)
					{
					 	case 0: P3NCS = 0x00;break;
						case 1: P3NCS = 0xFF;break;
					}
					break;
		}
	 }
	 else if(IOm >= 30)
	 {
	  	switch(Mode)
		{
			case 0:P0NCS &= ~(0x01 << (IOm - 30));break;
			case 1:P0NCS |= (0x01 << (IOm - 30));break;
		}
	 }
	 else if(IOm >= 20)
	 {
		switch(Mode)
		{
			case 0:P1NCS &= ~(0x01 << (IOm - 20));break;
			case 1:P1NCS |= (0x01 << (IOm - 20));break;  
		}
	 }
	 else if(IOm >= 10)
	 {
	  	switch(Mode)
		{
			case 0:P2NCS &= ~(0x01 << (IOm - 10));break;
			case 1:P2NCS |= (0x01 << (IOm - 10));break;  
		}
	 }
	 else if(IOm >= 0)
	 {
	  	switch(Mode)
		{
			case 0:P3NCS &= ~(0x01 << IOm);break;
			case 1:P3NCS |= (0x01 << IOm);break;  
		}
	 }		
}
