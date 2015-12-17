#ifndef CONTROL_H_
#define CONTROL_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/eeprom.h>
#include "../Drv_Keyboard/Drv_Keyboard.h"
#include "../Drv_EEPROM/Drv_EEPROM.h"
#include "../Indicate/Leds.h"

#define BUTTON_OPEN_PORT	(PORTB)
#define BUTTON_OPEN_DDR		(DDRB)
#define BUTTON_OPEN_PIN		(PINB)
#define BUTTON_OPEN_NUM		2

#define RELAY_PORT			(PORTB)
#define RELAY_DDR			(DDRB)
#define RELAY_NUM			(3)

typedef struct
{
	uint8_t addIbuttonKey[7];
	uint8_t changeKeyboardKey[7];
} SuperUserCode_t;

typedef struct
{
	uint8_t keys[7];
	uint8_t posInBuffer;	
} KeyBuffer_t;

typedef enum
{
	KEY_EVENT_NONE,							//По нажатию любой кнопки
	KEY_EVENT_ADD_IBUTTON,					//Команда добавления I-Button
	KEY_EVENT_TRUE_KEYBOARD_KEY,			//Введеный ключ подствержден
	KEY_EVENT_CHANGE_KEYBOARD_KEY,			//Команда изменения ключа
	KEY_EVENT_CHANGE_KEYBOARD_KEY_OK,		//Ключ успешно изменен
	KEY_EVENT_ERROR_CHANGE_KEYBOARD_KEY		//Ошибка изменения ключа
} KeyboardEvent_e;

void Control_Init();
bool Control_CheckIbutton(uint64_t iKey);
void Control_AddIbutton(uint64_t iKey);
void Control_OpenDoor();
void Control_Indicate(Indicate_e indicate);
bool Control_CheckOpenButton();
KeyboardEvent_e Control_CheckKeyboardKey(uint8_t keyboardKey);


#endif /* CONTROL_H_ */