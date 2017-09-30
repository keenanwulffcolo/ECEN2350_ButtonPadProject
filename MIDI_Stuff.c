//MIDI_Stuff.c
#include "MIDI_Stuff.h"
void ConfigureMIDI(void){
	UCA0CTLW0 &= UCSWRST;  // Put eUSCI in reset
	// We want no parity, LSB, 8-bit, UART, asynchronous mode, SMCLK,
	// 1 stop bit
	UCA0CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;
	//set baud rate here
	// UCBRx = 24
	UCA0BRW = 24;
	// UCBRFx = 0, UCOS16 = 1, UCBRSx = 0
	UCA0MCTLW = 0x0001;
	UCA0CTLW0 &= ~UCSWRST; //eUSCI out of reset
	UCA0IE |=  EUSCI_A_IE_RXIE;
    NVIC_EnableIRQ(EUSCIA0_IRQn);
    //define MIDIArray for sending stuff

    MIDIArray[0] = C3;
    MIDIArray[1] = D3;
    MIDIArray[2] = E3;
    MIDIArray[3] = F3;
    MIDIArray[4] = G3;
    MIDIArray[5] = A3;
    MIDIArray[6] = B3;
    MIDIArray[7] = C4;
    MIDIArray[8] = D4;
    MIDIArray[9] = E4;
    MIDIArray[10] = F4;
    MIDIArray[11] = G4;
    MIDIArray[12] = A4;
    MIDIArray[13] = B4;
    MIDIArray[14] = C4;
    MIDIArray[15] = D4;
}
void TransmitMIDI(MIDIData txMIDI){
	UCA0TXBUF = (uint8_t)txMIDI;
}
void ScanMIDI(uint16_t ArrayState, uint16_t *midistate){
	uint16_t noteState = ArrayState ^ *midistate;
	uint8_t i;
	if(noteState){
		for(i=0;i<16;i++){
			if((noteState & (1<<i)) && (*midistate & (1<<i) == 1)){
				TransmitMIDI(NoteOff);
				TransmitMIDI(MIDIArray[i]);
				TransmitMIDI(StandardVelocity);
				*midistate ^= (1<<i);
			}
			else if((noteState & (1<<i)) && (*midistate & (1<<i) == 0)){
				TransmitMIDI(NoteOn);
				TransmitMIDI(MIDIArray[i]);
				TransmitMIDI(StandardVelocity);
				*midistate ^= (1<<i);
			}
		}
	}
}

