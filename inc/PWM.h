#ifndef PWH_H_
#define PWM_H_

#include <avr/io.h>

void PWM0_init();
void PWM2_init();
void PWM_setval0A(uint8_t val);
void PWM_setval0B(uint8_t val);
void PWM_setval2A(uint8_t val);
void PWM_setval2B(uint8_t val);

#endif /*PWM_H_ */
