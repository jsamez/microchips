
#ifndef SERVICE_TM_H_
#define SERVICE_TM_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../Model/Model_TimeModeState.h"
#include "../presenter/Presenter.h"

void TimeClock_init();
void timClock_inMilisec();
void timeClock_Run();



#endif /* SERVICE_TM_H_ */