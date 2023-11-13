/*
 * timer.h
 *
 *  Created on: 2023. 9. 11.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_INCLUDE_TIMER_H_
#define SRC_COMMON_INCLUDE_TIMER_H_

#include "hw_def.h"

#ifdef _USE_HW_TIMER
#define TIMER_MAX_CH          4       //해당 타이머가 보유하고 있는 capture/compare 채널갯수


void timerInit(void);
void timerStart(uint8_t ch);
void timerStop(uint8_t ch);
void timerSetPeriod(uint8_t ch, uint32_t us);
void timerAttachInterrupt(uint8_t ch, void (*func)(void));
void timerDetachInterrupt(uint8_t ch);


#endif //_USE_HW_TIMER

#endif /* SRC_COMMON_INCLUDE_TIMER_H_ */
