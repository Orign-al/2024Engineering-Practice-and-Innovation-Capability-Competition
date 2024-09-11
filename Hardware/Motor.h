
#ifndef __MOTOR_H
#define __MOTOR_H



// ??????
#define MOTOR_A_PWM1_Pin    GPIO_Pin_8
#define MOTOR_A_PWM2_Pin    GPIO_Pin_9
#define MOTOR_A_PWM_GPIO_Port  GPIOB

#define MOTOR_B_PWM1_Pin    GPIO_Pin_5
#define MOTOR_B_PWM2_Pin    GPIO_Pin_6
#define MOTOR_B_PWM_GPIO_Port  GPIOE

#define MOTOR_C_PWM1_Pin    GPIO_Pin_9
#define MOTOR_C_PWM2_Pin    GPIO_Pin_11
#define MOTOR_C_PWM_GPIO_Port  GPIOE

#define MOTOR_D_PWM1_Pin    GPIO_Pin_13
#define MOTOR_D_PWM2_Pin    GPIO_Pin_14
#define MOTOR_D_PWM_GPIO_Port  GPIOE

void Motor_Init(int arr, int psc);
void Motor_SetSpeed(char motor, int16_t speed);
void Motor_Brake(char motor);



#endif // __MOTOR_H



