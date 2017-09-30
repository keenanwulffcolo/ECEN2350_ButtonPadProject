//Configure
#include "Configure.h"
void configure_MSP(ARR* ARR_i)
{
	//run all general config functions
	configure_UART_clocks();
	configure_joystick();
	__enable_interrupts();
	ConfigurePorts();
	configure_timer();
	ConfigureMIDI();
	// Configure port and pin numbers

	ARR_i->DRIVE_PINS.PortNo[0] = 8;
	ARR_i->DRIVE_PINS.PinNo[0] = 6;
	ARR_i->DRIVE_PINS.PortNo[1] = 8;
	ARR_i->DRIVE_PINS.PinNo[1] = 5;
	ARR_i->DRIVE_PINS.PortNo[2] = 9;
	ARR_i->DRIVE_PINS.PinNo[2] = 1;
	ARR_i->DRIVE_PINS.PortNo[3] = 8;
	ARR_i->DRIVE_PINS.PinNo[3] = 4;
	configure_DRIVE(&ARR_i->DRIVE_PINS);

	ARR_i->READ_PINS.PortNo[0] = 10;
	ARR_i->READ_PINS.PinNo[0] = 5;
	ARR_i->READ_PINS.PortNo[1] = 7;
	ARR_i->READ_PINS.PinNo[1] = 7;
	ARR_i->READ_PINS.PortNo[2] = 9;
	ARR_i->READ_PINS.PinNo[2] = 5;
	ARR_i->READ_PINS.PortNo[3] = 6;
	ARR_i->READ_PINS.PinNo[3] = 3;
	configure_READ(&ARR_i->READ_PINS);

	ARR_i->DRIVE_LED.PortNo[0] = 8;
	ARR_i->DRIVE_LED.PinNo[0] = 7;
	ARR_i->DRIVE_LED.PortNo[1] = 9;
	ARR_i->DRIVE_LED.PinNo[1] = 0;
	ARR_i->DRIVE_LED.PortNo[2] = 8;
	ARR_i->DRIVE_LED.PinNo[2] = 3;
	ARR_i->DRIVE_LED.PortNo[3] = 8;
	ARR_i->DRIVE_LED.PinNo[3] = 2;
	configure_DRIVE(&ARR_i->DRIVE_LED);

	ARR_i->LED_R.PortNo[0] = 10;
	ARR_i->LED_R.PinNo[0] = 4;
	ARR_i->LED_R.PortNo[1] = 7;
	ARR_i->LED_R.PinNo[1] = 6;
	ARR_i->LED_R.PortNo[2] = 9;
	ARR_i->LED_R.PinNo[2] = 6;
	ARR_i->LED_R.PortNo[3] = 7;
	ARR_i->LED_R.PinNo[3] = 3;
	configure_RGB(&ARR_i->LED_R);

	ARR_i->LED_G.PortNo[0] = 10;
	ARR_i->LED_G.PinNo[0] = 3;
	ARR_i->LED_G.PortNo[1] = 7;
	ARR_i->LED_G.PinNo[1] = 5;
	ARR_i->LED_G.PortNo[2] = 7;
	ARR_i->LED_G.PinNo[2] = 0;
	ARR_i->LED_G.PortNo[3] = 9;
	ARR_i->LED_G.PinNo[3] = 3;
	configure_RGB(&ARR_i->LED_G);

	ARR_i->LED_B.PortNo[0] = 10;
	ARR_i->LED_B.PinNo[0] = 2;
	ARR_i->LED_B.PortNo[1] = 7;
	ARR_i->LED_B.PinNo[1] = 4;
	ARR_i->LED_B.PortNo[2] = 9;
	ARR_i->LED_B.PinNo[2] = 4;
	ARR_i->LED_B.PortNo[3] = 6;
	ARR_i->LED_B.PinNo[3] = 2;
	configure_RGB(&ARR_i->LED_B);

	// Set DEBOUNCE_COUNT to 0
	uint8_t i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			ARR_i->DEBOUNCE_COUNT[i][j] = 0;
			ARR_i->LED_COLOR[i][j] = 0;
		}
	}
}

void ConfigurePorts(void){
	//Configure Port 1
	P1DIR = BIT0;
	P1IE = BIT1 | BIT4;
	P1IES = 0;
	P1IFG = 0;
	P1OUT = BIT1 | BIT4;
	P1REN = BIT1 | BIT4;
	NVIC_EnableIRQ(PORT1_IRQn);
	//Configure Port 2
	P2DIR = BIT0 | BIT1 | BIT2;
	P2OUT = 0x00;
}

static void configure_DRIVE(PinAd* DRIVE_PINS)
{
	uint8_t i;
	// for loop to configure each pin the same
	for(i=0; i<4; i++)
	{
		// Configure to be output
		*PORT_DIR(DRIVE_PINS->PortNo[i]) |= 1 << DRIVE_PINS->PinNo[i];
		// Drive Pins high (should be high until driven low)
		*PORT_OUT(DRIVE_PINS->PortNo[i]) |= 1 << DRIVE_PINS->PinNo[i];
	}
}
static void configure_RGB(PinAd* RGB_PINS)
{
	uint8_t i;
	// for loop to configure each pin the same

	for(i=0; i<4; i++)
	{
		// Configure to be output
		*PORT_DIR(RGB_PINS->PortNo[i]) |= 1 << RGB_PINS->PinNo[i];
		// Drive Pins low
		*PORT_OUT(RGB_PINS->PortNo[i]) &= ~(1 << RGB_PINS->PinNo[i]);
	}
}
static void configure_READ(PinAd* READ_PINS)
{
	uint8_t i;
	for(i=0; i<4; i++)
	{
		// Configure to be input
		*PORT_DIR(READ_PINS->PortNo[i]) &= ~(1 << READ_PINS->PinNo[i]);
		// Enable Resistor
		*PORT_REN(READ_PINS->PortNo[i]) |= 1 << READ_PINS->PinNo[i];
		// Enable Pullup or Pulldown (not sure which??)
		*PORT_OUT(READ_PINS->PortNo[i]) |= (1 << READ_PINS->PinNo[i]);
	}
}
