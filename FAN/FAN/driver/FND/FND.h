
#ifndef FND_H_
#define FND_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_DIGIT_DDR	DDRC
#define FND_DATA_DDR	DDRF

#define FND_DIGIT_4		4
#define FND_DIGIT_3		5
#define FND_DIGIT_2		6
#define FND_DIGIT_1		7

void FND_init();
void FND_colonON();
void FND_colonOFF();
void FND_dispNum(uint16_t fndNum);
void FND_setFndData(uint16_t data);
void FND_ISR_Process();


#endif /* FND_H_ */