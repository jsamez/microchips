#include "Service.h"

uint16_t milisec;
uint16_t sec, min, hour;

void StopWatch_init(){
	
	milisec = 0;
	sec = 0;
	min = 0;
	hour = 0;
}

void StopWatch_incMilisec(){
	uint8_t StopWatchState;
	
	StopWatchState=Model_getStopWatchData();
	
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


void Service_Run(){
	
	uint8_t StopWatchState;
	StopWatchState = Model_getStopWatchData();
	
	if(StopWatchState == RESET){
		milisec = 0;
		sec = 0;
		min = 0;
		hour = 0;
	}
	Presenter_dispStopWatchData(hour,min,sec,milisec);
}