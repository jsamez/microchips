#include "I2C.h"


void I2C_init()
{
	I2C_DDR |= ((1<<I2C_SCL) | (1<< I2C_SDA));
	TWBR = 72;
	//TWBR = 32;
	//TWBR = 12;
	TWSR = 	0;
}


void I2C_txByte (uint8_t SLA_W,uint8_t data)
{
	// 1byte의 Data를 송수신 하는 상황 AVR(MASTER)->Device(Slave)
	// 1. Start_bit 송신 (m->s)
	I2C_Start();
	// 2. SLA + W 송신
	I2C_txDevAddr(SLA_W);
	// 3. Ack송신
	//4. 1byte data 송신
	I2C_txData(data);
	//5 ACK송신
	// 6. Stop bit 송신
	I2C_Stop();
}

void I2C_Start()
{
	// send Start condition
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	//Wait for TWINT flag set. This indicates that the START condition has been transmitted
	while (!(TWCR & (1<<TWINT)));
}

void I2C_txDevAddr(uint8_t SLA_W)
{
	//Load SLA_W into TWDR Register.
	//Clear TWINT bit in TWCR to start transmission of address
	TWDR = SLA_W;
	TWCR = (1<<TWINT) | (1<<TWEN);
	//Wait for TWINT flag set. This indicates that the SLA+W has been transmitted, and ACK/NACK has been received.
	while (!(TWCR & (1<<TWINT)));
}

void I2C_txData(uint8_t data)
{
	//Load DATA into TWDR Register. Clear TWINT bit in TWCR to start transmission of data
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	//Wait for TWINT flag set. This indicates that theDATA has been transmitted,
	//and ACK/NACK has been received.
	while (!(TWCR & (1<<TWINT)));
}

void I2C_Stop()
{
	//Transmit STOP condition
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
