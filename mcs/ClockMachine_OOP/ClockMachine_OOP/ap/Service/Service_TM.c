#include "Service_TM.h"

uint8_t sec, min, hour;
uint8_t timeClockState;
uint8_t timeClockModi;
uint16_t milisec;


void TimeClock_init(){
	
	
	
	milisec = 0;
	sec = 46;
	min = 14;
	hour = 10;

}

void timClock_inMilisec(){
	
	milisec = (milisec+1)%1000;

	if(milisec) return;
	
	sec = (sec +1)%60;
	if (sec) return;
	
	min = (min +1)%60;
	if(min) return;
	
	hour = (hour +1) %24;
	if(hour) return;
	
}

void timeClock_Run(){
	uint8_t timeModeState;
	timeModeState = Model_getTimeClockData();
	if (timeModeState != timeclock ) return;


	Presenter_dispTimeClockData(hour,min,sec,milisec);
	
}
