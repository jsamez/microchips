#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR  DDRD
#define LED_PORT PORTD

enum{TRAFFIC_LIGHT_vGREEN ,TRAFFIC_LIGHT_vYELLOW, TRAFFIC_LIGHT_vRED	, TRAFFIC_LIGHT_hGREEN, TRAFFIC_LIGHT_hYELLOW,	TRAFFIC_LIGHT_hRED};
void LED_init();
void LED_WriteData(uint8_t data);
void TrafficSifnal_REDGREEN();
void TrafficSifnal_REDGYELLOW();
void TrafficSifnal_GREENRED();
void TrafficSifnal_YELLOWRED();

#endif /* LED_H_ */