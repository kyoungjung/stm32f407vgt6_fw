/*
 * swtimer.c
 *
 *  Created on: 2023. 9. 18.
 *      Author: kjkim
 */


#include "swtimer.h"



/**
 * @ swtimer 관련 변수들 구조체로 선언
 */
typedef struct
{
  uint8_t Timer_En;                   //타이머 인에이블
  uint8_t Timer_Mode;                 //타이머 모드
  uint32_t Timer_Cnt;                 //현재의 타이머 값
  uint32_t Timer_Init;                //타이머 초기하 될 때 타이머 값
  void (*TmrFunt)(void *);            //타이머 만료시 동작할 함수
  void *TmrFuntArg;                   //함수로 전달할 인자
}swtimer_t;


static volatile uint32_t sw_timer_counter         = 0;
static volatile uint16_t sw_timer_handle_index    = 0;
static swtimer_t    swtimer_tbl[SW_TIMER_MAX];            //타이머 배열 선언

bool swtimerInit(void)
{
  uint8_t i;
  static uint8_t excute = 0;

  if(excute == 1)
  {
    return false;           //이미 한번 실행했다면 정지
  }

  //구조체 초기화
  for(i=0;i<SW_TIMER_MAX;i++)
  {
    swtimer_tbl[i].Timer_Cnt      = 0;          //현재 타이머값 0으로 초기화
    swtimer_tbl[i].Timer_En       = OFF;        //타이머는 초기에 비활성화
    swtimer_tbl[i].Timer_Init     = 0;          //타이머 초기화될때 타이머값 변수 초기화
    swtimer_tbl[i].TmrFunt        = NULL;       //타이머 만료시 실행할 함수는 Null로 초기화
  }

  //한번 실행됬으므로 변수 1로 설정
  excute = 1;

  return true;
}

/*
 * @ 타이머 인터럽트 발생시 ㅅ실행되는 인럽텁트 서비스 루틴
 */
void swtimerISR(void)
{
  uint8_t i;

  //설정된 주기마다 이 함수가 실행되므로 카운터 변수가 설정된 주기마다 1씩 증가한다.
  //여기서는 주기가 1ms이므로 1ms 주기로 카운터 변수가 1씩 증가한다.
  sw_timer_counter++;

  for(i=0;i<SW_TIMER_MAX && i<sw_timer_handle_index; i++)
  {
    if(swtimer_tbl[i].Timer_En == ON)                             //해당 타이머가 활성화 됬는지??
    {
      swtimer_tbl[i].Timer_Cnt--;                                 //타이머 1씩 감소

      if(swtimer_tbl[i].Timer_Cnt == 0)                           //해당 활성화된 타이머가 계속감소하여 0이 됬다면
      {
        if(swtimer_tbl[i].Timer_Mode == ONE_TIME)                 //타이머를 한번만 실행하는 모드라면
        {
          swtimer_tbl[i].Timer_En = OFF;                          //타이머를 비활성화 시킨다.
        }

        swtimer_tbl[i].Timer_Cnt = swtimer_tbl[i].Timer_Init;     //현재 타이머 값을 초기화 한다.

        (*swtimer_tbl[i].TmrFunt)(swtimer_tbl[i].TmrFuntArg);     //함수를 실행한다.
      }
    }
  }
}

/*
 * @ 타이머 번호별로 모드, 실행할 함수설정
 * */
void swtimerSet(uint8_t TmrNum, uint32_t TmrData, uint8_t TmrMode, void (*Func)(void*), void *arg)
{
  swtimer_tbl[TmrNum].Timer_Mode    = TmrMode;      //해당 타이머 번호의 동작 모드
  swtimer_tbl[TmrNum].TmrFunt       = Func;          //해당 타이머 번호 타이머 만료 시 실행할 함수
  swtimer_tbl[TmrNum].TmrFuntArg    = arg;          //해당 타이머 번호 타이머 만료 시 실행할 함수의 입력 매개변수
  swtimer_tbl[TmrNum].Timer_Cnt     = TmrData;      //해당 타이머의 현재 카운터 값
  swtimer_tbl[TmrNum].Timer_Init    = TmrData;      //해당 타이머의 초기화 시 카운터 값
}


void swtimerStart(uint8_t TmrNum)
{
  if(TmrNum  < SW_TIMER_MAX)
  {
    swtimer_tbl[TmrNum].Timer_Cnt = swtimer_tbl[TmrNum].Timer_Init;     //타이머 시작전에 카운터 변수 초기화
    swtimer_tbl[TmrNum].Timer_En = ON;                                  //해당 타이머 번호가 시작됨을 알리는 변수 ON 설정
  }
}

void swtimerStop(uint8_t TmrNum)
{
  if(TmrNum  < SW_TIMER_MAX)
  {
    swtimer_tbl[TmrNum].Timer_En = OFF;                                 //해당 타이머 번호가 정지됬음을 알리는 변수 OFF 설정
  }
}

void swtimerReset(uint8_t TmrNum)
{
  swtimer_tbl[TmrNum].Timer_Cnt = swtimer_tbl[TmrNum].Timer_Init;     //해당 타미머 카운터 변수 초기화
  swtimer_tbl[TmrNum].Timer_En  = OFF;                                //해당 타이머 비활성화
}

swtimer_handle_t swtimerGetHandle(void)
{
  swtimer_handle_t  TmrIndex = sw_timer_handle_index;

  sw_timer_handle_index++;

  return TmrIndex;
}

uint32_t swtimerGetCounter(void)
{
  return sw_timer_counter;
}
