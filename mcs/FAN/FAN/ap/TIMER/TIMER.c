#include "TIMER.h"

button_t btnTimerInc, btnTimerDic;
uint8_t Sec, Min, Hour, t_min, t_hour;
uint16_t Milisec;

void Timer_inMilisec(){
	
	Milisec = (Milisec+1)%1000;
	if(Milisec) return;

	Sec = (Sec +1)%60;
	if (Sec) return;
	
	Min = (Min +1)%60;
	if(Min) return;
	
	Hour = (Hour +1) %24;
	if(Hour) return;
	
}

void Timer_init()
{
	TIM0_init();
	TIM2_init();
	FND_init();
	LCD_init();
	Button_init(&btnTimerInc, &DDRA, &PINA, 2);
	Button_init(&btnTimerDic, &DDRA, &PINA, 4);
	
	Milisec = 0;
	Sec = 0;
	Min = 0;
	Hour = 0;
	t_hour = 0;
	t_min = 0;
}

void Timer_EventCheck()
{
	if(button_getstate(&btnTimerInc)==ACT_RELEASED)
	{
		t_min = t_min + 5;
	}
	else if(button_getstate(&btnTimerInc)==ACT_RELEASED)
	{
		t_min = t_min - 5;
	}
}

void Timer_FndData()
{
	uint8_t FndData;
	FndData = (t_hour-Hour)*100 + (t_min - Min);
	FND_setFndData(FndData);
}