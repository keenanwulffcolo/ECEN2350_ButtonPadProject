/*
 * IO_Ports.h
 *
 *  Created on: Nov 13, 2016
 *      Author: Dylan
 */

#ifndef IO_PORTS_H_
#define IO_PORTS_H_
#include <stdint.h>
#include "msp.h"
#include "UART_Function.h"
#include "CircBuf.h"
uint8_t PLAYMODE;
uint8_t UARTLOG;
extern CircBuf LogBuffer;

void Port1_Handler(void);



#endif /* IO_PORTS_H_ */
