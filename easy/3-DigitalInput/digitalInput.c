/*
Now that you can set a pin to 1 or 0, let's read a pin.
*/

#define F_CPU 16000000UL

#include <avr/io.h>

int main(void) {
	byte value;

	//TODO: Set pin 12 as an input


	while(1) {
		//Value of digital read is already stored in the PINB register
		value = PINB;
		/*
		value variable now stores 0bx_xxxxxx, with the blank space being what we are interested in
		and 'x's we do not care what the value is. The value is either a 1 or a 0, so we make use
		of bit masking to get what we want
		*/
		value = (value >> 6) & 0b00000001;
	}
}
