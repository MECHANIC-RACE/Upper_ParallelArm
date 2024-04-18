/*
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-17 22:15:23
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-18 15:39:12
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
    
    hDJI[0].motorType      = M3508; //云台
    hDJI[1].motorType      = M2006; //下pitch轴
    hDJI[2].motorType      = M2006; //上pitch轴

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
        xSemaphoreTakeRecursive(ArmControl.xMutex_control, portMAX_DELAY);
        ARM_MOVING_STATE ArmControl_tmp = ArmControl;
        xSemaphoreGiveRecursive(ArmControl.xMutex_control);

        double motor_velocity[4] = {0};
        CalculateParallelArm(motor_velocity,
                                   ArmControl_tmp.velocity.x,
                                   ArmControl_tmp.velocity.y,
                                   ArmControl_tmp.velocity.z);
        DJI_t hDJI_tmp[4];

        vPortEnterCritical();
        for (int i = 0; i < 4; i++) { memcpy(&(hDJI_tmp[i]), JointComponent.hDJI[i], sizeof(DJI_t)); }
        memcpy(&(hDJI_tmp[3]), JointComponent.hDJI[3], sizeof(DJI_t));
        vPortExitCritical();

        for (int i = 0; i < 4; i++) { positionServo(motor_velocity[i], &(hDJI_tmp[i])); }
        CanTransmit_DJI_1234(&hcan_Dji,
                             hDJI_tmp[0].speedPID.output,
                             hDJI_tmp[1].speedPID.output,
                             hDJI_tmp[2].speedPID.output,
                             hDJI_tmp[3].speedPID.output);

        vPortEnterCritical();
        for (int i = 0; i < 4; i++) { memcpy(JointComponent.hDJI[i], &(hDJI_tmp[i]), sizeof(DJI_t)); }
        vPortExitCritical();

        vTaskDelay(10);
    }
}

/**
 * @brief: 启动机械臂伺服线程
 * @return {*}
 */
void Arm_Servo_TaskStart()
{
    osThreadNew(Arm_Servo_Task, NULL, NULL);
}

/**
 * @brief T型速度规划函数（？不知道在机械臂控制里还有用吗）
 * @param initialAngle 初始角度
 * @param maxAngularVelocity 最大角速度
 * @param AngularAcceleration 角加速度
 * @param targetAngle 目标角度
 * @param currentTime 当前时间
 * @param currentTime 当前角度
 * @todo 转换为国际单位制
 */
void VelocityPlanning(float initialAngle, float maxAngularVelocity, float AngularAcceleration, float targetAngle, float currentTime, volatile float *currentAngle)
{

    float angleDifference = targetAngle - initialAngle;     // 计算到目标位置的角度差
    float sign            = (angleDifference > 0) ? 1 : -1; // 判断角度差的正负(方向)

    float accelerationTime = maxAngularVelocity / AngularAcceleration;                                                      // 加速(减速)总时间
    float constTime        = (fabs(angleDifference) - AngularAcceleration * pow(accelerationTime, 2)) / maxAngularVelocity; // 匀速总时间
    float totalTime        = constTime + accelerationTime * 2;                                                              // 计算到达目标位置所需的总时间

    // 判断能否达到最大速度
    if (constTime > 0) {
        // 根据当前时间判断处于哪个阶段
        if (currentTime <= accelerationTime) {
            // 加速阶段
            *currentAngle = initialAngle + sign * 0.5 * AngularAcceleration * pow(currentTime, 2);
        } else if (currentTime <= accelerationTime + constTime) {
            // 匀速阶段
            *currentAngle = initialAngle + sign * maxAngularVelocity * (currentTime - accelerationTime) + 0.5 * sign * AngularAcceleration * pow(accelerationTime, 2);
        } else if (currentTime <= totalTime) {
            // 减速阶段
            float decelerationTime = currentTime - accelerationTime - constTime;
            *currentAngle          = initialAngle + sign * maxAngularVelocity * constTime + 0.5 * sign * AngularAcceleration * pow(accelerationTime, 2) + sign * (maxAngularVelocity * decelerationTime - 0.5 * AngularAcceleration * pow(decelerationTime, 2));
        } else {
            // 达到目标位置
            *currentAngle = targetAngle;
        }
    } else {
        maxAngularVelocity = sqrt(fabs(angleDifference) * AngularAcceleration);
        accelerationTime   = maxAngularVelocity / AngularAcceleration;
        totalTime          = 2 * accelerationTime;
        constTime          = 0;
        // 根据当前时间判断处于哪个阶段
        if (currentTime <= accelerationTime) {
            // 加速阶段
            *currentAngle = initialAngle + sign * 0.5 * AngularAcceleration * pow(currentTime, 2);
        } else if (currentTime <= totalTime) {
            // 减速阶段
            float decelerationTime = currentTime - accelerationTime; // 减速时间
            *currentAngle          = initialAngle + sign * 0.5 * AngularAcceleration * pow(accelerationTime, 2) + sign * (maxAngularVelocity * decelerationTime - 0.5 * AngularAcceleration * pow(decelerationTime, 2));
        } else {
            // 达到目标位置
            *currentAngle = targetAngle;
        }
    }
}