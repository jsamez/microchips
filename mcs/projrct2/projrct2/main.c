
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define TRAFFIC_BUTTON_AUTO		0
#define TRAFFIC_BUTTON_MANUAL	1
#define TRAFFIC_BUTTON_CONTROL	2

#define  TRAFFIC_LIGHT_vGREEN	0
#define  TRAFFIC_LIGHT_vYELLOW	1
#define	 TRAFFIC_LIGHT_vRED		2

#define  TRAFFIC_LIGHT_hGREEN	3
#define  TRAFFIC_LIGHT_hYELLOW	4
#define	 TRAFFIC_LIGHT_hRED		5



uint8_t	trafficState=RED_GREEN;
uint32_t timetic;
void TrafficSifnal_REDGREEN(){
	TRAFFIC_LED_PORT = (1<<TRAFFIC_LIGHT_hRED) | (1<<TRAFFIC_LIGHT_vGREEN);
	
}

void TrafficSifnal_REDYELLOW(){
	TRAFFIC_LED_PORT = (1<<TRAFFIC_LIGHT_hRED) | (1<<TRAFFIC_LIGHT_vYELLOW);
}

void TrafficSifnal_GREENRED(){
	TRAFFIC_LED_PORT = (1<<TRAFFIC_LIGHT_hGREEN) | (1<<TRAFFIC_LIGHT_vRED);
}

void TrafficSifnal_YELLOWRED(){
	TRAFFIC_LED_PORT = (1<<TRAFFIC_LIGHT_hYELLOW) | (1<<TRAFFIC_LIGHT_vRED);
}

uint8_t TrafficgetState(){
	static uint8_t prevState = 1;
	uint8_t corState = TRAFFIC_BUTTON_PIN & (1<<TRAFFIC_BUTTON_CONTROL);
	if ((corState == 0) &&(prevState = 1)){
		_delay_ms(10);
		prevState = 0;
		return 0;
	}
	else if ((corState != 0 )&&(prevState == 0)){
		_delay_ms(10);
		prevState =1;
		return 1;
	}
	return 0;
	
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
		if(TrafficgetState()){
			trafficState = RED_YELLOW;
		}
		break;
		
		case RED_YELLOW:
		TrafficSifnal_REDYELLOW();
		if(TrafficgetState()){
			trafficState = GREEN_RED;
		}
		break;
		
		case GREEN_RED:
		TrafficSifnal_GREENRED();
		if(TrafficgetState()){
			trafficState = YELLOW_RED;
		}
		break;
		
		case YELLOW_RED:
		TrafficSifnal_YELLOWRED();
		if(TrafficgetState()){
			trafficState = RED_GREEN;
		}
		break;
	}
	
}




int main(void)
{
	TRAFFIC_LED_DDR = 0xff;
	TRAFFIC_BUTTON_PORT = 0xff;
	TRAFFIC_BUTTON_DDR &= ~((1<<TRAFFIC_BUTTON_AUTO)| (1<<TRAFFIC_BUTTON_MANUAL) | (1<<TRAFFIC_BUTTON_CONTROL) );
	
	uint8_t trafficModeState = AUTO;
	
	while (1)
	{
		//Event Process
		if((TRAFFIC_BUTTON_PIN & (1<<TRAFFIC_BUTTON_AUTO)) == 0){
			trafficModeState = AUTO;
		}
		
		else if((TRAFFIC_BUTTON_PIN & (1<<TRAFFIC_BUTTON_MANUAL))==0){
			trafficModeState=MANUAL;
		}
		
		switch(trafficModeState){
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
}

