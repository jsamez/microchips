#include "StopWatch.h"

button_t btnMode,btnReSet;
uint16_t milisec;
uint16_t sec, min, hour;
uint8_t StopWatchState;

void StopWatch_init(){
	
	FND_init();
	TIM0_init();
	TIM2_init();
	Button_init(&btnMode,&DDRA,&PINA,0);
	Button_init(&btnReSet,&DDRA,&PINA,1);
	StopWatchState = STOP;
	milisec = 0;
	sec = 46;
	min = 14;
	hour = 0;
}

void StopWatch_incMilisec(){
	
	if (StopWatchState == RUN){
		milisec = (milisec+1)%1000;
	}
	else return;
	
	if(milisec)return;
	
	sec = (sec +1)%60;
	if (sec) return;
	
	min = (min +1)%60;
	if(min) return;
	
	hour = (hour +1) %24;
	if(hour) return;
	
}

void StopWatch_excute(){

	StopWatch_eventCheck();
	StopWatch_Run();

}

void StopWatch_eventCheck(){
	switch(StopWatchState)
	{
		case STOP:
		if (button_getstate(&btnMode) == ACT_RELEASED)
		{
			StopWatchState = RUN;
		}
		else if (button_getstate(&btnReSet) == ACT_RELEASED){
			StopWatchState = RESET;
		}
		break;
		
		case RUN:
		if (button_getstate(&btnMode) == ACT_RELEASED)
		{
			StopWatchState = STOP;
		}
		break;
		
		case RESET:
		StopWatchState = STOP;
		break;
	}
	
}

void StopWatch_Run(){
	
	uint16_t stopwatch_data;
	
	if(StopWatchState == RESET){
		milisec = 0;
		sec = 0;
		min = 0;
		hour = 0;
	}
	
	stopwatch_data = (min%10*1000)+(sec*10)+(milisec/100%10);
	FND_setFndData(stopwatch_data);
	
	
	
}