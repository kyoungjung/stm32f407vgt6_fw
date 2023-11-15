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

extern uint32_t cdcAvailable(void);
extern uint8_t cdcRead(void);
extern void cdcDataIn(uint8_t rx_data);
extern uint32_t cdcWrite(uint8_t *p_data, uint32_t length);


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
  pre_time = millis();

  uint8_t rx_data;

  while(1)
  {
    if(millis() - pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

    //usb cdc로 입력되는 데이터가 있다면
    if(cdcAvailable() > 0)
    {
      //usb로 수신된 데이터를 변수에 저장
      rx_data = cdcRead();
      //수신된 변수를 usb로 1바이트씩 write한다.
      cdcWrite(&rx_data, 1);
    }
  }
}
