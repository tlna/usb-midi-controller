#ifndef _MIDI_H_
#define _MIDI_H_

#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/USB/Class/Device/MIDIClassDevice.h>
#include <descriptors.h>


void midi_init(void);
void midi_disable(void);
void midi_handle_tasks(void);

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);


#endif
