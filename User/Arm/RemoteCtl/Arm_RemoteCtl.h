/*** 
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-18 14:41:17
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-19 16:04:13
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
    int16_t x;
    int16_t y;
    int16_t z;
    int8_t choice;  //机械臂状态设置接口
} Remote_t;


extern uint8_t ReceiveData[4];  //外部传入的目标x,y,z，case方位数据
extern Remote_t RemoteCtl_RawData;

void Arm_RemoteCtl_Init();

#endif // __ARM_REMOTECTL_H__