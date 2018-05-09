#include <stdio.h>
#include <avr/pgmspace.h>
#include "lcd.h"
#include "preset.h"

const unsigned char INTRO_TEXT[] PROGMEM = "   JAMM  LIVE \0";

const unsigned char PLAYBACK_MODE_TOP_TEXT[] PROGMEM = "PLAYBACK MODE   \0";
const unsigned char PLAYBACK_MODE_BTM_TEXT[] = "Preset: %c \0";

const unsigned char TOGGLE_MODE_TOP_TEXT[] PROGMEM = "TOGGLE MODE: \0";
const unsigned char TOGGLE_MODE_BTM_TEXT[] = "Edit Preset: %c \0";

const unsigned char ORDER_MODE_TOP_TEXT[] = "ORDER MODE  %s\0";
const unsigned char ORDER_MODE_BTM_TEXT[] = "Pre: %c  Pedal: %c \0";

//char orderText[4] = "CBDA";

char playback_btm_text[100];
char toggle_btm_text[100];
char order_top_text[100];
char order_btm_text[100];

//demonstration of animation
void init_animation(void)
{
	lcd_clear();
	lcd_copy_str(INTRO_TEXT, 0, 0);
    _delay_ms(1000);
}

void ui_update() {
    switch(getMode()) {
        case 0:
            sprintf( playback_btm_text, PLAYBACK_MODE_BTM_TEXT, getCurrentPresetName());

            lcd_clear();
            lcd_copy_str(PLAYBACK_MODE_TOP_TEXT, 0, 0);
            lcd_send_str(playback_btm_text, 0, 1);

            _delay_ms(1000);
            break;
        case 1:
            sprintf( toggle_btm_text, TOGGLE_MODE_BTM_TEXT, getCurrentPresetName());

            lcd_clear();
            lcd_copy_str(TOGGLE_MODE_TOP_TEXT, 0, 0);
            lcd_send_str(toggle_btm_text, 0, 1);

            _delay_ms(1000);
            break;
        case 2:
            sprintf( order_top_text, ORDER_MODE_TOP_TEXT, getPedalOrderString());
            sprintf( order_btm_text, ORDER_MODE_BTM_TEXT, getCurrentPresetName(), getSelectedPedalName());

            lcd_clear();
            lcd_send_str(order_top_text, 0, 0);
            lcd_send_str(order_btm_text, 0, 1);

            _delay_ms(1000);
            break;
        default:
            lcd_clear();
            lcd_send_str("ERROR", 0, 0);
            lcd_send_str("INVALID MODE", 0, 1);

            _delay_ms(1000);
            break;
    }

}

void ui_init(void) {
	lcd_init();//init LCD bit, dual line, cursor right

	lcd_clear();//clears LCD

	_delay_ms(50);
	lcd_cursor_off(); //Hides cursor

	_delay_ms(50);

	init_animation();

	ui_update();
}
