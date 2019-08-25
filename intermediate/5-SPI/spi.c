/*
We do not use the following chip (MCP4821), it is just an example on the SPI protocol. Search up
the datasheet for this chip to understand the bits that we set. The MCP4821 is a Digital to Analog
Converter (DAC). We give it an integer from 0-4095 and the chip will output an analog voltage from
0-5V.
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
void SPI_Transmit_MCP4821(uint16_t i);

int main(void) {
	SPI_MasterInit();
	PORTB = PORTB &~ (1<<PB1);		//LDAC DOWN

	while(1) {
		//We output a triangle wave here
		//Increments of 32 to see noticeable difference each iteration
		for(uint16_t i = 0; i < 4096; i += 32) {
			SPI_Transmit_MCP4821(i);
			_delay_ms(20);
		}
		for(uint16_t i = 4095; i >= 0; i -= 32) {
			SPI_Transmit_MCP4821(i);
			_delay_ms(20);
		}
	}
}

void SPI_MasterInit(void)
{
	DDRB = (1<<DDB3)|(1<<DDB5) |(1<<DDB2)|(0<<DDB0); // Set MOSI, SCK, SS as output, all others input
	SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR0)|(0<<SPR1); // Enables SPI, Master, set clock rate, double speed SPI
	DDRB &= ~(1<<DDB0); // Set trigger source selection pin as input
	SPSR = (1<<SPI2X);
	DDRD |= (1<<DDD7); // Set Pin D7 to be output for indicator light
	//  DDRC &= ~(1<<DDC2);
}

void SPI_MasterTransmit(char cData)
{
	SPDR = cData; // Transfer SPI data to register
	while(!(SPSR & (1<<SPIF)));   // Waits till SPI transfer is completed
}

void SPI_Transmit_MCP4821(uint16_t i) {
	char highbyte, lowbyte;
	highbyte = i>>8;
	lowbyte = i;
	PORTB &= ~(1<<2); //SS sets to low
	SPI_MasterTransmit(highbyte);
	SPI_MasterTransmit(lowbyte);
	PORTB |= 1<<2;   //SS sets to high
}
