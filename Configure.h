//Configure.h
#ifndef CONFIGURE_H_
#define CONFIGURE_H_
//#include "UART_Function.h"
#include "PortDeclaration.h"
#include <stdint.h>
#include "JoyStick_Stuff.h"
#include "UART_Function.h"
#include "Timer_Config.h"
#include "MIDI_Stuff.h"
#include "IO_Ports.h"
extern CircBuf LogBuffer;
typedef struct PinAd_t
{
	uint8_t PortNo [4];  // PortNo (1:10)
	uint8_t PinNo [4];	// PinNo (0:7)
}PinAd;
typedef struct ARR_t
{
	uint8_t DEBOUNCE_COUNT [4][4];
	uint8_t LED_COLOR [4][4];		// Dictates the color of the LED
	uint16_t INPUT_VALUE;
	/*
	 * For INPUT_VALUE, bit diagram is as follows
	 *          |BIT 15| |BIT 14| |BIT 13| |BIT 12|
	 * |COL 03| |ROW 03| |ROW 02| |ROW 01| |ROW 00|
	 * 			-----------------------------------
	 * 			|BIT 11| |BIT 10| |BIT 09| |BIT 08|
	 * |COL 02| |ROW 03| |ROW 02| |ROW 01| |ROW 00|
	 * 			-----------------------------------
	 * 			|BIT 07| |BIT 06| |BIT 05| |BIT 04|
	 * |COL 01| |ROW 03| |ROW 02| |ROW 01| |ROW 00|
	 * 			-----------------------------------
	 * 			|BIT 03| |BIT 02| |BIT 01| |BIT 00|
	 * |COL 00| |ROW 03| |ROW 02| |ROW 01| |ROW 00|
	 *
	 * For Col y, Row x, set with
	 * INPUT_VALUE |= 1 << (4*y + x)
	 */
	PinAd DRIVE_PINS;				// Specifies the location of driving pins
	PinAd READ_PINS;				// Specifies the location of read pins
	PinAd DRIVE_LED;				// Specifies the location of LED drive pins
	PinAd LED_R;					// Specifies the location of red LED read
	PinAd LED_G;					// Specifies the location of red LED read
	PinAd LED_B;					// Specifies the location of red LED read
}ARR;
void configure_MSP(ARR* ARR_i);
static void configure_DRIVE(PinAd* DRIVE_PINS);
static void configure_READ(PinAd* READ_PINS);
static void configure_RGB(PinAd* RGB_Pins);
void ConfigurePorts(void);
#endif /* CONFIGURE_H_ */
