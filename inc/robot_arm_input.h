#ifndef ROBOT_ARM_INPUT_H_
#define ROBOT_ARM_INPUT_H_



#include "../inc/ADC.h"
#include "../inc/robot_arm_output.h"



extern ArmState state;

void initInput();
uint8_t getJoistickX();
uint8_t getJoistickY();
uint8_t getJoistickB();

#endif /*ROBOT_ARM_INPUT_H_ */
