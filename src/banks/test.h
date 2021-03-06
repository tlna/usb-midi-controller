#ifndef _BANKS_TEST_H_
#define _BANKS_TEST_H_

#include <interface.h>
#include <midi.h>

/* temporary functions for buttons presses */

void bank_test_init(struct Bank* bank_handler);

void bank_test_l_press(void);
void bank_test_l_dpress(void);
void bank_test_l_hold(void);

void bank_test_m_press(void);
void bank_test_m_dpress(void);
void bank_test_m_hold(void);

void bank_test_r_press(void);
void bank_test_r_dpress(void);
void bank_test_r_hold(void);

void bank_test_noop(void);

#endif
