/*
 * button.h
 *
 *  Created on: 2023. 9. 7.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_INCLUDE_BUTTON_H_
#define SRC_COMMON_INCLUDE_BUTTON_H_

#include "hw_def.h"

#ifdef _USE_HW_BUTTON

#define BUTTON_MAX_CH         HW_BUTTON_MAX_CH

void buttonInit(void);
bool buttonGetPressed(uint8_t ch);


#endif //_USE_HW_BUTTON


#endif /* SRC_COMMON_INCLUDE_BUTTON_H_ */
