#include <avr/io.h>

#include <lcd.h>
#include <midi.h>
#include <interface.h>
#include <descriptors.h>


int main (void) {
    DDRC |= _BV(DDC7); // make arduino led working

    lcd_init();
    interface_init_bank();

    midi_init();

    _delay_ms(3000);

    while(1) {
        midi_handle_tasks();
        interface_handle_buttons();
    }
}

