
#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../periph/TIM/TIM.h"
#include "../../periph/TIM/TIM2.h"
#include "../../driver/Button/button.h"

enum{Start, Stop};

void StopWatch_init();
void StopWatch_run();


#endif /* STOPWATCH_H_ */