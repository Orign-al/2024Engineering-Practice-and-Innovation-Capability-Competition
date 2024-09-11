#ifndef __OLED_H
#define __OLED_H

#include "stm32f4xx.h"

// ????
#define OLED_SCK_Pin    GPIO_Pin_14
#define OLED_SCK_GPIO_Port  GPIOD
#define OLED_MOSI_Pin   GPIO_Pin_13
#define OLED_MOSI_GPIO_Port GPIOD
#define OLED_RES_Pin    GPIO_Pin_12
#define OLED_RES_GPIO_Port  GPIOD
#define OLED_DC_Pin     GPIO_Pin_11
#define OLED_DC_GPIO_Port   GPIOD

// ?????
#define OLED_SCK_Clr()  GPIO_ResetBits(OLED_SCK_GPIO_Port, OLED_SCK_Pin)
#define OLED_SCK_Set()  GPIO_SetBits(OLED_SCK_GPIO_Port, OLED_SCK_Pin)
#define OLED_MOSI_Clr() GPIO_ResetBits(OLED_MOSI_GPIO_Port, OLED_MOSI_Pin)
#define OLED_MOSI_Set() GPIO_SetBits(OLED_MOSI_GPIO_Port, OLED_MOSI_Pin)
#define OLED_DC_Clr()   GPIO_ResetBits(OLED_DC_GPIO_Port, OLED_DC_Pin)
#define OLED_DC_Set()   GPIO_SetBits(OLED_DC_GPIO_Port, OLED_DC_Pin)
#define OLED_RES_Clr()  GPIO_ResetBits(OLED_RES_GPIO_Port, OLED_RES_Pin)
#define OLED_RES_Set()  GPIO_SetBits(OLED_RES_GPIO_Port, OLED_RES_Pin)

// ????
void SPI_SendByte(uint8_t byte);
void OLED_WriteCommand(uint8_t command);
void OLED_WriteData(uint8_t data);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x, uint8_t y, char chr);
void OLED_ShowString(uint8_t x, uint8_t y, char *chr);
void OLED_ShowNumber(uint8_t x, uint8_t y, int32_t num);
void OLED_ShowExample(void);
void OLED_ShowUTF8String(uint8_t x, uint8_t y, char *chr);

#endif // __OLED_H
