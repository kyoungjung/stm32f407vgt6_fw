/*
 * swtimer.h
 *
 *  Created on: 2023. 9. 18.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_INCLUDE_SWTIMER_H_
#define SRC_COMMON_INCLUDE_SWTIMER_H_

#include "hw_def.h"


#ifdef _USE_SW_TIMER

#define SW_TIMER_MAX          HW_SW_TIMER_MAX

#define ON                    1
#define OFF                   0


#define ONE_TIME              1
#define LOOP_TIME             2

typedef int16_t               swtimer_handle_t;


bool swtimerInit(void);
void swtimerSet(uint8_t TmrNum, uint32_t TmrData, uint8_t TmrMode, void (*Func)(void*), void *arg);
void swtimerStart(uint8_t TmrNum);
void swtimerStop(uint8_t TmrNum);
void swtimerReset(uint8_t TmrNum);
void swtimerISR(void);

int16_t swtimerGetHandle(void);
uint32_t swtimerGetCounter(void);

#endif //USE_SW_TIMER

#endif /* SRC_COMMON_INCLUDE_SWTIMER_H_ */
