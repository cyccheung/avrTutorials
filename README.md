# AVR Tutorials for Unmanned Ground Vehicle (UGV)
These tutorials assume that you are familiar with using the Arduino IDE and language. Do check out the other [repo](https://github.com/cyccheung/ArdTutorials) if you are not.

## Datasheets
You should be at least comfortable with looking for solutions in component datasheets by now. With AVR, you now need to start looking at ATmega328P's datasheet a lot more often. It is a very long datasheet and you might not understand a lot of what they are saying (I do not either). But having said that, there is still a lot of information in there that you need. The bits to set to change an interrupt's behavior and code examples are just a small fraction of the things in there.

## Useful links and documents
1. [TI I2C guide](http://www.ti.com/lit/an/slva704/slva704.pdf)
2. [HMC5883L Compass](https://www.electronicwings.com/avr-atmega/magnetometer-hmc5883l-interfacing-with-atmega16)
3. [u-blox 8 GPS Receiver Description](https://www.u-blox.com/sites/default/files/products/documents/u-blox8-M8_ReceiverDescrProtSpec_%28UBX-13003221%29_Public.pdf)

## BN-880 Wiring
Here is how you hook up the BN-880. SDA and SCL are for the compass. TX and RX are the serial lines for the GPS.
![alt text](https://github.com/cyccheung/avrTutorials/blob/master/images/GPS%20Wiring.JPG "GPS Wiring")

## Feedback
Constructive feedback on my code is always welcome as usual. If there are errors or code that should be explained better, do send me an email and I would be happy to learn from you.
