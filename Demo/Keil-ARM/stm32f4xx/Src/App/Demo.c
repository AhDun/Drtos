#include "main.h"
#include "SysTick.h"
#include "Demo.h"
#include "SysTick.h"
#include "usart.h"
#include "tftlcd.h"
#include "rtc.h"
#include "math.h"


_Signal* s1;

_TaskHandle*	TaskHandle_Task1;
_TaskHandle*	TaskHandle_Task2;
_TaskHandle*	TaskHandle_Task3;
_TaskHandle*	TaskHandle_Task4;

_SIRQList SIRQ_RTC[3];



void ADC_Temp_Init(void);
u16 Get_ADC_Temp_Value(u8 ch,u8 times);
int Get_Temperture(void);


#define PI 3.1415926 

void Task1_Func(char* a)
{
	RTC_TimeTypeDef RTC_TimeStruct;
	u8* buf = osMemoryMalloc(20);
	TFTLCD_Init();			//LCD初始化
	print(a);
	osPostSend((u32*)"hello Main",TaskHandle_Main);
	print("%s",osPostReadWait());
	print("%s",osPostReadWait());
//	osSignalFree(s1);
	LCD_Clear(BLACK);
	FRONT_COLOR=YELLOW;
	BACK_COLOR=BRED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"softos Demo");
	RTC_Config();
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);//配置WAKE UP中断,1秒钟中断一次
	timebz = osSignalLogin(Signal_Count);

	osTaskSIRQLogin(&SIRQ_RTC[0],RTC_Func);

	osTimeLogin("RPost",1000,STimeConfig_Restart,Time_Func);

	while(1) 
	{
		osSignalUseWait(timebz);
        RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
		osMemoryReset(buf,' ');
        sprint((char *)buf,"RTC:%2d:%2d:%2d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds);
		FRONT_COLOR=GRAYBLUE;
		BACK_COLOR=BLACK;
		LCD_ShowString(10,90,tftlcd_data.width,tftlcd_data.height,16,buf);	
		
	}
	
}

void Task2_Func(void)
{
	_TaskHandle* TaskHandleListBuf = TaskHandleListHead;
	u8 a;
	u8* buf = osMemoryMalloc(50);
	

    //osSignalWaitInquire(&S1);
    //osTaskPause();
//	s1 = osSignalLogin(Signal_Mutual);

	osPostSend((u32*)"Hello",TaskHandle_Task1);
	osPostSend((u32*)"World",TaskHandle_Task1);
//	osSignalApply_Wait(s1);

    LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"STM32F407ZGT6@168MHz");
    LCD_ShowString(10,60,tftlcd_data.width,tftlcd_data.height,16,osNameVersionNumberS);
	while(1){

//		sprint((char *)buf,"TaskCount: %d TaskSwitchTime: %dus",TaskSwitchState.TSC,TaskSwitchState.TSC*TaskSwitchState.TSSU);
//		LCD_ShowString(10,120,tftlcd_data.width,tftlcd_data.height,16,buf);
//		for(b = 0; b < 50;b++){
//				buf[b] = ' ';
//		}
		osMemoryReset(buf,' ');
		sprint((char *)buf,"Memory F: %dB P: %dB S:%d",osMemoryGetFreeValue(),osMemoryGetPassValue(),osMemorySum());
		LCD_ShowString(10,120,tftlcd_data.width,tftlcd_data.height,16,buf);

		osMemoryReset(buf,' ');
		sprint((char *)buf,"CPU: %d%% = T %d%% + I %d%% + S %d%%",PS.CTO+PS.CISRO+PS.CSO,PS.CTO,PS.CISRO,PS.CSO);
		LCD_ShowString(10,150,tftlcd_data.width,tftlcd_data.height,16,buf);
		osMemoryReset(buf,' ');
		sprint((char *)buf,"R:%d:%2d:%2d:%2d",(osTime. TSRT / 1000) /86400,((osTime. TSRT / 1000) /3600) % 24,((osTime. TSRT / 1000) /60) % 60,(osTime. TSRT / 1000) % 60);
		LCD_ShowString(10,180,tftlcd_data.width,tftlcd_data.height,16,buf);
		LCD_ShowString(10,210,tftlcd_data.width,tftlcd_data.height,16,"------------TaskList--------------");
		LCD_ShowString(10,240,tftlcd_data.width,tftlcd_data.height,16,"Name  CPU  Class ");
		a = 0;
		do{
			osMemoryReset(buf,' ');
			sprint((char *)buf,"%s  %d%ms  %d ",TaskHandleListBuf -> Name,TaskHandleListBuf -> OccupyRatio,TaskHandleListBuf -> PriorityLevel);
			LCD_ShowString(10,270+(a*25),tftlcd_data.width,tftlcd_data.height,16,buf);
			a++;
			TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
		}while(TaskHandleListBuf != TaskHandleListHead);
		osSignalUseWait(timebz);
	}
}

