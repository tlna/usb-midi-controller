#include "sooperlooper_3tracks.h"

void bank_sl3track_init(struct Bank *bank_handler) {
    bank_handler->name = "S-looper 3tracks";
    bank_handler->info = "";
    bank_handler->buttons[BUTTON_LEFT].pressed = bank_sl3track_l_press;
    bank_handler->buttons[BUTTON_LEFT].double_pressed = bank_sl3track_l_dpress;
    bank_handler->buttons[BUTTON_LEFT].hold = bank_sl3track_l_hold;
    bank_handler->buttons[BUTTON_MIDDLE].pressed = bank_sl3track_m_press;
    bank_handler->buttons[BUTTON_MIDDLE].double_pressed = bank_sl3track_m_dpress;
    bank_handler->buttons[BUTTON_MIDDLE].hold = bank_sl3track_m_hold;
    bank_handler->buttons[BUTTON_RIGHT].pressed = bank_sl3track_r_press;
    bank_handler->buttons[BUTTON_RIGHT].double_pressed = bank_sl3track_r_dpress;
    bank_handler->buttons[BUTTON_RIGHT].hold = bank_sl3track_r_hold;
}

void bank_sl3track_just_play_note(int note) {
    MIDI_EventPacket_t MIDIEvent = (MIDI_EventPacket_t)
    {
        .Event       = MIDI_EVENT(0, MIDI_COMMAND_NOTE_ON),
        .Data1       = MIDI_COMMAND_NOTE_ON | MIDI_CHANNEL(1),
        .Data2       = note,
        .Data3       = MIDI_STANDARD_VELOCITY,
    };

    MIDI_Device_SendEventPacket(&Controller_MIDI_Interface, &MIDIEvent);
    MIDI_Device_Flush(&Controller_MIDI_Interface);
}

void bank_sl3track_l_press(void) {
    bank_sl3track_just_play_note(0x3C);
} 

void bank_sl3track_l_dpress(void) {
    bank_sl3track_just_play_note(0x3D);
} 

void bank_sl3track_l_hold(void) {
    bank_sl3track_just_play_note(0x3E);
}

void bank_sl3track_m_press(void) {
    bank_sl3track_just_play_note(0x3F);
} 

void bank_sl3track_m_dpress(void) {
    bank_sl3track_just_play_note(0x40);
} 

void bank_sl3track_m_hold(void) {
    bank_sl3track_just_play_note(0x41);
}

void bank_sl3track_r_press(void) {
    bank_sl3track_just_play_note(0x42);
} 

void bank_sl3track_r_dpress(void) {
    bank_sl3track_just_play_note(0x43);
} 

void bank_sl3track_r_hold(void) {
    bank_sl3track_just_play_note(0x44);
}
