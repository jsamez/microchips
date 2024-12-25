#include "FAN.h"

button_t btnMode, btnFanState;
uint8_t uartMessage0[20];
uint8_t fanMode;
uint8_t fanState;

void Fan_init()
{
	Buzzer_init();
	UART0_init();
	TIM0_init();
	TIM2_init();
	LCD_init();
	Button_init(&btnMode, &DDRA, &PINA, 0); // 1번 버튼
	Button_init(&btnFanState, &DDRA, &PINA, 1); // 2번 버튼
	
	DDRD = 0xff;
	fanState = MANUAL;
	fanMode = OFF;
}

void Fan_StateEventCheck()
{
	
	switch (fanState)
	{
		case MANUAL:
		if(button_getstate(&btnFanState) == ACT_RELEASED)
		{
			fanState = AUTO;
			fanMode = NATURAL;
		}
		break;
		
		case AUTO:
		if(button_getstate(&btnFanState) == ACT_RELEASED)
		{
			fanState = MANUAL;
			fanMode = OFF;
		}
		break;
	}
}

void Fan_ManualModeCheck()
{
	switch (fanMode) {
		case OFF:
		if(button_getstate(&btnMode) == ACT_RELEASED)
		{
			UART0_sendString("Fan Mode: LOW\n");
			fanMode = LOW;
		}
		break;
		
		case LOW:
		if (button_getstate(&btnMode) == ACT_RELEASED)
		{
			UART0_sendString("Fan Mode: MIDLE\n");
			fanMode = MIDLE;
		}
		break;
		
		case MIDLE:
		if(button_getstate(&btnMode) == ACT_RELEASED)
		{
			UART0_sendString("Fan Mode: HIGH\n");
			fanMode = HIGH;
		}
		break;
		
		case HIGH:
		if(button_getstate(&btnMode) == ACT_RELEASED)
		{
			UART0_sendString("Fan Mode: OFF\n");
			fanMode = OFF;
		}
		break;
	}
}

void Fan_AUTOModeCheck()
{
	switch (fanMode) {
		case NATURAL:
		if(button_getstate(&btnMode) == ACT_RELEASED)
		{
			UART0_sendString("Fan Mode: SLEEP\n");
			fanMode = SLEEP;
		}
		break;
		
		case SLEEP:
		if (button_getstate(&btnMode) == ACT_RELEASED)
		{
			UART0_sendString("Fan Mode: NATURAL\n");
			fanMode = NATURAL;
		}
		break;
	}
}

void FAN_ManualMode()
{
	if(UART0_getRxFlag())
	{
		UART0_clearRxFlag();
		uint8_t* RxString = UART0_readRxBuff();
		
		
		if(!strcmp((char *)RxString,"Fan Mode: OFF\n"))
		{
			fanMode = OFF;
		}
		else if(!strcmp((char *)RxString,"Fan Mode: LOW\n"))
		{
			fanState = LOW;
		}
		else if(!strcmp((char *)RxString,"Fan Mode: MIDLE\n"))
		{
			fanState = MIDLE;
		}
		else if(!strcmp((char *)RxString,"Fan Mode: HIGH\n"))
		{
			fanState = HIGH;
		}
		printf("%s", (char *)RxString);
	}
}

void FAN_AUTOMode()
{
	if(UART0_getRxFlag())
	{
		UART0_clearRxFlag();
		uint8_t* RXstring = UART0_readRxBuff();
		printf("%s", (char *)RXstring);
		
		if(!strcmp((char *)RXstring,"Fan Mode: SLEEP\n"))
		{
			fanMode = SLEEP;
		}
		else if(!strcmp((char *)RXstring,"Fan Mode: NATURAL\n"))
		{
			fanMode = NATURAL;
		}
	}
}

void Fan_OFFMode()
{
	Buzzer_makeHertz(0);
	_delay_ms(10);
	TCNT3 = 0;
}

void Fan_LOWMode()
{
	
	Buzzer_makeHertz(450);
	_delay_ms(10);
	TCNT3 = 0;
}

void Fan_MIDLEMode()
{
	
	Buzzer_makeHertz(900);
	_delay_ms(10);
	TCNT3 = 0;
}

void Fan_HIGHMode()
{
	Buzzer_makeHertz(1350);
	_delay_ms(10);
	TCNT3 = 0;
}

void Fan_SLEEPMode()
{

	switch (fanMode)
	{
		case  LOW:
		if(Fan_AutoTimer())
		{
			fanMode = MIDLE;
		}
		break;
		
		case MIDLE:
		if(Fan_AutoTimer())
		{
			fanMode = OFF;
		}
		break;
		
		case OFF:
		if(Fan_AutoTimer())
		{
			fanMode = LOW;
		}
		break;
	}
	
}
void Fan_NATURALMode()
{

	switch (fanMode)
	{
		case HIGH:
		if(Fan_AutoTimer())
		{
			fanMode = LOW;
		}
		break;
	
		case LOW:
		if(Fan_AutoTimer())
		{
			fanMode = MIDLE;
		}
		break;
		
		case MIDLE:
		if(Fan_AutoTimer())
		{
			fanMode = HIGH;
		}
		break;
	}
}

uint8_t Fan_AutoTimer()
{
	uint16_t MILISEC = 0;
	MILISEC++;
	if(MILISEC>=10000)
	{
		MILISEC = 0;
		return 1;
	}
	return 0;
}
void Fan_Run()
{
	switch (fanMode) {
		case OFF:
		PORTD = 0xff;
		Fan_OFFMode();
		break;
		
		case LOW:
		PORTD = 0b00000100;
		Fan_LOWMode();
		break;
		
		case MIDLE:
		PORTD = 0b00001000;
		Fan_MIDLEMode();
		break;
		
		case HIGH:
		PORTD = 0b00010000;
		Fan_HIGHMode();
		break;
		
		case SLEEP:
		PORTD = 0b00001100;
		Fan_SLEEPMode();
		break;
		
		case NATURAL:
		PORTD = 0b00010100;
		Fan_NATURALMode();
		break;
	}
}
	
void Fan_execute()
{
	Buzzer_SoundON();
	Fan_StateEventCheck();
	Fan_ManualModeCheck();
	FAN_ManualMode();
	Fan_AUTOModeCheck();
	FAN_AUTOMode();
	Fan_Run();
	Buzzer_SoundOFF();
}

void Fan_LCDData()
{
	char buff[30];
	sprintf(buff,"Table Clock");
	LCD_writeStringXY(0,3,buff);
	sprintf(buff,"%s ", UART0_readRxBuff());
	LCD_writeStringXY(1,4,buff);
}