/*
 * timer.c
 *
 *  Created on: 2023. 9. 11.
 *      Author: kjkim
 */


#include "timer.h"

#define HWTIMER_MAX_CH          1         //여기서 사용하는 하드웨어 타이머는 TIM3 1개임

#define HWTIMER_TIMER1          0
#define HWTIMER_TIMER2          1
#define HWTIMER_TIMER3          2
#define HWTIMER_TIMER4          3

#define HWTIMER_CH1             0
#define HWTIMER_CH2             1
#define HWTIMER_CH3             2
#define HWTIMER_CH4             3


/*
 *  @ 타이머 관리에 필요한 변수 구조체로 선언
 */
typedef struct
{
  TIM_HandleTypeDef           hTIM;           //Timer Handler Configuration Struct Var
  TIM_OC_InitTypeDef          sConfig[4];     //Output Compare Configuration Struct var
                                              //Capture/compare channels : 4ea
  uint32_t freq;                              //max timer clock / prescaler 값
  void (*p_func[4])(void);                    //인터럽트 발생 주기로 실행할 함수의 포인터

}hwtimer_t;


typedef struct
{
  uint8_t number;                             //timer 번호(여기서는 1개만 사용, HWTIMER_TIMER1 => TIM3임)
  uint8_t index;                              //timer의 Capture/compare channels 번호 인덱스
  uint32_t active_channel;                    //timer 동작할 채널(HAL에서 제공하는 채널 번호 저장변수)
}hwtimer_index_t;

static hwtimer_index_t            hwtimer_index[TIMER_MAX_CH] =
    {
        {HWTIMER_TIMER1, HWTIMER_CH1, HAL_TIM_ACTIVE_CHANNEL_1},  //_DEF_TIMEWR1
        {HWTIMER_TIMER1, HWTIMER_CH2, HAL_TIM_ACTIVE_CHANNEL_2},  //_DEF_TIMEWR2
        {HWTIMER_TIMER1, HWTIMER_CH3, HAL_TIM_ACTIVE_CHANNEL_3},  //_DEF_TIMEWR3
        {HWTIMER_TIMER1, HWTIMER_CH4, HAL_TIM_ACTIVE_CHANNEL_4}   //_DEF_TIMEWR4
    };

static hwtimer_t          timer_tbl[HWTIMER_MAX_CH];

void timerInit(void)
{
  timer_tbl[HWTIMER_TIMER1].freq                        = 1000000;      //인터럽트 발샐시키고자 하는 최소 단위 주파수 => 1MHz ==> 1us
                                                                        //Period와 곱하면 최종 인터럽트 발생주기(주파수)가 됨
  timer_tbl[HWTIMER_TIMER1].hTIM.Instance               = TIM3;         //TIM3 사용 설정
  /*
   * 타이머 최대 클럭을 주파수로 나누면 프리스케일러 값이 됨. 수식 아래 참고
   *  TIM3 Timer Max Clock : 84Mhz (System Clock / 2)
   *  (TIM3 Timer Max Clock / Prescaler)
   *
   *  84,000,000Hz / 4000Hz = 21,000
   */
  timer_tbl[HWTIMER_TIMER1].hTIM.Init.Prescaler         = ((uint32_t)(SystemCoreClock / 2) / timer_tbl[HWTIMER_TIMER1].freq) - 1;
  timer_tbl[HWTIMER_TIMER1].hTIM.Init.ClockDivision     = 0;
  timer_tbl[HWTIMER_TIMER1].hTIM.Init.CounterMode       = TIM_COUNTERMODE_UP;
  timer_tbl[HWTIMER_TIMER1].hTIM.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  timer_tbl[HWTIMER_TIMER1].hTIM.Init.RepetitionCounter = 0;

  timer_tbl[HWTIMER_TIMER1].p_func[0]                   = NULL;
  timer_tbl[HWTIMER_TIMER1].p_func[1]                   = NULL;
  timer_tbl[HWTIMER_TIMER1].p_func[2]                   = NULL;
  timer_tbl[HWTIMER_TIMER1].p_func[3]                   = NULL;
}

void timerStop(uint8_t ch)
{
  hwtimer_t         *p_timer;   //타이머 핸들러 구조체 포인터 변수 선언

  if(ch > TIMER_MAX_CH)     return;

  p_timer = &timer_tbl[hwtimer_index[ch].number];   //해당 채널의 구조체 변수 주소값 포인터 변수에 저장

  HAL_TIM_Base_DeInit(&p_timer->hTIM);               //해당 채널의 핸들러를 De Init 한다.
}

/*
 *  @ 하드웨어 타이머가 가지고 있는 출력 비교 채널중 사용자가 설정하고자 하는 채널이
 *  인터럽트를 발생할 주기를 설정하는 함수임
 */
