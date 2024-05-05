/*
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-17 22:15:23
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-30 23:29:57
 * @FilePath: \Upper_ParallelArm\User\Arm\Servo\Arm_Servo.c
 * @Description: 机械臂伺服
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */

#include "Arm_Servo.h"
JOINT_COMPONENT JointComponent;

/**
 * @brief 大疆电机初始化
 * @return {*}
 */

void Arm_Servo_Init()
{
    CANFilterInit(&hcan1);
    JointComponent.hDJI[0] = &hDJI[0];
    JointComponent.hDJI[1] = &hDJI[1];
    JointComponent.hDJI[2] = &hDJI[2];
    
    hDJI[0].motorType      = M2006; //云台
    hDJI[1].motorType      = M3508; //下pitch轴
    hDJI[2].motorType      = M3508; //上pitch轴

    DJI_Init();
    for (int i = 0; i < 8; i++) {
        hDJI[i].speedPID.KP        = 2.0;
        hDJI[i].speedPID.KI        = 0.00;
        hDJI[i].speedPID.KD        = 0.0;
        hDJI[i].speedPID.outputMax = 8000;

        hDJI[i].posPID.KP        = 80.0f;
        hDJI[i].posPID.KI        = 0.0f;
        hDJI[i].posPID.KD        = 0.0f;
        hDJI[i].posPID.outputMax = 4000;
    }
}

/**
 * @brief: 伺服线程
 * @return {*}
 */
void Arm_Servo_Task(void *argument)
{

    osDelay(1000);
    for (;;) {
        DJI_t hDJI_tmp[4];

        vPortEnterCritical();
        for (int i = 0; i < 4; i++) { memcpy(&(hDJI_tmp[i]), JointComponent.hDJI[i], sizeof(DJI_t)); }
        // memcpy(&(hDJI_tmp[3]), JointComponent.hDJI[3], sizeof(DJI_t));
        vPortExitCritical();

        for (int i = 0; i < 4; i++) { positionServo(current_angle[i], &(hDJI_tmp[i])); }
        // for (int i = 0; i < 4; i++) { positionServo(150, &(hDJI_tmp[i])); } // 调试用数据
        CanTransmit_DJI_1234(&hcan_Dji,
                             hDJI_tmp[0].speedPID.output,
                             hDJI_tmp[1].speedPID.output,
                             hDJI_tmp[2].speedPID.output,
                             hDJI_tmp[3].speedPID.output);

        vPortEnterCritical();
        for (int i = 0; i < 4; i++) { memcpy(JointComponent.hDJI[i], &(hDJI_tmp[i]), sizeof(DJI_t)); }
        vPortExitCritical();

        vTaskDelay(2);
    }
}

/**
 * @brief: 启动机械臂伺服线程
 * @return {*}
 */
void Arm_Servo_TaskStart()
{
    osThreadId_t Arm_Servo_TaskHandle;
    const osThreadAttr_t Arm_Servo_Task_attributes = {
    .name = "Arm_Servo_Task",
    .stack_size = 128 * 10,
    .priority = (osPriority_t) osPriorityHigh1,
    };
    Arm_Servo_TaskHandle = osThreadNew(Arm_Servo_Task, NULL, &Arm_Servo_Task_attributes);
}

