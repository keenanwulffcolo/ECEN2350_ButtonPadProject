#include "IO_Ports.h"
void Port1_Handler(void){
	uint8_t i;
	for(i=0;i<50;i++){}
	if(P1IFG & BIT1){
		//Enable PLAYMODE
		PLAYMODE = 1;
		//toggle state LED
		P2OUT ^= BIT1;
		AddItemToBuffer(&LogBuffer, PLAYSTART);
		P1IFG &= ~BIT1;
	}
	if(P1IFG & BIT4){
		//Disable PLAYMODE
		PLAYMODE = 0;
		//toggle state LED
		P2OUT ^= BIT1;
		//Enable UARTLOG
		UARTLOG = 1;
		AddItemToBuffer(&LogBuffer, PLAYSTOP);
		P1IFG &= ~BIT1;
	}
	P1IFG = 0;
}
