#include "LedMachine.h"

uint8_t leddata;
button_t btnNext, btnPrev;
uint8_t ledstate;


{
	
	leddata=0x00;

	Button_init(&btnNext, &DDRA, &PINA,0);
	Button_init(&btnPrev, &DDRA, &PINA,1);

	LED_init();
	ledstate = led3;
	
}

void LedMachine_execute(){
	switch(ledstate)
	{
		case led1 :
		led1_blink();
		if(button_getstate(&btnNext)==ACT_RELEASED){
			ledstate = led2;
			leddata = 0x00;
		}
		else if(button_getstate(&btnPrev)==ACT_PUSHED){
			ledstate = led4;
			leddata = 0x00;
		}
		break;
		case led2 :
		led2_blink();
		if(button_getstate(&btnNext)==ACT_RELEASED){
			ledstate = led3;
			leddata = 0x00;
		}
		else if(button_getstate(&btnPrev)==ACT_PUSHED){
			ledstate = led1;
			leddata = 0x00;
		}
		break;
		case led3 :
		led3_blink();
		if(button_getstate(&btnNext)==ACT_RELEASED){
			ledstate = led4;
			leddata = 0x00;
		}
		else if(button_getstate(&btnPrev)==ACT_PUSHED){
			ledstate = led2;
			leddata = 0x00;
		}
		break;
		case led4 :
		led4_blink();
		if(button_getstate(&btnNext)==ACT_RELEASED){
			ledstate = led1;
			leddata = 0x00;
		}
		else if(button_getstate(&btnPrev)==ACT_PUSHED){
			ledstate = led3;
			leddata = 0x00;
		}
		break;
	}
	_delay_ms(100);
	
}




void led1_blink()
{
	leddata ^= 0x01;
	LED_WriteData(leddata);
}
void led2_blink()
{
	leddata ^= 0x02;
	LED_WriteData(leddata);
}
void led3_blink()
{
	leddata ^= 0x04;
	LED_WriteData(leddata);
}
void led4_blink()
{
	leddata ^= 0x08;
	LED_WriteData(leddata);
}
