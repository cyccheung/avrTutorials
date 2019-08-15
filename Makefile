MCU         = atmega328p
TARGET_ARCH = -mmcu=$(MCU)
TARGET      = main
CC          = avr-gcc
CPPFLAGS    = -mmcu=$(MCU)
CFLAGS      = -Os -g -Wall -I.
LDFLAGS     = -g -mmcu=$(MCU) -lm -Wl,--gc-sections -Os
PGMER       = -c usbtiny -b 115200
PGMERISP    = -c avrispv2 -P /dev/ttyACM0
DUDE        = /usr/bin/avrdude -V -p $(MCU)

C_SRCS      = $(wildcard *.c)
OBJ_FILES   = $(C_SRCS:.c=.o)

all:	$(TARGET).hex

clean:
	rm -f $(TARGET).elf *.o *.hex

%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_FILES)

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex main.elf eeprom.hex

upload: $(TARGET).hex
	$(DUDE) $(PGMER) -U flash:w:main.hex

flash: main.hex
	avrdude -c usbtiny -p m328p -v -v -U flash:w:main.hex:i

size: main.elf
	avr-size --format=avr --mcu=$(MCU) main.elf
