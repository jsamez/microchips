﻿
#ifndef PRESENTER_H_
#define PRESENTER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "../../driver/FND/FND.h"
#include "../../driver/LCD/LCD.h"
#include "../Model/Model_TimeClockPispState.h"
#include "../Model/Model_TimeModeState.h"

void Presenter_init();
void Presenter_dispStopWatchData(uint8_t hour, uint8_t min, uint8_t sec, uint16_t milisec);
void Presenter_dispTimeClockData(uint8_t hour, uint8_t min, uint8_t sec, uint16_t milisec);


#endif /* PRESENTER_H_ */