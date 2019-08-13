/*
In this code, the Arduino is doing three hypothetical tasks. It does task 3 at all times and tasks 1 and 2 occasionally. We make use of both external interrupts on the Arduino
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>		//Include the interrupt library

volatile int mode = 0;			//Remember to include the volatile keyword

int main(void) {
	//Configure INT0 to trigger on a rising edge
	EICRA |= (1 << ISC01);
	EICRA |= (1 << ISC00);
	//Configure INT1 to trigger on a falling edge
	EICRA |= (1 << ISC11);
	//Enable INT0 and INT1
	EIMSK |= (1 << INT0) | (1 << INT1);

	sei();		//Sets external interrupts

	while(1) {
		if(mode == 1) {
			mode = 0;
			//Do task 1
		}
		else if(mode == 2) {
			mode = 0;
			//Do task 2
		}
		else {
			//Do task 3
		}
	}
}

/*
This is how interrupt service routines are defined in AVR. If you remember, the Arduino Nano has 2 external interrupt pins at digital 2 and 3. These are called INT0 and INT1 respectively.
Note that these ISRs do the least amount of work possible. We could have put all the code needed for Task 1 in the first ISR but it is good practice to leave the heavy lifting to the main function.
*/
ISR(INT0_vect) {
	mode = 1;
}

ISR(INT1_vect) {
	mode = 2;
}
