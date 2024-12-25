#include "Service.h"

uint16_t milisec_s;
uint16_t sec_s, min_s, hour_s;

void StopWatch_init(){
	
	milisec_s = 0;
	sec_s = 0;
	min_s = 0;
	hour_s = 0;
}

void StopWatch_incMilisec(){
	uint8_t StopWatchState;
	
	StopWatchState=Model_getStopWatchData();
	
	if (StopWatchState == RUN){
		milisec_s = (milisec_s+1)%1000;
	}
	else return;
	
	if(milisec_s)return;
	
	sec_s = (sec_s +1)%60;
	if (sec_s) return;
	
	min_s = (min_s +1)%60;
	if(min_s) return;
	
	hour_s = (hour_s +1) %24;
	if(hour_s) return;
	
}


void Service_Run(){
	
	uint8_t timeModeState;
	timeModeState = Model_getTimeClockData();
	if (timeModeState != stopwatch ) return;

	uint8_t StopWatchState;
	StopWatchState = Model_getStopWatchData();
	
	if(StopWatchState == RESET){
		milisec_s = 0;
		sec_s = 0;
		min_s = 0;
		hour_s = 0;
	}
	Presenter_dispStopWatchData(hour_s,min_s,sec_s,milisec_s);
}