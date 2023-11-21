/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_cdc_if.c
  * @version        : v1.0_Cube
  * @brief          : Usb device for Virtual Com Port.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"

/* USER CODE BEGIN INCLUDE */

/*******************************************************************************/
/* Line Coding Structure                                                       */
/*-----------------------------------------------------------------------------*/
/* Offset | Field       | Size | Value  | Description                          */
/* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
/* 4      | bCharFormat |   1  | Number | Stop bits                            */
/*                                        0 - 1 Stop bit                       */
/*                                        1 - 1.5 Stop bits                    */
/*                                        2 - 2 Stop bits                      */
/* 5      | bParityType |  1   | Number | Parity                               */
/*                                        0 - None                             */
/*                                        1 - Odd                              */
/*                                        2 - Even                             */
/*                                        3 - Mark                             */
/*                                        4 - Space                            */
/* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
/*******************************************************************************/

USBD_CDC_LineCodingTypeDef          LineCoding =
    {
        115200,         //  baudrate
        0x00,           //  stop bits
        0x00,           //  Paritry
        0x08            //  Number Data bits
    };

uint32_t ptr_in   = 0;
uint32_t ptr_out  = 0;
uint32_t rx_len   = 512;  //rx buffer length
uint8_t rx_buf[512];

void cdcFlush(void)
{
  ptr_in = 0;
  ptr_out = 0;
}

/**
 *  @ usb 수신 버퍼에 들어있는 데이터 갯수 확인
 */
uint32_t cdcAvailable(void)
{
  uint32_t ret;

  ret = (ptr_in - ptr_out) % rx_len;

  return ret;
}

/*
 * @ 수신버퍼에서 데이터를 읽는다.
 * 데이터 읽은 후 출력 인덱스 1 증가시킨다.
 * */
uint8_t cdcRead(void)
{
  uint8_t ret;

  ret = rx_buf[ptr_out];

  if(ptr_out != ptr_in)
  {
    ptr_out = (ptr_out + 1) % rx_len;
  }

  return ret;
}

/*
 * @ 수신버퍼에 데이터를 write한다.
 * 데이터 write 후에 입력 인덱스 1 증가시킨다.
 * */
void cdcDataIn(uint8_t rx_data)
{
  uint32_t next_ptr_in;

  rx_buf[ptr_in] = rx_data;   //수신데이터 수신버퍼에 입력

  //next_ptr_in은 현재 입력 인덱스의 다음 인덱스를 의미함
  next_ptr_in = (ptr_in + 1) % rx_len;

  //현재의 다음 입력 인덱스가 출력 인덱스와 다르면
  //(같으면 버퍼 full 상태임)
  if(next_ptr_in != ptr_out)
  {
    //입력인덱스를 1 증가시킨다.
    ptr_in = next_ptr_in;
  }
}

/*
 * @ 입력된 데이터를 길이만큼 usb로 전송한다.
 * */
uint32_t cdcWrite(uint8_t *p_data, uint32_t length)
{
  uint32_t pre_time;  //타임아웃 처리용 변수
  uint8_t state;

  //현재 타이머 카운터 값을 저장
  pre_time = millis();

  while(1)
  {
    //usb로 데이터 전송 후 결과를 변수에 저장
    state =CDC_Transmit_FS(p_data, length);

    if(state == USBD_OK)
    {
      //전송 성공 시 길이 리턴
      return length;
    }
    else if(state == USBD_FAIL)
    {
      //전송실패 시 리턴
      return 0;
    }
    if(millis() - pre_time >= 100)
    {
      //타임아웃 발생 시 루프탈출
      break;
    }
  }

  return 0;
}

/**
 * @ 현재 baudrate를 확인하는 함수
 */
uint32_t cdcGetBaud(void)
{
  return LineCoding.bitrate;
}

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device library.
  * @{
  */

/** @addtogroup USBD_CDC_IF
  * @{
  */

/** @defgroup USBD_CDC_IF_Private_TypesDefinitions USBD_CDC_IF_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Defines USBD_CDC_IF_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Macros USBD_CDC_IF_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Variables USBD_CDC_IF_Private_Variables
  * @brief Private variables.
  * @{
  */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_FunctionPrototypes USBD_CDC_IF_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t* pbuf, uint32_t *Len);
