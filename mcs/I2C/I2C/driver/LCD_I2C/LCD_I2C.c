#include "LCD_I2C.h"

uint8_t lcdControlData;

void LCD_BackLighteON(){
	lcdControlData |= (1<<LCD_BackLighte);
	LCD_SendToI2C(LCD_SLA_W,lcdControlData);
}

void LCD_BackLighteOFF(){
	lcdControlData &= ~(1<<LCD_BackLighte);
	LCD_SendToI2C(LCD_SLA_W,lcdControlData);
}

void LCD_init()
{

	I2C_init();
	lcdControlData = 0;
	_delay_ms(15);
	
	LCD_cmdMode();
	LCD_writeMode();
	LCD_writeNibble(0x30);
	_delay_ms(5);
	LCD_writeNibble(0x30);
	_delay_ms(1);
	LCD_writeNibble(0x30);
	LCD_writeNibble(0x20);
	LCD_writeCmdData(LCD_4bit_FUNCTION_SET);   // LCD_4bit_FUNCTION_SET      0x28
	LCD_writeCmdData(LCD_DISPLAY_OFF);         // LCD_DISPLAY_OFF            0x08
	LCD_writeCmdData(LCD_DISPLAY_CLEAR);      // LCD_DISPLAY_CLEAR         0x01
	LCD_writeCmdData(LCD_ENTRY_MODE_SET);      // LCD_ENTRY_MODE_SET         0x06
	LCD_writeCmdData(LCD_DISPLAY_ON);         // LCD_DISPLAY_ON            0x0C
	LCD_BackLighteON();
}

void LCD_SendToI2C(uint8_t sla_w, uint8_t data)
{
	I2C_txByte(sla_w, data);
}

void LCD_cmdMode()
{
	// RS pin : bit 0 set
	lcdControlData &= ~(1<<LCD_RS);
	LCD_SendToI2C(LCD_SLA_W,lcdControlData);
	
}

void LCD_charMode()
{
	// RS pin : bit 0 set
	lcdControlData |= (1<<LCD_RS);
	LCD_SendToI2C(LCD_SLA_W,lcdControlData);;
}

void LCD_writeMode()
{lcdControlData &= ~(1<<LCD_RW);
	LCD_SendToI2C(LCD_SLA_W,lcdControlData);
}

void LCD_enableHigh()
{
	// E pin : bit 1 set
	lcdControlData |= (1<<LCD_E);
	LCD_SendToI2C(LCD_SLA_W,lcdControlData);;
	_delay_ms(1);
}

void LCD_enableLow()
{
	// E pin : bit 0 set
	lcdControlData &= ~(1<<LCD_E);
	LCD_SendToI2C(LCD_SLA_W,lcdControlData);
	_delay_ms(1);
}

void LCD_writeNibble(uint8_t data)
{
	LCD_enableHigh();
	lcdControlData = (lcdControlData & 0x0f)| (data & 0xf0);
	LCD_SendToI2C(LCD_SLA_W, lcdControlData);
	LCD_enableLow();
}

void LCD_writeByte(uint8_t data)
{
	// 8 bit PORTC write
	LCD_writeNibble(data);
	data<<=4;
	LCD_writeNibble(data);
}


// MCU -> LCD 명령어를 보낼 경우 (write mode)

void LCD_writeCmdData(uint8_t data)
{
	// LCD 명령어 전달
	LCD_cmdMode();
	LCD_writeMode();
	LCD_enableHigh();
	LCD_writeByte(data);
	LCD_enableLow();
	
}

// MCU -> LCD Data를 보낼 경우 (write mode)
void LCD_writeCharData(uint8_t data)
{
	// LCD Character 쓰기 전달
	LCD_charMode();
	LCD_writeMode();
	LCD_enableHigh();
	LCD_writeByte(data);
	LCD_enableLow();
}

void LCD_writeString(char *str)
{
	for(int i=0; str[i] ; i++)
	{
		LCD_writeCharData(str[i]);
	}
}

void LCD_gotoXY(uint8_t row, uint8_t col)
{
	col%= 16; row %=2;
	uint8_t lcdregisterAddress = (0x40 * row ) + col;
	uint8_t command = 0x80 + lcdregisterAddress;
	LCD_writeCmdData(command);
}

void LCD_writeStringXY(uint8_t row, uint8_t col, char *str)
{
	LCD_gotoXY(row,col);
	LCD_writeString(str);
}

void LCD_clearDisplay()
{
	LCD_writeCmdData(LCD_DISPLAY_CLEAR);
}
