#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_RIGHT   0
#define BUTTON_LEFT      1
#define BUTTON_BLNIK   2
#define BUTTON_ALLOFF   3

#define BUTTON_PIN      PINA
#define BUTTON_DDR      DDRA
#define BUTTON_PORT      PORTA

#define LED_DDR         DDRD
#define LED_PORT      PORTD

enum {LEFT, RIGHT, BLINK, ALLOFF};

uint8_t ledData = 0x01;

void ledLeftShift()
{
	ledData = (ledData >> 7) | (ledData <<1);
	LED_PORT = ledData;
}

void ledRightShift()
{
	ledData = (ledData << 7) | (ledData >>1);
	LED_PORT = ledData;
}

void ledAllBlink()
{
	static uint8_t ledBlinkData = 0x00;
	ledBlinkData ^= 0xff;
	LED_PORT = ledBlinkData;
}

void ledAllOff()
{
	LED_PORT = 0x00;
}



int main(void)
{
	LED_DDR = 0xff;  // 0b11111111
	BUTTON_DDR &= ~((1<<BUTTON_RIGHT)|(1<<BUTTON_LEFT)|(1<<BUTTON_BLNIK)|(1<<BUTTON_ALLOFF));
	BUTTON_PORT = 0xff;
	
	uint8_t buttonState;
	uint8_t ledState = LEFT;
	
	while (1)
	{
		buttonState = BUTTON_PIN;
		if((buttonState & (1<<BUTTON_RIGHT)) == 0)
		{
			ledState = RIGHT;
		}
		if((buttonState & (1<<BUTTON_LEFT)) == 0)
		{
			ledState = LEFT;
		}
		if((buttonState & (1<<BUTTON_BLNIK)) == 0)
		{
			ledState = BLINK;
		}
		if((buttonState & (1<<BUTTON_ALLOFF)) == 0)
		{
			ledState = ALLOFF;
		}
		
		switch (ledState)
		{
			case LEFT :
			ledLeftShift();
			break;
			case RIGHT :
			ledRightShift();
			break;
			case BLINK :
			ledAllBlink();
			break;
			case ALLOFF :
			ledAllOff();
			break;
		}
		_delay_ms(200);
	}
}

