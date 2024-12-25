
#ifndef LISTENER_H_
#define LISTENER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../../driver/Button/button.h"
#include "../Model/Model_StopWatchState.h"
#include "../Model/Model_TimeModeState.h"
#include "../Model/Model_TimeClockPispState.h"

void Listener_init();
void Listener_eventCheck();
void Listener_StopWatchEvent();

#endif /* LISTENER_H_ */