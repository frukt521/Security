#include "Drv_EEPROM.h"

void EEPROM_WriteInt8(uint8_t* addr, uint8_t data)
{
	cli();
	eeprom_write_byte(addr, data);
	sei();
}

uint8_t EEPROM_ReadInt8(uint8_t* addr)
{
	uint8_t tmp = 0;
	cli();
	tmp = eeprom_read_byte(addr);
	sei();
	return tmp;
}

void EEPROM_WriteInt64(uint64_t* addr, uint64_t data)
{
	cli();
	eeprom_write_block(&data, addr, sizeof(uint64_t));
	sei();
}

uint64_t EEPROM_ReadInt64(uint64_t* addr)
{
	uint64_t tmp = 0;
	cli();
	eeprom_read_block(&tmp, addr, sizeof(uint64_t));
	sei();
	return tmp;
}