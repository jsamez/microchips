#include "trafficsignal.h"

uint8_t leddata;
button_t btnNext, btnPrev;
uint8_t ledstate;

void trafficsignal_init(){
	
	leddata=0x00;

	Button_init(&btnNext, &DDRA, &PINA,0);
	Button_init(&btnPrev, &DDRA, &PINA,1);

	LED_init();
	ledstate = AUTO;
	
}

void trafficsignal_execute(){
	switch(ledstate)
	{
		case AUTO:
		led_alloff();
		if(button_getstate(&btnNext)==ACT_RELEASED){
			ledstate = led1;
			led_tr();
		}
		else if(button_getstate(&btnPrev)==ACT_PUSHED){
			ledstate = led_off;
		}
		break;
		case led1 :
		led_on();
		if(button_getstate(&btnNext)==ACT_RELEASED){
			ledstate = led2;
			led_tr();
		}
		else if(button_getstate(&btnPrev)==ACT_PUSHED){
			ledstate = led_off;
		}
		break;
		case led2 :
		led_on();
		if(button_getstate(&btnNext)==ACT_RELEASED){
			ledstate = led3;
			led_tr();
		}
		else if(button_getstate(&btnPrev)==ACT_PUSHED){
			ledstate = led_off;
		}
		break;
		case led3 :
		led_on();
		if(button_getstate(&btnNext)==ACT_RELEASED){
			ledstate = led4;
			led_tr();
		}
		else if(button_getstate(&btnPrev)==ACT_PUSHED){
			ledstate = led_off;
		}
		break;
		
		case led4 :
		led_on();
		if(button_getstate(&btnNext)==ACT_RELEASED){
			ledstate = led_off;
		}
		else if(button_getstate(&btnPrev)==ACT_PUSHED){
			ledstate = led_off;
		}
		break;
		
	}
	_delay_ms(100);
	
}




void led_alloff()
{
	leddata = 0b00000000;
	LED_WriteData(leddata);
}
void led_tr(){
	leddata = (leddata<<2);
	leddata = leddata +3;
}
void led_on(){
	LED_WriteData(leddata);
}
