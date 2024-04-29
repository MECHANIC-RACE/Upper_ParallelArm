/*** 
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-18 14:41:17
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-28 22:26:45
 * @FilePath: \Upper_ParallelArm\User\Arm\RemoteCtl\Arm_RemoteCtl.h
 * @Description: 机械臂遥控代码
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */


#ifndef __ARM_REMOTECTL_H__
#define __ARM_REMOTECTL_H__

#include "Arm_Start.h"

typedef struct
{
    float x;
    float y;
    float z;
    int8_t choice;  //机械臂状态设置接口
} Remote_t;


extern uint8_t ReceiveData[15];  //外部传入的目标x,y,z，case方位数据
extern Remote_t RemoteCtl_RawData; //处理过的目标x,y,z方位数据
// extern float TargetPosition[4];  

void Arm_RemoteCtl_Init();
void RemoteCtl_Decode();

#endif // __ARM_REMOTECTL_H__