#include "apMain.h"

ISR(TIMER0_OVF_vect){
	FND_ISR_Process();
	TCNT0=130;
}
ISR(TIMER2_COMP_vect){
	StopWatch_incMilisec();
	timClock_inMilisec();
}

void apMain_init(){
	
	Listener_init();
	StopWatch_init();
	Presenter_init();
	TimeClock_init();
	TIM0_init();
	TIM2_init();
	sei();
	Model_getStopWatchData(STOP);
	
	Model_getTimeModeData(timeclock);
	Model_getTimeClockData(h_m);
	
}

void apMain_execute(){
	Listener_eventCheck();
	Service_Run();
	timeClock_Run();
	
}