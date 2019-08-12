/*
As always we start off with blinking an LED. The structure of the code is different from what you might be used to with the Arduino language. If you have or are taking 101/183, it is similar to what you do for C++.
*/

/*
This first line defines the macro 'F_CPU' as the speed of the MCU that you are working with. On an Arduino Nano, it is 16MHz (16 followed by 6 zeros). It is primarily used by the code to determine how much real time has passed. For instance, if you want the code to delay for a second, the Arduino will delay the code for 16 million clock cycles. If F_CPU is defined incorrectly, let's say the real speed is 16MHz and it is defined as 8MHz, then your one second delays will end up being 0.5 second delays.
*/
#define F_CPU 16000000UL

/*
Next, you include the libraries which you need. Usually you fill this part up as you write the code, including libraries containing functions that you use along the way.
*/
#include <avr/io.h>
#include <util/delay.h>

//Every code has a function called 'main'
int main(void)
{
	/*
	When you were using the Arduino language, you had a setup() and a loop() function. Anything in the setup() function is run once when the code starts up. And anything in the loop() function is run over and over again. With AVR, anything that goes here before the while(1) loop is the equivalent of the setup() function.
	*/

	/*
	This next line defines pin Digital 13 as an output.
	DDRB - Data Direction Register B. As the name suggests, this register sets whether a pin is an input(0) or an output(1). It has a total of 8 bits, setting the data direction of 8 pins (B7-B0).
	NOTE: There are a lot of different ways that you can write the same thing using macros provided in the <avr/io.h> library. If you happen across another way while googling, feel free to try them.
	*/
	//TODO: Try to google 'Arduino Nano Pinout' and look for images. Look for an image that tells you which pins correspond to which number. Then change a single digit in the following line such that pin 13 is an output.
	DDRB = 0b00000000;

	/*
	This while loop is the equivalent of the loop() function in Arduino language
	*/
    while(1)
    {
		/*
		The following 4 lines sets the PORTB register accordingly and delays for half a second. Setting the appropriate bit to 1 will cause the LED to light up.
		*/
		PORTB = 0b00100000;
		_delay_ms(500);
		PORTB = 0b00000000;
		_delay_ms(500);
    }
}
