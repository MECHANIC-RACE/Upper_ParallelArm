#include "Arm_Servo.h"

void Arm_Servo_Init()
{
    //三个dji电机初始化
    hDJI[0].motorType = M3508;
    hDJI[1].motorType = M2006;
    hDJI[2].motorType = M2006;
    CANFilterInit(&hcan1);
    DJI_Init();

    // 云台m3508电机pid参数（yaw轴）
    hDJI[0].speedPID.KP        = 10;
    hDJI[0].speedPID.KI        = 0.2;
    hDJI[0].speedPID.KD        = 2;
    hDJI[0].speedPID.outputMax = 1000;

    hDJI[0].posPID.KP        = 180.0f;
    hDJI[0].posPID.KI        = 0.0f;
    hDJI[0].posPID.KD        = 2.0f;
    hDJI[0].posPID.outputMax = 5000;

    // 下臂pitch轴m2006电机pid参数
    hDJI[1].speedPID.KP        = 10;
    hDJI[1].speedPID.KI        = 0.2;
    hDJI[1].speedPID.KD        = 2;
    hDJI[1].speedPID.outputMax = 1000;

    hDJI[1].posPID.KP        = 180.0f;
    hDJI[1].posPID.KI        = 0.0f;
    hDJI[1].posPID.KD        = 2.0f;
    hDJI[1].posPID.outputMax = 5000;

    // 上臂pitch轴m2006电机pid参数
    hDJI[2].speedPID.KP        = 10;
    hDJI[2].speedPID.KI        = 0.2;
    hDJI[2].speedPID.KD        = 2;
    hDJI[2].speedPID.outputMax = 1000;

    hDJI[2].posPID.KP        = 180.0f;
    hDJI[2].posPID.KI        = 0.0f;
    hDJI[2].posPID.KD        = 2.0f;
    hDJI[2].posPID.outputMax = 5000;
}
