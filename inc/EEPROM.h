#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>

void EEPROM_wait();
void EEPROM_write(uint16_t address, uint8_t data);
uint8_t EEPROM_read(uint16_t address);
void EEPROM_writeArray(uint16_t address, void * array, uint8_t byte_size);
void EEPROM_readArray(uint16_t address, void * array, uint8_t byte_size);

#endif /* EEPROM_H_ */  
