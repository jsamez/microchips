#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "periph/UART0/UART0.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);


ISR(USART0_RX_vect)
{
	UART0_ISR_Process();
}

int main(void)
{
	DDRD = 0xff;
	UART0_init();
	stdout = &OUTPUT;
	
	sei();
	UART0_sendString("Seoul Tech LED Machine!\n");
	
	while (1)
	{
		//UART0_sendString("TEST\n");
		
		if(UART0_getRxFlag())
		{
			UART0_clearRxFlag();
			uint8_t* rxString = UART0_readRxBuff();
			
			if(!strcmp((char *)rxString,"LED1_TOGGLE\n"))
			{
				PORTD ^= (1<<2);
				if(PORTD & (1<<2))
				{
					printf("LED_1_ON\n");
				}
				else
				{
					printf("LED_1_OFF\n");
				}
			}
			else if(!strcmp((char *)rxString,"LED2_TOGGLE\n"))
			{
				PORTD ^= (1<<3);
				if(PORTD & (1<<3))
				{
					printf("LED_2_ON\n");
				}
				else
				{
					printf("LED_2_OFF\n");
				}
			}
			else if(!strcmp((char *)rxString,"LED3_TOGGLE\n"))
			{
				PORTD ^= (1<<4);
				if(PORTD & (1<<4))
				{
					printf("LED_3_ON\n");
				}
				else
				{
					printf("LED_3_OFF\n");
				}
				
			}
		}
		
	}
}

