#include "test.h"

void bank_test_init(struct Bank *bank_handler) {
    bank_handler->name = "Test bank";
    bank_handler->info = "For dev and debug";
    bank_handler->buttons[BUTTON_LEFT].pressed = bank_test_l_press;
    bank_handler->buttons[BUTTON_LEFT].double_pressed = bank_test_l_dpress;
    bank_handler->buttons[BUTTON_LEFT].hold = bank_test_l_hold;
    bank_handler->buttons[BUTTON_MIDDLE].pressed = bank_test_m_press;
    bank_handler->buttons[BUTTON_MIDDLE].double_pressed = bank_test_m_dpress;
    bank_handler->buttons[BUTTON_MIDDLE].hold = bank_test_m_hold;
    bank_handler->buttons[BUTTON_RIGHT].pressed = bank_test_r_press;
    bank_handler->buttons[BUTTON_RIGHT].double_pressed = bank_test_r_dpress;
    bank_handler->buttons[BUTTON_RIGHT].hold = bank_test_r_hold;
}

void bank_test_l_press() {
    interface_print_info("left pressed");
} 

void bank_test_l_dpress() {
    interface_print_info("left pressed twice");
} 

void bank_test_l_hold() {
    interface_print_info("left hold");
}

void bank_test_m_press() {
    interface_print_info("middle pressed");
} 

void bank_test_m_dpress() {
    interface_print_info("middle pressed twice");
} 

void bank_test_m_hold() {
    interface_print_info("middle hold");
}

void bank_test_r_press() {
    interface_print_info("right pressed");
} 

void bank_test_r_dpress() {
    interface_print_info("right pressed twice");
} 

void bank_test_r_hold() {
    interface_print_info("right hold");
}

void bank_b_noop() {
    interface_print_info("noop");
}
