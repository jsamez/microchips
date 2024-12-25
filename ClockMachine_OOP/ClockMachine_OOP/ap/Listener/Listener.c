#include "Listener.h"

button_t btnRunStop,btnReset,btnTimeclock,btnTimclocpisph;

void Listener_init(){
	Button_init(&btnRunStop,&DDRA,&PINA,0);
	Button_init(&btnReset,&DDRA,&PINA,1);
	Button_init(&btnTimeclock,&DDRA,&PINA,2);
	Button_init(&btnTimclocpisph,&DDRA,&PINA,4);
}

void Listener_eventCheck(){
	uint8_t Mode;
	Mode = Model_getTimeModeData();
	
	if(Mode == stopwatch ){
		Listener_StopWatchEvent();
		}
	else
	{
		Listener_TimeClockEvent();
	}
	
	
}

void Listener_StopWatchEvent(){
	
	uint8_t StopWatchState;
	StopWatchState = Model_getStopWatchData();
	
	switch(StopWatchState)
	{
		case STOP:
		if (button_getstate(&btnRunStop) == ACT_RELEASED)
		{
			StopWatchState = RUN;
			Model_setStopWatchData(StopWatchState);
		}
		else if (button_getstate(&btnReset) == ACT_RELEASED){
			StopWatchState = RESET;
			Model_setStopWatchData(StopWatchState);
		}
		break;
		
		case RUN:
		if (button_getstate(&btnRunStop) == ACT_RELEASED)
		{
			StopWatchState = STOP;
			Model_setStopWatchData(StopWatchState);
		}
		break;
		
		case RESET:
		{
			StopWatchState = STOP;
			Model_setStopWatchData(StopWatchState);
		}
		break;
	}
	
}

void Listener_TimeClockEvent(){
	uint8_t TimeClockState, TimeClockPisp;
	TimeClockState = Model_getTimeModeData();
	TimeClockPisp = Model_getTimeClockData();
	
	switch(TimeClockState)
	{
		case stopwatch:
		if (button_getstate(&btnTimeclock) == ACT_RELEASED)
		{
			TimeClockState = timeclock;
			Model_setStopWatchData(TimeClockState);
		}
		
		break;
		
		case timeclock:
		if (button_getstate(&btnTimeclock) == ACT_RELEASED)
		{
			TimeClockState = stopwatch;
			Model_setStopWatchData(TimeClockState);
		}
		else if (button_getstate(&btnTimclocpisph) == ACT_RELEASED)
		{
			TimeClockPisp = s_m;
			Model_setTimeClockData(TimeClockPisp);
			
		}
		else if (button_getstate(&btnTimclocpisph) == ACT_RELEASED)
		{
			TimeClockPisp = h_m;
			Model_setTimeClockData(TimeClockPisp);
			
		}
		break;

	}
}