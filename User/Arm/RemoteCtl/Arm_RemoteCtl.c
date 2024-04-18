/*
 * @Author: Chen Yitong
 * @Date: 2023-09-23 13:47:29
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-18 14:43:05
 * @FilePath: \Upper_ParallelArm\User\Arm\RemoteCtl\Arm_RemoteCtl.c
 * @Brief: 机械臂遥控代码
 *
 * Copyright (c) 2023 by ChenYiTong, All Rights Reserved.
 */

#include "Arm_RemoteCtl.h"


/**
 * @brief 底盘遥控初始化
 * @return {*}
 */
void Arm_RemoteCtl_Init()
{
    HAL_UART_Receive_DMA(&huart_RemoteCtl, JoyStickReceiveData, 18);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); // IDLE 中断使能
}
