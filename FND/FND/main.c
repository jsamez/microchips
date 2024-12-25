#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "driver/FND/FND.h"
#include "periph/TIM/TIM.h"

ISR(TIMER0_OVF_vect){
	FND_ISR_Process();
	TCNT0 = 130;
}

int main(void)
{

	FND_init();
	TIM0_init();
	sei();

	uint16_t counter =0;
	
	while (1)
	{
		FND_setFndData(counter++);
		_delay_ms(1000);
	}
}

