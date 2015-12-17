#include "SmartIndicate.h"

void  SmartIndicate_IndicateProcess(IndicateOrder_t* order, uint8_t stages, uint8_t cycles)
{
	for (uint8_t c = 0; c < cycles; c++)
	{
		for (uint8_t s = 0; s < stages; s++)
		{
			switch(order[s].Led.LedState)
			{
				case LED_ON:
					*order[s].Led.LedPort |= (1 << order[s].Led.LedNumber);
					break;
				case LED_OFF:
					*order[s].Led.LedPort &= ~(1 << order[s].Led.LedNumber);
					break;
			}
			for (uint16_t k = 0; k < order[s].DelayMs; k++)
			{
				_delay_ms(1);
				#ifdef WATCHDOG_ENABLE
					wdt_reset();
				#endif
			}
		}
	}
	
}
