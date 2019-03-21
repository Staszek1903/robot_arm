/*
 *	AVR analog digital converter driver
 */
 
#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

// DEFINE ISR(ADC_vector)!!!!!!!!!!

void ADC_init(uint8_t chanel_mask);
void ADC_chanel_select(uint8_t chanel);
uint8_t ADC_get_chanel();
void ADC_start();
 
#endif /*ACD_H_*/
 
 
 
