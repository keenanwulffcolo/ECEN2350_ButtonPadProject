/*
 * Joystick_Stuff.h
 *
 *  Created on: Nov 16, 2016
 *      Author: kewu4568
 */

#ifndef JOYSTICK_STUFF_H_
#define JOYSTICK_STUFF_H_

#include "msp.h"
#include <stdint.h>

void ADC14_IRQHandler(void);
void configure_joystick(void);

volatile uint16_t JoystickX;
volatile uint16_t JoystickY;




#endif /* JOYSTICK_STUFF_H_ */
