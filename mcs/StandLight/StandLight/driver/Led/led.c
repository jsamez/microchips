#include "LED.h"

void LED_init(volatile uint8_t *DDR){
	
	Gpio_initPort(DDR,OUTPUT);
	
}

void LED_ALLOFF(volatile uint8_t *PORT){
	Gpio_writePort(PORT, 0b00000000);
	
}

void LED_WriteData(volatile uint8_t *PORT,uint8_t data){
	Gpio_writePort(PORT, data);
}