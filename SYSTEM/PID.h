#ifndef PID_H
#define PID_H

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float integral;
    float prevError;
    float minOutput;
    float maxOutput;
    float integralLimit;  // 新增：积分项限制
} PIDController;

void PID_Init(PIDController* pid, float Kp, float Ki, float Kd, float integralLimit);
void PID_SetOutputLimits(PIDController *pid, float min, float max);
float PID_Compute(PIDController *pid, float setpoint, float measurement);

#endif
