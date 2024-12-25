
#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define Buzzer_ICR ICR3
#define Buzzer_OCR OCR3A

void Buzzer_init();
void Buzzer_buttonOn();
void Buzzer_SoundON();
void Buzzer_SoundOFF();
void Buzzer_makeHertz(uint16_t hertz);





#endif /* BUZZER_H_ */