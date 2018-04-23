void updateLoop(int state, int pin) {
    if( state == 1 ) {
        PORTD &= ~(1 << pin);
    }
    else {
        PORTD |= (1 << pin);
    }
}
