#ifndef _FineTune_h_
#define _FineTune_h_

#include "include.h"



// ??PID?????
typedef struct {
    float Kp, Ki, Kd;
    float integral, prev_error;
    float output_min, output_max;
} FineTunePIDController;

// ????????
typedef struct {
    FineTunePIDController angle_pid;
    FineTunePIDController speed_pid;
    FineTunePIDController current_pid;
} MotorFineTuneController;



// ????
void InitializeMotorFineTuneControllers(void);
void MotorFineTuneControl(MotorFineTuneController* controller, MotorFeedback* feedback, float target_angle, float* output_current);

// ??????
extern MotorFineTuneController motor_fine_tune_controllers[MOTOR_COUNT];

#endif // FINE_TUNE_PID_H

