#include "interface.h"

static struct Bank bank_list[BANK_LIST_COUNT];
static int bank_id = 0;

/* temporary functions for buttons presses */
void bank_a_l_press() { interface_print_info("left pressed"); } 
void bank_a_l_dpress() { interface_print_info("left pressed twice"); } 
void bank_a_l_hold() { interface_print_info("left hold"); }

void bank_a_m_press() { interface_print_info("middle pressed"); } 
void bank_a_m_dpress() { interface_print_info("middle pressed twice"); } 
void bank_a_m_hold() { interface_print_info("middle hold"); }

void bank_a_r_press() { interface_print_info("right pressed"); } 
void bank_a_r_dpress() { interface_print_info("right pressed twice"); } 
void bank_a_r_hold() { interface_print_info("right hold"); }

void bank_b_noop() { interface_print_info("noop"); }
/* end of temporary function */


void interface_init_bank() {
    bank_list[0].name = "Bank A";
    bank_list[0].info = "foo";
    bank_list[0].buttons[BUTTON_LEFT].pressed = bank_a_l_press;
    bank_list[0].buttons[BUTTON_LEFT].double_pressed = bank_a_l_dpress;
    bank_list[0].buttons[BUTTON_LEFT].hold = bank_a_l_hold;
    bank_list[0].buttons[BUTTON_MIDDLE].pressed = bank_a_m_press;
    bank_list[0].buttons[BUTTON_MIDDLE].double_pressed = bank_a_m_dpress;
    bank_list[0].buttons[BUTTON_MIDDLE].hold = bank_a_m_hold;
    bank_list[0].buttons[BUTTON_RIGHT].pressed = bank_a_r_press;
    bank_list[0].buttons[BUTTON_RIGHT].double_pressed = bank_a_r_dpress;
    bank_list[0].buttons[BUTTON_RIGHT].hold = bank_a_r_hold;

    bank_list[1].name = "Bank B";
    bank_list[1].info = "foo for bank B";
    bank_list[1].buttons[BUTTON_LEFT].pressed = bank_b_noop;
    bank_list[1].buttons[BUTTON_LEFT].double_pressed = bank_b_noop;
    bank_list[1].buttons[BUTTON_LEFT].hold = bank_b_noop;
    bank_list[1].buttons[BUTTON_MIDDLE].pressed = bank_b_noop;
    bank_list[1].buttons[BUTTON_MIDDLE].double_pressed = bank_b_noop;
    bank_list[1].buttons[BUTTON_MIDDLE].hold = bank_b_noop;
    bank_list[1].buttons[BUTTON_RIGHT].pressed = bank_b_noop;
    bank_list[1].buttons[BUTTON_RIGHT].double_pressed = bank_b_noop;
    bank_list[1].buttons[BUTTON_RIGHT].hold = bank_b_noop;

    interface_print_bank(bank_list[bank_id].name, bank_list[bank_id].info);
}


void interface_handle_buttons() {
    // left button
    if( ( PINC & _BV(BUTTON_LEFT_PIN) ) >> BUTTON_LEFT_PIN == 1 )
        interface_handle_button(BUTTON_LEFT, BUTTON_PRESSED);
    else
        interface_handle_button(BUTTON_LEFT, BUTTON_RELEASED);

    // middle button
    if( ( PIND & _BV(BUTTON_MIDDLE_PIN) ) >> BUTTON_MIDDLE_PIN == 1 )
        interface_handle_button(BUTTON_MIDDLE, BUTTON_PRESSED);
    else
        interface_handle_button(BUTTON_MIDDLE, BUTTON_RELEASED);

    // right button
    if( ( PIND & _BV(BUTTON_RIGHT_PIN) ) >> BUTTON_RIGHT_PIN == 1 )
        interface_handle_button(BUTTON_RIGHT, BUTTON_PRESSED);
    else
        interface_handle_button(BUTTON_RIGHT, BUTTON_RELEASED);

    // bank button
    if( ( PIND & _BV(BUTTON_BANK_PIN) ) >> BUTTON_BANK_PIN == 1 )
        interface_handle_button_bank(BUTTON_PRESSED);
    else 
        interface_handle_button_bank(BUTTON_RELEASED);
}


void interface_handle_button(const char button, const char pressed) {
    static char was_pressed[BUTTONS_COUNT];
    static unsigned int delay_hold[BUTTONS_COUNT], delay_doublepress[BUTTONS_COUNT];

    if( pressed == BUTTON_PRESSED
            && delay_hold[button] == BUTTON_HOLD_TIME )
        bank_list[bank_id].buttons[button].hold();

    if( delay_doublepress[button] < BUTTON_DOUBLEPRESS_TIME
            && was_pressed[button] == BUTTON_RELEASED
            && pressed == BUTTON_PRESSED )
        bank_list[bank_id].buttons[button].double_pressed();

    if( was_pressed[button] == BUTTON_PRESSED
            && pressed == BUTTON_RELEASED
            && delay_hold[button] < BUTTON_HOLD_TIME
            && delay_doublepress[button] >= BUTTON_DOUBLEPRESS_TIME )
    {
        bank_list[bank_id].buttons[button].pressed();
        delay_doublepress[button] = 0;
    }

    if( pressed == BUTTON_RELEASED ) delay_hold[button] = 0;
    else ++delay_hold[button];

    if( delay_doublepress[button] < BUTTON_DOUBLEPRESS_TIME ) ++delay_doublepress[button];

    if( was_pressed[button] != pressed ) _delay_ms(BUTTON_CLICK_DELAY_MS);

    was_pressed[button] = pressed;
}


void interface_handle_button_bank(const char pressed) {
    static char was_pressed;

    if(was_pressed == pressed) return;

    if(pressed == BUTTON_PRESSED) {
        bank_id = (bank_id + 1) % BANK_LIST_COUNT;
        interface_print_bank(bank_list[bank_id].name, bank_list[bank_id].info);
    }

    was_pressed = pressed;

    _delay_ms(BUTTON_CLICK_DELAY_MS);
}


void interface_print_bank(const char* bank_name, const char* bank_info) {
    char line[21];

    sprintf(line, "%02d: %-16s", bank_id, bank_name);
    line[20] = '\0';
    lcd_cursor_home();
    lcd_print(line);

    interface_print_info(bank_info);
}


void interface_print_info(const char* bank_info) {
    char line[21];

    sprintf(line, "%-20s", bank_info);
    line[20] = '\0';
    lcd_cursor_move(0,1);
    lcd_print(line);
}
