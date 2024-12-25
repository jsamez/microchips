#include "FAN.h"

button_t btnMode, btnFanState, btnTimerInc, btnTimerDic;
uint8_t uartMessage[20];
uint8_t fanMode;
uint8_t fanState;

void Fan_init()
{
	Buzzer_init();
	UART0_init();
	TIM0_init();
	TIM2_init();
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
		Fan_ManualModeCheck();
		FAN_ManualMode();
		break;
		case AUTO:
		if(button_getstate(&btnFanState) == ACT_RELEASED)
		{
			fanState = MANUAL;
			fanMode = OFF;
		}
		Fan_AUTOModeCheck();
		FAN_AUTOMode();
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
		uint8_t* rxString = UART0_readRxBuff();
		printf("%s\n", (char *)rxString);
		if(!strcmp((char *)rxString,"Fan Mode: OFF\n"))
		{
			Fan_OFFMode();
		}
		else if(!strcmp((char *)rxString,"Fan Mode: LOW\n"))
		{
			Fan_LOWMode();
		}
		else if(!strcmp((char *)rxString,"Fan Mode: MIDLE\n"))
		{
			Fan_MIDLEMode();
		}
		else if(!strcmp((char *)rxString,"Fan Mode: HIGH\n"))
		{
			Fan_HIGHMode();
		}
	}
}

void FAN_AUTOMode()
{
	if(UART0_getRxFlag())
	{
		UART0_clearRxFlag();
		uint8_t* rxString = UART0_readRxBuff();
		printf("%s\n", (char *)rxString);
		
		if(!strcmp((char *)rxString,"Fan Mode: SLEEP\n"))
		{
			Fan_SLEEPMode();
		}
		else if(!strcmp((char *)rxString,"Fan Mode: NATURAL\n"))
		{
			Fan_NATURALMode();
		}
	}
}

void FAN_makeHertz(uint16_t hertz)
{
	if (hertz < 100)
	{
		hertz =100;
	}
	else if(hertz >5000)
	{
		hertz = 5000;
	}
	FAN_ICR = (250000/ hertz)-1;
	FAN_OCR = FAN_ICR/2;
}

void Fan_OFFMode()
{
	FAN_makeHertz(0);
}

void Fan_LOWMode()
{
	FAN_makeHertz(300);
}

void Fan_MIDLEMode()
{
	FAN_makeHertz(600);
}

void Fan_HIGHMode()
{
	FAN_makeHertz(900);
}

void Fan_execute()
{
	Fan_StateEventCheck();
}

void Fan_SLEEPMode()
{
	uint8_t Sleep_mode;
	Sleep_mode = LOW;
	switch (Sleep_mode)
	{
		case LOW:
		if(Fan_AutoTimer())
		{
			Sleep_mode = MIDLE;
		}
		Fan_LOWMode();
		break;
		case MIDLE:
		if(Fan_AutoTimer())
		{
			Sleep_mode = OFF;
		}
		Fan_MIDLEMode();
		break;
		case OFF:
		if(Fan_AutoTimer())
		{
			Sleep_mode = LOW;
		}
		Fan_LOWMode();
		break;
	}
	
}
void Fan_NATURALMode()
{
	uint8_t Natural_mode;
	Natural_mode = HIGH;
	switch (Natural_mode)
	{
		case HIGH:
		if(Fan_AutoTimer())
		{
			Natural_mode = LOW;
		}
		Fan_HIGHMode();
		break;
		case LOW:
		if(Fan_AutoTimer())
		{
			Natural_mode = MIDLE;
		}
		Fan_LOWMode();
		break;
		case MIDLE:
		if(Fan_AutoTimer())
		{
			Natural_mode = HIGH;
		}
		Fan_MIDLEMode();
		break;
	}
}

uint8_t Fan_AutoTimer()
{
	uint16_t milisec = 0;
	if(milisec>=5000)
	{
		milisec = 0;
		return 1;
	}
	milisec++;
	return 0;
}