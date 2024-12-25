#include "TIM.h"

void TIM0_init(){
	
	TCCR0 |= ((1<<CS02)|(0<<CS01)|(1<<CS00)); //128 preScaler
	TIMSK |= (1<<TOIE0);					  //TIMSK Timer/counter
	TCNT0=130;
}