static int8_t CDC_TransmitCplt_FS(uint8_t *pbuf, uint32_t *Len, uint8_t epnum);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS,
  CDC_TransmitCplt_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{
  /* USER CODE BEGIN 3 */
  /* Set Application Buffers */
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
  return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  DeInitializes the CDC media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
  /* USER CODE BEGIN 5 */
  switch(cmd)
  {
    case CDC_SEND_ENCAPSULATED_COMMAND:

    break;

    case CDC_GET_ENCAPSULATED_RESPONSE:

    break;

    case CDC_SET_COMM_FEATURE:

    break;

    case CDC_GET_COMM_FEATURE:

    break;

    case CDC_CLEAR_COMM_FEATURE:

    break;

  /*******************************************************************************/
  /* Line Coding Structure                                                       */
  /*-----------------------------------------------------------------------------*/
  /* Offset | Field       | Size | Value  | Description                          */
  /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
  /* 4      | bCharFormat |   1  | Number | Stop bits                            */
  /*                                        0 - 1 Stop bit                       */
  /*                                        1 - 1.5 Stop bits                    */
  /*                                        2 - 2 Stop bits                      */
  /* 5      | bParityType |  1   | Number | Parity                               */
  /*                                        0 - None                             */
  /*                                        1 - Odd                              */
  /*                                        2 - Even                             */
  /*                                        3 - Mark                             */
  /*                                        4 - Space                            */
  /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
  /*******************************************************************************/
    case CDC_SET_LINE_CODING:
      //외부에서 설정한 통신 파라미터를 구조체 변수에 저장한다.
      LineCoding.bitrate     = (uint32_t)(pbuf[0] << 0);
      LineCoding.bitrate    |= (uint32_t)(pbuf[1] << 8);
      LineCoding.bitrate    |= (uint32_t)(pbuf[2] << 16);
      LineCoding.bitrate    |= (uint32_t)(pbuf[3] << 24);
      LineCoding.format     = pbuf[4];
      LineCoding.paritytype = pbuf[5];
      LineCoding.datatype   = pbuf[6];

    break;

    case CDC_GET_LINE_CODING:
      //LineCoding 구조체 변수에 현재 저장된 통신파라미터값을 불러온다.
      //-------> baudrate
      pbuf[0] = (uint8_t)(LineCoding.bitrate >> 0 & 0x000000FF);
      pbuf[1] = (uint8_t)(LineCoding.bitrate >> 8 & 0x000000FF);
      pbuf[2] = (uint8_t)(LineCoding.bitrate >> 16 & 0x000000FF);
      pbuf[3] = (uint8_t)(LineCoding.bitrate >> 24 & 0x000000FF);
      //-------> Stop bits
      pbuf[4] = (uint8_t)(LineCoding.format & 0xFF);
      //-------> Parity
      pbuf[5] = (uint8_t)(LineCoding.paritytype & 0xFF);
      //-------> Number Data bits
      pbuf[6] = (uint8_t)(LineCoding.datatype & 0xFF);

    break;

    case CDC_SET_CONTROL_LINE_STATE:

    break;

    case CDC_SEND_BREAK:

    break;

  default:
    break;
  }

  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will issue a NAK packet on any OUT packet received on
  *         USB endpoint until exiting this function. If you exit this function
  *         before transfer is complete on CDC interface (ie. using DMA controller)
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  /* USER CODE BEGIN 6 */
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
  USBD_CDC_ReceivePacket(&hUsbDeviceFS);

  //usb 수신 데이터 수신 데이터 길이만큼 수신버퍼에 저장
  for(int i=0;i<*Len;i++)
  {
    cdcDataIn(Buf[i]);
  }

  return (USBD_OK);
  /* USER CODE END 6 */
}

/**
  * @brief  CDC_Transmit_FS
  *         Data to send over USB IN endpoint are sent over CDC interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;
  /* USER CODE BEGIN 7 */
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
  if (hcdc->TxState != 0){
    return USBD_BUSY;
  }
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
  result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
  /* USER CODE END 7 */
  return result;
}

/**
  * @brief  CDC_TransmitCplt_FS
  *         Data transmitted callback
  *
  *         @note
  *         This function is IN transfer complete callback used to inform user that
  *         the submitted Data is successfully sent over USB.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_TransmitCplt_FS(uint8_t *Buf, uint32_t *Len, uint8_t epnum)
{
  uint8_t result = USBD_OK;
  /* USER CODE BEGIN 13 */
  UNUSED(Buf);
  UNUSED(Len);
  UNUSED(epnum);
  /* USER CODE END 13 */
  return result;
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */
