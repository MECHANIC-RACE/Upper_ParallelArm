/*
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-15 23:10:34
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-30 20:38:24
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
    // Arm_VelocityPlanning_Init(); //梯形速度规划初始化
    //================启动线程==================
    Arm_StateMachine_TaskStart(); // 状态机进程启动
    Arm_Servo_TaskStart();        // 机械臂伺服进程启动
    Arm_VelocityPlanning_TaskStart(); //梯形速度规划启动

    for (;;) {
        HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_14);
        // osDelay(2);
        // HAL_UART_Transmit(&huart_RemoteCtl,"HelloWorld\r\n", strlen("HelloWorld\r\n"), 0xFFFF);  //调试串口用
        // printf("HelloWorld\r\n");  //调试串口重定向用
        // HAL_UART_Transmit(&huart_RemoteCtl, ReceiveData_tmp, 4, 0xFFFF);  //调试串口数据收发用
        // printf("%f,%f,%f,%d\n" , RemoteCtl_RawData.x,RemoteCtl_RawData.y,RemoteCtl_RawData.z,RemoteCtl_RawData.choice);  //调试串口浮点数据收发用
        printf("%f,%f,%f,%f,%f\n", JointComponent_lowerPitch->AxisData.AxisVelocity * 50, JointComponent_lowerPitch->AxisData.AxisAngle_inDegree, 
                JointComponent_lowerPitch->speedPID.ref, JointComponent_lowerPitch->speedPID.output, current_angle[1]); //调试pid+速度规划用
    }
}