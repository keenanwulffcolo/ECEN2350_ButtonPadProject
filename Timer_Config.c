//Timer_Config.c
#include "Timer_Config.h"
void configure_timer()
{
	TA0CCR0 = 300;     // Capture Compare Value to give a period of 1200us
	TA0CTL = TIMER_A_CTL_MC_1 | TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_ID_0;	// SMCLK, up mode, no pre scalar
	TA0CCTL0 &= ~CCIFG;
	TA0CTL &= ~CCIFG;
	TA0R = 0;
	NVIC_EnableIRQ(TA0_0_IRQn);  // Enable interrupt in NVIC
}

