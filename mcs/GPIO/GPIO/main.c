/*
* GPIO.c
*
* Created: 2024-07-25 오후 2:09:52
* Author : iot
*/

#define F_CPU 16000000UL
#include <avr/io.h> //레지스터 사용
#include <util/delay.h> //delay함수 사용

#define BUTTON_AUTO 0
#define BUTTON_MANUAL 1
#define BUTTON_CONTROL 2
#define BUTTON_PIN	PINA
#define	BUTTON_DDR	DDRA
#define BUTTON_PORT PORTA

#define LED_DDR		DDRD
#define LED_PORT	PORTD

enum{AUTO, MANUAL, CONTROL};
uint8_t ledData=0b00100001;
uint8_t buttonState;

void AUTOCONTROL(int a[], int *pi){
	LED_PORT = ledData;
	ledData = a[*pi];
	if(1 == *pi%2){
		_delay_ms(1000);
	}
	else{
		_delay_ms(3000);
	}
	*pi=*pi+1;
}

void Manual(int a[], int *pi){
	LED_PORT =ledData;
	if((buttonState & (1<<BUTTON_CONTROL))==0){
		ledData=a[*pi];
		*pi=*pi+1;
	}
}


int main(void)
{
	LED_DDR = 0xff;
	BUTTON_DDR = 0b00000000;
	BUTTON_PORT = 0xff;
	
	
	uint8_t ledState = AUTO;
	int colors[4] = {0b00100010, 0b00001100, 0b00010100, 0b00100001};
	int i=0;
	

	/* Replace with your application code */
	while (1)
	{
		buttonState = BUTTON_PIN;
		if((buttonState & (1<<BUTTON_AUTO))==0){
			ledState = AUTO;
		}
		if((buttonState & (1<<BUTTON_MANUAL))==0){
			ledState = MANUAL;
		}
		
		switch(ledState){
			case AUTO:
			AUTOCONTROL(colors, &i);
			if(i==4){
				i=0;
			}
			break;
			
			case MANUAL:
			Manual(colors,&i);
			if(i==4){
				i=0;
			}
			_delay_ms(180);
			break;
			
		}
		/*
		if(buttonState == 0b11111110){
		PORTD = 0xff;
		}
		else if (buttonState == 0b11111101){
		PORTD = 0x00;
		}
		else if (buttonState == 0b11111011){
		PORTD = 0x01;
		}
		else if (buttonState == 0b11110111){
		PORTD = 0x0c;
		}
		
		if(i >= 5){
		if(i >= 5){
		ledData = 0b00000000;
		PORTD = ledData;
		_delay_ms(300);
		}
		for(i = 0; i<5; i++){
		PORTD = ledData;
		_delay_ms(1000);
		ledData =(ledData<<2);
		ledData =(ledData+3);
		}
		}
		
		PORTD = ledData;
		_delay_ms(200);
		if(ledData >= 0b10000000){
		for(int i= 0; i<7; i++){
		ledData = (ledData <<7)|(ledData >>1);
		PORTD = ledData;
		_delay_ms(200);
		}
		}
		else{
		ledData =(ledData<<1)|(ledData>>7);
		}

		for(int i =0; i<7; i++){
		PORTD = ledData;
		ledData <<=1;
		_delay_ms(200);
		}
		for(int i =0; i<7; i++){
		PORTD = ledData;
		ledData >>=1;
		_delay_ms(200);
		}
		PORTD = 0b00000001;
		_delay_ms(200);
		PORTD = 0b00000010;
		_delay_ms(300);
		PORTD = 0b00000100;
		_delay_ms(400);
		PORTD = 0b00001000;
		_delay_ms(500);
		PORTD = 0b00010000;
		_delay_ms(600);
		PORTD = 0b00100000;
		_delay_ms(700);
		PORTD = 0b01000000;
		_delay_ms(800);
		PORTD = 0b10000000;
		_delay_ms(900);
		
		for(int i=0; i<8; i++){
		PORTD = 0x01<<i;
		_delay_ms(200);
		
		}
		*/
	}
}
