// /*
// #define f_cpu 16000000ul
// #include <avr/io.h>
// #include <util/delay.h>
// 
// #define led_ddr ddrd
// #define led_port portd
// #define led_pin	pind
// #define led_button_ddr	ddra
// #define led_button_port	porta
// #define	led_button_pin	pina
// 
// #define led_button_right_shift	0
// #define led_button_left_shift	1
// 
// #define led_1		0
// #define led_2		1
// #define led_3		2
// #define led_4		3
// 
// enum{blink1,blink2,blink3,blink4};
// 
// uint8_t ledstate = blink1;
// uint32_t timetic = 0;
// uint32_t prevtime = 0;
// 
// void led1_blink(){
// 	led_port = (1<<led_1);
// 	if(timetic-prevtime >= 2){
// 		led_port = 0x00;
// 		if(timetic-prevtime >= 4){
// 			led_port = (1<<led_1);
// 			timetic = prevtime;
// 		}
// 	}
// 	else if((led_button_pin & (1<<led_button_right_shift)) == 0){
// 		ledstate = blink2;
// 	}
// 	else if((led_button_pin & (1<<led_button_left_shift)) == 0){
// 		ledstate = blink4;
// 	}
// 
// }
// 
// void led2_blink(){
// 	led_port = (1<<led_2);
// 	if(timetic-prevtime >= 2){
// 		led_port = 0x00;
// 		if(timetic-prevtime >= 4){
// 			led_port = (1<<led_2);
// 			timetic = prevtime;
// 		}
// 	}
// 	else if((led_button_pin & (1<<led_button_right_shift)) == 0){
// 		ledstate = blink3;
// 	}
// 	else if((led_button_pin & (1<<led_button_left_shift)) == 0){
// 		ledstate = blink1;
// 	}
// }
// 
// void led3_blink(){
// 	led_port = (1<<led_3);
// 	if(timetic-prevtime >= 2){
// 		led_port = 0x00;
// 		if(timetic-prevtime >= 4){
// 			led_port = (1<<led_3);
// 			timetic = prevtime;
// 		}
// 	}
// 	else if((led_button_pin & (1<<led_button_right_shift)) == 0){
// 		ledstate = blink4;
// 	}
// 	else if((led_button_pin & (1<<led_button_left_shift)) == 0){
// 		ledstate = blink2;
// 	}
// 
// }
// 
// void led4_blink(){
// 	led_port = (1<<led_4);
// 	if(timetic-prevtime >= 2){
// 		led_port = 0x00;
// 		if(timetic-prevtime >= 4){
// 			led_port = (1<<led_4);
// 			timetic = prevtime;
// 		}
// 	}
// 	else if((led_button_pin & (1<<led_button_right_shift)) == 0){
// 		ledstate = blink1;
// 	}
// 	else if((led_button_pin & (1<<led_button_left_shift)) == 0){
// 		ledstate = blink3;
// 	}
// 
// }
// 
// int main(void)
// {
// 	led_ddr |= ((1<<led_1)|(1<<led_2)|(1<<led_3)|(1<<led_4));
// 	led_button_port = 0xff;
// 	led_button_ddr &= ~((1<<led_button_right_shift)|(1<<led_button_left_shift));
// 
// 	while (1)
// 	{
// 
// 		switch(ledstate){
// 			case blink1 :
// 			led1_blink();
// 			break;
// 
// 			case blink2:
// 			led2_blink();
// 			break;
// 
// 			case blink3:
// 			led3_blink();
// 			break;
// 
// 			case blink4:
// 			led4_blink();
// 			break;
// 		}
// 		_delay_ms(1);
// 		timetic++;
// 		_delay_ms(50);
// 	}
// }*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ap/LEDMACHINE/LedMachine.h"

int main(void)
{
	LEDMACHINE_init();

	while (1)
	{
		LedMachine_execute();
	}
}

