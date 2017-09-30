//Joystick_Stuff.c
#include "Joystick_Stuff.h"
volatile uint16_t JoystickX;
volatile uint16_t JoystickY;
void ADC14_IRQHandler(void){
	if (ADC14->IFGR0 & ADC14_IFGR0_IFG0) {
	 // Insert Code here
		//Joystick code
		JoystickX = ADC14->MEM[0];
		JoystickY = ADC14->MEM[1];
		// Do stuff with joystick
	ADC14->CLRIFGR0 |= ADC14_IFGR0_IFG0;
	}
}

void configure_joystick(void){
	// Put pins 4.4 and 6.0 in tertiary mode
	P4DIR &= ~BIT0;
	P6DIR &= ~BIT0;
	P4SEL0 |= BIT4;
	P4SEL1 |= BIT4;
	P6SEL0 |= BIT0;
	P6SEL1 |= BIT0;
	//Configure ADC for joystick
	// Initialize the shared reference module
	// By default, REFMSTR=1 => REFCTL is used to configure the internal reference
	while(REF_A->CTL0 & REF_A_CTL0_GENBUSY); // If ref generator busy, WAIT
	REF_A->CTL0 = REF_A_CTL0_VSEL_0 | REF_A_CTL0_ON ; // Enable internal 1.2V ref
	// Configure ADC - Pulse sample mode; ADC14SC trigger
	// ADC ON, temperature sample period>30us
	ADC14->CTL0 &= ~ADC14_CTL0_ENC;//, disable conversion(allows configuration of registers)
	//notes: should consider changing and confifuring SSEL and changinf source freq. to optimize
	//also consider changing resolution to 8bit, we don't need it to be that accurate
	ADC14->CTL0 |= ADC14_CTL0_SHT0_5 | ADC14_CTL0_ON | ADC14_CTL0_SHP | ADC14_CTL0_CONSEQ_1 | ADC14_CTL0_MSC;
	ADC14->CTL1 |= ADC14_CTL1_RES__14BIT; // set resolution
	ADC14->MCTL[0] |= ADC14_MCTLN_INCH_9 | ADC14_MCTLN_VRSEL_14; // Map josystick x axis Analog channel to MEM0/MCTL0, set 3.3v ref
	ADC14->MCTL[1] |= ADC14_MCTLN_INCH_15 | ADC14_MCTLN_VRSEL_14; // Map josystick y axis Analog channel to MEM1/MCTL1, set 3.3v ref
	ADC14->IER0 = ADC14_IER0_IE0; // Enable MCTL0/MEM0 Interrupts
	ADC14->IER1 = ADC14_IER0_IE1; // Enable MCTL1/MEM1 Interrupts
	while(!(REF_A->CTL0 & REF_A_CTL0_GENRDY)); // Wait for ref generator to settle
	ADC14->CTL0 |= ADC14_CTL0_ENC; // re-Enable Conversions
	NVIC_EnableIRQ(ADC14_IRQn); // Enable ADC int in NVIC module
}

