/*
 * @Author: Chen Yitong
 * @Date: 2023-09-23 13:47:29
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-29 21:17:42
 * @FilePath: \Upper_ParallelArm\User\Arm\RemoteCtl\Arm_RemoteCtl.c
 * @Brief: 机械臂遥控代码
 *
 * Copyright (c) 2023 by ChenYiTong, All Rights Reserved.
 */

#include "Arm_RemoteCtl.h"

uint8_t ReceiveData[15] = {0}; // 串口传入的目标x,y,z方位原始数据（专门多留出这个数组供接收外界传入数据，因为还不清楚数据具体传入方式，留出这个接口后就只用修改这个数组及相关解算而不用动RemoteCtl_RawData）
//uint8_t tmp[4] = {0};  
Remote_t RemoteCtl_RawData; //处理过的目标x,y,z方位数据
typedef union
{
    float data;
    uint8_t byte[4];
}byte_to_float;//用联合体将浮点数拆分为可收发的字节

/**
 * @brief 机械臂遥控初始化
 * @return {*}
 */
void Arm_RemoteCtl_Init()
{
    // __HAL_UART_ENABLE_IT(&huart_RemoteCtl,UART_IT_RXNE);
    HAL_UART_Receive_IT(&huart_RemoteCtl, (uint8_t *)ReceiveData, 15);
    // __HAL_UART_ENABLE_IT(&huart_RemoteCtl, UART_IT_IDLE); // IDLE 中断使能
}

void RemoteCtl_Decode()
{
    // RemoteCtl_RawData.x = 40;
    // RemoteCtl_RawData.y = 60;
    // RemoteCtl_RawData.z = 50;
    // RemoteCtl_RawData.choice = 3;
    if(ReceiveData[0] == 0xFF && ReceiveData[14] == 0xFE)
    {
        byte_to_float data_tmp;

        data_tmp.byte[3]=ReceiveData[1];
        data_tmp.byte[2]=ReceiveData[2];
        data_tmp.byte[1]=ReceiveData[3];
        data_tmp.byte[0]=ReceiveData[4];
        RemoteCtl_RawData.x      = data_tmp.data;
        
        data_tmp.byte[3]=ReceiveData[5];
        data_tmp.byte[2]=ReceiveData[6];
        data_tmp.byte[1]=ReceiveData[7];
        data_tmp.byte[0]=ReceiveData[8];
        RemoteCtl_RawData.y      = data_tmp.data;

        data_tmp.byte[3]=ReceiveData[9];
        data_tmp.byte[2]=ReceiveData[10];
        data_tmp.byte[1]=ReceiveData[11];
        data_tmp.byte[0]=ReceiveData[12];
        RemoteCtl_RawData.z      = data_tmp.data;
        
        RemoteCtl_RawData.choice = ReceiveData[13];
    }
    else
    {
        osDelay(2);
    }
    // __HAL_UART_ENABLE_IT(&huart_RemoteCtl, UART_IT_IDLE); // IDLE 中断使能
    // HAL_UART_Transmit(&huart_RemoteCtl, ReceiveData, 4, 0xFFFF);
    /* UART1 callback decode function  */
}