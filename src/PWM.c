#include "../inc/PWM.h"

void PWM0_init()
{
	DDRD |= (1<<6) | (1<<5);
	PORTD &= ~((1<<6) | (1<<5));	// USTAWIENIA DLA OC0B i OC0A (PD5, PD6)
	
 	TCCR0A = (1<<COM0A1) |  (1<<COM0B1) | ( 1<<WGM00) | (1<<WGM01); 
 	//FAST PWM, clear on compare, set at top A&B
 	
 	OCR0A = 0; //init PWMs
 	OCR0B = 0;
 	
 	TCCR0B =  (1<<CS00) | /*| (1<<CS01) ;| (1<<WGM02); */ (1<<CS02); 
 	// start time Prescaler = 256;
}

void PWM2_init()
{
	
	DDRD |= (1<<3);
	PORTD &= ~(1<<3);
	DDRB |= (1<<3);
	PORTB &= ~(1<<3);	// USTAWIENIA DLA OC2B i OC2A (PD3, PB3)
	
 	TCCR2A = (1<<COM2A1) |  (1<<COM2B1) | ( 1<<WGM20) | (1<<WGM21);
 	//FAST PWM, clear on compare, set at top A&B
 	
 	OCR2A = 0; //init PWMs
 	OCR2B = 0;
 	
 	TCCR2B =  (1<<CS20) |  (1<<CS21) | (1<<CS22); 
 	// start time Prescaler = 256;
}

void PWM_setval0A(uint8_t val)
{
	OCR0A = val;
}

void PWM_setval0B(uint8_t val)
{
	OCR0B = val;
}

void PWM_setval2A(uint8_t val)
{
	OCR2A = val;
}
void PWM_setval2B(uint8_t val)
{
	OCR2B = val;
}
