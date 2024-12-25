#include "trafficsignal.h"

button_t btnNext, btnPrev,btnCon;
uint8_t ledstate;
uint32_t timetic;
uint8_t	trafficState=RED_GREEN;

void standinglight_init(){
	

	Button_init(&btnNext, &DDRA, &PINA,0);
	Button_init(&btnPrev, &DDRA, &PINA,1);
	Button_init(&btnCon, &DDRA, &PINA,2);
	
	LED_init();
	ledstate = AUTO;
	
}

void standinglight_execute(){
	
	if(button_getstate(&btnNext)==ACT_RELEASED){
		ledstate = AUTO;
	}
	if(button_getstate(&btnPrev)==ACT_RELEASED){
		ledstate = MANUAL;
	}
	switch(ledstate)
	{
			case AUTO:
			TrafficSignal_AUTO();
			break;
			
			case MANUAL:
			TrafficSignal_MANUAL();
			break;
		}
		_delay_ms(1);
		timetic++;
	}
	




void TrafficSignal_AUTO(){
	static uint32_t prevTime = 0;
	
	switch(trafficState){
		case RED_GREEN:
		TrafficSifnal_REDGREEN();
		if(timetic - prevTime >= 3000){
			prevTime = timetic;
			trafficState = RED_YELLOW;
		}
		break;
		
		case RED_YELLOW:
		TrafficSifnal_REDYELLOW();
		if(timetic - prevTime >= 1000){
			prevTime = timetic;
			trafficState = GREEN_RED;
		}
		
		break;
		
		case GREEN_RED:
		TrafficSifnal_GREENRED();
		if(timetic - prevTime >= 3000){
			prevTime = timetic;
			trafficState = YELLOW_RED;
		}
		
		break;
		
		case YELLOW_RED:
		TrafficSifnal_YELLOWRED();
		if(timetic - prevTime >= 1000){
			prevTime = timetic;
			trafficState = RED_GREEN;
		}
		
		break;
	}
	
}

void TrafficSignal_MANUAL(){
	
	
	switch(trafficState){
		case RED_GREEN:
		TrafficSifnal_REDGREEN();
		if(button_getstate(&btnCon)==ACT_RELEASED){
			trafficState = RED_YELLOW;
		}
		break;
		
		case RED_YELLOW:
		TrafficSifnal_REDYELLOW();
		if(button_getstate(&btnCon)==ACT_RELEASED){
			trafficState = GREEN_RED;
		}
		break;
		
		case GREEN_RED:
		TrafficSifnal_GREENRED();
		if(button_getstate(&btnCon)==ACT_RELEASED){
			trafficState = YELLOW_RED;
		}
		break;
		
		case YELLOW_RED:
		TrafficSifnal_YELLOWRED();
		if(button_getstate(&btnCon)==ACT_RELEASED){
			trafficState = RED_GREEN;
		}
		break;
	}
	
}