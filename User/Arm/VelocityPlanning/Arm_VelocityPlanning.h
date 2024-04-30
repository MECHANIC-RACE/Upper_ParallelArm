/*** 
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-29 22:30:15
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-29 22:39:22
 * @FilePath: \Upper_ParallelArm\User\VelocityPlanning\Arm_VelocityPlanning.h
 * @Description: 梯形速度规划代码
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */
#ifndef ARM_VELOCITYPLANNING_H
#define ARM_VELOCITYPLANNING_H

#include "Arm_Start.h"

// extern double motor_position_ref[4]; //电机目标角度数组
extern float current_angle[4];

void Arm_VelocityPlanning_TaskStart(void);
// void Arm_VelocityPlanning_Init();
void VelocityPlanning(float initialAngle, float maxAngularVelocity, float AngularAcceleration, float targetAngle, float currentTime, volatile float *currentAngle);

#endif // ARM_VELOCITYPLANNING_H