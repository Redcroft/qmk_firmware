MCU = atmega32u4
BOOTLOADER = atmel-dfu

# Enable the features we discussed
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = no  # Use 'no' if you are strictly using sm_td to save space
LTO_ENABLE = yes       # IMPORTANT: Shrinks the firmware size so it fits on the chip

# Standard Gherkin/Pro Micro features
BOOTMAGIC_ENABLE = lite
MOUSEKEY_ENABLE = no   # Disable to save memory
EXTRAKEY_ENABLE = yes  # Required for Media keys/Volume
CONSOLE_ENABLE = no    # Disable to save memory
COMMAND_ENABLE = no    # Disable to save memory
NKRO_ENABLE = no       # Usually not needed for a 30-key board
