
#ifndef MODEL_STOPWATCHSTATE_H_
#define MODEL_STOPWATCHSTATE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

enum{STOP, RUN, RESET};

uint8_t Model_getStopWatchData();
void Model_setStopWatchData(uint8_t state);

#endif /* MODEL_STOPWATCHSTATE_H_ */