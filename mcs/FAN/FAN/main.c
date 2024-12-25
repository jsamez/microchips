#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ap/FAN/FAN.h"

ISR(TIMER2_COMP_vect){
	Fan_AutoTimer();
}

int main(void)
{
	sei();
    Fan_init();
    while (1) 
    {
		Fan_execute();
    }
}

