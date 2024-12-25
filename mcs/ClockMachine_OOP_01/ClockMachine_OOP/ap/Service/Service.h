
#ifndef SERVICE_H_
#define SERVICE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../Model/Model_StopWatchState.h"
#include "../presenter/Presenter.h"
#include "../../periph/TIM/TIM.h"
#include "../../periph/TIM/TIM2.h"

void StopWatch_init();
void StopWatch_incMilisec();
void Service_Run();

#endif /* SERVICE_H_ */