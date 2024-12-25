﻿
#ifndef UART0_H_
#define UART0_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


void UART0_init();
void UART0_ISR_PROCESS();
void UART0_Transmit( unsigned char data );
unsigned char UART0_Receive( void );
void UART0_SendString(char *str);
uint8_t UART0_Avail();
uint8_t UART0_RxFlag();
void UART0_ResetRxFlag();
void UART0_WriteRxBuff();

#endif /* UART0_H_ */