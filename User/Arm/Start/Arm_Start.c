/*
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-15 23:10:34
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-19 19:29:14
 * @FilePath: \Upper_ParallelArm\User\Arm\Start\Arm_Start.c
 * @Description: 机械臂启动文件
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */

#include "Arm_Start.h"

/**
 * @brief 默认任务，启动其他线程
 * @return {*}
 */
void StartDefaultTask(void *argument)
{
    //================初始化====================
    Arm_RemoteCtl_Init();    // 遥控初始化
    Arm_StateMachine_Init(); // 状态机初始化
    Arm_Servo_Init();        // 机械臂电机初始化
    //================启动线程==================
    Arm_StateMachine_TaskStart(); // 状态机进程启动
    Arm_Servo_TaskStart();        // 机械臂伺服进程启动

    for (;;)
    {
        HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_14);
        osDelay(100);
    }
}