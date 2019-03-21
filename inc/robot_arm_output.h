#ifndef ROBOT_ARM_OUTPUT_H_
#define ROBOT_ARM_OUTPUT_H_

#define F_CPU 1000000UL
#include <util/delay.h>

#include "../inc/LCD.h"
#include "../inc/PWM.h"
#include "../inc/arm_state.h"
#include "../inc/EEPROM.h"

void initOutput();

//LCD
void binprint(uint8_t data);
void decprint(uint16_t num);
uint16_t stoi(const char * tab, uint8_t size);
void printJoistick(uint8_t x, uint8_t y);

//SERVO
uint8_t servoNormalize(uint8_t val);
void setRotation(uint8_t val);
void setArm(uint8_t val);
void setForeArm(uint8_t val);
void setHand(uint8_t val);
void setArmState(ArmState state);

void clear_eeprom();
void save_state(ArmState state);
ArmState revive_state(uint16_t index);
void execute_steps();


#endif /*ROBOT_ARM_OUTPUT_H_ */
