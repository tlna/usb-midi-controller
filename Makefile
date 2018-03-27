#
#            DMBS Build System
#     Released into the public domain.
#
#  dean [at] fourwalledcubicle [dot] com
#        www.fourwalledcubicle.com
#




# Run "make help" for target help.

MCU          = atmega32u4
ARCH         = AVR8

F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = FootMidiCtlSoftware
SRC          = src/main.c src/descriptors.c src/lcd.c src/midi.c src/interface.c src/banks/test.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH	 = lufa/LUFA
CC_FLAGS     = -Isrc -DUSE_LUFA_CONFIG_HEADER
LD_FLAGS     =

# Default target
all:

# Include LUFA-specific DMBS extension modules
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_LUFA_PATH)/lufa-sources.mk
include $(DMBS_LUFA_PATH)/lufa-gcc.mk

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
include $(DMBS_PATH)/cppcheck.mk
include $(DMBS_PATH)/doxygen.mk
include $(DMBS_PATH)/dfu.mk
include $(DMBS_PATH)/gcc.mk
include $(DMBS_PATH)/hid.mk
include $(DMBS_PATH)/avrdude.mk
include $(DMBS_PATH)/atprogram.mk


upload: ${TARGET}.hex
	avrdude -F -V -c avr109 -p m32u4 -P /dev/ttyACM0 -b 115200 -U flash:w:$^
