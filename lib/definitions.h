/*
|--------------------------------------------------------------------------
| Miscellaneous
|--------------------------------------------------------------------------
*/
/**
 * Defines how slow the input debouncer should be.
 * Increase if signal is noisy, decrease if there's no reaction from buttons.
 */
#define DEBOUNCE_SPEED 100

//Defines how many loops this device has.
#define PEDAL_COUNT 4

/*
|--------------------------------------------------------------------------
| Hardware macros
|--------------------------------------------------------------------------
| These macros defines which pins each component is connected to.
| The pins are defined based on the MCU port names instead of the default
| arduino pin numbers.
*/

/**
 * Switches
 */
//Switch 1
#define SWT_1 PE4
#define SWT_1_PORT PINE

//Switch 2
#define SWT_2 PE5
#define SWT_2_PORT PINE

//Switch 3
#define SWT_3 PG4
#define SWT_3_PORT PING

//Switch 4
#define SWT_4 PE3
#define SWT_4_PORT PINE

//Mode Switch
#define SWT_PROG PH3
#define SWT_PROG_PORT PINH

/**
 * LEDS
 */

//Mode Indicator led (Red Color)
#define MODE_LED_RED PJ0
#define MODE_LED_RED_PORT PORTJ

//Mode Indicator led (Green Color)
#define MODE_LED_GREEN PJ1
#define MODE_LED_GREEN_PORT PORTJ

//Mode Indicator led (Blue Color)
#define MODE_LED_BLUE PH0
#define MODE_LED_BLUE_PORT PORTH

/**
 * Relays
 */
//Relay A
#define OUT_A PE4
#define OUT_A_PORT PORTE
//Relay B
#define OUT_B PE5
#define OUT_B_PORT PORTE
//Relay C
#define OUT_C PG5
#define OUT_C_PORT PORTG
//Relay D
#define OUT_D PE3
#define OUT_D_PORT PORTE

//Group pins/ports
#define GRP_IN_MASTER PA0
#define GRP_IN_MASTER_PORT PORTA
#define GRP_IN_AB PA1
#define GRP_IN_AB_PORT PORTA
#define GRP_IN_CD PA2
#define GRP_IN_CD_PORT PORTA

#define GRP_A_MASTER PA3
#define GRP_A_MASTER_PORT PORTA
#define GRP_A_OB PA4
#define GRP_A_OB_PORT PORTA
#define GRP_A_CD PA5
#define GRP_A_CD_PORT PORTA

#define GRP_B_MASTER PA6
#define GRP_B_MASTER_PORT PORTA
#define GRP_B_AO PA7
#define GRP_B_AO_PORT PORTA
#define GRP_B_CD PC0
#define GRP_B_CD_PORT PORTC

#define GRP_C_MASTER PC1
#define GRP_C_MASTER_PORT PORTC
#define GRP_C_AB PC2
#define GRP_C_AB_PORT PORTC
#define GRP_C_OD PC3
#define GRP_C_OD_PORT PORTC

#define GRP_D_MASTER PC4
#define GRP_D_MASTER_PORT PORTC
#define GRP_D_AB PC5
#define GRP_D_AB_PORT PORTC
#define GRP_D_CO PC6
#define GRP_D_CO_PORT PORTC
