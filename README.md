# AVR Tutorials for Unmanned Ground Vehicle (UGV)
These tutorials assume that you are familiar with using the Arduino IDE and language. Do check out the other [repo](https://github.com/cyccheung/ArdTutorials) if you are not.

## Datasheets
You should be at least comfortable with looking for solutions in component datasheets by now. With AVR, you now need to start looking at ATmega328P's datasheet a lot more often. It is a very long datasheet and you might not understand a lot of what they are saying (I do not either). But having said that, there is still a lot of information in there that you need. The bits to set to change an interrupt's behavior and code examples are just a small fraction of the things in there.

## Useful links and documents
1. [TI I2C guide](http://www.ti.com/lit/an/slva704/slva704.pdf)
2. [HMC5883L Compass](https://www.electronicwings.com/avr-atmega/magnetometer-hmc5883l-interfacing-with-atmega16)
3. [u-blox 8 GPS Receiver Description](https://www.u-blox.com/sites/default/files/products/documents/u-blox8-M8_ReceiverDescrProtSpec_%28UBX-13003221%29_Public.pdf)

## Compiling and flashing code to Arduino
There is a Makefile that you should copy into the same folder as your code. Note that the Makefile looks for any main.c file in the same folder as it is. I have not gone round to making the Makefile more adaptable so each main.c file requires its own Makefile and folder.
Run the following in your terminal to compile the main.c:
```
make
```
If you are using Windows, run the following line in cmd.exe:
```
avrdude -c usbtiny -p m328p -v -v -U flash:w:main.hex:i
```
If you are using Mac or Linux, see if the preceding line runs in terminal. I do not have the means to try it so I have no idea.

## Common Bugs and Problems
**1. Bad connection to Arduino board**
```
avrdude: initialization failed, rc=-1
		 Double check connections and try again, or use -F to override this check.

avrdude done. Thank you.
```
Try reversing how the ribbon cable is connected to the Arduino. That is usually the fix although other connection issues are possible.

**2. Bootloader for Arduino**
```
avrdude: stk500_recv(): programmer is not responding
avrdude: stk500_getsync() attempt 1 of 10: not in sync: resp=0x77
avrdude: stk500_recv(): programmer is not responding
avrdude: stk500_getsync() attempt 2 of 10: not in sync: resp=0x77
...
avrdude done.  Thank you.

Problem uploading to board.  See http://www.arduino.cc/en/Guide/Troubleshooting#upload for suggestions.
```
Sometimes when you are debugging, it is convenient to switch back to Arduino just to make sure the hardware is working correctly. Once you have flashed an AVR C code to the Arduino, you will be unable to upload the code using the Arduino IDE. Arduino IDE will take a while to attempt all 10 tries. To solve this, plug in the Arduino as you would when you flash AVR C code. Then in the Arduino IDE, go to the "Tools" drop down menus at the top and then click on "Burn Bootloader".

**3. Serial isn't working**
A couple of our devices use serial to send data to the Arduino. Sometimes it just does not work and there are a few possible reasons why.
* Make sure the baud rate is correct
* Make sure the device has power
* Make sure the Tx and Rx lines are connected correctly. It is worth it to flip these two even if you think you have it right

## BN-880 Wiring
Here is how you hook up the BN-880. SDA and SCL are for the compass. TX and RX are the serial lines for the GPS.
![alt text](https://github.com/cyccheung/avrTutorials/blob/master/images/GPS%20Wiring.JPG "GPS Wiring")

## Feedback
Constructive feedback on my code is always welcome as usual. If there are errors or code that should be explained better, do send me an email and I would be happy to learn from you.
