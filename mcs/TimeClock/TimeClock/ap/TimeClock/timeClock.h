
#ifndef TIMECLOCK_H_
#define TIMECLOCK_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "../../driver/FND/FND.h"
#include "../../periph/TIM/TIM.h"
#include "../../periph/TIM/TIM2.h"
#include "../../driver/Button/button.h"
#include "../../driver/LCD/LCD.h"

enum{Hour_Min, Sec_Milisec};
enum{Modify, Run};

void TimeClock_init();
void timClock_inMilisec();
void timeClock_excute();
void timeClock_eventCheck();
void timeClock_Run();
void timeClock_modify();
void incHour();
void incMin();


#endif /* TIMECLOCK_H_ */