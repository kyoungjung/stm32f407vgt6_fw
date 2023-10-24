/*
 * ap.c
 *
 *  Created on: 2023. 9. 5.
 *      Author: kjkim
 */


#include "ap.h"


void apInit(void)
{

}

void apMain(void)
{
  uint32_t pre_time;
  uint32_t cnt = 0;

  pre_time = millis();
  while(1)
  {
    if(millis() - pre_time >= 500)
    {
      pre_time = millis();

      ledToggle(_DEF_LED1);
    }

    if(buttonGetPressed(_DEF_BUTTON1) == _DEF_BUTTON_PRESSED)
    {
      ledOn(_DEF_LED2);
      if(cnt > 500)
      {
        cnt = 0;
        ledToggle(_DEF_LED5);
      }
      else
      {
        cnt++;
      }
    }
    else
    {
      ledOff(_DEF_LED2);
      ledOff(_DEF_LED5);
    }

    if(buttonGetPressed(_DEF_BUTTON2) == _DEF_BUTTON_PRESSED)
    {
      ledOn(_DEF_LED3);
    }
    else
    {
      ledOff(_DEF_LED3);
    }

    if(buttonGetPressed(_DEF_BUTTON3) == _DEF_BUTTON_PRESSED)
    {
      ledOn(_DEF_LED4);
    }
    else
    {
      ledOff(_DEF_LED4);
    }

  }
}
