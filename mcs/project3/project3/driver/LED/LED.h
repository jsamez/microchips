#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR  DDRD
#define LED_PORT PORTD

void LED_init();
void LED_allOFF();
void LED_allON();
void LED_WriteData(uint8_t data);

#endif /* LED_H_ */