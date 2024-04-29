/*** 
 * @Author: doge60 3020118317@qq.com
 * @Date: 2024-04-14 20:29:53
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-04-19 20:19:59
 * @FilePath: \Upper_ParallelArm\User\Arm\Config\Arm_User_Config.h
 * @Description: 自定义宏
 * 
 * @Copyright (c) 2024 by doge60 3020118317@qq.com, All Rights Reserved. 
 */
#ifndef __ARM_USER_CONFIG_H__
#define __ARM_USER_CONFIG_H__

/**
 * @brief 自定义端口 *
 */

#define huart_RemoteCtl huart8  //其实不是用遥控，只是借用遥控端口，往工程里传目标相对于机械臂基坐标的x,y,z值
#define hcan_Dji        hcan1
#define JointComponent_X JointComponent.hDJI[0]
#define JointComponent_Y JointComponent.hDJI[1]
#define JointComponent_Z JointComponent.hDJI[2]

#endif // __ARM_USER_CONFIG_H__