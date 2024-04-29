/*
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-17 22:37:00
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-29 14:06:57
 * @FilePath: \Upper_ParallelArm\User\Arm\Calculate\Arm_Calculate.c
 * @Description: 机械臂解算
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */

#include "Arm_Calculate.h"

void CalculateParallelArm(double *motor_position, double x, double y, double z)
{
    motor_position[0] = atan2(x,y) / DEC ;  //云台
    motor_position[1] = ( M_PI_2 - atan2( sqrt(x*x+y*y),z ) - acos( (x*x+y*y+z*z+L1*L1-L2*L2) / (2*L1*sqrt(x*x+y*y+z*z)) ) ) / DEC ;  //下部pitch轴电机
    motor_position[2] = ( - M_PI_2 + atan2( z,sqrt(x*x+y*y) ) + acos( (x*x+y*y+z*z+L2*L2-L1*L1) / (2*L2*sqrt(x*x+y*y+z*z)) ) ) / DEC; ;  //上部pitch轴电机
}