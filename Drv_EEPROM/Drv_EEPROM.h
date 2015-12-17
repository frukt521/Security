#ifndef DRV_EEPROM_H_
#define DRV_EEPROM_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

void EEPROM_WriteInt8(uint8_t* addr, uint8_t data);
void EEPROM_WriteInt64(uint64_t* addr, uint64_t data);
uint8_t EEPROM_ReadInt8(uint8_t* addr);
uint64_t EEPROM_ReadInt64(uint64_t* addr);


#endif /* DRV_EEPROM_H_ */