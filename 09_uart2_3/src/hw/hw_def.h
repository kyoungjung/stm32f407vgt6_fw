/*
 * hw_def.h
 *
 *  Created on: 2023. 9. 5.
 *      Author: kjkim
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"
#include "bsp.h"

#define _USE_HW_LED
#define      MAX_HW_LED_CH          5

#define _USE_HW_BUTTON
#define      HW_BUTTON_MAX_CH       3

#define _USE_HW_TIMER
#define      HW_TIMER_MAX_CH        4

#define _USE_SW_TIMER
#define      HW_SW_TIMER_MAX        8

#define _USE_HW_UART
#define     HW_UART_MAX_CH          4

#endif /* SRC_HW_HW_DEF_H_ */
