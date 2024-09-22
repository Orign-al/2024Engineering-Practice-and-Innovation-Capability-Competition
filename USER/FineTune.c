#include "include.h"


// ?????????
MotorFineTuneController motor_fine_tune_controllers[MOTOR_COUNT];

// ?????PID???
static void FineTunePID_Init(FineTunePIDController* pid, float Kp, float Ki, float Kd, float min, float max) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->integral = 0;
    pid->prev_error = 0;
    pid->output_min = min;
    pid->output_max = max;
}

// ??PID??
static float FineTunePID_Compute(FineTunePIDController* pid, float error, float dt) {
    pid->integral += error * dt;
    float derivative = (error - pid->prev_error) / dt;
    float output = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;

    if (output > pid->output_max) {
        output = pid->output_max;
    } else if (output < pid->output_min) {
        output = pid->output_min;
    }

    pid->prev_error = error;
    return output;
}

// ??????????
void InitializeMotorFineTuneControllers(void) {
    for (int i = 0; i < MOTOR_COUNT; i++) {
        // ??PID???
        FineTunePID_Init(&motor_fine_tune_controllers[i].angle_pid, 1.5f, 0.1f, 0.05f, -5000, 5000);
        
        // ??PID???
        FineTunePID_Init(&motor_fine_tune_controllers[i].speed_pid, 0.9f, 0.05f, 0.02f, -1000, 1000);
        
        // ??PID???
        FineTunePID_Init(&motor_fine_tune_controllers[i].current_pid, 0.5f, 0.01f, 0.005f, -3000, 3000);
    }
}

// ????????
void MotorFineTuneControl(MotorFineTuneController* controller, MotorFeedback* feedback, float target_angle, float* output_current) {
    // ??????(??????)
    float angle_error = target_angle - (float)feedback->angle;
    if (angle_error > 4096) angle_error -= 8192;
    if (angle_error < -4096) angle_error += 8192;

    // ??PID??
    float angle_output = FineTunePID_Compute(&controller->angle_pid, angle_error, 0.001f);

    // ??PID??
    float speed_error = angle_output - feedback->speed;
    float speed_output = FineTunePID_Compute(&controller->speed_pid, speed_error, 0.001f);

    // ??PID??
    float current_error = speed_output - feedback->current;
    *output_current = FineTunePID_Compute(&controller->current_pid, current_error, 0.001f);
}