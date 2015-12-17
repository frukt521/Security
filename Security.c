#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Control/Control.h"
#include "Drv_OneWire/OneWire.h"
#include "Drv_Keyboard/Drv_Keyboard.h"

void Key_EVENT_OnButtonPushed(uint8_t key) //Клавиатура отключается во время обработки
{
	cli();
	KeyboardEvent_e currKey = Control_CheckKeyboardKey(key);
	switch (currKey)
	{
		case KEY_EVENT_NONE:
			break;
			
		case KEY_EVENT_ADD_IBUTTON:
			Leds_Indicate(INDICATE_IBUTTON_WAIT);
			for (uint8_t i = 0; i < 255; i++)	//Ожидание ключа I-Button
			{
				if (OneWire_ResetAndDetectPresence() == OneWire_DEVICEIS)
				{
					Control_AddIbutton(OneWire_ReadRom());
					Leds_Indicate(INDICATE_IBUTTON_ADDED);										
					break;
				}
				_delay_ms(50);
			}
			Leds_Indicate(INDICATE_IBUTTON_WAIT_END);
			break;
			
		case KEY_EVENT_TRUE_KEYBOARD_KEY:
			Control_OpenDoor();
			Leds_Indicate(INDICATE_DOOR_OPEN);
			break;
			
		case KEY_EVENT_CHANGE_KEYBOARD_KEY:
			Leds_Indicate(INDICATE_KEY_WAIT);
			break;
			
		case KEY_EVENT_CHANGE_KEYBOARD_KEY_OK:
			Leds_Indicate(INDICATE_KEY_CHANGED);
			break;
			
		case KEY_EVENT_ERROR_CHANGE_KEYBOARD_KEY:
			Leds_Indicate(INDICATE_ERROR);
			break;
	}
	sei();
}

int main(void)
{
	OneWire_Init();
	Key_Init();
	Control_Init();
	sei();

	while(1)
    {
		if (OneWire_ResetAndDetectPresence() == OneWire_DEVICEIS)	//Подключена iButton?
		{				
			if (Control_CheckIbutton(OneWire_ReadRom()))	//Ключ верный?
			{
				Control_OpenDoor();
				Leds_Indicate(INDICATE_DOOR_OPEN);				
			}
			else
				Leds_Indicate(INDICATE_ERROR);
		}
		if (Control_CheckOpenButton())	//Нажата кнопка?
		{
			Control_OpenDoor();
			Leds_Indicate(INDICATE_DOOR_OPEN);
			
		}
		_delay_ms(100);
    }
}