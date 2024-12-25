
#ifndef TIMER_H_
#define TIMER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../../periph/TIM/TIM.h"
#include "../../periph/TIM/TIM2.h"
#include "../../driver/FND/FND.h"
#include "../../driver/LCD/LCD.h"
#include "../../driver/Button/button.h"
#include "../FAN/FAN.h"

button_t btnTimerInc, btnTimerDic;
uint8_t Sec, Min, Hour, t_min, t_hour;
uint16_t Milisec;

void Timer_inMilisec();
void Timer_init();
void Timer_EventCheck(uint8_t *uptime, uint8_t *downtime);
void Timer_setFNDData();
void Timer_run(uint8_t *data1, uint8_t *data2);
void Timer_LCDData();


#endif /* TIMER_H_ */