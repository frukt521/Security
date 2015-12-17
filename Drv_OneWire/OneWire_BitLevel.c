#include "OneWire.h"

/* Макросы */
//! Прижать шину к нулю
#define OneWire_SetLow()		do {OneWire_DDR |=  (1 << OneWire_NUM); OneWire_PORT &= ~(1 << OneWire_NUM);} while(0)
//! Отпустить шину
#define OneWire_SetHigh()		do {OneWire_DDR &= ~(1 << OneWire_NUM); OneWire_PORT |=  (1 << OneWire_NUM);} while(0)
#define OneWire_GetPin()		((OneWire_PIN & (1 << OneWire_NUM)) == (1 << OneWire_NUM) ? 1 : 0)
/* ------- */

void OneWire_WriteBit1 (void)
{
	cli();
	OneWire_SetLow();
	_delay_us(OneWire_DELAY_A);
	OneWire_SetHigh();
	_delay_us(OneWire_DELAY_B);
	sei();
}

void OneWire_WriteBit0 (void)
{
	cli();
	OneWire_SetLow();
	_delay_us(OneWire_DELAY_C);
	OneWire_SetHigh();
	_delay_us(OneWire_DELAY_D);
	sei();
}

uint8_t OneWire_ReadBit(void)
{
	uint8_t data = 0;
	cli();
	OneWire_SetLow();
	_delay_us(OneWire_DELAY_A);
	OneWire_SetHigh();
	_delay_us(OneWire_DELAY_E);
	if (OneWire_GetPin() == 1) data = 1;
	_delay_us(OneWire_DELAY_F);
	sei();
	return data;
}

uint8_t OneWire_ResetAndDetectPresence(void)
{
	uint8_t presenceDetected = OneWire_EMPTYBUS;
	cli();
	OneWire_SetLow();
	_delay_us(OneWire_DELAY_H);
	OneWire_SetHigh();
	_delay_us(OneWire_DELAY_I);
	if (OneWire_GetPin() == 0) presenceDetected = OneWire_DEVICEIS;
	_delay_us(OneWire_DELAY_J);
	sei();
	return presenceDetected;
}