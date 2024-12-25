
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	apMain_init();
	
    while (1) 
    {
		apMain_execute();
    }
}

