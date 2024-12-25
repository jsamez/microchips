#include "STOPWATCH.h"

button_t btnMode;
uint16_t counter;
uint8_t StopwatchState;

void StopWatch_init(){
	FND_init();
	Button_init(&btnMode, &DDRA, &PINA, 0);
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