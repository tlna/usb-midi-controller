#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"

#define BUTTON_LEFT_PIN     PC6
#define BUTTON_MIDDLE_PIN   PD4
#define BUTTON_RIGHT_PIN    PD0
#define BUTTON_BANK_PIN     PD1
#define BANK_LIST_COUNT 2
#define BUTTONS_COUNT 3
#define BUTTON_LEFT   0
#define BUTTON_MIDDLE 1
#define BUTTON_RIGHT  2
#define BUTTON_PRESSED  1
#define BUTTON_RELEASED 0
#define BUTTON_HOLD_TIME 32000
#define BUTTON_CLICK_DELAY_MS 0.5


struct Button {
    void (*pressed)();
    void (*double_pressed)();
    void (*hold)();
};


struct Bank {
    const char *name;
    const char *info;
    struct Button buttons[3];
};


void interface_init_bank();

void interface_handle_buttons();
void interface_handle_button(const char button, const char pressed);
void interface_handle_button_bank(const char pressed);

void interface_print_bank(const char* bank_name, const char* bank_info);
void interface_print_info(const char* bank_info);

#endif
