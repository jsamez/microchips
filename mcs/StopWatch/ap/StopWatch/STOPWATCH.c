#include "STOPWATCH.h"

button_t btnMode, btnReset;
uint16_t counter;
uint8_t StopwatchState;

void StopWatch_init(){
	FND_init();
	Button_init(&btnMode, &DDRA, &PINA, 0);
	Button_init(&btnReset, &DDRA, &PINA, 1);
	counter = 0;
	StopwatchState = Stop;
}

void StopWatch_run(){
	switch (StopwatchState){
		
		case Stop:
		FND_ISR_Process();
		if(button_getstate(&btnMode) == ACT_RELEASED)
		{
			StopwatchState = Start;
		}
		else if (button_getstate(&btnReset) == ACT_RELEASED)
		{
			counter = 0;
			FND_setFndData(counter);
		}
		break;
		
		case Start:
		FND_ISR_Process();
		FND_setFndData(counter++);
		if(button_getstate(&btnMode) == ACT_RELEASED)
		{
			StopwatchState = Stop;
		}
		break;
		_delay_ms(100);
	}
	
}