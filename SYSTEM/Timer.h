#ifndef _Timer_H_
#define _Timer_H_

#include "stm32f4xx.h"

void TIM6_Int_Init(uint16_t arr, uint16_t psc);
void TIM7_Int_Init(uint16_t arr, uint16_t psc);
#include <stdint.h>

uint32_t millis(void);
void timer_init(void);


#endif


