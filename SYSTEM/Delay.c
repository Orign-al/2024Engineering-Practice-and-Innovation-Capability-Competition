#include "include.h"

static uint32_t fac_us = 0;
static uint32_t fac_ms = 0;

void delay_init(uint8_t SYSCLK)
{
    if (SYSCLK == 0) return;  // ????

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SYSCLK / 8;
    fac_ms = fac_us * 1000;
}

void delay_us(uint32_t nus)
{
    uint32_t temp;
    SysTick->LOAD = (uint32_t)(nus * fac_us);
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp = SysTick->CTRL;
    }
    while ((temp & SysTick_CTRL_ENABLE_Msk) && !(temp & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}

void delay_ms(uint32_t nms)
{
    uint32_t repeat = nms / 500;
    uint32_t remain = nms % 500;

    while (repeat)
    {
        delay_us(500 * 1000);
        repeat--;
    }

    if (remain)
    {
        delay_us(remain * 1000);
    }
}