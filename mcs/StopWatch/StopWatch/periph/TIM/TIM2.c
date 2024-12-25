#include "TIM2.h"

void TIM2_init(){
	
		//timer/counter 2 1/64 1ms period interrupt, ctc mode
		TCCR2 |= ((0<<CS22)|(1<<CS21)|(1<<CS20));	// 1/64 prescaler
		TIMSK |= (1<<OCIE2);
		
		//CTC MODE
		TCCR2 |= ((1<<WGM21) | (0<<WGM20));
		OCR2 = 250-1;
		
}
