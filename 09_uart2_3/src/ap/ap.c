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
  uartOpen(_DEF_UART2, 115200);

  uartPrintf(_DEF_UART1, "UART 1(USART) OPEN \r\n");
  uartPrintf(_DEF_UART2, "UART 2(USB)   OPEN \r\n");
}

void apMain(void)
{
  uint32_t pre_time;
  uint32_t pre_baud;  //baudrate값 저장변수

  pre_time = millis();

  //usb cdc의 baudrate값을 저장한다.
  pre_baud = uartGetBaud(_DEF_UART2);

  uint8_t rx_data;

  while(1)
  {
    //최초의 usb baudrate와 현재 usb baudrate가 다르다면
    if(pre_baud != uartGetBaud(_DEF_UART2))
    {
      //현재 설정한 baudrate값을 다시 저장하고,
      pre_baud = uartGetBaud(_DEF_UART2);
      //변경된 baudrate값을 출력한다.
      uartPrintf(_DEF_UART2, "USB BaudRate Changed To %d \r\n", uartGetBaud(_DEF_UART2));
    }

    if(millis() - pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }

    //usb cdc로 입력되는 데이터가 있다면
    if(uartAvailable(_DEF_UART2) > 0)
    {
      //usb로 수신된 데이터를 변수에 저장
      rx_data = uartRead(_DEF_UART2);

      uartPrintf(_DEF_UART2, "rx_data : 0x%X [%c] \r\n", rx_data, rx_data);
    }
  }
}