/*
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-29 22:29:47
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-30 16:10:44
 * @FilePath: \Upper_ParallelArm\User\Arm\VelocityPlanning\Arm_VelocityPlanning.c
 * @Description: 梯形速度规划代码
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */
#include "Arm_VelocityPlanning.h"

ARM_MOVING_STATE Target;
float initial_angle[3] = {0};
float current_angle[4] = {0};
double motor_position_ref[4] = {0};


/**
 * @description: 梯形速度规划线程
 * @param {void} *argument
 * @return {*}
 */
void Arm_VelocityPlanning_Task(void *argument)
{
    osDelay(100);

    for (;;) {
        xSemaphoreTakeRecursive(ArmControl.xMutex_control, portMAX_DELAY);
        ARM_MOVING_STATE ArmControl_tmp = ArmControl;
        xSemaphoreGiveRecursive(ArmControl.xMutex_control);

        CalculateParallelArm(motor_position_ref,
                                   ArmControl_tmp.position.x,
                                   ArmControl_tmp.position.y,
                                   ArmControl_tmp.position.z);
        
        TickType_t StartTick = xTaskGetTickCount();
        
        initial_angle[0] = JointComponent_X->AxisData.AxisAngle_inDegree;
        initial_angle[1] = JointComponent_Y->AxisData.AxisAngle_inDegree;
        initial_angle[2] = JointComponent_Z->AxisData.AxisAngle_inDegree;

        _Bool isArray         = 0;
        float diff[3]        = {0};
        do {
            TickType_t CurrentTick = xTaskGetTickCount();
            float current_time     = (CurrentTick - StartTick)*1.0 / 1000.0;
            VelocityPlanning(initial_angle[0], 1000, 500, motor_position_ref[0], current_time, &(current_angle[0]));
            VelocityPlanning(initial_angle[1], 1000, 500, motor_position_ref[1], current_time, &(current_angle[1]));
            VelocityPlanning(initial_angle[2], 1000, 500, motor_position_ref[2], current_time, &(current_angle[2]));
            for (uint16_t i = 0; i < 3; i++) { diff[i] = fabs(motor_position_ref[i] - current_angle[i]); }
            if ((diff[0] < 0.1) && (diff[1] < 0.1) && (diff[2] < 0.1)) { isArray = 1; }
            //printf("%d,%d,%f,%f\n", StartTick, CurrentTick, current_time,current_angle[0]);
        } while (!isArray);

        osDelay(2);
    }
    
}

/**
 * @description: 启动梯形速度规划线程
 * @return {*}
 */
void Arm_VelocityPlanning_TaskStart(void)
{
    osThreadId_t Arm_VelocityPlanning_TaskHandle;
    const osThreadAttr_t Arm_VelocityPlanning_Task_attributes = {
        .name       = "Arm_VelocityPlanning_Task",
        .stack_size = 1280 * 4,
        .priority   = (osPriority_t) osPriorityHigh,
    };

    Arm_VelocityPlanning_TaskHandle = osThreadNew(Arm_VelocityPlanning_Task, NULL, &Arm_VelocityPlanning_Task_attributes);
}

/**
 * @description: 梯形速度规划初始化
 * @return {*}
 */
// void Arm_VelocityPlanning_Init()
// {
//     ;
// }


/**
 * @brief 梯型速度规划函数
 * @param initialAngle 初始角度
 * @param maxAngularVelocity 最大角速度
 * @param AngularAcceleration 角加速度
 * @param targetAngle 目标角度
 * @param currentTime 当前时间
 * @param currentAngle 当前角度
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