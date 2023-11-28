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
#define UART_RX_QBUF_LENGTH                 256

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart3_rx;

DMA_HandleTypeDef hdma_tx;
DMA_HandleTypeDef hdma_rx;

static qbuffer_t  qbuffer[UART_MAX_CH];

extern void cdcFlush(void);
extern uint32_t cdcAvailable(void);
extern uint8_t cdcRead(void);
extern void cdcDataIn(uint8_t rx_data);
extern uint32_t cdcWrite(uint8_t *p_data, uint32_t length);
extern uint32_t cdcGetBaud(void);
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

  DMA_HandleTypeDef         hdma_rx;       //DMA를 다루기 위한 구조체 변수
  UART_HandleTypeDef        handle;     //UART를 다루기 위한 구조체 변수
}uart_t;


uart_t      uart_tbl[UART_MAX_CH];  //채널별 UART 핸들링위한 UART 구조체 변수 선언
//static uint8_t     uart_rx_qbuf[256];   //uart채널별 큐버퍼 선언
uint8_t uart_rx_qbuf[UART_MAX_CH][UART_RX_BUF_LENGTH];

void uartStartRx(uint8_t ch);         //uart 수신시작 설정 함수
void uartRxHandler(uint8_t ch);       //uart 수신 핸들러 함수

