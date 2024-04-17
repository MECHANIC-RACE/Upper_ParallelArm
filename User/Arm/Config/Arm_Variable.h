/*
 * @Author: Chen Yitong
 * @Date: 2023-09-23 17:18:52
 * @LastEditors: Chen Yitong 
 * @LastEditTime: 2023-10-21 21:56:25
 * @FilePath: \WTR_Chassis\麦克纳姆轮\UserCode\Chassis\Config\Chassis_Variable.h
 * @Brief: 结构体、变量的声明
 *
 * Copyright (c) 2023 by ChenYiTong, All Rights Reserved.
 */
#ifndef __CHASSIS_VARIABLE_H__
#define __CHASSIS_VARIABLE_H__

#include "Arm_Start.h"
#include "Arm_commen.h"
extern ARM_MOVING_STATE ArmState;   // 机械臂运动状态
extern ARM_MOVING_STATE ArmControl; // 机械臂运动状态控制
extern MOTOR_COMPONENT MotorComponent;      // 电机控制

#endif // __CHASSIS_VARIABLE_H__