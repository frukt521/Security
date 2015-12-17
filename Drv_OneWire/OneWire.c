#include "OneWire.h"

void OneWire_Init(void)
{
	// input
	OneWire_DDR  &= ~(1 << OneWire_NUM);
	OneWire_PORT |=  (1 << OneWire_NUM);
	
	_delay_us(OneWire_DELAY_H);
}

void OneWire_SendByte(uint8_t data)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if ((data & 0x01) == 1)
			OneWire_WriteBit1();
		else
			OneWire_WriteBit0();
	    data >>= 1;
	}
}

uint8_t OneWire_ReceiveByte(void)
{
	uint8_t data = 0;
	for (uint8_t i = 0; i < 8; i++)
		data |= (OneWire_ReadBit() << i);
	return data;
}

uint64_t OneWire_ReadRom(void)
{
	uint64_t addr = 0;
	// отправка команды
	OneWire_SendByte(OneWire_READ_ROM_CMD);
	//чтение
	for (uint8_t i = 0 ; i < 8; i++)
	{
		// младший байт вперед
		addr |= (((uint64_t)OneWire_ReceiveByte()) << (i * 8));
	}
	return addr;
}

void OneWire_MatchRom(uint64_t addr)
{
	// отправка команды
	OneWire_SendByte(OneWire_MATCH_ROM_CMD);
	for (unsigned char i = 0 ; i < 8; i++)
	{
		// младший байт вперед
		OneWire_SendByte((unsigned char)(addr >> (i*8)));
	}
}

void OneWire_SkipRom(void)
{
	// отправка команды
	OneWire_SendByte(OneWire_SKIP_ROM_CMD);
}
/*void OneWire_SearchRom()
{
	// TODO: реализовать
}*/