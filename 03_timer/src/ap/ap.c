/*
 * ap.c
 *
 *  Created on: 2023. 9. 5.
 *      Author: kjkim
 */


#include "ap.h"

void timerISR_1(void)
{
  ledToggle(_DEF_LED1);     //toggle LED1
}

void timerISR_2(void)
{
  ledToggle(_DEF_LED2);     //toggle LED2
}

void timerISR_3(void)
{
  ledToggle(_DEF_LED3);     //toggle LED3
}

void timerISR_4(void)
{
  ledToggle(_DEF_LED4);     //toggle LED4
}

void apInit(void)
{
  //인터럽트 발생 주기가 1000ms 되도록 아래와 같이 설정한다.
  //set timer 1000ms(1000us * 1000)
  timerSetPeriod(_DEF_TIMER1, 250*1000);
  timerSetPeriod(_DEF_TIMER2, 500*1000);
  timerSetPeriod(_DEF_TIMER3, 750*1000);
  timerSetPeriod(_DEF_TIMER4, 1000*1000);

  timerAttachInterrupt(_DEF_TIMER1, timerISR_1);  //인터럽트 발생시 동작할 함수 등록
  timerAttachInterrupt(_DEF_TIMER2, timerISR_2);  //인터럽트 발생시 동작할 함수 등록
  timerAttachInterrupt(_DEF_TIMER3, timerISR_3);  //인터럽트 발생시 동작할 함수 등록
  timerAttachInterrupt(_DEF_TIMER4, timerISR_4);  //인터럽트 발생시 동작할 함수 등록

  timerStart(_DEF_TIMER1);                      //start timer...
  timerStart(_DEF_TIMER2);                      //start timer...
  timerStart(_DEF_TIMER3);                      //start timer...
  timerStart(_DEF_TIMER4);                      //start timer...
}

void apMain(void)
{
  uint32_t pre_time;

  pre_time = millis();
  while(1)
  {
    if(millis() - pre_time >= 500)
    {
      pre_time = millis();

      //ledToggle(_DEF_LED1);
    }
  }
}
