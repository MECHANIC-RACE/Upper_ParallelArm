#include "Arm_Try.h"
void Arm_Try_Init()
{
    //三个dji电机初始化
    hDJI[0].motorType = M3508;
    hDJI[1].motorType = M2006;
    hDJI[2].motorType = M2006;
    CANFilterInit(&hcan1);
    DJI_Init();
}

void Arm_Get_Angle()
{
    
}