void Task3_Func(u32* a)
{
	u8 b=0;
	u8 c;
	LED_Init();
	while(1){
		for(c = 0; c < 50; c++){
			LED2 = 0;
			osTaskDelayMs(b);
			LED2 = 1;
			osTaskDelayMs(20-b);
			if(c % 5 == 0){
				if(b>=20){
					b= 0;
				}
				b = b + 1;
			}
		}
		for(c = 0; c < 50; c++){
			LED2 = 0;
			osTaskDelayMs(b);
			LED2 = 1;
			osTaskDelayMs(20-b);
			if(c % 5 == 0){
				if(b == 0){
					b= 20;
				}
				b = b - 1;
			}
		}
		
	}
}

void Task4_Func(u32* a)
{
	u8 b=0;
	u8 c;
	LED_Init();
	while(1){
		for(c = 0; c < 50; c++){
			LED1 = 0;
			osTaskDelayMs(b);
			LED1 = 1;
			osTaskDelayMs(20-b);
			if(c % 5 == 0){
				if(b>=20){
					b= 0;
				}
				b = b + 1;
			}
		}
		for(c = 0; c < 50; c++){
			LED1 = 0;
			osTaskDelayMs(b);
			LED1 = 1;
			osTaskDelayMs(20-b);
			if(c % 5 == 0){
				if(b == 0){
					b= 20;
				}
				b = b - 1;
			}
		}
		
	}
}

void RTC_Func(void)
{
	osSignalFree(timebz);
	osSignalFree(timebz);
	osSignalFree(timebz);
	
}

void Time_Func(void)
{
	u32 _tr0;
	for(_tr0 = 0;_tr0 < 500;_tr0++){
		osPostSend((u32*)"hello",TaskHandle_Main);
	}
}


void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
	
	RCC_AHB1PeriphClockCmd(LED1_PORT_RCC|LED2_PORT_RCC,ENABLE); //使能端口时钟
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT; //输出模式
	GPIO_InitStructure.GPIO_Pin=LED1_PIN;//管脚设置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度为100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉
	GPIO_Init(LED1_PORT,&GPIO_InitStructure); //初始化结构体
	GPIO_SetBits(LED1_PORT,LED1_PIN);
	
	GPIO_InitStructure.GPIO_Pin=LED2_PIN;//管脚设置
	GPIO_Init(LED2_PORT,&GPIO_InitStructure); //初始化结构体
	GPIO_SetBits(LED2_PORT,LED2_PIN);

}

/*******************************************************************************
* 函 数 名         : ADC_Temp_Init
* @函数功能		   : ADC_Temp初始化函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void ADC_Temp_Init(void)
{	
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束
	
	ADC_TempSensorVrefintCmd(ENABLE);//打开ADC内部温度传感器
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器
}

/*******************************************************************************
* 函 数 名         : Get_ADC_Temp_Value
* @函数功能		   : 获取通道ch的转换值，取times次,然后平均 	
* 输    入         : ch:通道编号
					 times:获取次数
* 输    出         : 通道ch的times次转换结果平均值
*******************************************************************************/
u16 Get_ADC_Temp_Value(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles);	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	for(t=0;t<times;t++)
	{
		ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
		temp_val+=ADC_GetConversionValue(ADC1);
		delay_ms(5);
	}
	return temp_val/times;
} 

/*******************************************************************************
* 函 数 名         : Get_Temperture
* @函数功能		   : 获取温度值 	
* 输    入         : 无
* 输    出         : 温度值(扩大了100倍,单位:℃)
*******************************************************************************/
int Get_Temperture(void)
{
	u32 adc_value;
	int temp;
 	double temperture;
	adc_value=Get_ADC_Temp_Value(ADC_Channel_16,10);	//读取通道16内部温度传感器通道,10次取平均
	temperture=(float)adc_value*(3.3/4096);		//电压值
	temperture=(temperture-0.76)/0.0025 + 25; //转换为温度值 
	temp=temperture*100;					//扩大100倍.
	return temp;
}