void timerSetPeriod(uint8_t ch, uint32_t us)
{
  hwtimer_t         *p_timer;   //타이머 핸들러 구조체 포인터 변수 선언

  uint32_t period;
  uint32_t time_div;

  if(ch > TIMER_MAX_CH)        return;

  p_timer = &timer_tbl[hwtimer_index[ch].number];   //해당 채널의 구조체 변수 주소값 포인터 변수에 저장

  time_div = 1000000 / p_timer->freq;     //1000000 / 4000 = 250

  period = us / time_div;   // ex) 만약 us 가 1000*1000 이라면 period는 1000000 / 250 = 4000 이다.

  if(period == 0)
  {
    period = 1;
  }

  //최종 타이머 인터럽트 발생 주기는 Timer Max Clock / Prescaler 을 시간으로 환산한 다음
  //아래 Period 값을 곱해준다.
  //Timer Max Clock / Prescaler 은 4000 이고 시간으로 환산하면 0.00025 sec 이다.
  //0.00025 sec 를 period 4000 곱하면 1 sec가 되어
  //1초 주기로 타이머 인터럽트가 발생하도록 설정되게 된다.
  p_timer->hTIM.Init.Period = period - 1;
}

/*
 *  @ 하드웨어 타이머가 가지고 있는 출력 비교 채널중 사용자가 설정하고자 하는 채널이
 *  인터럽트 발생 시 실행될 함수를 등록하는 함수임
 */
void timerAttachInterrupt(uint8_t ch, void (*func)(void))
{
  hwtimer_t         *p_timer;

  if(ch > TIMER_MAX_CH)         return;

  p_timer = &timer_tbl[hwtimer_index[ch].number];

  //타이머 인터럽트 시 동작할 함수 등록전에 해당 인터럽트 핸들러를 De Init 한다.
  timerStop(ch);
  //등록할 함수를 함수포인터에 저장한다.
  p_timer->p_func[hwtimer_index[ch].index] = func;
}

/*
 *  @ 하드웨어 타이머가 가지고 있는 출력 비교 채널중 사용자가 설정하고자 하는 채널이
 *  인터럽트 발생 시 실행될 함수를 등록해제 하는 함수임
 */
void timerDetachInterrupt(uint8_t ch)
{
  hwtimer_t         *p_timer;

  if(ch > TIMER_MAX_CH)         return;

  p_timer = &timer_tbl[hwtimer_index[ch].number];

  //타이머 인터럽트 시 동작할 함수 등록전에 해당 인터럽트 핸들러를 De Init 한다.
  timerStop(ch);
  //구조파 함수 포인터 변수를 null 처리한다.
  p_timer->p_func[hwtimer_index[ch].index] = NULL;
}

void timerStart(uint8_t ch)
{
  //함수내에서 구조체 변수에 접근하기 위해 구조체 포인터 변수 선언한다.
  hwtimer_t         *p_timer;
  uint32_t timer_sub_ch = 0;

  if(ch > TIMER_MAX_CH)         return;

  p_timer = &timer_tbl[hwtimer_index[ch].number];

  switch(hwtimer_index[ch].index)
  {
    case HWTIMER_CH1:
      timer_sub_ch = TIM_CHANNEL_1;
      break;

    case HWTIMER_CH2:
      timer_sub_ch = TIM_CHANNEL_2;
     break;

    case HWTIMER_CH3:
      timer_sub_ch = TIM_CHANNEL_3;
     break;

    case HWTIMER_CH4:
      timer_sub_ch = TIM_CHANNEL_4;
     break;
  }
  //TIM3의 Output Compare 기능을 사용하므로 해당 초기화 함수를 이용하여 초기화 한다.
  HAL_TIM_OC_Init(&p_timer->hTIM);
  //TIM3 Output Compare 파라미터를 설정한다.
  HAL_TIM_OC_ConfigChannel(&p_timer->hTIM, &p_timer->sConfig[hwtimer_index[ch].index], timer_sub_ch);
  //TIM3 Output Compare 인터럽트 동작을 시작한다.
  HAL_TIM_OC_Start_IT(&p_timer->hTIM, timer_sub_ch);
}

void timerCallBack(TIM_HandleTypeDef *htim)
{
  uint8_t i;
  uint32_t index;
  hwtimer_t         *p_timer;

  for(i=0;i<TIMER_MAX_CH;i++)
  {
    p_timer = &timer_tbl[hwtimer_index[i].number];
    index   = hwtimer_index[i].index;

    //사용할 Output Compare 채널이 맞다면
    if(htim->Channel == hwtimer_index[i].active_channel)
    {
      //등록된 함수가 존재한다면
      if(p_timer->p_func[index] != NULL)
      {
        //등록된 함수를 불려온다.
        (*p_timer->p_func[index])();
      }
    }
  }
}


void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timer_tbl[HWTIMER_CH1].hTIM);
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  timerCallBack(htim);
  swtimerISR();
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == timer_tbl[HWTIMER_CH1].hTIM.Instance)
  {
    __HAL_RCC_TIM3_CLK_ENABLE();

    HAL_NVIC_SetPriority(TIM3_IRQn, 15, 1);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == timer_tbl[HWTIMER_CH1].hTIM.Instance)
  {
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  }
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == timer_tbl[HWTIMER_CH1].hTIM.Instance)
  {
    //TIM3 클릭을 활성화 한다.
    __HAL_RCC_TIM3_CLK_ENABLE();

    //인터럽트 우선순위를 설정하고, 활성화 한다.
    HAL_NVIC_SetPriority(TIM3_IRQn, 15, 1);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  }
}

void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == timer_tbl[HWTIMER_CH1].hTIM.Instance)
  {
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  }
}

