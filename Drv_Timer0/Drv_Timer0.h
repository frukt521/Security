#ifndef DRV_TIMER0_H_
#define DRV_TIMER0_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void Timer0_Init();
void Timer0_Enable();
void Timer0_Disable();
void Timer0_EVENT_OnOvewflow();


#endif /* DRV_TIMER0_H_ */