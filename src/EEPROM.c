#include "../inc/EEPROM.h"

void EEPROM_wait()
{
	while(EECR & (1<<EEPE)){}
}

void EEPROM_write(uint16_t address, uint8_t data)
{
	EEPROM_wait();
	EEAR = address;
	EEDR = data;
	EECR |= (1<<EEMPE);
	EECR |= (1<<EEPE);
}

uint8_t EEPROM_read(uint16_t address)
{
	EEPROM_wait();
	EEAR = address;
	EECR |= (1<<EERE);
	return EEDR;
}

void EEPROM_writeArray(uint16_t address, void * array, uint8_t byte_size)
{
	uint8_t * data_array = (uint8_t*)array;
	
	for(uint8_t i=0; i<byte_size; ++i)
	{
		uint8_t data = data_array[i];
		EEPROM_write(address, data);
		++address;
	}
}

void EEPROM_readArray(uint16_t address, void * array, uint8_t byte_size)
{
	uint8_t * data_array = (uint8_t*)array;
	for(uint8_t i=0; i<byte_size; ++i)
	{
		uint8_t data = EEPROM_read(address);
		data_array[i] = data;
		++address;
	}
}
