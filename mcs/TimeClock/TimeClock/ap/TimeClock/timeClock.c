#include "timeClock.h"

button_t btnMode, btnHourUp, btnMinUP, btnModify;
uint8_t sec, min, hour;
uint8_t timeClockState;
uint8_t timeClockModi;
uint16_t milisec;


void TimeClock_init(){
	
	FND_init();
	TIM0_init();
	TIM2_init();
	Button_init(&btnModify,&DDRA,&PINA,0);
	Button_init(&btnHourUp,&DDRA,&PINA,1);
	Button_init(&btnMinUP,&DDRA,&PINA,2);
	Button_init(&btnMode,&DDRA,&PINA,4);
	LCD_init();
	
	milisec = 0;
	sec = 46;
	min = 06;
	hour = 03;
	timeClockState = Hour_Min;
	timeClockModi = Modify;
	
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

void timeClock_excute(){
	
	timeClock_eventCheck();
	timeClock_Run();
	
}

void timeClock_eventCheck(){
	
	switch(timeClockModi){
		case Modify:
		if(button_getstate(&btnModify) == ACT_RELEASED){
			sec = 0;
			milisec = 0;
			timeClockModi = Run;
		}
		timeClockState = Hour_Min;
		timeClock_modify();
		break;
		
		case Run:
		if(button_getstate(&btnModify) == ACT_RELEASED){
			timeClockModi = Modify;
		}
		break;
		
	}
	
	
	switch(timeClockState){
		
		case Sec_Milisec:
		if(button_getstate(&btnMode)==ACT_RELEASED){
			timeClockState = Hour_Min;
		}
		
		else if(button_getstate(&btnModify) == ACT_RELEASED){
			timeClockModi = Modify;
		}
		
		
		break;
		
		
		case Hour_Min:
		if(button_getstate(&btnMode)==ACT_RELEASED){
			timeClockState = Sec_Milisec;
		}
		break;
	}
}

void timeClock_Run(){
	uint16_t timeClock_data;
	
	static uint8_t PrevSec = 0xff;
	if (sec != PrevSec)
	{
		PrevSec = sec;
		char buff[30];
		sprintf(buff,"Time Clock");
		LCD_writeStringXY(0,3,buff);
		sprintf(buff,"%02d:%02d:%02d ", hour, min, sec);
		LCD_writeStringXY(1,4,buff);
	}
	switch(timeClockState){
		
		case Sec_Milisec:
		timeClock_data = (sec*100)+(milisec/10);
		FND_setFndData(timeClock_data);
		
		if (milisec%100<50)
		{
			FND_colonON();
		}
		else {
			FND_colonOFF();
		}
		
		break;
		
		case Hour_Min:
		timeClock_data = hour*100 + min;
		FND_setFndData(timeClock_data);
		if (milisec<500)
		{
			FND_colonON();
		}
		else if(timeClockModi == Modify){
			FND_colonON();
		}
		else {
			FND_colonOFF();
		}
		break;
		
	}
	
}

void timeClock_modify(){

	if(button_getstate(&btnHourUp)==ACT_RELEASED)
	{
		incHour();
	}
	else if(button_getstate(&btnMinUP)==ACT_RELEASED)
	{
		incMin();
	}
}

void incHour(){
	if (hour >= 23 ){
		hour = 0;
	}
	hour++;
}

void incMin(){
	if (min >= 59 ){
		min = 0;
	}
	min++;
}


