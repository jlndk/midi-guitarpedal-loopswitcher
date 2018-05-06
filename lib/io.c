#include <avr/io.h>
#include <util/delay.h>

#include "definitions.h"

int button_is_pressed(volatile unsigned char *port, int pin)
{
    if(!bit_is_clear(*port, pin)) {
        _delay_ms(DEBOUNCE_SPEED);

        return bit_is_clear(*port, pin);
    }

    return 0;
}

void pin_set(int state, int pin, volatile unsigned char *port) {
    if( state == 1 ) {
        *port &= ~(1 << pin);
    }
    else {
        *port |= (1 << pin);
    }
}
