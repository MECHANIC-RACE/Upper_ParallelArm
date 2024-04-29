/*
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-17 22:15:23
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-29 23:53:47
 * @FilePath: \Upper_ParallelArm\User\Arm\Servo\Arm_Servo.c
 * @Description: 机械臂伺服
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */

#include "Arm_Servo.h"
JOINT_COMPONENT JointComponent;
double motor_position_ref[4] = {0};

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
}

/**
 * @brief: 伺服线程
 * @return {*}
 */
void Arm_Servo_Task(void *argument)
{

    osDelay(1000);
    for (;;) {
        // xSemaphoreTakeRecursive(ArmControl.xMutex_control, portMAX_DELAY);
        // ARM_MOVING_STATE ArmControl_tmp = ArmControl;
        // xSemaphoreGiveRecursive(ArmControl.xMutex_control);

        // double motor_position[4] = {0};
        // CalculateParallelArm(motor_position,
        //                            ArmControl_tmp.position.x,
        //                            ArmControl_tmp.position.y,
        //                            ArmControl_tmp.position.z);
        
        DJI_t hDJI_tmp[4];

        vPortEnterCritical();
        for (int i = 0; i < 4; i++) { memcpy(&(hDJI_tmp[i]), JointComponent.hDJI[i], sizeof(DJI_t)); }
        // memcpy(&(hDJI_tmp[3]), JointComponent.hDJI[3], sizeof(DJI_t));
        vPortExitCritical();

        for (int i = 0; i < 4; i++) { positionServo(motor_position_ref[i], &(hDJI_tmp[i])); }
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
    .stack_size = 1280 * 4,
    .priority = (osPriority_t) osPriorityHigh,
    };
    Arm_Servo_TaskHandle = osThreadNew(Arm_Servo_Task, NULL, &Arm_Servo_Task_attributes);
}

