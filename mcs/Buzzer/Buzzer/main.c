#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "driver/Buzzer/Buzzer.h"


int main(void)
{
	
	Buzzer_init();
	
	while (1)
	{
		Buzzer_buttonOn();
	}
}

