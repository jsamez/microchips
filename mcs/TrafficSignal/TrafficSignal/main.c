
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ap/TrafficSignal/trafficsignal.h"

int main(void)
{
	standinglight_init();

	while (1)
	{
		standinglight_execute();
	}
}

