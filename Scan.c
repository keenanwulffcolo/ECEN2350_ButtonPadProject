//scan.c
#include "Scan.h"
#define MAX_DEBOUNCE (4)
void scan(ARR * pARR_i, uint8_t ColIden)
{
	uint8_t i;
	uint8_t val;
	// 1.  Drive Led select pin ColIden and button select pin ColIden low
	*PORT_OUT(pARR_i->DRIVE_PINS.PortNo[ColIden]) &= ~(1 << pARR_i->DRIVE_PINS.PinNo[ColIden]);
	*PORT_OUT(pARR_i->DRIVE_LED.PortNo[ColIden]) &= ~(1 << pARR_i->DRIVE_LED.PinNo[ColIden]);
	// 2.  val = & Led outputs with 0x03 (either R G or B) (skipping for now)
	// 3.  Write led pins to correspond (skipping for now)
	// 4.  Repeat for each row (skipping for now)
	// 5.  For row from 0-3:
	for (i=0; i < 4; i++)
	{
		// 5a.  val = Read row
		if (!(*PORT_IN(pARR_i->READ_PINS.PortNo[i]) & 1 << pARR_i->READ_PINS.PinNo[i]))
			// 5b.  If read as low, write only if DEBOUNCE_COUNT == MAX_DEBOUNCE
		{
			if (pARR_i->DEBOUNCE_COUNT[ColIden][i] == MAX_DEBOUNCE - 1)
			{
				pARR_i->INPUT_VALUE |= 1 << (4*ColIden + i);
				AddItemToBuffer(&LogBuffer, BUTTONPRESS);
				// Change color matrix up, or if already at max value, to 0
				//*PORT_OUT(pARR_i->DRIVE_LED.PortNo[1]) &= ~(1 << pARR_i->DRIVE_LED.PinNo[1]);
				//*PORT_OUT(pARR_i->LED_R.PortNo[1]) |= 1 << pARR_i->LED_R.PinNo[1];
				pARR_i->DEBOUNCE_COUNT[ColIden][i]++;
				if (pARR_i->LED_COLOR[ColIden][i] <= 3){
					pARR_i->LED_COLOR[ColIden][i]++;
				}
				else{
					pARR_i->LED_COLOR[ColIden][i] = 0;
				}
			}
			else if(pARR_i->DEBOUNCE_COUNT[ColIden][i] == MAX_DEBOUNCE){
				pARR_i->INPUT_VALUE |= 1 << (4*ColIden + i);
				if (pARR_i->LED_COLOR[ColIden][i] <= 3){
					pARR_i->LED_COLOR[ColIden][i]++;
				}
				else{
					pARR_i->LED_COLOR[ColIden][i] = 0;
				}
			}
			else{
				pARR_i->DEBOUNCE_COUNT[ColIden][i]++;
			}
		}
		else{
			// 5c.  Else, decrement
			if (pARR_i->DEBOUNCE_COUNT[ColIden][i] == 0){
				pARR_i->INPUT_VALUE &= ~(1 << (4*ColIden + i));
				pARR_i->LED_COLOR[ColIden][i] = 0;
			}
			else{
				pARR_i->DEBOUNCE_COUNT[ColIden][i]--;
			}
			*PORT_OUT(pARR_i->DRIVE_LED.PortNo[1]) |= (1 << pARR_i->DRIVE_LED.PinNo[1]);
		}
	}
	for(i = 0; i < 4; i++)
		{
			val = (pARR_i->LED_COLOR[ColIden][i] & 0x03);
			if(val == 1){
				*PORT_OUT(pARR_i->LED_R.PortNo[i]) |= (1 << pARR_i->LED_R.PinNo[i]);
			}
			if(val == 2){
				*PORT_OUT(pARR_i->LED_G.PortNo[i]) |= (1 << pARR_i->LED_G.PinNo[i]);
			}
			if(val == 3){
				*PORT_OUT(pARR_i->LED_B.PortNo[i]) |= (1 << pARR_i->LED_B.PinNo[i]);
			}
			else{
				*PORT_OUT(pARR_i->LED_B.PortNo[i]) &= ~(1 << pARR_i->LED_B.PinNo[i]);
				*PORT_OUT(pARR_i->LED_G.PortNo[i]) &= ~(1 << pARR_i->LED_G.PinNo[i]);
				*PORT_OUT(pARR_i->LED_R.PortNo[i]) &= ~(1 << pARR_i->LED_R.PinNo[i]);
			}
	  }
	// 6.  Set drive to high
	*PORT_OUT(pARR_i->DRIVE_PINS.PortNo[ColIden]) |= (1 << pARR_i->DRIVE_PINS.PinNo[ColIden]);
	*PORT_OUT(pARR_i->DRIVE_LED.PortNo[ColIden]) |= (1 << pARR_i->DRIVE_LED.PinNo[ColIden]);
	// 7.  Write light back to low
}




//Sparkfun code below
	/******************************************************************************
	rgb-plus-buttons.ino
	Byron Jacquot @ SparkFun Electronics
	1/6/2015

	Example to drive the RGB LEDs and scan the buttons of the RGB button pad.

	Exercise 3 in a series of 3.
	https://learn.sparkfun.com/tutorials/button-pad-hookup-guide/exercise-3-rgb-leds-and-buttons

	Development environment specifics:
	Developed in Arduino 1.6.5
	For an Arduino Mega 2560

	This code is released under the [MIT License](http://opensource.org/licenses/MIT).

	Distributed as-is; no warranty is given.
	******************************************************************************/
	//config variables
