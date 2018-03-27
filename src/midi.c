#include "midi.h"


USB_ClassInfo_MIDI_Device_t Controller_MIDI_Interface = {
    .Config = {
        .StreamingInterfaceNumber = INTERFACE_ID_AudioStream,
        .DataINEndpoint           = {
            .Address          = MIDI_STREAM_IN_EPADDR,
            .Size             = MIDI_STREAM_EPSIZE,
            .Banks            = 1,
        },
        .DataOUTEndpoint           = {
            .Address          = MIDI_STREAM_OUT_EPADDR,
            .Size             = MIDI_STREAM_EPSIZE,
            .Banks            = 1,
        },
    },
};


void midi_init(void) {
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    clock_prescale_set(clock_div_1);

    USB_Init();
    GlobalInterruptEnable();
}


void midi_disable(void) {
    USB_Disable();
}


void midi_handle_tasks(void) {
    MIDI_Device_USBTask(&Controller_MIDI_Interface);
    USB_USBTask();
}


void EVENT_USB_Device_Connect(void) {}


void EVENT_USB_Device_Disconnect(void) {}


void EVENT_USB_Device_ConfigurationChanged(void)
{
    MIDI_Device_ConfigureEndpoints(&Controller_MIDI_Interface);
}


void EVENT_USB_Device_ControlRequest(void)
{
    MIDI_Device_ProcessControlRequest(&Controller_MIDI_Interface);
}

