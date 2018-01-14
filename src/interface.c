#include "interface.h"

static struct Bank bank_list[BANK_LIST_COUNT];
static int bank_id = 0;


void interface_init_bank() {
    bank_test_init(&bank_list[0]);

    bank_list[1].name = "Bank B";
    bank_list[1].info = "foo for bank B";

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

    // enter into boodloader
    if( ( PIND & _BV(BUTTON_BANK_PIN) ) >> BUTTON_BANK_PIN == 1
            && ( PINC & _BV(BUTTON_LEFT_PIN) ) >> BUTTON_LEFT_PIN == 1  ) {
        lcd_clear();
        lcd_cursor_home();
        lcd_print("Flashing...");
        asm volatile("jmp 0x3800");
    }
}


void interface_handle_button(const char button, const char pressed) {
    static char was_pressed[BUTTONS_COUNT];
    static unsigned int delay_hold[BUTTONS_COUNT], delay_doublepress[BUTTONS_COUNT];

    // handle hold button action
    if( pressed == BUTTON_PRESSED
            && delay_hold[button] == BUTTON_HOLD_TIME )
        bank_list[bank_id].buttons[button].hold();

    // handle double press button action
    if( delay_doublepress[button] < BUTTON_DOUBLEPRESS_TIME
            && was_pressed[button] == BUTTON_RELEASED
            && pressed == BUTTON_PRESSED )
        bank_list[bank_id].buttons[button].double_pressed();

    // handle single button press action
    if( was_pressed[button] == BUTTON_PRESSED
            && pressed == BUTTON_RELEASED
            && delay_hold[button] < BUTTON_HOLD_TIME
            && delay_doublepress[button] >= BUTTON_DOUBLEPRESS_TIME )
    {
        bank_list[bank_id].buttons[button].pressed();
        delay_doublepress[button] = 0;
    }

    // counter for hold button action
    if( pressed == BUTTON_RELEASED ) delay_hold[button] = 0;
    else ++delay_hold[button];

    // counter for double press button action
    if( delay_doublepress[button] < BUTTON_DOUBLEPRESS_TIME ) ++delay_doublepress[button];

    // delay for button press - to avoid unwanted extra click
    if( was_pressed[button] != pressed ) _delay_ms(BUTTON_CLICK_DELAY_MS);

    // save selected button as previous one
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
