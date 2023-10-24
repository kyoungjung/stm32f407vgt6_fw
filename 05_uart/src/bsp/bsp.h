/*
 * bsp.h
 *
 *  Created on: 2023. 9. 5.
 *      Author: kjkim
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "def.h"
#include "stm32f4xx_hal.h"

void bspInit(void);

void delay(uint32_t ms);
uint32_t millis(void);


#endif /* SRC_BSP_BSP_H_ */