void uartInit(void)
{
  uint8_t i;
  for(i=0;i<UART_MAX_CH;i++)
  {
    uart_tbl[i].is_open   = false;
    uart_tbl[i].vcp_mode  = false;
    //uart_tbl[i].rx_mode   = UART_MODE_INTERRUPT;
    //uart_tbl[i].tx_mode   = UART_MODE_INTERRUPT;
    uart_tbl[i].rx_mode   = UART_MODE_DMA;
    uart_tbl[i].tx_mode   = UART_MODE_DMA;
  }
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

      p_uart->handle.Instance           = USART1;
      p_uart->handle.Init.BaudRate      = baud;
      p_uart->handle.Init.WordLength    = UART_WORDLENGTH_8B;
      p_uart->handle.Init.StopBits      = UART_STOPBITS_1;
      p_uart->handle.Init.Parity        = UART_PARITY_NONE;
      p_uart->handle.Init.Mode          = UART_MODE_TX_RX;
      p_uart->handle.Init.HwFlowCtl     = UART_HWCONTROL_NONE;
      p_uart->handle.Init.OverSampling  = UART_OVERSAMPLING_16;

      HAL_UART_DeInit(&p_uart->handle);

      qbufferCreate(&p_uart->qbuffer_rx , uart_rx_qbuf[ch], UART_RX_QBUF_LENGTH);    //큐 버퍼 생성

      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        /* DMA controller clock enable */
        __HAL_RCC_DMA2_CLK_ENABLE();

        /* DMA interrupt init */
        /* DMA2_Stream2_IRQn interrupt configuration */
        HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
      }

      if(HAL_UART_Init(&p_uart->handle) != HAL_OK)         //uart 초기화
      {
        ret = false;
      }
      else
      {
        uartStartRx(ch);
      }

      break;

    case _DEF_UART2:
      p_uart = &uart_tbl[ch];

      p_uart->baud = baud;
      p_uart->is_open = true;
      p_uart->vcp_mode  = false;
      p_uart->rx_mode   = UART_MODE_DMA;

      p_uart->handle.Instance           = USART2;
      p_uart->handle.Init.BaudRate      = baud;
      p_uart->handle.Init.WordLength    = UART_WORDLENGTH_8B;
      p_uart->handle.Init.StopBits      = UART_STOPBITS_1;
      p_uart->handle.Init.Parity        = UART_PARITY_NONE;
      p_uart->handle.Init.Mode          = UART_MODE_TX_RX;
      p_uart->handle.Init.HwFlowCtl     = UART_HWCONTROL_NONE;
      p_uart->handle.Init.OverSampling  = UART_OVERSAMPLING_16;

      HAL_UART_DeInit(&p_uart->handle);

      qbufferCreate(&p_uart->qbuffer_rx , uart_rx_qbuf[ch], UART_RX_QBUF_LENGTH);    //큐 버퍼 생성

      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        /* DMA controller clock enable */
        __HAL_RCC_DMA1_CLK_ENABLE();

        /* DMA interrupt init */
        /* DMA2_Stream2_IRQn interrupt configuration */
        HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
      }

      if(HAL_UART_Init(&p_uart->handle) != HAL_OK)                                          //uart 초기화
      {
        ret = false;
      }
      else
      {
        uartStartRx(ch);
      }
      break;

    case _DEF_UART3:
      p_uart = &uart_tbl[ch];

      p_uart->baud = baud;
      p_uart->is_open = true;
      p_uart->vcp_mode  = false;
      p_uart->rx_mode   = UART_MODE_DMA;

      p_uart->handle.Instance           = USART3;
      p_uart->handle.Init.BaudRate      = baud;
      p_uart->handle.Init.WordLength    = UART_WORDLENGTH_8B;
      p_uart->handle.Init.StopBits      = UART_STOPBITS_1;
      p_uart->handle.Init.Parity        = UART_PARITY_NONE;
      p_uart->handle.Init.Mode          = UART_MODE_TX_RX;
      p_uart->handle.Init.HwFlowCtl     = UART_HWCONTROL_NONE;
      p_uart->handle.Init.OverSampling  = UART_OVERSAMPLING_16;

      HAL_UART_DeInit(&p_uart->handle);

      qbufferCreate(&p_uart->qbuffer_rx , uart_rx_qbuf[ch], UART_RX_QBUF_LENGTH);    //큐 버퍼 생성

      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        /* DMA controller clock enable */
        __HAL_RCC_DMA1_CLK_ENABLE();

        HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
      }

      if(HAL_UART_Init(&p_uart->handle) != HAL_OK)                                          //uart 초기화
      {
        ret = false;
      }
      else
      {
        uartStartRx(ch);
      }
      break;


    case _DEF_UART4:            //usb
      p_uart = &uart_tbl[ch];
      p_uart->is_open = true;   //usb 통신채널이 오픈됨.

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
        HAL_UART_Receive_IT(&p_uart->handle, (uint8_t*)&uart_rx_qbuf[0], 1);
      }

      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        if(HAL_UART_Receive_DMA(&p_uart->handle, (uint8_t*)p_uart->qbuffer_rx.p_buf, p_uart->qbuffer_rx.length) != HAL_OK)
        {
          return;
        }
        p_uart->qbuffer_rx.ptr_in = p_uart->qbuffer_rx.length - p_uart->hdma_rx.Instance->NDTR;
        p_uart->qbuffer_rx.ptr_out = p_uart->qbuffer_rx.ptr_in;
      }
      break;

    case _DEF_UART2:
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        if(HAL_UART_Receive_DMA(&p_uart->handle, (uint8_t*)p_uart->qbuffer_rx.p_buf, p_uart->qbuffer_rx.length) != HAL_OK)
        {
          return;
        }
      }
      break;

    case _DEF_UART3:
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        if(HAL_UART_Receive_DMA(&p_uart->handle, (uint8_t*)p_uart->qbuffer_rx.p_buf, p_uart->qbuffer_rx.length) != HAL_OK)
        {
          return;
        }
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

  switch(ch)
  {
    case _DEF_UART1:    //uart
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        p_uart->qbuffer_rx.ptr_in = p_uart->qbuffer_rx.length - p_uart->hdma_rx.Instance->NDTR;
        ret = qbufferAvailable(&p_uart->qbuffer_rx);
        uartPrintf(_DEF_UART4, "%d   %d   %d  %d\r\n",
                   p_uart->qbuffer_rx.ptr_in, p_uart->qbuffer_rx.length, p_uart->hdma_rx.Instance->NDTR, ret);
      }

      if(p_uart->rx_mode == UART_MODE_INTERRUPT)
      {
        ret = qbufferAvailable(&qbuffer[ch]);
      }
      break;

    case _DEF_UART2:
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        p_uart->qbuffer_rx.ptr_in = p_uart->qbuffer_rx.length - p_uart->hdma_rx.Instance->NDTR;
        ret = qbufferAvailable(&p_uart->qbuffer_rx);
      }
      break;

    case _DEF_UART3:
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        p_uart->qbuffer_rx.ptr_in = p_uart->qbuffer_rx.length - p_uart->hdma_rx.Instance->NDTR;
        ret = qbufferAvailable(&p_uart->qbuffer_rx);
      }
      break;

    case _DEF_UART4:            //usb
      ret = cdcAvailable();     //usb 수신버퍼 사용가능한지 확인
      break;
  }
  return ret;
}

