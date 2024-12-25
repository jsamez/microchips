
#ifndef LEDMACHINE_H_
#define LEDMACHINE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/Button/button.h"
#include "../../driver/Led/led.h"

#define LED_DDR DDRD
#define LED_PORT PORTD
#define BUTTON_DDR DDRA
#define BUTTON_PIN	PINA

#define BUTTON_MODE 0
#define BUTTON_OFF	1

enum {led_off,led1, led2, led3, led4};
	
void standinglight_init();
void standinglight_eventcheck();
void standinglight_run();
void standinglight_execute();
void led_alloff();
void led_tr();
void led_on();

#endif /* LEDMACHINE_H_ */