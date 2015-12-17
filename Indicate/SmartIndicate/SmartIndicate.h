#ifndef SMARTINDICATE_H_
#define SMARTINDICATE_H_

#include <avr/io.h>
#include <util/delay.h>

#define INDICATE_MAX_ORDER_STAGES	8
#define WATCHDOG_ENABLE

#ifdef WATCHDOG_ENABLE
	#include <avr/wdt.h>
#endif

typedef enum
{
	LED_ON,
	LED_OFF
} LedStates_e;

typedef struct
{
	LedStates_e LedState;
	volatile uint8_t* LedPort;
	uint8_t LedNumber;
} IndicateLed_t;

typedef struct 
{
	IndicateLed_t Led;
	uint16_t DelayMs;
} IndicateOrder_t;

void  SmartIndicate_IndicateProcess(IndicateOrder_t* order, uint8_t stages, uint8_t cycles);

#endif /* SMARTINDICATE_H_ */