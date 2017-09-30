#include "main.h"

void main(void)
{
    PLAYMODE = 0;
	WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
    ARR* pARR_i = (ARR*)malloc(sizeof(ARR));
	configure_MSP(pARR_i);
	uint8_t ColIden = 0;	//Passed to scan to signal which column to do
	uint16_t MIDIState = 0; //holds current state of what midi note is playing
	//initialize log buffer
	InitializeBuffer(&LogBuffer, 127);
    while(1){
    	//conditional if msp in play mode
    	if(PLAYMODE)
    	{
    		//run scan function continuously
    		if(TA0CCTL0 == TIMER_A_CCTLN_CCIFG)
    		{
				scan(pARR_i,ColIden);
				// Columns can be 1 to 3.  Once it gets to 3, it has to go to 0
				if(ColIden == 3){
					ColIden = 0;
				}
				else{
					ColIden++;
				}
				//ScanMIDI(ArrayState, &MIDIState);
				TA0CCTL0 &= ~TIMER_A_CCTLN_CCIFG; // Clear flag
    		}
    	}
    	else if(UARTLOG){
    		//configure UART and transmit all of Log Buffer data
    		UART_Configure(BAUD_VAL_38400);
    		UART_Print_Buffer(&LogBuffer);
    		//Reset UARTLOG
    		UARTLOG = 0;
    	}
    }
}
