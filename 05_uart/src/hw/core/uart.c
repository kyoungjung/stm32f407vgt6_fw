/*
 * uart.c
 *
 *  Created on: 2023. 10. 16.
 *      Author: kjkim
 */


#include "uart.h"
#include "qbuffer.h"

#define UART_MODE_POLLING                   0
#define UART_MODE_INTERRUPT                 1
#define UART_MODE_DMA                       2
#define UART_MODE_VCP                       4

#define UART_RX_BUF_LENGTH                  16
#define UART_RX_QBUF_LENGTH                 255

DMA_HandleTypeDef hdma_tx;
DMA_HandleTypeDef hdma_rx;


void Error_Handler(void);

/*
 * @ uart 사용하기 위해 관련 변수를 구조체로 정의
 * */
typedef struct
{
  bool      is_open;    //해당 채널 오픈유무 확인용 변수 정의
  uint32_t  baud;       //통신속도 변수 정의
  bool      vcp_mode;
  uint8_t   tx_mode;
  uint8_t   rx_mode;

  uint8_t   rx_buf[UART_RX_BUF_LENGTH]; //수신버퍼 정의

  qbuffer_t   qbuffer_rx;               //큐버퍼 구조체 변수

  DMA_HandleTypeDef         hdma;       //DMA를 다루기 위한 구조체 변수
  UART_HandleTypeDef        handle;     //UART를 다루기 위한 구조체 변수
}uart_t;


uart_t      uart_tbl[UART_MAX_CH];  //채널별 UART 핸들링위한 UART 구조체 변수 선언
uint8_t     uart_rx_qbuf[UART_RX_QBUF_LENGTH];   //uart채널별 큐버퍼 선언

void uartStartRx(uint8_t ch);         //uart 수신시작 설정 함수
void uartRxHandler(uint8_t ch);       //uart 수신 핸들러 함수

void uartInit(void)
{
  uint8_t i;
  for(i=0;i<UART_MAX_CH;i++)
  {
    uart_tbl[i].is_open   = false;
    uart_tbl[i].vcp_mode  = false;
    uart_tbl[i].rx_mode   = UART_MODE_POLLING;
    uart_tbl[i].tx_mode   = UART_MODE_POLLING;
  }

  __HAL_RCC_USART1_CLK_ENABLE();
}

bool uartOpen(uint8_t ch, uint32_t baud)
{
  bool ret = true;
  uart_t  *p_uart;        //uart 핸들용 구조체 포인터 변수 선언


  if(ch > UART_MAX_CH)    return false;

  switch(ch)
  {
    case _DEF_UART1:

      p_uart = &uart_tbl[ch];

      p_uart->baud = baud;
      p_uart->is_open = true;
      p_uart->vcp_mode  = false;
      p_uart->rx_mode   = UART_MODE_DMA;
      p_uart->tx_mode   = UART_MODE_DMA;

      p_uart->handle.Instance           = USART1;
      p_uart->handle.Init.BaudRate      = baud;
      p_uart->handle.Init.WordLength    = UART_WORDLENGTH_8B;
      p_uart->handle.Init.StopBits      = UART_STOPBITS_1;
      p_uart->handle.Init.Parity        = UART_PARITY_NONE;
      p_uart->handle.Init.Mode          = UART_MODE_TX_RX;
      p_uart->handle.Init.HwFlowCtl     = UART_HWCONTROL_NONE;
      p_uart->handle.Init.OverSampling  = UART_OVERSAMPLING_16;

      qbufferCreate(&p_uart->qbuffer_rx, &uart_rx_qbuf[0], UART_RX_QBUF_LENGTH);    //큐 버퍼 생성

      if(HAL_UART_Init(&p_uart->handle) != HAL_OK)                                          //uart 초기화
      {
        ret = false;
      }
      else
      {
        uartStartRx(ch);
      }

      break;
  }



  return ret;
}

/**
 * @uart 수신시작 설정 함수
 */
void uartStartRx(uint8_t ch)
{
  uart_t        *p_uart;

  p_uart = &uart_tbl[ch];

  switch(ch)
  {
    case _DEF_UART1:
      if(p_uart->rx_mode == UART_MODE_INTERRUPT)
      {
        HAL_UART_Receive_IT(&p_uart->handle, p_uart->rx_buf, 1);
      }

      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        if(HAL_UART_Receive_DMA(&p_uart->handle, (uint8_t*)&uart_rx_qbuf[0], 255) != HAL_OK)
        {
          return;
        }
        p_uart->qbuffer_rx.ptr_in = p_uart->qbuffer_rx.length - p_uart->hdma.Instance->NDTR;
        p_uart->qbuffer_rx.ptr_out = p_uart->qbuffer_rx.ptr_in;
      }
      break;
  }
}