void uartFlush(uint8_t ch)
{
  uart_t    *p_uart;

  p_uart = &uart_tbl[ch];

  switch(ch)
  {
    case _DEF_UART1:
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        p_uart->qbuffer_rx.ptr_in = p_uart->qbuffer_rx.length - p_uart->hdma_rx.Instance->NDTR;
        p_uart->qbuffer_rx.ptr_out = p_uart->qbuffer_rx.ptr_in;
      }
      if(p_uart->rx_mode == UART_MODE_INTERRUPT)
      {
        p_uart->qbuffer_rx.ptr_out  = 0;
        p_uart->qbuffer_rx.ptr_in   = 0;
      }
      break;

    case _DEF_UART2:
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        p_uart->qbuffer_rx.ptr_in = p_uart->qbuffer_rx.length - p_uart->hdma_rx.Instance->NDTR;
        p_uart->qbuffer_rx.ptr_out = p_uart->qbuffer_rx.ptr_in;
      }
      break;

    case _DEF_UART3:
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        p_uart->qbuffer_rx.ptr_in = p_uart->qbuffer_rx.length - p_uart->hdma_rx.Instance->NDTR;
        p_uart->qbuffer_rx.ptr_out = p_uart->qbuffer_rx.ptr_in;
      }
      break;

    case _DEF_UART4:    //usb
      cdcFlush();       //usb 버퍼 처리용 입출력 인덱스 변수 초기화
      break;
  }
}

void uartPutch(uint8_t ch, uint8_t c)
{
  switch(ch)
  {
    case _DEF_UART1:
      uartWrite(ch, &ch, 1);
      break;

    case _DEF_UART2:
      uartWrite(ch, &ch, 1);
      break;

    case _DEF_UART3:
      uartWrite(ch, &ch, 1);
      break;

    case _DEF_UART4:    //usb
      cdcWrite(&c, 1);  //usb cdc로 1바이트 문자 write
      break;
  }
}

uint8_t uartGetch(uint8_t ch)
{
  uint8_t ret = 0;

  if(ch >= HW_UART_MAX_CH)   return 0;

  switch(ch)
  {
    case _DEF_UART1:
      if(uartAvailable(ch) > 0)
      {
        ret = uartRead(ch);
      }
      break;

    case _DEF_UART2:
      if(uartAvailable(ch) > 0)
      {
        ret = uartRead(ch);
      }
      break;

    case _DEF_UART3:
      if(uartAvailable(ch) > 0)
      {
        ret = uartRead(ch);
      }
      break;

    case _DEF_UART4:            //usb
      if(cdcAvailable() > 0)
      {
        //usb 수신버퍼에 데이터가 있으면
        //1바이트 읽어온다.
        ret = cdcRead();
      }
      break;
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

      if(p_uart->rx_mode == UART_MODE_INTERRUPT)
      {
        if(HAL_UART_Transmit(&huart1, p_data, length, 100) == HAL_OK)
        {
          ret = length;
        }
      }
      break;

    case _DEF_UART2:
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        if(HAL_UART_Transmit(&p_uart->handle, p_data, length, 100) == HAL_OK)
        {
          ret = length;
        }
      }
      break;

    case _DEF_UART3:
      if(p_uart->rx_mode == UART_MODE_DMA)
      {
        if(HAL_UART_Transmit(&p_uart->handle, p_data, length, 100) == HAL_OK)
        {
          ret = length;
        }
      }
      break;

    case _DEF_UART4:      //usb
      //usb로 수신된 데이터를 길이만큼 write한다.
      ret = cdcWrite(p_data, length);
      break;
  }

  return ret;
}
uint8_t uartRead(uint8_t ch)
{
  uint8_t ret = 0;

  uart_t  *p_uart;

  switch(ch)
  {
    case _DEF_UART1:
      p_uart = &uart_tbl[ch];
      qbufferRead(&p_uart->qbuffer_rx, &ret, 1);
      break;

    case _DEF_UART2:
      p_uart = &uart_tbl[ch];
      qbufferRead(&p_uart->qbuffer_rx, &ret, 1);
      break;

    case _DEF_UART3:
      p_uart = &uart_tbl[ch];
      qbufferRead(&p_uart->qbuffer_rx, &ret, 1);
      break;

    case _DEF_UART4:      //usb
      p_uart = &uart_tbl[ch];
      //usb로 수신된 데이터를 읽어서 변수에 저장한다.
      ret = cdcRead();
      break;
  }

  return ret;
}

