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
	
	switch(Mode){
		case timeclock:
		Listener_TimeClockEvent();
		if(button_getstate(&btnTimeclock) == ACT_RELEASED){
			Model_setTimeModeData(stopwatch);
		}
		break;
		case stopwatch:
		Listener_StopWatchEvent();
		if(button_getstate(&btnTimeclock) == ACT_RELEASED){
			Model_setTimeModeData(timeclock);
		}
		break;
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
	uint8_t TimeClockPisp;
	TimeClockPisp = Model_getTimeClockData();
	switch (TimeClockPisp)
	{
		case h_m:
		if (button_getstate(&btnTimclocpisph) == ACT_RELEASED)
		{
			TimeClockPisp =s_m;
			Model_setTimeModeData(TimeClockPisp);
		}
		break;
		
		case s_m:
		if (button_getstate(&btnTimclocpisph) == ACT_RELEASED)
		{
			TimeClockPisp = h_m;
			Model_getTimeModeData(TimeClockPisp);
		}
		break;
		
	}
	

}