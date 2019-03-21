#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>

#include "../inc/robot_arm_input.h"
#include "../inc/robot_arm_output.h"

int main(void)
{
	clock_prescale_set(clock_div_1);
	
	int change_counter = 0;
	
	initInput();
	initOutput();
	getJoistickB();
	
	sei();
	
	while(1)
	{
		
	}
	
	return 0;
}
