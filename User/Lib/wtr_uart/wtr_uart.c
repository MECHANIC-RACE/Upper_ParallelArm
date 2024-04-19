/*
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-16 00:09:47
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-19 15:41:19
 * @FilePath: \Upper_ParallelArm\User\Lib\wtr_uart\wtr_uart.c
 * @Description: 
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */
#include "wtr_uart.h"
#include "wtr_dji.h"
#include "string.h"
#include "math.h"
#include "usart.h"

DjiRemote_t DjiRemoteCtl_RawData;
uint8_t JoyStickReceiveData[18];

double angMax = 360;
double posRef; // 工程中也可调用需要参数来传值

/**
 * @brief 解码大疆电机
 * @return {*}
 */
void DjiRemoteCtl_Decode()
{

    DjiRemoteCtl_RawData.ch0 = ((int16_t)JoyStickReceiveData[0] | ((int16_t)JoyStickReceiveData[1] << 8)) & 0x07FF;
    DjiRemoteCtl_RawData.ch1 = (((int16_t)JoyStickReceiveData[1] >> 3) | ((int16_t)JoyStickReceiveData[2] << 5)) & 0x07FF;
    DjiRemoteCtl_RawData.ch2 = (((int16_t)JoyStickReceiveData[2] >> 6) | ((int16_t)JoyStickReceiveData[3] << 2) |
                             ((int16_t)JoyStickReceiveData[4] << 10)) &
                            0x07FF;
    DjiRemoteCtl_RawData.ch3   = (((int16_t)JoyStickReceiveData[4] >> 1) | ((int16_t)JoyStickReceiveData[5] << 7)) & 0x07FF;
    DjiRemoteCtl_RawData.left  = ((JoyStickReceiveData[5] >> 4) & 0x000C) >> 2;
    DjiRemoteCtl_RawData.right = ((JoyStickReceiveData[5] >> 4) & 0x0003);
    DjiRemoteCtl_RawData.wheel = ((int16_t)JoyStickReceiveData[16]) | ((int16_t)JoyStickReceiveData[17] << 8);
    /* UART1 callback decode function  */
}

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

//
//}
