#include "Leds.h"
	
IndicateOrder_t Indicate_G10_1_1[1] = //Green 1000ms: Cycle x1 = DOOR_OPEN;
{
	{{LED_ON, &LED_PORT, LED_GREEN_NUM}, 1000}
};

IndicateOrder_t Indicate_R10_1_1[1] = //Red 1000ms: Cycle x1 = ERROR;
{
	{{LED_ON, &LED_PORT, LED_RED_NUM}, 1000}
};

IndicateOrder_t Indicate_G2R2G2_5_1[5] = //Green 200ms Red 200ms Green 200ms: Cycle x1 = IBUTTON_WAIT;
{
	{{LED_ON, &LED_PORT, LED_GREEN_NUM}, 200},
	{{LED_OFF, &LED_PORT, LED_GREEN_NUM}, 0},
	{{LED_ON, &LED_PORT, LED_RED_NUM}, 200},
	{{LED_OFF, &LED_PORT, LED_RED_NUM}, 0},
	{{LED_ON, &LED_PORT, LED_GREEN_NUM}, 200}
};

IndicateOrder_t Indicate_R2_2_3[2] = //Red 200ms: Cycle x3 = IBUTTON_WAIT_END;
{
	{{LED_ON, &LED_PORT, LED_RED_NUM}, 200},
	{{LED_OFF, &LED_PORT, LED_RED_NUM}, 200}
};

IndicateOrder_t Indicate_G2_2_Add3Change2[2] = //Green 200ms: Cycle x3 = IBUTTON_ADDED;  Cycle x2 = INDICATE_KEY_CHANGED;
{
	{{LED_ON, &LED_PORT, LED_GREEN_NUM}, 200},
	{{LED_OFF, &LED_PORT, LED_GREEN_NUM}, 200}
};

IndicateOrder_t Indicate_G2R2_3_1[3] = //Green 200ms Red 200ms: Cycle x1 = KEY_WAIT;
{
	{{LED_ON, &LED_PORT, LED_GREEN_NUM}, 200},
	{{LED_OFF, &LED_PORT, LED_GREEN_NUM}, 0},
	{{LED_ON, &LED_PORT, LED_RED_NUM}, 200}
};

uint8_t ledsState[2] = {0, 0};

void _Leds_StoreState(void)
{
	ledsState[0] = (LED_PORT & (1 << LED_RED_NUM));
	ledsState[1] = (LED_PORT & (1 << LED_GREEN_NUM));
}

void _Leds_RestoreState(void)
{
	LED_PORT ^= (ledsState[0] | ledsState[1]);
}

void Leds_Init(void)
{
	LED_DDR |= (1 << LED_RED_NUM) | (1 << LED_GREEN_NUM);
}

void Leds_Switch(LedsList_e led, LedStates_e state)
{
	switch (state)
	{
		case LED_ON:
			switch (led)
			{
				case LED_RED:
					LED_PORT |= (1 << LED_RED_NUM);
					break;
				case LED_GREEN:
					LED_PORT |= (1 << LED_GREEN_NUM);
					break;
			}
			break;
		case LED_OFF:
			switch (led)
			{
				case LED_RED:
					LED_PORT &= ~(1 << LED_RED_NUM);
					break;
				case LED_GREEN:
					LED_PORT &= ~(1 << LED_GREEN_NUM);
					break;
			}
			break;
	}
}

void Leds_Indicate(Indicate_e indicate)
{
	_Leds_StoreState();
	Leds_Switch(LED_RED, LED_OFF);
	Leds_Switch(LED_GREEN, LED_OFF);
	
	switch (indicate)
	{
		case INDICATE_DOOR_OPEN:
			SmartIndicate_IndicateProcess(Indicate_G10_1_1, 1, 1);
			break;
		case INDICATE_ERROR:
			SmartIndicate_IndicateProcess(Indicate_R10_1_1, 1, 1);
			break;
		case INDICATE_IBUTTON_WAIT:
			SmartIndicate_IndicateProcess(Indicate_G2R2G2_5_1, 3, 1);
			break;
		case INDICATE_IBUTTON_WAIT_END:
			SmartIndicate_IndicateProcess(Indicate_R2_2_3, 2, 3);
			break;
		case INDICATE_IBUTTON_ADDED:
			SmartIndicate_IndicateProcess(Indicate_G2_2_Add3Change2, 2, 3);
			break;
		case INDICATE_KEY_WAIT:
			SmartIndicate_IndicateProcess(Indicate_G2R2_3_1, 3, 1);
			break;
		case INDICATE_KEY_CHANGED:
			SmartIndicate_IndicateProcess(Indicate_G2_2_Add3Change2, 2, 2);
			break;
	}
	_Leds_RestoreState();
}