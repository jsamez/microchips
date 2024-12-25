
#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../../driver/FND/FND.h"
#include "../../periph/TIM/TIM.h"
#include "../../driver/Button/button.h"
#include "../../periph/TIM/TIM2.h"

enum{STOP, RUN, RESET};

void StopWatch_init();
void StopWatch_incMilisec();
void StopWatch_excute();
void StopWatch_eventCheck();
void StopWatch_Run();





#endif /* STOPWATCH_H_ */