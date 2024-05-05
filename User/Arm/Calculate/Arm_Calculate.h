/*** 
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-18 13:24:44
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-05-02 18:01:15
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
#define K0 5/3  //云台驱动齿轮与传动齿轮角度比
#define K1 6/5  //下pitch轴电机驱动齿轮与传动齿轮角度比
#define K2 6/5  //上pitch轴电机驱动齿轮与传动齿轮角度比
#define offset_0 0  //云台坐标零点与上电零点角度差
#define offset_1 15  //下pitch轴电机坐标零点与上电零点角度差
#define offset_2 -30  //上pitch轴电机坐标零点与上电零点角度差 

void CalculateParallelArm(double *motor_position, double x, double y, double z);

#endif // ARM_CALCULATE_H