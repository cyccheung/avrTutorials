/*
For I2C, we will use a library by Peter Fleury. He has a website with documentation and
instructions on how to install and use this library, do Google it.

Our compass module uses the I2C protocol. Its model number is HMC5883L, pull up its datasheet

Arduino A4 - Compass SDA
Arduino A5 - Compass SCL

Note that the heading will be a float. We are unable to transmit it using our USART_TRANSMIT
function. For the purpose of seeing the result, we will convert the float into a string before
printing it out
*/

#include "i2cmaster.h"
#include "math.h"

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)			//Equation for calculating	UBRR value

#define compass 0x3C      // I2C device address of compass
float PI = 3.1415;

//Function prototypes, if you write any new functions, put prototypes here
void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
void USART_TransmitString(char *data);
char USART_Receive( void );
int getHeading();

int main(void) {
	USART_Init ( MYUBRR );		//Starts up USART

	int heading = 0;
	char headingString[4];				//Array to store string version of heading
	i2c_init();                             // initialize I2C library
	i2c_start_wait(compass+I2C_WRITE);     // set device address and write mode

	//Set to continuous measurement mode
	i2c_write(0x02);
	i2c_write(0x00);
	i2c_stop();
	while(1) {
		heading = getHeading();
		itoa(heading, headingString, 10);	//Convert int into string, store in headingString, base 10
		USART_TransmitString(headingString);
		USART_TransmitString("\r\n");
		_delay_ms(67);		//Datasheet recommends waiting 67ms between reads. 15Hz equates to roughly 67ms delay between reads
	}
}

void USART_Init( unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (3<<UCSZ00);

} // USART_Init

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void USART_TransmitString(char *data){

	while(*data){
		USART_Transmit(*data++);
	}

}

char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

//Function reads compass registers and returns heading as int
int getHeading() {
	int x,y,z;
	double heading;
	i2c_start_wait(compass);	//Start communication with compass
	i2c_write(0x03);			//Memory location address
	i2c_rep_start(compass+I2C_READ);	//Repeated start
	//Read data output registers. Note x,z,y register configuration on compass
	x = (((int)i2c_readAck() << 8) | (int)i2c_readAck());
	z = (((int)i2c_readAck() << 8) | (int)i2c_readAck());
	y = (((int)i2c_readAck() << 8) | (int)i2c_readNak());	//Note readNak for last read
	i2c_stop();
	heading = atan2((double)y,(double)x) + declination;		//Calculate heading and add declination
	//Makes sure 0 < heading < 360 deg
	if(heading > 2*PI) {
		heading -= 2*PI;
	}
	else if(heading < 0) {
		heading += 2*PI;
	}
	return heading * 180 / PI;		//Convert into degrees before returning
}
