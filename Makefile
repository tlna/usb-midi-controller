CC=avr-gcc

prog.hex: prog.elf
	avr-objcopy -O ihex -R .eeprom $^ $@

prog.elf: src/main.c src/lcd.c
	${CC} -Os -DF_CPU=16000000UL -mmcu=atmega328p -o $@ $^

upload: prog.hex
	avrdude -F -V -c avr109 -p m32u4 -P /dev/ttyACM0 -b 115200 -U flash:w:$^

clean:
	rm -v prog{.elf,.hex}   ||true
