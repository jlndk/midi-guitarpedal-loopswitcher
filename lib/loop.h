void updateLoop(int state, int pin, volatile *port) {
    if( state == 1 ) {
        *port &= ~(1 << pin);
    }
    else {
        *port |= (1 << pin);
    }
}
