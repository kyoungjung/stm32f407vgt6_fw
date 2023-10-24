/*
 * qbuffer.h
 *
 *  Created on: 2023. 9. 25.
 *      Author: kjkim
 */

#ifndef SRC_COMMON_CORE_QBUFFER_H_
#define SRC_COMMON_CORE_QBUFFER_H_


#include "def.h"

/*
 * @ 큐버퍼 구현에 필요한 변수들 구조체로 정의
 * */

typedef struct
{
  uint32_t ptr_in;              //q input
  uint32_t ptr_out;             //q output
  uint32_t length;              //q data length
  uint8_t *p_buf;               //q buffer pointer
}qbuffer_t;

void qbufferInit(void);

bool qbufferCreate(qbuffer_t *p_node, uint8_t *p_buf, uint32_t length);
bool qbufferWrite(qbuffer_t *p_node, uint8_t *p_buf, uint32_t length);
bool qbufferRead(qbuffer_t *p_node, uint8_t *p_data, uint32_t length);
uint32_t qbufferAvailable(qbuffer_t *p_node);
void qbufferFlush(qbuffer_t *p_node);


#endif /* SRC_COMMON_CORE_QBUFFER_H_ */
