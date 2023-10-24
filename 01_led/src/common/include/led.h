/*
 * led.h
 *
 *  Created on: 2023. 9. 7.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_INCLUDE_LED_H_
#define SRC_COMMON_INCLUDE_LED_H_

#include "hw_def.h"


#ifdef _USE_HW_LED

#define HW_LED_CH         MAX_HW_LED_CH

void ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);

#endif // _USE_HW_LED

#endif /* SRC_COMMON_INCLUDE_LED_H_ */
