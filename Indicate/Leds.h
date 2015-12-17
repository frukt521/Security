#ifndef LEDS_H_
#define LEDS_H_

#include <avr/io.h>
#include "SmartIndicate/SmartIndicate.h"

#define LED_PORT			(PORTC)
#define LED_DDR				(DDRC)
#define LED_RED_NUM			0
#define LED_GREEN_NUM		1

typedef enum
{
	LED_RED,
	LED_GREEN
} LedsList_e;

typedef enum
{
	INDICATE_DOOR_OPEN,			//Green 1000ms
	INDICATE_ERROR,				//Red	1000ms
	INDICATE_IBUTTON_WAIT,		//Green 200ms Red 200ms Green 200ms
	INDICATE_IBUTTON_WAIT_END,	//Red 200ms Red 200ms Red 200ms
	INDICATE_IBUTTON_ADDED,		//Green 200ms Green 200ms Green 200ms
	INDICATE_KEY_WAIT,			//Green 200ms Red 200ms
	INDICATE_KEY_CHANGED		//Green 200ms Green 200ms
} Indicate_e;


void Leds_Init(void);
void Leds_Switch(LedsList_e led, LedStates_e state);
void Leds_Indicate(Indicate_e indicate);

#endif /* LEDS_H_ */