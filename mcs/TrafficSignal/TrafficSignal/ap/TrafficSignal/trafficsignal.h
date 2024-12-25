
#ifndef TRAFFICSIGNAL_H_
#define TRAFFICSIGNAL_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../driver/Button/button.h"
#include "../../driver/Led/led.h"

enum {AUTO, MANUAL};
enum{ RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED};

void standinglight_init();
void standinglight_execute();
void TrafficSignal_AUTO();
void TrafficSignal_MANUAL();

#endif /* LEDMACHINE_H_ */