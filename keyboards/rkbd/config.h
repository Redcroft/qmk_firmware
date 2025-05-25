#pragma once

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 9

/* Split keyboard configuration */
#define SPLIT_USB_DETECT  // Automatically detect which side has USB connection
#define MASTER_RIGHT      // Right side is the master (USB connected side)
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_USART_SPEED 38400

/* Debounce reduces chatter (delay in ms) */
#define DEBOUNCE 5

/* Additional features you might want */
#define TAPPING_term 200
#define PERMISSIVE_HOLD