int32_t uartPrintf(uint8_t ch, const char *fmt, ...)
{
  char buf[256];
  va_list   args;
  int len;
  int32_t ret = 0;
  va_start(args, fmt);

  len = vsnprintf(buf, 256, fmt, args);

  switch(ch)
  {
    case _DEF_UART1:
      ret = uartWrite(ch, (uint8_t*)buf, len);
      break;

    case _DEF_UART2:
      ret = uartWrite(ch, (uint8_t*)buf, len);
      break;

    case _DEF_UART3:
      ret = uartWrite(ch, (uint8_t*)buf, len);
      break;

    case _DEF_UART4:  //usb
      //usb로 print한다.
      ret = cdcWrite((uint8_t*)buf, len);
      break;
  }

  va_end(args);

  return ret;
}

uint32_t uartGetBaud(uint8_t ch)
{
  uint32_t baud;
  switch(ch)
  {
    case _DEF_UART1:      //uart
      break;

    case _DEF_UART2:
      break;

    case _DEF_UART3:
      break;

    case _DEF_UART4:      //usb cdc
      baud = cdcGetBaud();
      break;
  }

  return baud;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(uart_tbl[_DEF_UART1].rx_mode == UART_MODE_INTERRUPT)
  {
    qbufferWrite(&qbuffer[_DEF_UART1], &qbuffer[_DEF_UART1].p_buf[0], 1); //uart rx 수신데이터를 큐버퍼에 쓴다.

    HAL_UART_Receive_IT(&huart1, (uint8_t*)&uart_rx_qbuf[0], 1);  //수신인터럽트를 다시 활성화 한다.
  }
  else
  {
    return;
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  uart_t *p_uart;

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */

    p_uart = &uart_tbl[_DEF_UART1];

    p_uart->hdma_rx.Instance = DMA2_Stream2;
    p_uart->hdma_rx.Init.Channel = DMA_CHANNEL_4;
    p_uart->hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    p_uart->hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    p_uart->hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
    p_uart->hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    p_uart->hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    p_uart->hdma_rx.Init.Mode = DMA_CIRCULAR;
    p_uart->hdma_rx.Init.Priority = DMA_PRIORITY_LOW;
    p_uart->hdma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&p_uart->hdma_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(&p_uart->handle,hdmarx,p_uart->hdma_rx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */

    p_uart = &uart_tbl[_DEF_UART2];

    p_uart->hdma_rx.Instance = DMA1_Stream5;
    p_uart->hdma_rx.Init.Channel = DMA_CHANNEL_4;
    p_uart->hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    p_uart->hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    p_uart->hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
    p_uart->hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    p_uart->hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    p_uart->hdma_rx.Init.Mode = DMA_CIRCULAR;
    p_uart->hdma_rx.Init.Priority = DMA_PRIORITY_LOW;
    p_uart->hdma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&p_uart->hdma_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(&p_uart->handle,hdmarx,p_uart->hdma_rx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 DMA Init */
    /* USART3_RX Init */

    p_uart = &uart_tbl[_DEF_UART3];

    p_uart->hdma_rx.Instance = DMA1_Stream1;
    p_uart->hdma_rx.Init.Channel = DMA_CHANNEL_4;
    p_uart->hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    p_uart->hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    p_uart->hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
    p_uart->hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    p_uart->hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    p_uart->hdma_rx.Init.Mode = DMA_CIRCULAR;
    p_uart->hdma_rx.Init.Priority = DMA_PRIORITY_LOW;
    p_uart->hdma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&p_uart->hdma_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(&p_uart->handle,hdmarx,p_uart->hdma_rx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
    __HAL_RCC_USART2_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
    __HAL_RCC_USART3_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
