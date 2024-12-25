#include "Presenter.h"

void Presenter_init(){
	FND_init();
	LCD_init();
}


void Presenter_dispStopWatchData(uint8_t hour, uint8_t min, uint8_t sec, uint16_t milisec)
{
	static uint16_t prevMilisec = 0xff;
	if(milisec/10 == prevMilisec){
		prevMilisec = milisec/10;
		return;
	}
	uint16_t stopwatch_data;
	
	stopwatch_data = (min%10*1000)+(sec*10)+(milisec/100%10);
	FND_setFndData(stopwatch_data);
	
	char buff[30];
	
	sprintf(buff,"Stop Watch");
	LCD_writeStringXY(0,3,buff);
	sprintf(buff,"%02d:%02d:%02d:%02d",hour,min,sec,milisec/10);
	LCD_writeStringXY(1,2,buff);
}

void Presenter_dispTimeClockData(uint8_t hour, uint8_t min, uint8_t sec, uint16_t milisec)
{
	static uint16_t prevMilisec = 0xff;
	if(milisec/10 == prevMilisec){
		prevMilisec = milisec/10;
		return;
	}
	
	uint16_t timeClockData = 0;
	uint8_t timeclockdirpStateData;
	timeclockdirpStateData = Model_getTimeModeData();
	
	switch(timeclockdirpStateData)
	{
		case s_m:
		timeClockData = hour*100 + min;
		FND_setFndData(timeClockData);
		break;
		case h_m:
		timeClockData = (sec*100) + (milisec/10);
		FND_setFndData(timeClockData);
		break;
	}
	char buff[30];
	
	sprintf(buff,"Time Clock");
	LCD_writeStringXY(0,3,buff);
	sprintf(buff,"%02d:%02d:%02d:%02d",hour,min,sec,milisec/10);
	LCD_writeStringXY(1,2,buff);
	
	if (milisec <50)
	{
		FND_colonON();
	}
	else
	{
		FND_colonOFF();
	}
}