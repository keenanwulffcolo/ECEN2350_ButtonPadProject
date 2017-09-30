/*
 * ButtonArray.h
 *
 *  Created on: Nov 11, 2016
 *      Author: kewu4568
 */

#ifndef SCAN_H_
#define SCAN_H_
#include "msp.h"
#include "Configure.h"
#include <stdint.h>
#include "main.h"
#include "UART_Function.h"


extern CircBuf LogBuffer;
void scan(ARR * pARR_i, uint8_t ColIden);



#endif /* SCAN_H_ */
