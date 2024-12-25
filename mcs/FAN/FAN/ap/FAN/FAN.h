
#ifndef FAN_H_
#define FAN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include "../../driver/Button/button.h"
#include "../../periph/UART/UART0.h"
#include "../../driver/Buzzer/Buzzer.h"
#include "../../periph/TIM/TIM.h"
#include "../../periph/TIM/TIM2.h"

#define FAN_ICR ICR3
#define FAN_OCR OCR3A

enum{OFF,LOW,MIDLE,HIGH,NATURAL,SLEEP};
enum{MANUAL,AUTO};

void Fan_init();
void Fan_StateEventCheck();
void Fan_ManualModeCheck();
void Fan_AUTOModeCheck();
void FAN_AUTOMode();
void FAN_ManualMode();
void FAN_makeHertz(uint16_t hertz);
void Fan_OFFMode();
void Fan_LOWMode();
void Fan_MIDLEMode();
void Fan_HIGHMode();
void Fan_execute();
void Fan_SLEEPMode();
void Fan_NATURALMode();
uint8_t Fan_AutoTimer();

#endif /* FAN_H_ */