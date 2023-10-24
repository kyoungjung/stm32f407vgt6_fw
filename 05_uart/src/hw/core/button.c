/*
 * button.c
 *
 *  Created on: 2023. 9. 7.
 *      Author: kjkim
 */


#include "button.h"


static GPIO_InitTypeDef  GPIO_InitStruct;

typedef struct
{
  GPIO_TypeDef          *port;
  uint16_t              pin;
  GPIO_PinState         on_state;
  GPIO_PinState         off_state;
}button_tbl_t;

button_tbl_t          button_tbl[HW_BUTTON_MAX_CH] =
    {
        {GPIOC, GPIO_PIN_13, GPIO_PIN_RESET, GPIO_PIN_SET},
        {GPIOC, GPIO_PIN_0, GPIO_PIN_RESET, GPIO_PIN_SET},
        {GPIOC, GPIO_PIN_1, GPIO_PIN_RESET, GPIO_PIN_SET}
    };

void buttonInit(void)
{
  uint8_t i = 0;
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

  for(i=0; i<HW_BUTTON_MAX_CH; i++)
  {
    GPIO_InitStruct.Pin = button_tbl[i].pin;
    HAL_GPIO_Init(button_tbl[HW_BUTTON_MAX_CH].port, &GPIO_InitStruct);
  }
}


/*
 * @ output
 *  - true  : button pressed
 *  - false : button release
 */
bool buttonGetPressed(uint8_t ch)
{
  bool ret = false;

  if(ch > HW_BUTTON_MAX_CH)     return false;

  if(HAL_GPIO_ReadPin(button_tbl[ch].port, button_tbl[ch].pin) == button_tbl[ch].on_state)
  {
    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}
