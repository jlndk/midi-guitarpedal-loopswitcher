/*
Defines how slow the input debouncer should be.
Increase if signal is noisy, decrease if there's no reaction from buttons.
 */
#define DEBOUNCE_SPEED 100

#define OUT_A PE4
#define OUT_A_PORT PORTE
#define OUT_B PE5
#define OUT_B_PORT PORTE
#define OUT_C PG5
#define OUT_C_PORT PORTG
#define OUT_D PE3
#define OUT_D_PORT PORTE

#define SWT_1 PH5
#define SWT_1_PORT PINH
#define SWT_2 PH6
#define SWT_2_PORT PINH
#define SWT_3 PB4
#define SWT_3_PORT PINB
#define SWT_4 PB5
#define SWT_4_PORT PINB

#define SWT_PROG PB6
#define SWT_PROG_PORT PINB

#define MODE_LED_RED PJ0
#define MODE_LED_RED_PORT PORTJ
#define MODE_LED_GREEN PJ1
#define MODE_LED_GREEN_PORT PORTJ
#define MODE_LED_BLUE PH1
#define MODE_LED_BLUE_PORT PORTH
