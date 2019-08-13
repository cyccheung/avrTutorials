/*
As of now, we do not have a good serial monitor that we use when we code with AVR. This makes it
difficult to debug as you are no longer able to print out variable values. The way we work around
that right now is we get the Arduino to transmit the value of the variable through serial to our
computer. On our computers, we have RS232 terminals that can send and receive data via serial. On
my computer, I am running a software called Termite, it is free and you can download it.
Most of the code in here comes from the ATmega328P datasheet. Do read their explanations for these
functions. It also provides information on the different flag bits and how you can use them to
determine if a transmission is complete and other useful conditions.
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
Clock Speed. Some libraries require the macro 'FOSC' and some require 'F_CPU'. Just define both of
them as the same value if you are unsure. It does not affect performance
*/
#define FOSC 16000000
#define BAUD 9600		//Baud rate
#define MYUBRR (FOSC/16/BAUD-1)			//Equation for calculating UBRR value


void USART_Init( unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (3<<UCSZ00);

} // USART_Init

//NOTE: This can only send one char (1 byte) at a time
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

unsigned char received;

int main(void)
{
	USART_Init ( MYUBRR );
	USART_Transmit('H');
	USART_TransmitString("Hello");
	unsigned char data;

    while(1)
    {
        data = USART_Receive();
		USART_TransmitString("Hello");
    }
}
