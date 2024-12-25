#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ap/FAN/FAN.h"
#include "ap/TIMER/TIMER.h"

uint8_t decide_LCD = 0;
uint8_t timer_state = 0;
ISR(TIMER0_OVF_vect)
{
	FND_ISR_Process();
	TCNT0 = 120;
}

ISR(USART0_RX_vect)
{
	UART0_ISR_Process();
}

ISR(TIMER2_COMP_vect)
{
	Timer_inMilisec();
	Fan_AutoTimer();
}

int main(void)
{
	Fan_init();
	Timer_init();
	sei();

	uint8_t timer_up = 0;
	uint8_t timer_down = 0;


	while (1)
	{
		uint8_t prevDecide_LCD = 0;
		Fan_execute();
		if (button_getstate(&btnTimerInc)==ACT_RELEASED)
		{
			timer_state = 1;
		}
	if (timer_state)
	{	
		if (button_getstate(&btnTimerInc)==ACT_RELEASED)
		{
			timer_up = 1;
		}
		else if(button_getstate(&btnTimerDic)==ACT_RELEASED)
		{
			timer_down = 1;
		}
		Timer_run(&timer_up, &timer_down);
	}
		
		if (decide_LCD != prevDecide_LCD)
		{
			Timer_LCDData();
		}
		else
		{
			Fan_LCDData();
		}
		
		
		
	}
}

