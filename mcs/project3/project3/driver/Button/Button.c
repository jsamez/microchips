#include "Button.h"


void Button_init(button_t *btn, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinnum){
	btn ->DDR =ddr;
	btn->PIN = pin;
	btn->pinNum = pinnum;
	btn->pS = 1;
	*btn->DDR &= ~(1<<btn->pinNum);
	
}

uint8_t button_getstate(button_t *btn){
	
	uint8_t curState = *btn->PIN &(1<<btn->pinNum);
	if ((curState == 0) &&(btn->pS = 1)){
		_delay_ms(10);
		btn->pS = PUSHED;
		
		
		return ACT_PUSHED;
	}
	else if ((curState != 0 )&&(btn->pS == 0)){
		_delay_ms(10);
		btn->pS = RELEASED;
		return ACT_RELEASED;
	}
	
	return ACT_NONE;
}