#include "include.h"

// 定时器6中断初始化
void TIM6_Int_Init(uint16_t arr, uint16_t psc) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); // 使能TIM6时钟

    // 初始化定时器TIM6
    TIM_TimeBaseStructure.TIM_Period = arr; // 自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler = psc; // 预分频器值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); // 使能TIM6更新中断
    TIM_Cmd(TIM6, ENABLE); // 使能TIM6

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

// 定时器7中断初始化
void TIM7_Int_Init(uint16_t arr, uint16_t psc) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); // 使能TIM7时钟

    // 初始化定时器TIM7
    TIM_TimeBaseStructure.TIM_Period = arr; // 自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler = psc; // 预分频器值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); // 使能TIM7更新中断
    TIM_Cmd(TIM7, ENABLE); // 使能TIM7

    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//// TIM6中断服务程序
//void TIM6_DAC_IRQHandler(void) {
//    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
//        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
//        // 用户代码
//    }
//}

//// TIM7中断服务程序
//void TIM7_IRQHandler(void) {
//    if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) {
//        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
//        // 用户代码
//    }
//}

volatile uint32_t msTicks = 0;


uint32_t millis(void)
{
    return msTicks;
}

void timer_init(void)
{
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);
}

