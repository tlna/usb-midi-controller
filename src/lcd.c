#include "lcd.h"

void lcd_init(void) {
    DDRD |= _BV( P_RS  );
    DDRB |= _BV( P_EN  );
    DDRB |= _BV( P_DB4 );
    DDRB |= _BV( P_DB5 );
    DDRB |= _BV( P_DB6 );
    DDRE |= _BV( P_DB7 );

    _delay_ms( 30 );
    P_RS_DOWN; P_EN_DOWN;

    lcd_db_pin_set(0x3);
    P_EN_UP; _delay_ms( 4.1 ); P_EN_DOWN;

    lcd_db_pin_set(0x3);
    P_EN_UP; _delay_ms( 0.1 ); P_EN_DOWN;

    lcd_db_pin_set(0x3);
    P_EN_UP; _delay_ms( 4.1 ); P_EN_DOWN;

    lcd_db_pin_set(0x2);
    P_EN_UP; _delay_ms( 2 ); P_EN_DOWN; // from here we have 4 bit mode

    lcd_cmd_set( 0x0C, 0 ); // display on/off control - turn on display, no cursor
    lcd_cmd_set( 0x06, 0 ); // entry mode - set cursor to increment, no display shift
    lcd_cmd_set( 0x28, 0 ); // function set - set 4 bit mode, two lines

    lcd_clear(); // clear the screen
}

void lcd_db_pin_set(char db) {
    (db & 8) >> 3 == 1 ? P_DB7_UP : P_DB7_DOWN;
    (db & 4) >> 2 == 1 ? P_DB6_UP : P_DB6_DOWN;
    (db & 2) >> 1 == 1 ? P_DB5_UP : P_DB5_DOWN;
    (db & 1) >> 0 == 1 ? P_DB4_UP : P_DB4_DOWN;
}

void lcd_cmd_set(char db, char rs) {
    P_EN_DOWN;
    rs == 0 ? P_RS_DOWN : P_RS_UP;
    lcd_db_pin_set( db >> 4 );
    P_EN_UP;
    _delay_ms( 0.2 );
    P_EN_DOWN;
    lcd_db_pin_set( db & 0x0F );
    P_EN_UP;
    _delay_ms( 0.2 );
    P_EN_DOWN;
}

void lcd_cursor_home(void) {
    lcd_cmd_set( 0x02, 0 );
    _delay_ms( 2 );
}

void lcd_cursor_move(int row, int line) {
    static const int line_ofsets[] = { 0, 0x40 };
    lcd_cmd_set( 0x80 + row + line_ofsets[line] , 0 );
}

void lcd_clear(void) {
    lcd_cmd_set( 0x01, 0 );
    _delay_ms( 2 );
}

void lcd_print(const char *str) {
    for(; *str != '\0'; str++ ) lcd_cmd_set(*str, 1);
}
