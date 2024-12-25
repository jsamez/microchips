
#ifndef MODEL_TIMEMODESTATE_H_
#define MODEL_TIMEMODESTATE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

enum{stopwatch, timeclock};

uint8_t Model_getTimeModeData();
void Model_setTimeModeData(uint8_t state);



#endif /* MODEL_TIMEMODESTATE_H_ */