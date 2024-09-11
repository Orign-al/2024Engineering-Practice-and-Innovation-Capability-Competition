#include "pid.h"
#include <math.h>
#include "include.h"

#define MOTOR_COUNT 4


void PID_Init(PIDController* pid, float Kp, float Ki, float Kd, float integralLimit) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->integral = 0.0f;
    pid->prevError = 0.0f;
    pid->minOutput = -16384.0f;
    pid->maxOutput = 16384.0f;
    pid->integralLimit = integralLimit;
}

void PID_SetOutputLimits(PIDController *pid, float min, float max) {
    pid->minOutput = min;
    pid->maxOutput = max;
}

float PID_Compute(PIDController* pid, float setpoint, float measurement) {
    float error = setpoint - measurement;
    float P = pid->Kp * error;
    
    // 积分分离
    // if (fabs(error) < INTEGRAL_SEPARATOR) {
    //     pid->integral += error;
    // } else {
    //     pid->integral = 0;  // 误差较大时，重置积分项
    // }
    
    // 积分限幅
    if (pid->integral > pid->integralLimit) {
        pid->integral = pid->integralLimit;
    } else if (pid->integral < -pid->integralLimit) {
        pid->integral = -pid->integralLimit;
    }
    
    float I = pid->Ki * pid->integral;
    float D = pid->Kd * (error - pid->prevError);
    
    pid->prevError = error;
    
    float output = P + I + D;
    
    // 输出限幅
    if (output > pid->maxOutput) {
        output = pid->maxOutput;
    } else if (output < pid->minOutput) {
        output = pid->minOutput;
    }
    
    return output;
}

