/*** 
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-17 20:35:15
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-20 16:08:26
 * @FilePath: \Upper_ParallelArm\User\Arm\Config\Arm_Variable.h
 * @Description: 结构体、变量的声明
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */

#ifndef __ARM_VARIABLE_H__
#define __ARM_VARIABLE_H__

#include "Arm_Start.h"
#include "Arm_commen.h"

extern uint8_t ReceiveData[15];    //外部传入的目标x,y,z方位数据包
extern ARM_MOVING_STATE ArmState;   // 机械臂运动状态
extern ARM_MOVING_STATE ArmControl; // 机械臂运动状态控制
extern JOINT_COMPONENT JointComponent;      // 机械臂关节控制

#endif // __ARM_VARIABLE_H__