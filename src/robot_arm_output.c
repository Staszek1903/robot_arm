#include "../inc/robot_arm_output.h"

void initOutput()
{
//LCD
	LCD_init();
	
	LCD_DisplayControl(-1,0,0);
	LCD_clear();
	
//PWM

	PWM0_init();
	PWM2_init();
	
	ArmState state = {135,135,135,135};
	
	setArmState(state);
}

void binprint(uint8_t data)
{
	LCD_data('<');
	for(uint8_t i=0; i<8; ++i)
		LCD_data((data&(1<<(7-i)))? '1':'0');
	LCD_data('>');
}

void decprint(uint16_t num)
{
	if(num == 0)
	{
		LCD_data('0');
		return;
	}
	
	uint8_t i = 0;
	char tab[16];
	while(num != 0)
	{
		tab[i] = num%10;
		num/=10;
		i++;
	}
	
	while(i != 0)
	{
		i--;
		LCD_data(tab[i] + 48);
	}
}

uint16_t stoi(const char * tab, uint8_t size)
{
	uint16_t result =0;
	for(uint8_t i=0; i<size; ++i)
	{
		result *=10;
		result += tab[i] -48;
	}
	
	return result;
}

void printJoistick(uint8_t x, uint8_t y)
{
	static uint8_t prev_x =0;
	static uint8_t prev_y =0;
	
	if(prev_x != x)
	{
		prev_x = x;
		LCD_setDDaddr(0x0);
		LCD_print("X:    ");
		LCD_setDDaddr(0x3);
		decprint(x);
	}
	if(prev_y != y)
	{
		prev_y = y;
		LCD_setDDaddr(0x8);
		LCD_print("Y:    ");
		LCD_setDDaddr(0xb);
		decprint(y);
	}
}


void clear_eeprom()
{
	EEPROM_write(0,0);
	EEPROM_write(1,0);
	
	LCD_setDDaddr(0x0);
	LCD_print("                ");
	LCD_setDDaddr(0x0);
	LCD_print("Memory cleared");
	_delay_ms(10000);
	LCD_setDDaddr(0x0);
	LCD_print("                ");	
}

void save_state(ArmState state)
{
	const uint8_t size = 4;
	
	uint16_t index = EEPROM_read(0);
	index <<= 8;
	index |= EEPROM_read(1);
	uint16_t addr = (index*size)+2;
	
	EEPROM_write(addr,state.rotation);
	addr++;
	EEPROM_write(addr,state.arm);
	addr++;
	EEPROM_write(addr,state.fore_arm);
	addr++;
	EEPROM_write(addr,state.hand);
	
	
	LCD_setDDaddr(0x0);
	LCD_print("                ");
	LCD_setDDaddr(0x0);
	LCD_print("Saved to: ");
	decprint(index);
	_delay_ms(10000);
	LCD_setDDaddr(0x0);
	LCD_print("                ");
	
	index++;
	
	EEPROM_write(0, index>>8);
	EEPROM_write(1, index&0xff);
}

ArmState revive_state(uint16_t index)
{
	const uint8_t size = 4;
	ArmState temp_state;
	
	uint16_t addr = (index*size)+2;
	
	temp_state.rotation = EEPROM_read(addr);
	addr++;
	temp_state.arm = EEPROM_read(addr);
	addr++;
	temp_state.fore_arm = EEPROM_read(addr);
	addr++;
	temp_state.hand = EEPROM_read(addr);
	
	LCD_setDDaddr(0x0);
	LCD_print("                ");
	LCD_setDDaddr(0x0);
	LCD_print("revived: ");
	decprint(index);
	_delay_ms(10000);
	LCD_setDDaddr(0x0);
	LCD_print("                ");
	
	return temp_state;	
}

void execute_steps()
{
	uint16_t end_index = EEPROM_read(0);
	end_index <<= 8;
	end_index |= EEPROM_read(1);
	ArmState state;
		
	LCD_setDDaddr(0x0);
	LCD_print("executing:      ");
	LCD_setDDaddr(0x40);
	LCD_print("out of ");
	binprint(end_index);
	LCD_print(" steps");
	
	for(uint16_t i =0; i<end_index; ++i)
	{
		LCD_setDDaddr(0xb);
		decprint(i+1);
		LCD_print("       ");
		state = revive_state(i);
		setArmState(state);
		_delay_ms(500);
	}
}
