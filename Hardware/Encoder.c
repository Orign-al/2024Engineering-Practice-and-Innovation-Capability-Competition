#include "include.h"


void Encoder_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    // ?? GPIO ? TIM ??
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5, ENABLE);


    // ?? GPIO ???????
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    // ??? ENCODER A
    GPIO_InitStructure.GPIO_Pin = ENCODER_A_Pin1;
    GPIO_Init(ENCODER_A_1_GPIO_Port, &GPIO_InitStructure);
    GPIO_PinAFConfig(ENCODER_A_1_GPIO_Port, GPIO_PinSource15, GPIO_AF_TIM2); // PA15: TIM2_CH1

    GPIO_InitStructure.GPIO_Pin = ENCODER_A_Pin2;
    GPIO_Init(ENCODER_A_2_GPIO_Port, &GPIO_InitStructure);
    GPIO_PinAFConfig(ENCODER_A_2_GPIO_Port, GPIO_PinSource3, GPIO_AF_TIM2); // PB3: TIM2_CH2

    // ??? ENCODER B
    GPIO_InitStructure.GPIO_Pin = ENCODER_B_Pin1 | ENCODER_B_Pin2;
    GPIO_Init(ENCODER_B_GPIO_Port, &GPIO_InitStructure);
    GPIO_PinAFConfig(ENCODER_B_GPIO_Port, GPIO_PinSource4, GPIO_AF_TIM3); // PB4: TIM3_CH1
    GPIO_PinAFConfig(ENCODER_B_GPIO_Port, GPIO_PinSource5, GPIO_AF_TIM3); // PB5: TIM3_CH2

    // ??? ENCODER C
    GPIO_InitStructure.GPIO_Pin = ENCODER_C_Pin1 | ENCODER_C_Pin2;
    GPIO_Init(ENCODER_C_GPIO_Port, &GPIO_InitStructure);
    GPIO_PinAFConfig(ENCODER_C_GPIO_Port, GPIO_PinSource6, GPIO_AF_TIM4); // PB6: TIM4_CH1
    GPIO_PinAFConfig(ENCODER_C_GPIO_Port, GPIO_PinSource7, GPIO_AF_TIM4); // PB7: TIM4_CH2

    // ??? ENCODER D
    GPIO_InitStructure.GPIO_Pin = ENCODER_D_Pin1 | ENCODER_D_Pin2;
    GPIO_Init(ENCODER_D_GPIO_Port, &GPIO_InitStructure);
    GPIO_PinAFConfig(ENCODER_D_GPIO_Port, GPIO_PinSource0, GPIO_AF_TIM5); // PA0: TIM5_CH1
    GPIO_PinAFConfig(ENCODER_D_GPIO_Port, GPIO_PinSource1, GPIO_AF_TIM5); // PA1: TIM5_CH2

    // ???????????
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0xF;  // ?????????

    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICInit(TIM4, &TIM_ICInitStructure);

    TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICInit(TIM5, &TIM_ICInitStructure);

    // ?????
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
    TIM_Cmd(TIM5, ENABLE);
}

int32_t Encoder_GetValue(char encoder) {
    int16_t encoder_value = 0;

    switch (encoder) {
        case 'A':
            encoder_value = TIM_GetCounter(TIM2);
				
						TIM_SetCounter(TIM2, 0);
            break;
        case 'B':
            encoder_value = TIM_GetCounter(TIM3);
						TIM_SetCounter(TIM3, 0);
            break;
        case 'C':
            encoder_value = -TIM_GetCounter(TIM4);
						TIM_SetCounter(TIM4, 0);
            break;
        case 'D':
            encoder_value = -TIM_GetCounter(TIM5);
						TIM_SetCounter(TIM5, 0);
            break;
        default:
            encoder_value = 40000;
            break;
    }

    return encoder_value;
}
