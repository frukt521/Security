#include "Drv_Timer0.h"

void Timer0_Init()
{
	TCCR0 &= ~(1 << WGM00) & ~(1 << WGM01) & ~(1 << FOC0);
	TIMSK |= (1 << TOIE0); 
	TCCR0 = 0;											
}

ISR (TIMER0_OVF_vect)
{
	Timer0_EVENT_OnOvewflow();
}

void Timer0_Enable()
{
	/*
	CS02	CS01	CS00 
	0		0		0		stopped
	0		0		1		F/1
	0		1		0		F/8
	0		1		1		F/64
	1		0		0		F/256
	1		0		1		F/1024
	1		1		0		Ext clk TO, falling edge
	1		1		1		Ext clk TO, rising edge
	*/
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TCCR0 &= ~(1 << CS01); 
}

void Timer0_Disable()
{
	TCCR0 &= ~(1 << CS02) & ~(1 << CS01) & ~(1 << CS00);
}

