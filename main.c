#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lib/definitions.h"
#include "lib/button.h"
#include "lib/preset.h"
#include "lib/loop.h"

void init() {
    DDRB = 0x00;
    DDRH = 0xff;
    DDRE = 0xff;
    DDRG = 0xff;
    DDRJ = 0xff;

    setPreset(current_preset);
    updateModeLed();
}

void handleProgrammingModeSwitches() {
    if( button_is_pressed(&SWT_1_PORT, SWT_1) ) {
        modifyPreset(0);
    }
    else if( button_is_pressed(&SWT_2_PORT, SWT_2) ) {
        modifyPreset(1);
    }
    else if( button_is_pressed(&SWT_3_PORT, SWT_3) ) {
        modifyPreset(2);
    }
    else if( button_is_pressed(&SWT_4_PORT, SWT_4) ) {
        modifyPreset(3);
    }
}

void handlePlaybackModeSwitches () {
    if( button_is_pressed(&SWT_1_PORT, SWT_1) ) {
        setPreset(0);
    }
    else if( button_is_pressed(&SWT_2_PORT, SWT_2) ) {
        setPreset(1);
    }
    else if( button_is_pressed(&SWT_3_PORT, SWT_3) ) {
        setPreset(2);
    }
    else if( button_is_pressed(&SWT_4_PORT, SWT_4) ) {
        setPreset(3);
    }
}

void loop() {
    if(mode) {
        handleProgrammingModeSwitches();
    } else {
        handlePlaybackModeSwitches();
    }

    if( button_is_pressed(&SWT_PROG_PORT, SWT_PROG)) {
        changeMode();
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
