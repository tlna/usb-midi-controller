#define __AVR_ATmega32U4__
#include <avr/io.h>

#include "lcd.h"
#include "interface.h"


int main (void) {
    DDRC |= _BV(DDC7); // make arduino led working

    lcd_init();
    interface_init_bank();

    while(1) interface_handle_buttons();
}
