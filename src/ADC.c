#include "../inc/ADC.h"

void ADC_init(uint8_t chanels_mask)
{
	DDRC &= ~chanels_mask;
	PORTC &= ~chanels_mask;
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}

void ADC_chanel_select(uint8_t chanel)
{
	if(chanel > 0b1111)
		chanel = 0;
		
	uint8_t mux = ADMUX;
	mux &= 0b11110000;
	mux |= chanel;
	ADMUX = mux;
}

uint8_t ADC_get_chanel()
{
	uint8_t mux = ADMUX;
	mux &= 0x0f;
	return mux;
}

void ADC_start()
{
	ADCSRA |= (1<<ADSC);
}


