#ifndef ARM_STATE_H_
#define ARM_STATE_H_

#include <avr/io.h>

typedef struct
{
	uint8_t rotation;
	uint8_t arm;
	uint8_t fore_arm;
	uint8_t hand;
} ArmState;

#endif /*ARM_STATE_H_*/
