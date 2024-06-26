#ifndef WTR_UART_H
#define WTR_UART_H

#include "main.h"

#define CH0_BIAS   1024
#define CH1_BIAS   1024
#define CH2_BIAS   1024
#define CH3_BIAS   1024
#define WHEEL_BIAS 1024
#define CH_RANGE   660.0

typedef struct
{
    int16_t ch0;
    int16_t ch1;
    int16_t ch2;
    int16_t ch3;
    int8_t left;
    int8_t right;
    int16_t wheel;
} DjiRemote_t;
void DjiRemoteCtl_Decode();
extern DjiRemote_t DjiRemoteCtl_RawData;
extern uint8_t JoyStickReceiveData[18];
extern double posRef;
#endif
