/*********************************************************************************************************
* 文件名称：PCA.h
* 摘    要：PCA
* 当前版本：1.0.0
* 作    者：麦特实验室
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
#ifndef __PCA_h_
#define __PCA_h_

void PCAAppMain();
void PCA0AppMain();
void PCA1AppMain();
void PCA2AppMain();
void PCA3AppMain();

extern u8 xdata cnt;//存储PCA计时溢出次数
extern u32 xdata Count0[4];//首数据
extern u32 xdata Count1[4];//次数据
extern u32 xdata length[4];//长度(us) 
                      
void PCAInit();
void PCA0Init();
void PCA1Init();
void PCA2Init();
void PCA3Init();
//void PCAInterrupt() interrupt 7;

#endif
