#include "LED.h"

void LED_init(){
	LED_DDR = 0xff;
	
}

//LED all off
void LED_allOFF(){
	LED_PORT = 0x00;
	
}

void LED_allON(){
	LED_PORT = 0xff;
	
}

void LED_WriteData(uint8_t data){
	LED_PORT = data;
}