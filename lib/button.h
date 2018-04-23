#include <avr/io.h>

int button_is_pressed(volatile uint8_t *port, int pin)
{
    if(!bit_is_clear(*port, pin)) {
        _delay_ms(DEBOUNCE_SPEED);

        return bit_is_clear(*port, pin);
    }

    return 0;
}
