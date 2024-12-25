
#ifndef TRAFFICSIGNAL_H_
#define TRAFFICSIGNAL_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/Button/button.h"
#include "../../driver/LED/led.h"

#define		TRAFFIC_LIGHT_VRED			2
#define		TRAFFIC_LIGHT_VYELLOW		1
#define		TRAFFIC_LIGHT_VGREEN		0

#define		TRAFFIC_LIGHT_HRED			5
#define		TRAFFIC_LIGHT_HYELLOW		4
#define		TRAFFIC_LIGHT_HGREEN		3

enum {AUTO, MANUAL};
enum {RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED};
	
void TrafficSignal_init();
void TrafficSignal_run();
void TrafficSignal_AUTO();
void TrafficSignal_MANUAL();
void TrafficSignal_REDGREEN();
void TrafficSignal_REDYELLOW();
void TrafficSignal_GREENRED();
void TrafficSignal_YELLOWRED();



#endif /* TRAFFICSIGNAL_H_ */