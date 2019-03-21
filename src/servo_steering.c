#include "../inc/robot_arm_output.h"

uint8_t servoNormalize(uint8_t val)
{
	return (val/18 + 3);
}

void setRotation(uint8_t val)
{
	PWM_setval0A(servoNormalize(val));
}

void setArm(uint8_t val)
{
	PWM_setval0B(servoNormalize(val));
}

void setForeArm(uint8_t val)
{
	PWM_setval2A(servoNormalize(val));
}

void setHand(uint8_t val)
{
	PWM_setval2B(servoNormalize(val));
}

void setArmState(ArmState state)
{
	setRotation(state.rotation);
	setArm(state.arm);
	setForeArm(state.fore_arm);
	setHand(state.hand);
}
