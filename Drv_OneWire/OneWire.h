/*  
	DATASHEET: AVR318: Dallas 1-Wire® master 
	(http://www.atmel.com/images/doc2579.pdf)
*/

#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

#include <avr/io.h>
#include <util/delay.h>
#include "OneWire_BitLevel.h"

/* Configure */
#define OneWire_DDR			(DDRB)
#define OneWire_PORT		(PORTB)
#define OneWire_PIN			(PINB)
#define OneWire_NUM			4
/* --------- */

/* Cmd numb */
#define OneWire_READ_ROM_CMD		(0x33)
#define OneWire_SKIP_ROM_CMD		(0xCC)
#define OneWire_MATCH_ROM_CMD		(0x55)
#define OneWire_SEARCH_ROM_CMD		(0xF0)
/* -------- */

//! Инициализация OneWire пина
//! Вызывается один раз до любого использования шины
void OneWire_Init(void);

//! Отправка байта данных @data по шине
void OneWire_SendByte(uint8_t data);
//! Получение байта данных return по шине
uint8_t OneWire_ReceiveByte(void);

//uint64_t OneWire_SearchRom(void);

//! Считывание серийного номера устройства (адреса)
//! Используется только если на шине одно устройство
//! return: серийный номер устройства (адрес)
uint64_t OneWire_ReadRom(void);

//! Выбор всех устройств
//! Удобен при наличии только одного устройства на шине
//! Так как позволяет передавать данные без адресов
void OneWire_SkipRom(void);

//! Выбор устройства по адресу @addr
void OneWire_MatchRom(uint64_t addr);

// Протокол работы с устройствами:
// Сброс: OneWire_ResetAndDetectPresence();
// Выбор устройства
// Команды устройства
// Когда потребуется новое устройство - сначала

#endif /* _ONEWIRE_H_ */