
#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../periph/GPIO/GPIO.h"

enum{PUSHED,RELEASED};
enum{ACT_PUSHED, ACT_RELEASED ,ACT_NONE};

typedef struct _button{
	volatile uint8_t *DDR;
	volatile uint8_t *PIN;
	uint8_t pS;
	uint8_t pinNum;
}button_t;


void Button_init(button_t *btn, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinnum);
uint8_t button_getstate(button_t *btn);

#endif /* BUTTON_H_ */

