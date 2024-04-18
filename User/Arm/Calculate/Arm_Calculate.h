/*** 
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-18 13:24:44
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-18 13:34:22
 * @FilePath: \Upper_ParallelArm\User\Arm\Calculate\Arm_Calculate.h
 * @Description: 机械臂解算
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */
#ifndef ARM_CALCULATE_H
#define ARM_CALCULATE_H

#include "Arm_Start.h"
#include <math.h>

#define L1 210  //下臂长度（单位mm）
#define L2 200  //上臂长度（单位mm）

void CalculateParallelArm(double *motor_position, double x, double y, double z);

#endif // ARM_CALCULATE_H