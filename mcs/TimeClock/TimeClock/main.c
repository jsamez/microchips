#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ap/TimeClock/timeClock.h"

ISR(TIMER0_OVF_vect){
	FND_ISR_Process();
	TCNT0 = 130;
}

ISR(TIMER2_COMP_vect){
	timClock_inMilisec();
}


int main(void)
{
	sei();
	
	TimeClock_init();
	
    while (1) 
    {
		timeClock_excute();
    }
}

