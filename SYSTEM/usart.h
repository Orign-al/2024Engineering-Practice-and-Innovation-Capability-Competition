#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"

void USART4_Init(uint32_t baudrate) ;
void UART_Transmit(uint8_t *pData, uint16_t Size);
void UART_Receive(uint8_t *pData, uint16_t Size);


void USART2_IO_Conf(void);
void USART2_Conf(uint32_t baud);
void Usart_SendString(USART_TypeDef* USARTx,uint8_t *data,uint32_t dataLen);


void USART5_Init(void) ;


#endif /* __UART_H */
