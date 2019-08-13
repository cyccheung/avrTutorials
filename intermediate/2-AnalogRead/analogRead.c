/*
Analog becomes a lot trickier compared to Arduino, much more so than digital. We now need to
understand what the Analog to Digital Converter (ADC) does and the registers that you have to set.
*/

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	//Set prescalar to 128, 16MHz --> 125kHz (between 50kHz and 200kHz desired)
	/*
	The ADC circuitry needs an input clock frequency between 50kHz and 200kHz. Given that our clock
	is 16MHz, we need a division factor between 80 and 320. Thus, the only available division
	factor that we can set is 128 by setting ADPS[2:0] to 0b111.
	Setting ADEN to 1 enables the ADC.
	Setting ADSC to 1 starts the first conversion and initializes the ADC
	*/
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN) | (1 << ADSC);

	/*
	Setting REFS0 to 1 sets the reference voltage to AVCC (5V). The reference voltage of an ADC
	allows the ADC to convert inputs from 0V up to the reference voltage.
	Setting ADLAR to 0 right justifies the result. The ADC conversion result consists of 10 bits
	stored in 2 registers (16 bits) called ADCH and ADCL. Left justifying means that bits 9 to 2
	(inclusive) will be stored in ADCH while bit 1 and 0 will be stored in ADCL. Right justifying
	means that bit 9 and 8 will be stored in ADCH and bits 7 to 0 will be stored in ADCL. Check out
	the datasheet for a graphic of how it works.
	*/
	/*
	NOTE: Depending on which ADC channel you are using, you will need to set the MUX[3:0] bits as
	well. We are using ADC0 here so they are set to 0000, the default. The datasheet contains a
	table for channel selections.
	*/
	ADMUX |= (1 << REFS0);

	DDRB |= (1 << PORTB5);	//Sets Digital 13 as an output
	int value;

    while (1)
    {
		value = adc_read();
		if(value < 200) {
			PORTB = 0b00100000;
		}
		else if(value >= 200 && value < 800) {
			PORTB = 0b00010000;
		}
		else {
			PORTB = 0b00001000;
		}
		_delay_ms(100);
    }
}

/*
This function returns a 10 bit number (0-1023). 0 means 0V while 1023 means AREF. The calculation
does involve floats and to save on runtime and memory, we usually just use the raw return value of
this function. We typically use 5V as our AREF.
*/
int adc_read() {
	return (ADCH << 8) | ADCL;
}
