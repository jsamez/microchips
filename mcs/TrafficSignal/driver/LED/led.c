#include "LED.h"

void LED_init(){
	LED_DDR = 0xff;
	
}


void LED_WriteData(uint8_t data){
	LED_PORT = data;
}