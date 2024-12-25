#include "TIMER.h"

button_t btnTimerInc, btnTimerDic;
uint8_t Sec, Min, Hour, t_hour,t_sec;
uint16_t Milisec;
uint8_t set_time = 0;
extern uint8_t fanState,fanMode;
extern uint8_t timer_state;

void Timer_inMilisec()
{	
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
	FND_init();
	Button_init(&btnTimerInc, &DDRA, &PINA, 2);
	Button_init(&btnTimerDic, &DDRA, &PINA, 4);
	
	Milisec = 0;
	Sec = 10;
	Min = 0;
	Hour = 0;
	t_sec = 0;
	t_min = 0;
	t_hour = 0;
}

void Timer_EventCheck(uint8_t *uptime, uint8_t *downtime)
{
	if(*uptime)
	{
		Milisec = 0;
		Sec = 0;
		Min = 0;
		Hour = 0;
		
		t_min = t_min +5;
		if(!(t_min%60))
		{
			t_hour++;
			t_min = 0;
		}

	}
	else if(*downtime)
	{
		Milisec = 0;
		Sec = 0;
		Min = 0;
		Hour = 0;
		
		if(t_min == 0 )
		{
			t_hour--;
			t_min = 55;
		}
		else
		{
			t_min = t_min -5;	
		}
	}
	
	if(t_min>=Min && t_hour>=Hour)
	{
		set_time =(t_hour - Hour)*100 + (t_min - Min); 
	}
	else
	{
		set_time = 0000;
	}
	
}

void Timer_setFNDData()
{	
	FND_setFndData(set_time);	
	if(t_hour == Hour && t_min == Min)
	{
		fanState = MANUAL;
		fanMode = OFF;
	}
}

void Timer_run(uint8_t *data1, uint8_t *data2)
{
		Timer_EventCheck(data1, data2);
		Timer_setFNDData(data1, data2);
		*data1 = 0;
		*data2 = 0;
}

void Timer_LCDData()
{
	uint8_t r_hour,r_min;
	r_hour = t_hour - Hour;
	r_min = t_min - Min;
	char buff[30];
	sprintf(buff,"%s ", UART0_readRxBuff());
	LCD_writeStringXY(0,4,buff);
	sprintf(buff,"Timer : %02d : %02d", r_hour, r_min);
	LCD_writeStringXY(1,4,buff);
}