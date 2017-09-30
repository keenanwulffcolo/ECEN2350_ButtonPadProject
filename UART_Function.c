//UART_Function.c
#include "UART_Function.h"
void configure_UART_clocks(void)
{
    CS->KEY = 0x695A; // Unlock CS module for register access
    CS->CTL0 = 0; // Reset tuning parameters
    CS->CTL0 = 0x00830000; // Enables DCO clock and sets DCO clock to 12 Mhz
   // Select ACLK = REFO, SMCLK = MCLK = DCO
    CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    CS->KEY = 0; // lock CS module for register access
}
void UART_Configure(UART_CONFIG_VAL UART_conf)
{
	P1SEL0 |= BIT2 | BIT3;
	P1SEL1 &= ~(BIT2| BIT3);
	UCA0CTLW0 &= UCSWRST;  // Put eUSCI in rese
	// We want no parity, LSB, 8-bit, UART, asynchronous mode, SMCLK,
	// 1 stop bit
	UCA0CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;
	switch (UART_conf){
	  case BAUD_VAL_38400:
		UCA0BRW = 0x0013; // Set Baud Rate to 38400, UCBRx = 19
		UCA0MCTLW = 0x6581; // UCBRFx = 8, UCOS16 = 1, UCBRSx = 0x65
		break;
	  case BAUD_VAL_19200:
		  // UCBRx = 3
		  UCA0BRW = 0x03;
		  // UCBRFx = 4, UCOS16 = 1, UCBRSx = 0x02
		  UCA0MCTLW = 0x0241;
		  break;
	  default:
		  break;
	}
	UCA0CTLW0 &= ~UCSWRST;
	UCA0IE |=  EUSCI_A_IE_RXIE;
    NVIC_EnableIRQ(EUSCIA0_IRQn);
}
void EUSCIA0_IRQHandler()
{
	if(UCA0IFG & UCRXIFG) {
		UCA0IFG &= ~UCRXIFG;
	}
}
uint8_t UART_putchar(uint8_t tx_data)
{
	while(!(UCA0IFG & UCTXIFG)){
	}
	UCA0TXBUF = tx_data;
	return 0;
}
uint8_t UART_putchar_n(uint8_t * data, uint32_t length)
{
	uint8_t i;
	for (i=0; i<length; i++){
		UART_putchar(*(data + i));
	}
	return 0;
}

//prior, initialize regular buffer
void UART_Print_Buffer(CircBuf * buf){
	//for loop to iterate through every logbuffer item.
	uint8_t i = 0;
	while(i==0){
	//conditionals for different states of items in LogBuffer
		if(*buf->head == PLAYSTART){
			UART_putchar_n("Playmode started.",17);
			UART_putchar(13);
			RemoveItemFromBuffer(buf);
		}
		else if(*buf->head == BUTTONPRESS){
			UART_putchar_n("Recieved button press from array.",33);
			UART_putchar(13);
			RemoveItemFromBuffer(buf);
		}
		else if(*buf->head == PITCHBEND){
			UART_putchar_n("Pitch modulation registered.",28);
			UART_putchar(13);
			RemoveItemFromBuffer(buf);
		}
		else if(*buf->head == MODESWITCH){
			UART_putchar_n("Switched to different soundpatch.",33);
			UART_putchar(13);
			RemoveItemFromBuffer(buf);
		}
		else if(*buf->head == PLAYSTOP){
			UART_putchar_n("Playmode ended.",15);
			UART_putchar(13);
			UART_putchar_n("End of log.",11);
			UART_putchar(13);
			ClearBuffer(buf);
			i = 1;
		}
	}
}
