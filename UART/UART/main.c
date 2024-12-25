#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "periph/UART0/UART0.h"


ISR(USART0_RX_vect)
{
	UART0_ISR_PROCESS();
}

int main(void)
{
	
	sei();
	UART0_init();
	
    while (1) 
    {	UART0_SendString("TEST\n");
		
		if(UART0_RxFlag()){
			UART0_ResetRxFlag();
			UART0_SendString("Receive Data : ");	
			UART0_WriteRxBuff();
		}
		_delay_ms(1000);
    }
}

