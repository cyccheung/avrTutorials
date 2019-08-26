/*
Connections:
Arduino TX - GPS TX
Arduino RX - GPS RX

The GPS outputs a long string containing information on latitude, longitude, altitude...
The GPS by default outputs this string continuously, flooding the serial line with that string.
We do not want that, we want to be able to control when we receive the GPS string. This GPS is part
of the U-blox family of GPS modules. There is a software called u-center that allows you to
configure the GPS behavior. We turn off automatic polling to prevent the serial line from getting
flooded. And to trigger the GPS polling, we send the following string via serial:
$PUBX,00*33\r\n
\r --> Carriage return
\n --> Newline character
*/

#include <avr/io.h>
#include <util/delay.h>

#define FOSC 16000000	//Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)			//Equation for calculating UBRR value

//Function prototypes
void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
void USART_TransmitString(char *data);
char USART_Receive( void );

int main(void) {
	USART_Init ( MYUBRR );
	while(1) {
		USART_TransmitString("$PUBX,00*33\r\n");
		_delay_ms(1000);
	}
}