#if 0
	#define NUM_LED_COLUMNS (4)
	#define NUM_LED_ROWS (4)
	#define NUM_BTN_COLUMNS (4)
	#define NUM_BTN_ROWS (4)
	#define NUM_COLORS (3)

	#define MAX_DEBOUNCE (3)

	// Global variables
	static uint8_t LED_outputs[NUM_LED_COLUMNS][NUM_LED_ROWS];
	static int32_t next_scan;

	static const uint8_t btnselpins[4]   = {50,51,52,53};
	static const uint8_t btnreadpins[4] = {46,47,48,49};
	static const uint8_t ledselpins[4]   = {42,43,44,45};

	// RGB pins for each of 4 rows
	static const uint8_t colorpins[4][3] = {{22,24,26}, {30,31,32},{33,34,35},{36,37,38}};


	static int8_t debounce_count[NUM_BTN_COLUMNS][NUM_BTN_ROWS];

	static void setuppins()
	{
	    uint8_t i;

	    // initialize
	    // select lines
	    for(i = 0; i < NUM_LED_COLUMNS; i++)
	    {
	        pinMode(ledselpins[i], OUTPUT);

	        // with nothing selected by default
	        digitalWrite(ledselpins[i], HIGH);
	    }

	    for(i = 0; i < NUM_BTN_COLUMNS; i++)
	    {
	        pinMode(btnselpins[i], OUTPUT);

	        // with nothing selected by default
	        digitalWrite(btnselpins[i], HIGH);
	    }

	    // key return lines
	    for(i = 0; i < 4; i++)
	    {
	        pinMode(btnreadpins[i], INPUT_PULLUP);
	    }

	    // LED drive lines
	    for(i = 0; i < NUM_LED_ROWS; i++)
	    {
	        for(uint8_t j = 0; j < NUM_COLORS; j++)
	        {
	            pinMode(colorpins[i][j], OUTPUT);
	            digitalWrite(colorpins[i][j], LOW);
	        }
	    }

	    for(uint8_t i = 0; i < NUM_BTN_COLUMNS; i++)
	    {
	        for(uint8_t j = 0; j < NUM_BTN_ROWS; j++)
	        {
	            debounce_count[i][j] = 0;
	        }
	    }
	}

	static void scan()
	{
	  static uint8_t current = 0;
	  uint8_t val;
	  uint8_t i, j;

	    //run
	    digitalWrite(btnselpins[current], LOW);
	    digitalWrite(ledselpins[current], LOW);

	    for(i = 0; i < NUM_LED_ROWS; i++)
	    {
	        uint8_t val = (LED_outputs[current][i] & 0x03);

	        if(val)
	        {
	            digitalWrite(colorpins[i][val-1], HIGH);
	        }
	  }


	  delay(1);

	  for( j = 0; j < NUM_BTN_ROWS; j++)
	  {
	    val = digitalRead(btnreadpins[j]);

	    if(val == LOW)
	    {
	      // active low: val is low when btn is pressed
	      if( debounce_count[current][j] < MAX_DEBOUNCE)
	      {
	        debounce_count[current][j]++;
	        if( debounce_count[current][j] == MAX_DEBOUNCE )
	        {
	          Serial.print("Key Down ");
	          Serial.println((current * NUM_BTN_ROWS) + j);

	          LED_outputs[current][j]++;
	        }
	      }
	    }
	    else
	    {
	      // otherwise, button is released
	      if( debounce_count[current][j] > 0)
	      {
	        debounce_count[current][j]--;
	        if( debounce_count[current][j] == 0 )
	        {
	          Serial.print("Key Up ");
	          Serial.println((current * NUM_BTN_ROWS) + j);
	        }
	      }
	    }
	  }// for j = 0 to 3;

	  delay(1);

	  digitalWrite(btnselpins[current], HIGH);
	  digitalWrite(ledselpins[current], HIGH);

	  for(i = 0; i < NUM_LED_ROWS; i++)
	  {
	    for(j = 0; j < NUM_COLORS; j++)
	    {
	      digitalWrite(colorpins[i][j], LOW);
	    }
	  }

	  current++;
	  if (current >= NUM_BTN_COLUMNS)
	  {
	    current = 0;
	  }
	}

	void setup()
	{
	  // put your setup code here, to run once:
	  Serial.begin(115200);

	  Serial.print("Starting Setup...");

	  // setup hardware
	  setuppins();

	  // init global variables
	  next_scan = millis() + 1;

	  for(uint8_t i = 0; i < NUM_LED_ROWS; i++)
	  {
	    for(uint8_t j = 0; j < NUM_LED_COLUMNS; j++)
	    {
	      LED_outputs[i][j] = 0;
	    }
	  }

	  Serial.println("Setup Complete.");
	}

	void loop() {
	  // put your main code here, to run repeatedly:

	  if(millis() >= next_scan)
	  {
	    next_scan = millis()+1;
	    scan();
	  }
	}
}
#endif


