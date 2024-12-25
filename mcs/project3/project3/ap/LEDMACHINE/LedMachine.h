
#ifndef LEDMACHINE_H_
#define LEDMACHINE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/Button/Button.h"
#include "../../driver/LED/LED.h"

enum {led1, led2, led3, led4};
	
void LEDMACHINE_init();
void LedMachine_execute();
void led1_blink();
void led2_blink();
void led3_blink();
void led4_blink();


#endif /* LEDMACHINE_H_ */