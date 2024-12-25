#include "LED.h"

void LED_init(){
	LED_DDR = 0xff;
	
}


void LED_WriteData(uint8_t data){
	LED_PORT = data;
}


void TrafficSifnal_REDGREEN(){
	LED_PORT = (1<<TRAFFIC_LIGHT_hRED) | (1<<TRAFFIC_LIGHT_vGREEN);
}

void TrafficSifnal_REDYELLOW(){
	LED_PORT = (1<<TRAFFIC_LIGHT_hRED) | (1<<TRAFFIC_LIGHT_vYELLOW);
}

void TrafficSifnal_GREENRED(){
	LED_PORT = (1<<TRAFFIC_LIGHT_hGREEN) | (1<<TRAFFIC_LIGHT_vRED);
}

void TrafficSifnal_YELLOWRED(){
	LED_PORT = (1<<TRAFFIC_LIGHT_hYELLOW) | (1<<TRAFFIC_LIGHT_vRED);
}
