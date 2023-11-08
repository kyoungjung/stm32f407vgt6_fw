/*
 * uart.h
 *
 *  Created on: 2023. 10. 16.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_INCLUDE_UART_H_
#define SRC_COMMON_INCLUDE_UART_H_

#include "hw_def.h"

#ifdef _USE_HW_UART

#define UART_MAX_CH         HW_UART_MAX_CH

void uartInit(void);
bool uartOpen(uint8_t ch, uint32_t baud);
bool uartClose(uint8_t ch);
uint32_t uartAvailable(uint8_t ch);
void uartFlush(uint8_t ch);
void uartPutch(uint8_t ch, uint8_t c);
uint8_t uartGetch(uint8_t ch);
int32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length);
uint8_t uartRead(uint8_t ch);
int32_t uartPrintf(uint8_t ch, const char *fmt, ...);


#endif //_USE_HW_UART

#endif /* SRC_COMMON_INCLUDE_UART_H_ */
