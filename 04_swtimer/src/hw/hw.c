/*
 * hw.c
 *
 *  Created on: 2023. 9. 5.
 *      Author: kjkim
 */


#include "hw.h"




void hwInit(void)
{
  bspInit();
  ledInit();
  buttonInit();
  timerInit();
  swtimerInit();
}
