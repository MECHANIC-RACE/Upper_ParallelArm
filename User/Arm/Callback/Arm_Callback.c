/*
 * @Author: Chen Yitong
 * @Date: 2023-09-23 14:13:20
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-19 19:07:06
 * @FilePath: \Upper_ParallelArm\User\Arm\Callback\Arm_Callback.c
 * @Brief: 机械臂用中断回调函数
 *
 * Copyright (c) 2023 by ChenYiTong, All Rights Reserved.
 */

#include "Arm_Callback.h"

/**
 * @brief: 串口接收中断回调函数
 * @param {UART_HandleTypeDef} *huart 中断串口
 * @return {*}
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == huart_RemoteCtl.Instance)
    {
        // __HAL_UART_ENABLE_IT(&huart_RemoteCtl, UART_IT_IDLE); // IDLE 中断使能
        RemoteCtl_Decode(); // 遥控解码
        HAL_UART_Receive_IT(&huart_RemoteCtl, (uint8_t*)ReceiveData, 15);
    }
}
