/*
 * led.c
 *
 *  Created on: 2023. 9. 7.
 *      Author: kjkim
 */


#include "led.h"

void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);

static GPIO_InitTypeDef  GPIO_InitStruct;

typedef struct
{
  GPIO_TypeDef          *port;
  uint16_t              pin;
  GPIO_PinState         on_state;
  GPIO_PinState         off_state;
}led_tbl_t;


led_tbl_t         led_tbl[HW_LED_CH] =
    {
        {GPIOE, GPIO_PIN_2, GPIO_PIN_RESET, GPIO_PIN_SET},
        {GPIOE, GPIO_PIN_3, GPIO_PIN_RESET, GPIO_PIN_SET},
        {GPIOE, GPIO_PIN_4, GPIO_PIN_RESET, GPIO_PIN_SET},
        {GPIOE, GPIO_PIN_5, GPIO_PIN_RESET, GPIO_PIN_SET},
        {GPIOB, GPIO_PIN_9, GPIO_PIN_SET  , GPIO_PIN_RESET}
    };

void ledInit(void)
{
  uint8_t i = 0;

  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

  for(i=0;i<MAX_HW_LED_CH;i++)
  {
    GPIO_InitStruct.Pin = led_tbl[i].pin;
    HAL_GPIO_Init(led_tbl[i].port, &GPIO_InitStruct);

    ledOff(i);
  }


}

void ledOn(uint8_t ch)
{
  if(ch > MAX_HW_LED_CH)    return;

  HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].on_state);
}

void ledOff(uint8_t ch)
{
  if(ch > MAX_HW_LED_CH)    return;

  HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pin, led_tbl[ch].off_state);
}

void ledToggle(uint8_t ch)
{
  if(ch > MAX_HW_LED_CH)    return;

  HAL_GPIO_TogglePin(led_tbl[ch].port, led_tbl[ch].pin);
}
