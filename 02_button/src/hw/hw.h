/*
 * hw.h
 *
 *  Created on: 2023. 9. 5.
 *      Author: kjkim
 */

#ifndef SRC_HW_HW_H_
#define SRC_HW_HW_H_

#include "hw_def.h"
#include "led.h"
#include "button.h"

void hwInit(void);
void ledInit(void);
void buttonInit(void);

#endif /* SRC_HW_HW_H_ */
