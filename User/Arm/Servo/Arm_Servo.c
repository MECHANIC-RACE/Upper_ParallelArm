/*
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-14 15:35:36
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-16 00:03:00
 * @FilePath: \Upper_ParallelArm\User\Arm\Servo\Arm_Servo.c
 * @Description: 机械臂伺服
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */

#include "Arm_Servo.h"
MOTOR_COMPONENT MotorComponent;

void Arm_Servo_Init()
{
    //三个dji电机初始化
    hDJI[0].motorType = M3508;
    hDJI[1].motorType = M2006;
    hDJI[2].motorType = M2006;
    CANFilterInit(&hcan1);
    DJI_Init();

    // 云台m3508电机pid参数（yaw轴）
    hDJI[0].speedPID.KP        = 10;
    hDJI[0].speedPID.KI        = 0.2;
    hDJI[0].speedPID.KD        = 2;
    hDJI[0].speedPID.outputMax = 1000;

    hDJI[0].posPID.KP        = 180.0f;
    hDJI[0].posPID.KI        = 0.0f;
    hDJI[0].posPID.KD        = 2.0f;
    hDJI[0].posPID.outputMax = 5000;

    // 下臂pitch轴m2006电机pid参数
    hDJI[1].speedPID.KP        = 10;
    hDJI[1].speedPID.KI        = 0.2;
    hDJI[1].speedPID.KD        = 2;
    hDJI[1].speedPID.outputMax = 1000;

    hDJI[1].posPID.KP        = 180.0f;
    hDJI[1].posPID.KI        = 0.0f;
    hDJI[1].posPID.KD        = 2.0f;
    hDJI[1].posPID.outputMax = 5000;

    // 上臂pitch轴m2006电机pid参数
    hDJI[2].speedPID.KP        = 10;
    hDJI[2].speedPID.KI        = 0.2;
    hDJI[2].speedPID.KD        = 2;
    hDJI[2].speedPID.outputMax = 1000;

    hDJI[2].posPID.KP        = 180.0f;
    hDJI[2].posPID.KI        = 0.0f;
    hDJI[2].posPID.KD        = 2.0f;
    hDJI[2].posPID.outputMax = 5000;
}
