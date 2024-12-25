
#ifndef MODEL_TIMECLOCKPISPSTATE_H_
#define MODEL_TIMECLOCKPISPSTATE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

enum{h_m, s_m};

uint8_t Model_getTimeClockData();
void Model_setTimeClockData(uint8_t state);



#endif /* MODEL_TIMECLOCKPISPSTATE_H_ */