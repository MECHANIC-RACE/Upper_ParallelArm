/*** 
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-17 13:31:15
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-17 20:26:19
 * @FilePath: \Upper_ParallelArm\User\Arm\Config\Arm_commen.h
 * @Description: 机械臂结构体定义
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */

#ifndef __ARM_COMMEN_H__
#define __ARM_COMMEN_H__

#include "Chassis_Start.h"
typedef enum {
    Stop       = 1, // 停止
    Run        = 3, // 启动
    Correcting = 2, // 机械臂校准
} ARM_STATE;    // 机械臂状态

typedef __IO struct
{
    __IO struct {
        double x;
        double y;
        double w;
    } velocity; // 速度结构体（？x,y,w分别是啥）

    __IO struct {
        double x;
        double y;
        double w;
    } position; // 位置结构体（？x,y,w分别是啥）
    
    SemaphoreHandle_t xMutex_control; // 互斥锁

} ARM_MOVING_STATE; // 底盘运动状态

typedef __IO struct {
    DJI_t *hDJI[3];  //改成3个，因为机械臂只用到了三个电机
    SemaphoreHandle_t xMutex_motor; // 互斥锁
} MOTOR_COMPONENT;

#endif // __ARM_COMMEN_H__