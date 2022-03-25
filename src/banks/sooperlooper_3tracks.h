#ifndef _BANKS_SOOPERLOOPER_3TRACKS_H_
#define _BANKS_SOOPERLOOPER_3TRACKS_H_

#include <interface.h>
#include <midi.h>

void bank_sl3track_init(struct Bank* bank_handler);

void bank_sl3track_l_press(void);
void bank_sl3track_l_dpress(void);
void bank_sl3track_l_hold(void);

void bank_sl3track_m_press(void);
void bank_sl3track_m_dpress(void);
void bank_sl3track_m_hold(void);

void bank_sl3track_r_press(void);
void bank_sl3track_r_dpress(void);
void bank_sl3track_r_hold(void);

#endif
