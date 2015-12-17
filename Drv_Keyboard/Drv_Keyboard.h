#ifndef DRV_KEYBOARD_H_
#define DRV_KEYBOARD_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Drv_Timer0/Drv_Timer0.h"

#define KEY_PORT	(PORTD)
#define KEY_DDR		(DDRD)
#define KEY_PIN		(PIND)
// 7-4 bit - rows [4 - top] (input), 3-0 bit - columns [0 - left] (shifted 0)

typedef enum
{
	KEY_1 =		0xEE,
	KEY_2 =		0xED,
	KEY_3 =		0xEB,
	KEY_4 =		0xDE,
	KEY_5 =		0xDD,
	KEY_6 =		0xDB,
	KEY_7 =		0xBE,
	KEY_8 =		0xBD,
	KEY_9 =		0xBB,
	KEY_STAR =	0x7E,
	KEY_0 =		0x7D,
	KEY_DIEZ =	0x7B,
} Keys_e;

void Key_Init();
void Key_EVENT_OnButtonPushed(uint8_t key);

#endif /* DRV_KEYBOARD_H_ */