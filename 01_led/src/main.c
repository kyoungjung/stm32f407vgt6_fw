/*
 * main.c
 *
 *  Created on: 2023. 9. 5.
 *      Author: kjkim
 */


#include "main.h"




int main(void)
{
  int ret = 0;


  hwInit();
  apInit();

  apMain();


  return ret;
}
