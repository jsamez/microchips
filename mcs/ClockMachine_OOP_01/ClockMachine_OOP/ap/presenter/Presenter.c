#include "Presenter.h"

void Presenter_init(){
	FND_init();
	LCD_init();
}


void Presenter_dispStopWatchData(uint8_t hour, uint8_t min, uint8_t sec, uint16_t milisec)
{
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
	uint16_t TimeClock_data;
	uint8_t TimeClockPisp;
	TimeClockPisp = Model_getTimeClockData();
	switch (TimeClockPisp)
	{
		
	
	case s_m:
	TimeClock_data = (sec*100)+(milisec/10);
	FND_setFndData(TimeClock_data);
	
	char buff[30];
	
	sprintf(buff,"Time Clock (sec,milisec)");
	LCD_writeStringXY(0,3,buff);
	sprintf(buff,"%02d:%02d",sec,milisec/10);
	LCD_writeStringXY(1,2,buff);
	break;
	
	case h_m:
	TimeClock_data = (hour*100)+(min);
	FND_setFndData(TimeClock_data);
	
	char buff_02[30];
	
	sprintf(buff_02,"Time Clock (hour, min)");
	LCD_writeStringXY(0,3,buff);
	sprintf(buff_02,"%02d:%02d",hour, min);
	LCD_writeStringXY(1,4,buff);
	break;
	}
}