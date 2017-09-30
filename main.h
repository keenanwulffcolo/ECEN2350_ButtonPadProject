/*
 * main.h
 *
 *  Created on: Nov 11, 2016
 *      Author: kewu4568
 */

#ifndef MAIN_H_
#define MAIN_H_
#include "msp.h"

#include "MIDI_Stuff.h"
#include "IO_Ports.h"
#include "UART_Function.h"
#include "Configure.h"
#include "Scan.h"
#include "CircBuf.h"






extern uint8_t PLAYMODE;
extern uint8_t UARTLOG;
CircBuf LogBuffer;
MIDIData MIDIArray[16];



#endif /* MAIN_H_ */