bool uartClose(uint8_t ch)
{
  bool ret = false;

  if(ch > UART_MAX_CH) return false;

  if(uart_tbl[ch].is_open == true)
  {
    if(HAL_UART_DeInit(&uart_tbl[ch].handle) == HAL_OK)
    {
      ret = true;
    }
  }

  return ret;
}

uint32_t uartAvailable(uint8_t ch)
{
  uint32_t ret;

  uart_t    *p_uart;

  p_uart = &uart_tbl[ch];

  if(p_uart->rx_mode == UART_MODE_DMA)
  {
    //
    p_uart->qbuffer_rx.ptr_in = p_uart->qbuffer_rx.length - p_uart->hdma.Instance->NDTR;
    ret = qbufferAvailable(&p_uart->qbuffer_rx);
  }

  if(p_uart->rx_mode == UART_MODE_INTERRUPT)
  {
    ret = qbufferAvailable(&p_uart->qbuffer_rx);
  }

  return ret;
}

void uartFlush(uint8_t ch)
{
  uart_t    *p_uart;

  p_uart = &uart_tbl[ch];

  if(p_uart->rx_mode == UART_MODE_DMA)
  {
    p_uart->qbuffer_rx.ptr_in = p_uart->qbuffer_rx.length - p_uart->hdma.Instance->NDTR;
    p_uart->qbuffer_rx.ptr_out = p_uart->qbuffer_rx.ptr_in;
  }
}

void uartPutch(uint8_t ch, uint8_t c)
{
  uartWrite(ch, &ch, 1);
}

uint8_t uartGetch(uint8_t ch)
{
  uint8_t ret = 0;

  if(ch >= HW_UART_MAX_CH)   return 0;

  if(uartAvailable(ch) > 0)
  {
    ret = uartRead(ch);
  }

  return ret;
}

int32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  int32_t ret = 0;

  uart_t    *p_uart;
  p_uart = &uart_tbl[ch];

  switch(ch)
  {
    case _DEF_UART1:
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        if(HAL_UART_Transmit(&p_uart->handle, p_data, length, 100) == HAL_OK)
        {
          ret = length;
        }
      }
      break;
  }

  return ret;
}
uint8_t uartRead(uint8_t ch)
{
  uint8_t ret = 0;

  uart_t  *p_uart;
  p_uart = &uart_tbl[ch];

  switch(ch)
  {
    case _DEF_UART1:

      qbufferRead(&p_uart->qbuffer_rx, &ret, 1);

      break;
  }

  return ret;
}

int32_t uartPrintf(uint8_t ch, const char *fmt, ...)
{
  int32_t ret = 0;
  va_list   arg;
  va_start(arg, fmt);
  int32_t len;

  char print_buffer[256];

  len = vsnprintf(print_buffer, 255, fmt, arg);

  ret = uartWrite(ch, (uint8_t*)print_buffer, len);

  va_end(arg);

  return ret;
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct;


  /* Enable GPIO clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();



  /*##-2- Configure peripheral GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = GPIO_PIN_9;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*##-3- Configure the DMA streams ##########################################*/
  /* Configure the DMA handler for Transmission process */
  hdma_rx.Instance                 = DMA2_Stream2;

  hdma_rx.Init.Channel             = DMA_CHANNEL_4;
  hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_rx.Init.Mode                = DMA_CIRCULAR;
  hdma_rx.Init.Priority            = DMA_PRIORITY_LOW;
  hdma_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  if(HAL_DMA_Init(&hdma_rx) != HAL_OK)
  {
    Error_Handler();
  }

  /* Associate the initialized DMA handle to the the UART handle */
  __HAL_LINKDMA(huart, hdmarx, hdma_rx);

  /*##-4- Configure the NVIC for DMA #########################################*/


  /* NVIC configuration for USART TC interrupt */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO, DMA and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  /*##-1- Reset peripherals ##################################################*/
  __HAL_RCC_USART1_FORCE_RESET();
  __HAL_RCC_USART1_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);

  /*##-3- Disable the DMA Streams ############################################*/
  /* De-Initialize the DMA Stream associate to transmission process */
  HAL_DMA_DeInit(&hdma_tx);
  /* De-Initialize the DMA Stream associate to reception process */
  HAL_DMA_DeInit(&hdma_rx);

  /*##-4- Disable the NVIC for DMA ###########################################*/
  HAL_NVIC_DisableIRQ(DMA2_Stream5_IRQn);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
