# MCU name
MCU = RP2040
BOARD = GENERIC_RP_RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Split keyboard
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor
UART_TX_PIN = GP0
UART_RX_PIN = GP1

# Additional features
LTO_ENABLE = yes            # Link time optimization for smaller firmware size
