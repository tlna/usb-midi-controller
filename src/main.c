
#define __AVR_ATmega32U4__
#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"


#define BLINK_DELAY_MS 1000
void blink_led(){
    PORTC |= _BV(PORTC7);
    _delay_ms(BLINK_DELAY_MS);

    PORTC &= ~_BV(PORTC7);
    _delay_ms(BLINK_DELAY_MS);
}


void handle_buttons(){
    lcd_cursor_home();

    // left button
    if( ( PINC & _BV(PC6) ) >> PC6 == 1 ){
        lcd_print("Left   on ");
    }
    else {
        lcd_print("Left  off ");
    }

    // middle button
    if( ( PIND & _BV(PD4) ) >> PD4 == 1 ){
        lcd_print("Middle  on ");
    }
    else {
        lcd_print("Middle off ");
    }

    lcd_cursor_move(0,1);

    // right button
    if( ( PIND & _BV(PD0) ) >> PD0 == 1 ){
        lcd_print("Right  on ");
    }
    else {
        lcd_print("Right off ");
    }

    // bank button
    if( ( PIND & _BV(PD1) ) >> PD1 == 1 ){
        lcd_print("Bank    on");
    }
    else {
        lcd_print("Bank   off");
    }

}


int main (void) {
    DDRC |= _BV(DDC7); // make arduino led working
    lcd_init();

    while(1) {
        handle_buttons();
        _delay_ms( 200 );
    }
}
