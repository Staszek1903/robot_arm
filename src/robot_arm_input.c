#include "../inc/robot_arm_input.h"

uint8_t x_axis =0;
uint8_t y_axis =0;
uint8_t mode =255;
uint8_t change_counter = 0;

ArmState state = {125,125,125,125};


ISR(ADC_vect)
{
	uint8_t temp = (ADC>>2);
	if(ADC_get_chanel() == 4){
		x_axis = temp;
		ADC_chanel_select(5);
	}
	else if(ADC_get_chanel() == 5){
		y_axis = temp;
		ADC_chanel_select(4);
	}
	
	
	uint8_t pressed = getJoistickB();
	if(mode && pressed) mode = 0;
	else if(!mode && pressed) mode=255;
			
	change_counter++;
	
	if(mode)
	{
		if(change_counter > 20)
		{
			change_counter= 0;
			if(x_axis > 200)
				if(state.rotation<240) state.rotation++;
			if(x_axis < 50)
				if(state.rotation>10) state.rotation--;
			if(y_axis > 200)
				if(state.arm<240) state.arm++;
			if(y_axis < 50)
				if(state.arm>10)  state.arm--;
			
			cli();
			LCD_setDDaddr(0x0);
			printJoistick(state.rotation, state.arm);
			LCD_setDDaddr(0x40);
			LCD_print("   LOWER MODE   ");
			sei();
		}
	}
	else
	{
	
		if(change_counter > 20)
		{
			change_counter= 0;
			if(x_axis > 200)
				if(state.hand<240) state.hand++;
			if(x_axis < 50)
				if(state.hand>10) state.hand--;
			if(y_axis > 200)
				if(state.fore_arm<240) state.fore_arm++;
			if(y_axis < 50)
				if(state.fore_arm>10) state.fore_arm--;
			
			cli();
			LCD_setDDaddr(0x0);
			printJoistick(state.hand, state.fore_arm);
			LCD_setDDaddr(0x40);
			LCD_print("   UPPER MODE   ");
			sei();
		}
	}
	
	setArmState(state);
	
	ADC_start();
}

ISR(PCINT0_vect)
{
	uint8_t data = PINB;
	uint8_t data2 = PIND;
	
	if(!(data&1))
		clear_eeprom();
	if(!(data&2))
		execute_steps();
	if(!(data&4))
		save_state(state);
}


void initInput()
{
	ADC_init(0b11000);
	ADC_chanel_select(4);
	ADC_start();
	
// button init
	DDRD &= ~(1<<4);
	PORTD |= (1<<4);

// interrupts;
	PORTB |= 0b00000111;
	PORTD |= 0b10000000;
	DDRB &= 0b11111000;
	DDRD &= 0b01111111;
	
	PCICR |= (1<<PCIE0);
	PCIFR |= (1<<PCIF0);
	PCMSK0 |= 0b00000111;
}

uint8_t getJoistickX()
{
	return x_axis;
}

uint8_t getJoistickY()
{
	return y_axis;
}

uint8_t getJoistickB()
{
	//DEBOUNCING
	static uint8_t count = 0;
	static uint8_t button_state = 0;
	static uint8_t button_down =0;
	
	if(button_down) button_down =0;
	
	uint8_t current_state = (~PIND & (1<<4)) != 0;
	
	if(current_state != button_state)
	{
		count++;
		if(count >= 100)
		{
			button_state = current_state;
			if(current_state != 0) button_down = 1;
			count = 0;
		}
	}
	else count = 0;
	return button_down;
}
