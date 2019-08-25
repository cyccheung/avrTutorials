/*
We can combine serial and interrupts so we do not have to keep receiving from uart and checking the
input.
*/

#define F_CPU 16000000UL
#define BAUD 9600                                   // define baud
#define MYUBRR ((F_CPU)/(BAUD*16UL)-1)

#include <avr/io.h>
#include <avr/interrupt.h>

void uart_initialize (void)
{
	UBRR0H = (MYUBRR >> 8);                      // shift the register right by 8 bits
	UBRR0L = MYUBRR;                           // set baud rate
	UCSR0B|= (1<<RXEN0 | 1<< TXEN0 | 1 << RXCIE0);							// enable receiver
	UCSR0C|= (1<<UMSEL01)|(1<<UCSZ00)|(1<<UCSZ01);   // 8bit data format
}

// function to receive data
unsigned char uart_recieve (void)
{
	while ((!(UCSR0A)) & (1<<RXC0));         // wait while data is being received
	return UDR0;                             // return 8-bit data
}

int main(void) {
	while(1) {
		if(mode) {
			//Do Task 1
		}
		else {
			//Do Task 2
		}
	}
}

ISR(USART_RX_vect)
{
	switch(byteReceived)
	{
		case 'A':
			mode = 0;
		break;
		case 'B':
			mode = 1;
		break;
		default:
		break;
	}
}
