#include "include.h"


// ?????
void Motor_Init(int arr, int psc) {
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    // ??GPIO??
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    // ??PWM??
    GPIO_InitStructure.GPIO_Pin = MOTOR_A_PWM1_Pin | MOTOR_A_PWM2_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = MOTOR_B_PWM1_Pin | MOTOR_B_PWM2_Pin |
                                  MOTOR_C_PWM1_Pin | MOTOR_C_PWM2_Pin |
                                  MOTOR_D_PWM1_Pin | MOTOR_D_PWM2_Pin;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // ????????
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM10);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM11);

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_TIM9);

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);

    // ???????
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

    // ??TIM1
    TIM_TimeBaseStructure.TIM_Period = arr; // ARR?
    TIM_TimeBaseStructure.TIM_Prescaler = psc; // PSC?
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    // ??TIM10
    TIM_TimeBaseStructure.TIM_Period = arr; // ARR?
    TIM_TimeBaseStructure.TIM_Prescaler = psc; // PSC?
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM10, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);

    TIM_Cmd(TIM10, ENABLE);

    // ??TIM11
    TIM_TimeBaseStructure.TIM_Period = arr; // ARR?
    TIM_TimeBaseStructure.TIM_Prescaler = psc; // PSC?
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM11, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);

    TIM_Cmd(TIM11, ENABLE);

    // ??TIM9
    TIM_TimeBaseStructure.TIM_Period = arr; // ARR?
    TIM_TimeBaseStructure.TIM_Prescaler = psc; // PSC?
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM9, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM9, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);

    TIM_Cmd(TIM9, ENABLE);
}

// ??????
void Motor_SetSpeed(char motor, int16_t speed) {
    uint16_t pwm_value = (uint16_t)abs(speed);

    if (pwm_value > 1000) {
        pwm_value = 1000;
    }

    switch (motor) {
        case 'A':
            if (speed < 0) {
                TIM_SetCompare1(TIM10, pwm_value);
                TIM_SetCompare1(TIM11, 0);
            } else if (speed > 0) {
                TIM_SetCompare1(TIM10, 0);
                TIM_SetCompare1(TIM11, pwm_value);
            } else {
                Motor_Brake('A');
            }
            break;
        case 'B':
            if (speed > 0) {
                TIM_SetCompare1(TIM9, pwm_value);
                TIM_SetCompare2(TIM9, 0);
            } else if (speed < 0) {
                TIM_SetCompare1(TIM9, 0);
                TIM_SetCompare2(TIM9, pwm_value);
            } else {
                Motor_Brake('B');
            }
            break;
        case 'C':
            if (speed > 0) {
                TIM_SetCompare1(TIM1, pwm_value);
                TIM_SetCompare2(TIM1, 0);
            } else if (speed < 0) {
                TIM_SetCompare1(TIM1, 0);
                TIM_SetCompare2(TIM1, pwm_value);
            } else {
                Motor_Brake('C');
            }
            break;
        case 'D':
            if (speed > 0) {
                TIM_SetCompare3(TIM1, pwm_value);
                TIM_SetCompare4(TIM1, 0);
            } else if (speed < 0) {
                TIM_SetCompare3(TIM1, 0);
                TIM_SetCompare4(TIM1, pwm_value);
            } else {
                Motor_Brake('D');
            }
            break;
        default:
            break;
    }
}

// ????
void Motor_Brake(char motor) {
    switch (motor) {
        case 'A':
            TIM_SetCompare1(TIM10, 4199);
            TIM_SetCompare1(TIM11, 4199);
            break;
        case 'B':
            TIM_SetCompare1(TIM9, 4199);
            TIM_SetCompare2(TIM9, 4199);
            break;
        case 'C':
            TIM_SetCompare1(TIM1, 4199);
            TIM_SetCompare2(TIM1, 4199);
            break;
        case 'D':
            TIM_SetCompare3(TIM1, 4199);
            TIM_SetCompare4(TIM1, 4199);
            break;
        default:
            break;
    }
}
