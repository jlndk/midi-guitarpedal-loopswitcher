#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
Defines how slow the input debouncer should be.
Increase if signal is noisy, decrease if there's no reaction from buttons.
 */
#define DEBOUNCE_SPEED 100
#define OUT_A PD2
#define OUT_B PD3
#define OUT_C PD4
#define OUT_D PD5

#define PROGRAMMER_LED PD6

#include "lib/button.h"
#include "lib/preset.h"
#include "lib/loop.h"

void init() {
    DDRB = 0b00100000;
    DDRD = 0xff;

    setPreset(current_preset);
}

void handleProgrammingModeSwitches() {
    if( button_is_pressed(&PINB, PB0) ) {
        modifyPreset(0);
    }
    else if( button_is_pressed(&PINB, PB1) ) {
        modifyPreset(1);
    }
    else if( button_is_pressed(&PINB, PB2) ) {
        modifyPreset(2);
    }
    else if( button_is_pressed(&PINB, PB3) ) {
        modifyPreset(3);
    }
}

void handlePlaybackModeSwitches () {
    if( button_is_pressed(&PINB, PB0) ) {
        setPreset(0);
    }
    else if( button_is_pressed(&PINB, PB1) ) {
        setPreset(1);
    }
    else if( button_is_pressed(&PINB, PB2) ) {
        setPreset(2);
    }
    else if( button_is_pressed(&PINB, PB3) ) {
        setPreset(3);
    }
}

void loop() {
    if(is_programming) {
        handleProgrammingModeSwitches();
    } else {
        handlePlaybackModeSwitches();
    }

    if( button_is_pressed(&PINB, PB4)) {
        toggleProgrammingMode();
    }

    //Reflect internal state of the loop to the hardware
    updateLoop(states[0], OUT_A);
    updateLoop(states[1], OUT_B);
    updateLoop(states[2], OUT_C);
    updateLoop(states[3], OUT_D);
}

int main (void)
{
    init();

    while(1) {
        loop();
    }
}
