/*
 * ap.c
 *
 *  Created on: 2023. 9. 5.
 *      Author: kjkim
 */


#include "ap.h"

void ledISR(void *arg)
{
  ledToggle(_DEF_LED3);     //led3 토글한다
}

void apInit(void)
{
  swtimer_handle_t          h_led_timer;    //동작할 타이머 인덱스 변수

  //하드웨어 타이머 인터럽트 발생 주기가 1000us(1ms) 되도록 아래와 같이 설정한다.
  timerSetPeriod(_DEF_TIMER1, 1000);
  //timerAttachInterrupt(_DEF_TIMER1, func);
  timerStart(_DEF_TIMER1);                      //start timer...

  h_led_timer = swtimerGetHandle();             //타이머 인덱스값을 받아서 변수에 저장
  swtimerSet(h_led_timer, 500, LOOP_TIME, ledISR, NULL);  //500ms 주기로 ledISR함수가 동작하도록 swtimer 설정
  swtimerStart(h_led_timer);    //swtimer 시작

  uartOpen(_DEF_UART1, 115200);

  uartPrintf(_DEF_UART1, "UART 1 OPEN \r\n");
}

void apMain(void)
{
  uint32_t pre_time;

  uint8_t rx_data;

  pre_time = millis();
  while(1)
  {
    if(millis() - pre_time >= 500)
    {
      pre_time = millis();
      //ledToggle(_DEF_LED1);
      //uartPrintf(_DEF_UART1, uartRead(_DEF_UART1));
    }

    if(uartAvailable(_DEF_UART1) > 0)
    {
      rx_data = uartRead(_DEF_UART1);
      uartPrintf(_DEF_UART1, "rx data : %c %X\r\n", rx_data, rx_data);
    }

  }
}
