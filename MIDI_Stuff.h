//MIDI_Stuff.h
#ifndef MIDI_STUFF_H_
#define MIDI_STUFF_H_
#include <stdint.h>
#include <msp.h>
typedef enum{
	NoteOn = 0b10010000,
	NoteOff = 0b10000000,
	StandardVelocity = 0b01000000, //play around with this to get the right one
	PatchChange = 0b11000000,
	//add more patches here if we want
	C3 = 48,
	CS3 = 49,
	D3 = 50,
	DS3 = 51,
	E3 = 52,
	F3 = 53,
	FS3 = 54,
	G3 = 55,
	GS3 = 56,
	A3 = 57,
	AS3 = 58,
	B3 = 59,

	C4 = 60, //middle c
	CS4 = 61,
	D4 = 62,
	DS4 = 63,
	E4 = 64,
	F4 = 65,
	FS4 = 66,
	G4 = 67,
	GS4 = 68,
	A4 = 69,
	AS4 = 70,
	B4 = 71,

	C5 = 72,
	CS5 = 73,
	D5 = 74,
	DS5 = 75,
	E5 = 76,
	F5 = 77,
	FS5 = 78,
	G5 = 79,
	GS5 = 80,
	A5 = 81,
	AS5 = 82,
	B5 = 83,

	C6 = 84,
	CS6 = 85,
	D6 = 86,
	DS6 = 87,
	E6 = 88,
	F6 = 89,
	FS6 = 90,
	G6 = 91,
	GS6 = 92,
	A6 = 93,
	AS6 = 94,
	B6 = 95,
}MIDIData;
extern MIDIData MIDIArray[16];
void ConfigureMIDI(void);
void TransmitMIDI(MIDIData txMIDI);
void ScanMIDI(uint16_t ArrayState, uint16_t *midistate);
#endif /* MIDI_STUFF_H_ */


