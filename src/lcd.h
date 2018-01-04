#ifndef _LCD_H_
#define _LCD_H_

#define __AVR_ATmega32U4__
#include <avr/io.h>
#include <util/delay.h>

#define P_RS  PD6  // lcd pin 4, register select signal
#define P_EN  PB7  // lcd pin 6, enable signal
#define P_DB4 PB6  // lcd pin 11, data bus line
#define P_DB5 PB5  // lcd pin 12, data bus line
#define P_DB6 PB4  // lcd pin 13, data bus line
#define P_DB7 PE6  // lcd pin 14, data bus line

#define P_RS_UP       (PORTD |=  _BV( P_RS ))
#define P_RS_DOWN     (PORTD &= ~_BV( P_RS ))

#define P_EN_UP       (PORTB |=  _BV( P_EN ))
#define P_EN_DOWN     (PORTB &= ~_BV( P_EN ))

#define P_DB4_UP      (PORTB |=  _BV( P_DB4 ))
#define P_DB4_DOWN    (PORTB &= ~_BV( P_DB4 ))

#define P_DB5_UP      (PORTB |=  _BV( P_DB5 ))
#define P_DB5_DOWN    (PORTB &= ~_BV( P_DB5 ))

#define P_DB6_UP      (PORTB |=  _BV( P_DB6 ))
#define P_DB6_DOWN    (PORTB &= ~_BV( P_DB6 ))

#define P_DB7_UP      (PORTE |=  _BV( P_DB7 ))
#define P_DB7_DOWN    (PORTE &= ~_BV( P_DB7 ))


void lcd_init();
void lcd_db_pin_set(char db);
void lcd_cmd_set(char db, char rs);

void lcd_cursor_home();
void lcd_cursor_move(int row, int line);

void lcd_clear();
void lcd_print(const char *str);

#endif
