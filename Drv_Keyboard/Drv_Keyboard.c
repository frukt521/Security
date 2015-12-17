#include "Drv_Keyboard.h"

volatile uint8_t _shiftCount = 0;

uint8_t _shiftMask[5] =
{
	0xFF & ~(1 << 0),
	0xFF & ~(1 << 1),
	0xFF & ~(1 << 2),
	0xFF & ~(1 << 3)
};


void Key_Init()
{
	Timer0_Init();
	Timer0_Enable();
	KEY_DDR = 0x0F;
	KEY_PORT = 0xFF;
} 

void Timer0_EVENT_OnOvewflow()
{
	// 1/(8000000/1024/255) = 34мс

	//Read current column 
	if ( (KEY_PIN & 0xF0) != 0xF0 )
		Key_EVENT_OnButtonPushed((Keys_e)( (KEY_PIN & 0xF0) | (KEY_PORT & 0x0F) ));
	//Ready to next read
	_shiftCount++;
	if (_shiftCount >=4) _shiftCount = 0;
	KEY_PORT = _shiftMask[_shiftCount];
}
