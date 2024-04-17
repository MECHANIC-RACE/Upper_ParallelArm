/*** 
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-15 23:10:48
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-17 20:23:05
 * @FilePath: \Upper_ParallelArm\User\Arm\Start\Arm_Start.h
 * @Description: 机械臂启动文件及其所有库
 * 
 * Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */

#ifndef __ARM_START_H__
#define __ARM_START_H__
// 基本引用
#include "main.h"
#include "can.h"
#include "gpio.h"
#include "usart.h"

//FreeRTOS相关
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h" //使用v2需要加上这个互斥锁头文件，或者直接调用v2包装好的加互斥锁函数
#include "cmsis_os.h"  //先不删它以提高容错，指不定哪个地方的v1代码没有改干净捏（）
#include "cmsis_os2.h" //学长用的是cmsis v1，所以这里原先引用的只有"cmsis_os.h"，但是我们需要迁移至v2，遂按官网说明将"cmsis_os2.h"加上

//祖传代码引用
#include "wtr_calculate.h"
#include "wtr_can.h"
#include "wtr_dji.h"
#include "wtr_uart.h"

//自己的引用
#include "Arm_Callback.h"
#include "Arm_commen.h"
#include "Arm_UserConfig.h"
#include "Arm_RemoteCtl.h"
#include "Arm_Servo.h"
#include "Arm_StateMachine.h"
#include "Arm_Variable.h"
#include "string.h"
#endif