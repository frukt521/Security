#include "Control.h"

uint8_t					keyboardKeyEE[4] EEMEM;
uint64_t				iButtonKeysEE[9] EEMEM;

volatile uint8_t		keyboardKey[4]		= {KEY_STAR, KEY_7, KEY_7, KEY_7};
volatile uint64_t		iButtonKeys[9]		= {0,0,0,0,0,0,0,0,0};
volatile KeyBuffer_t	keyBuffer			= {{0,0,0,0,0,0,0}, 0};
volatile bool			keyIsCurrentChange	= false;
const SuperUserCode_t	superUserCodes		= 
{
	{KEY_STAR, KEY_DIEZ, KEY_1, KEY_2, KEY_3, KEY_4, KEY_DIEZ},	//add button key
	{KEY_STAR, KEY_DIEZ, KEY_0, KEY_0, KEY_0, KEY_0, KEY_DIEZ}	//change keyboard key
};


void _Control_SaveKeyboardCode()
{
	for (uint8_t i = 0; i < 4; i++)
		EEPROM_WriteInt8(&keyboardKeyEE[i], keyboardKey[i]);
}

void _Control_LoadSettings()
{
	for (uint8_t i = 0; i < 9; i++)
		iButtonKeys[i] = EEPROM_ReadInt64(&iButtonKeysEE[i]);
	for (uint8_t i = 0; i < 4; i++)
		keyboardKey[i] = EEPROM_ReadInt8(&keyboardKeyEE[i]);
}

void Control_Init()
{
	//Init leds
	LED_DDR |= (1 << LED_GREEN_NUM) | (1 << LED_RED_NUM);
	//Relay for open doors
	RELAY_DDR |= (1 << RELAY_NUM);
	//Init open button
	BUTTON_OPEN_DDR &= ~(1 << BUTTON_OPEN_NUM);
	BUTTON_OPEN_PORT |= (1 << BUTTON_OPEN_NUM);
	//Load keys from eeprom memory
	_Control_LoadSettings();
}

bool Control_CheckIbutton(uint64_t iKey)
{
	for (uint8_t i = 0; i < 9; i++)
		if(iKey == iButtonKeys[i])
			return true;
	return false;
}

void Control_AddIbutton(uint64_t iKey)
{
	if (!Control_CheckIbutton(iKey)) //если ключ не прописан
	{
		for (uint8_t i = 0; i < 9; i++)
			if (iButtonKeys[i] == 0)
			{
				iButtonKeys[i] = iKey;
				EEPROM_WriteInt64(&iButtonKeysEE[i], iButtonKeys[i]);
				return;
			}
		iButtonKeys[0] = iKey;
		EEPROM_WriteInt64(&iButtonKeysEE[0], iButtonKeys[0]);
	}
}

void Control_OpenDoor()
{
	RELAY_PORT |= (1 << RELAY_NUM);
	_delay_ms(3000);
	RELAY_PORT &= ~(1 << RELAY_NUM);
}

bool Control_CheckOpenButton()
{
	return ( (BUTTON_OPEN_PIN & (1 << BUTTON_OPEN_NUM)) == (1 << BUTTON_OPEN_NUM) ? false : true );
}

void _Control_BufferProcess(uint8_t key)
{
	if (key == KEY_STAR)	//Если '*', то начало новой команды
	{
		keyBuffer.posInBuffer = 0;
		for (uint8_t i = 0; i < 7; i++)
			keyBuffer.keys[i] = 0;
		keyBuffer.keys[keyBuffer.posInBuffer] = key;
	}
	else
	{
		keyBuffer.posInBuffer++;
		if (keyBuffer.posInBuffer >= 7) keyBuffer.posInBuffer = 0;
		keyBuffer.keys[keyBuffer.posInBuffer] = key;
	}
}

KeyboardEvent_e Control_CheckKeyboardKey(uint8_t keybKey)
{
	_Control_BufferProcess(keybKey);
	if (keyBuffer.keys[0] == KEY_STAR)	//Если первая '*'
	{
		//Если в данный момент ключ изменяется
		if (keyIsCurrentChange)
		{
			if (keyBuffer.posInBuffer < 3) return KEY_EVENT_NONE;
			//Проверяем на термипнальные символы в новом ключе
			for (uint8_t i = 1; i < 4; i++)
				if ( (keyBuffer.keys[i] == KEY_STAR) || (keyBuffer.keys[i] == KEY_DIEZ))
				{
					keyIsCurrentChange = false;
					return KEY_EVENT_ERROR_CHANGE_KEYBOARD_KEY;
				}
			//Изменям ключ
			for (uint8_t i = 1; i < 4; i++)
				keyboardKey[i] = keyBuffer.keys[i];
			_Control_SaveKeyboardCode();
			keyIsCurrentChange = false;
			return KEY_EVENT_CHANGE_KEYBOARD_KEY_OK;
		}		
		
		//Если вторая '#' - начало команды суперпользователя
		if (keyBuffer.keys[1] == KEY_DIEZ)	
		{
			if (keyBuffer.posInBuffer < 6) return KEY_EVENT_NONE;
			//Проверяем на совпадения с кодами суперпользователя
			bool isAddButt = true;
			bool isAddKey = true;
			for (uint8_t i = 2; i < 7; i++)
			{
				if (keyBuffer.keys[i] != superUserCodes.addIbuttonKey[i]) isAddButt = false;
				if (keyBuffer.keys[i] != superUserCodes.changeKeyboardKey[i]) isAddKey = false;
			}
			if (isAddButt) return KEY_EVENT_ADD_IBUTTON;
			if (isAddKey)
			{
				keyIsCurrentChange = true;
				return KEY_EVENT_CHANGE_KEYBOARD_KEY;
			}
			return KEY_EVENT_NONE;
		}
		
		//Если происходит ввод ключа для открытия
		if (keyBuffer.posInBuffer < 3) return KEY_EVENT_NONE;
		//Проверяем ключ
		for (uint8_t i = 1; i < 4; i++)
			if (keyboardKey[i] != keyBuffer.keys[i]) return KEY_EVENT_NONE;
		return KEY_EVENT_TRUE_KEYBOARD_KEY;
	}
	else
	{
		if (keyIsCurrentChange)
		{
			keyIsCurrentChange = false;
			return KEY_EVENT_ERROR_CHANGE_KEYBOARD_KEY;	
		}
	}
	return KEY_EVENT_NONE;
}