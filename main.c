#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

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
#define SWT_1_REG PINH
#define SWT_2 PH6
#define SWT_2_REG PINH
#define SWT_3 PB4
#define SWT_3_REG PINB
#define SWT_4 PB5
#define SWT_4_REG PINB

#define SWT_PROG PB6
#define SWT_PROG_REG PINB

#define PROGRAMMER_LED PH3

#include "lib/button.h"
#include "lib/preset.h"
#include "lib/loop.h"

void init() {
    DDRB = 0x00;
    DDRH = 0xff;
    DDRE = 0xff;
    DDRG = 0xff;

    setPreset(current_preset);
}

void handleProgrammingModeSwitches() {
    if( button_is_pressed(&SWT_1_REG, SWT_1) ) {
        modifyPreset(0);
    }
    else if( button_is_pressed(&SWT_2_REG, SWT_2) ) {
        modifyPreset(1);
    }
    else if( button_is_pressed(&SWT_3_REG, SWT_3) ) {
        modifyPreset(2);
    }
    else if( button_is_pressed(&SWT_4_REG, SWT_4) ) {
        modifyPreset(3);
    }
}

void handlePlaybackModeSwitches () {
    if( button_is_pressed(&SWT_1_REG, SWT_1) ) {
        setPreset(0);
    }
    else if( button_is_pressed(&SWT_2_REG, SWT_2) ) {
        setPreset(1);
    }
    else if( button_is_pressed(&SWT_3_REG, SWT_3) ) {
        setPreset(2);
    }
    else if( button_is_pressed(&SWT_4_REG, SWT_4) ) {
        setPreset(3);
    }
}

void loop() {
    if(is_programming) {
        handleProgrammingModeSwitches();
    } else {
        handlePlaybackModeSwitches();
    }

    if( button_is_pressed(&SWT_PROG_REG, SWT_PROG)) {
        toggleProgrammingMode();
    }

    //Reflect internal state of the loop to the hardware
    updateLoop(states[0], OUT_A, &OUT_A_PORT);
    updateLoop(states[1], OUT_B, &OUT_B_PORT);
    updateLoop(states[2], OUT_C, &OUT_C_PORT);
    updateLoop(states[3], OUT_D, &OUT_D_PORT);
}

int main (void)
{
    init();
    //
    while(1) {
        loop();
    }
}
