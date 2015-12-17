#ifndef _ONEWIRE_BITLEVEL_H_
#define _ONEWIRE_BITLEVEL_H_

#include "avr/interrupt.h"

/* Задержки в us */
#define OneWire_DELAY_A		6
#define OneWire_DELAY_B		64
#define OneWire_DELAY_C		60
#define OneWire_DELAY_D		10
#define OneWire_DELAY_E		9
#define OneWire_DELAY_F		55
#define OneWire_DELAY_G		0
#define OneWire_DELAY_H		480
#define OneWire_DELAY_I		70
#define OneWire_DELAY_J		410
/* ------------- */

#define OneWire_EMPTYBUS		(0)
#define OneWire_DEVICEIS		(1)
	
//! Передача логического нуля по шине
void OneWire_WriteBit0 (void);
//! Передача логической единицы по шине
void OneWire_WriteBit1 (void);
//! Чтение бита от устройств на шине
//! return: искомый бит в старшем разряде
uint8_t OneWire_ReadBit (void);
//! Сброс и проверка, есть ли устройство на шине
//! return: 0 младшем бите, если есть; 1, если нет)
uint8_t OneWire_ResetAndDetectPresence(void);

#endif /* ONEWIRE_BITLEVEL_H_ */