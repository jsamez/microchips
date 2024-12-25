#include "Buzzer.h"

void Buzzer_init(){
	//TIM3 FastPWM, TOP ICR3 ,DutyCycle OCR3A, preScaler 1/64, NON-INVERTING
	// Frequency: 1Khz, Duty Cycle 50%
	
	TCCR3B |= ((0<<CS32)|(1<<CS31)|(1<<CS30));
	TCCR3B |= (1<<WGM33)| (1<<WGM32);
	TCCR3A |= (1<<WGM31)| (0<<WGM30); //Fast PWM 14
	
	DDRE |= (1<<3);
}

void Buzzer_SoundON(){
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0);
}

void Buzzer_SoundOFF(){
	TCCR3A &= ~((1<<COM3A1) | (1<<COM3A0));
}


void Buzzer_buttonOn(){
	Buzzer_SoundON();
	Buzzer_makeHertz(1006);		// 6옥타브 도
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makeHertz(1318);		// 6옥타브 미
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makeHertz(1567);		// 6옥타브 솔
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_makeHertz(2093);		// 7옥타브 도
	_delay_ms(100);
	TCNT3 = 0;
	Buzzer_SoundOFF();
}

void Buzzer_makeHertz(uint16_t hertz){
	if (hertz < 100) hertz =100;
	else if(hertz >5000) hertz = 5000;
	Buzzer_ICR = (250000/ hertz)-1;
	Buzzer_OCR = Buzzer_ICR/2;
}
