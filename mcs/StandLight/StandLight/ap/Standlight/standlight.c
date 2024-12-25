#include "standlight.h"

uint8_t leddata;
button_t btnNext, btnPrev;
uint8_t ledstate;

void standinglight_init(){
	
	LED_init(&DDRD);
	Button_init(&btnNext, &BUTTON_DDR, &BUTTON_PIN, BUTTON_MODE);
	Button_init(&btnPrev, &BUTTON_DDR, &BUTTON_PIN, BUTTON_OFF);

	leddata = 0b00000011;
	ledstate = led1;
	
}

void standinglight_execute(){
	
	standinglight_eventcheck();
	standinglight_run();
	
}

void standinglight_eventcheck(){
	switch(ledstate)
	{
		case led_off :
		if(button_getstate(&btnNext) == ACT_RELEASED)
		{
			led_tr();
			ledstate = led1;
		}
		else if(button_getstate(&btnPrev) == ACT_RELEASED)
		{
			ledstate = led_off;
		}
		break;
		
		case led1 :
		if(button_getstate(&btnNext) == ACT_RELEASED)
		{
			led_tr();
			ledstate = led2;
		}
		else if(button_getstate(&btnPrev)==ACT_RELEASED)
		{
			ledstate = led_off;
		}
		break;
		
		case led2 :
		if(button_getstate(&btnNext)==ACT_RELEASED)
		{
			led_tr();
			ledstate = led3;
		}
		else if(button_getstate(&btnPrev)==ACT_RELEASED)
		{
			ledstate = led_off;
		}
		break;
		
		case led3 :
		if(button_getstate(&btnNext)==ACT_RELEASED)
		{
			led_tr();
			ledstate = led4;
		}
		else if(button_getstate(&btnPrev) == ACT_RELEASED)
		{
			ledstate = led_off;
		}
		break;
		
		case led4 :
		if(button_getstate(&btnNext) == ACT_RELEASED)
		{
			led_tr();
			ledstate = led_off;
		}
		else if(button_getstate(&btnPrev) == ACT_RELEASED)
		{
			ledstate = led_off;
		}
		break;
		
	}
}

void standinglight_run(){
	switch(ledstate)
	{
		case led_off :
		led_alloff();
		break;
		
		case led1 :
		
		led_on();
		break;
		
		case led2 :
		led_on();
		break;
		
		case led3 :
		led_on();
		break;
		
		case led4 :
		led_on();
		break;
	}
}



void led_alloff()
{
	LED_ALLOFF(&LED_PORT);
}
void led2_leddata(){
	/*leddata = (leddata<<2);
	leddata = leddata +3;*/
	leddata=0b00001111;
}
void led_on(){
	LED_WriteData(&LED_PORT, leddata);
}

