#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ap/StopWatch/STOPWATCH.h"


ISR(TIMER0_OVF_vect){
	FND_ISR_Process();
	TCNT0 = 130;
}

int main(void)
{
	StopWatch_init();
	
    while (1) 
    {
		StopWatch_run();
    }
}

