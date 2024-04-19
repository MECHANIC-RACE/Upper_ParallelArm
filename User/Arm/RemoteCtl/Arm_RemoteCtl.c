/*
 * @Author: Chen Yitong
 * @Date: 2023-09-23 13:47:29
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-19 16:29:34
 * @FilePath: \Upper_ParallelArm\User\Arm\RemoteCtl\Arm_RemoteCtl.c
 * @Brief: 机械臂遥控代码
 *
 * Copyright (c) 2023 by ChenYiTong, All Rights Reserved.
 */

#include "Arm_RemoteCtl.h"

uint8_t ReceiveData[4];  //外部传入的目标x,y,z方位数据（专门多留出这个数组供接收外界传入数据，因为还不清楚数据具体传入方式，留出这个接口后就只用修改这个数组及相关解算而不用动RemoteCtl_RawData）
Remote_t RemoteCtl_RawData;


/**
 * @brief 机械臂遥控初始化
 * @return {*}
 */
void Arm_RemoteCtl_Init()
{
    HAL_UART_Receive_DMA(&huart_RemoteCtl, ReceiveData, 4);
    HAL_UART_Transmit(&huart_RemoteCtl, ReceiveData, 4, 1000);
    __HAL_UART_ENABLE_IT(&huart_RemoteCtl, UART_IT_IDLE); // IDLE 中断使能
}

void RemoteCtl_Decode()
{
    //RemoteCtl_RawData.x = 40;
    //RemoteCtl_RawData.y = 60;
    //RemoteCtl_RawData.z = 50;
    //RemoteCtl_RawData.choice = 3;
    RemoteCtl_RawData.x = ReceiveData[0];
    RemoteCtl_RawData.y = ReceiveData[1];
    RemoteCtl_RawData.z = ReceiveData[2];
    RemoteCtl_RawData.choice = ReceiveData[3];
    /* UART1 callback decode function  */
}