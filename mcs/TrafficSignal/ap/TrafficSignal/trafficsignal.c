#include "trafficsignal.h"

button_t btnAuto, btnManual, btnCtrl;
uint8_t trafficState;
uint32_t timeTick;
uint8_t trafficModeState;
uint8_t trafficData;


void TrafficSignal_init(){
	
	trafficState = RED_GREEN;
	timeTick = 0;
	
	LED_init();
	Button_init(&btnAuto, &DDRA, &PINA, 0);
	Button_init(&btnManual, &DDRA, &PINA, 1);
	Button_init(&btnCtrl, &DDRA, &PINA, 2);
	//TRAFFIC_BUTTON_PORT = 0xff
	
	trafficModeState = AUTO;

}

void TrafficSignal_run(){
	
	//Event Process
	if(button_getstate(&btnAuto) == ACT_RELEASED)
	{
		trafficModeState = AUTO;
	}
	else if(button_getstate(&btnManual) == ACT_RELEASED)
	{
		trafficModeState = MANUAL;
	}
	
	
	// State Running
	switch (trafficModeState)
	{
		case AUTO :
		TrafficSignal_AUTO();
		break;
		case MANUAL :
		TrafficSignal_MANUAL();
		break;
	}
	
	_delay_ms(1);
	timeTick++;
}


void TrafficSignal_AUTO()
{
	static uint32_t prevTime = 0;
	
	switch(trafficState)
	{
		case RED_GREEN :
		TrafficSignal_REDGREEN();
		if(timeTick - prevTime >= 3000)
		{
			prevTime = timeTick;
			trafficState = RED_YELLOW;
		}
		break;
		case RED_YELLOW :
		TrafficSignal_REDYELLOW();
		if(timeTick - prevTime >= 1000)
		{
			prevTime = timeTick;
			trafficState = GREEN_RED;
		}
		break;
		case GREEN_RED :
		TrafficSignal_GREENRED();
		if(timeTick - prevTime >= 3000)
		{
			prevTime = timeTick;
			trafficState = YELLOW_RED;
		}
		break;
		case YELLOW_RED :
		TrafficSignal_YELLOWRED();
		if(timeTick - prevTime >= 1000)
		{
			prevTime = timeTick;
			trafficState = RED_GREEN;
		}
		break;
	}
}

void TrafficSignal_MANUAL()
{
	switch(trafficState)
	{	
	
		
		case RED_GREEN :
		TrafficSignal_REDGREEN();
		if(button_getstate(&btnCtrl) == ACT_RELEASED)
		{
			trafficState = RED_YELLOW;
		}
		break;
		case RED_YELLOW :
		TrafficSignal_REDYELLOW();
		if(button_getstate(&btnCtrl) == ACT_RELEASED)		
		{
			trafficState = GREEN_RED;
		}
		break;
		case GREEN_RED :
		TrafficSignal_GREENRED();
		if(button_getstate(&btnCtrl) == ACT_RELEASED)		
		{
			trafficState = YELLOW_RED;
		}
		break;
		case YELLOW_RED :
		TrafficSignal_YELLOWRED();
		if(button_getstate(&btnCtrl) == ACT_RELEASED)		
		{
			trafficState = RED_GREEN;
		}
		break;
	}
	
}


void TrafficSignal_REDGREEN()
{
	trafficData = (1<<TRAFFIC_LIGHT_VRED) | (1<<TRAFFIC_LIGHT_HGREEN);
	LED_WriteData(trafficData);
}

void TrafficSignal_REDYELLOW()
{
	trafficData = (1<<TRAFFIC_LIGHT_VRED) | (1<<TRAFFIC_LIGHT_HYELLOW);
	LED_WriteData(trafficData);
}

void TrafficSignal_GREENRED()
{
	trafficData = (1<<TRAFFIC_LIGHT_VGREEN) | (1<<TRAFFIC_LIGHT_HRED);
	LED_WriteData(trafficData);
}

void TrafficSignal_YELLOWRED()
{
	trafficData = (1<<TRAFFIC_LIGHT_VYELLOW) | (1<<TRAFFIC_LIGHT_HRED);
	LED_WriteData(trafficData);
}