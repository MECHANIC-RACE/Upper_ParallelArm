/*** 
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-17 13:31:15
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-18 15:28:13
 * @FilePath: \Upper_ParallelArm\User\Arm\Config\Arm_commen.h
 * @Description: 机械臂结构体定义
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */

#ifndef __ARM_COMMEN_H__
#define __ARM_COMMEN_H__

#include "Arm_Start.h"
typedef enum {
    Store       = 1, // 存球
    Catch        = 3, // 取球
    Wait = 2, // 机械臂等待
} ARM_STATE;    // 机械臂状态

typedef __IO struct
{
    __IO struct {
        double x;
        double y;
        double z;
    } velocity; // 速度结构体（？x,y,z分别是啥）

    __IO struct {
        double x;
        double y;
        double z;
    } position; // 位置结构体（？x,y,z分别是啥）
    
    SemaphoreHandle_t xMutex_control; // 互斥锁

} ARM_MOVING_STATE; // 机械臂运动状态

typedef __IO struct {
    DJI_t *hDJI[4];  //机械臂只用到了三个电机，但是dji can的初始化似乎必须4个一起做，遂设4个，最后一个空挂着
    SemaphoreHandle_t xMutex_joint; // 互斥锁
} JOINT_COMPONENT;

#endif // __ARM_COMMEN_H__