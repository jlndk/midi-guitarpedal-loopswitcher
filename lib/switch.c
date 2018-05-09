#include <avr/io.h>
#include <util/delay.h>

#include "definitions.h"
#include "preset.h"
#include "io.h"

void handlePlaybackModeSwitches () {
    if( button_is_pressed(&SWT_1_PORT, SWT_1) ) {
        setPreset(0);
		ui_update();
    }
    else if( button_is_pressed(&SWT_2_PORT, SWT_2) ) {
        setPreset(1);
		ui_update();
    }
    else if( button_is_pressed(&SWT_3_PORT, SWT_3) ) {
        setPreset(2);
		ui_update();
    }
    else if( button_is_pressed(&SWT_4_PORT, SWT_4) ) {
        setPreset(3);
		ui_update();
    }
}

void handleToggleModeSwitches() {
    if( button_is_pressed(&SWT_1_PORT, SWT_1) ) {
        togglePedalInPreset(0);
		ui_update();
    }
    else if( button_is_pressed(&SWT_2_PORT, SWT_2) ) {
        togglePedalInPreset(1);
		ui_update();
    }
    else if( button_is_pressed(&SWT_3_PORT, SWT_3) ) {
        togglePedalInPreset(2);
		ui_update();
    }
    else if( button_is_pressed(&SWT_4_PORT, SWT_4) ) {
        togglePedalInPreset(3);
		ui_update();
    }
}

void handleOrderModeSwitches () {
    if( button_is_pressed(&SWT_1_PORT, SWT_1) ) {
        changeSelectedPedal(0);
		ui_update();
    }
    else if( button_is_pressed(&SWT_2_PORT, SWT_2) ) {
        changeSelectedPedal(1);
		ui_update();
    }
    else if( button_is_pressed(&SWT_3_PORT, SWT_3) ) {
        movePedalInPreset(0);
		ui_update();
    }
    else if( button_is_pressed(&SWT_4_PORT, SWT_4) ) {
        movePedalInPreset(1);
		ui_update();
    }
}

void handleSwitches() {
    switch(getMode()) {
        case 0:
            handlePlaybackModeSwitches();
            break;
        case 1:
            handleToggleModeSwitches();
            break;
        case 2:
            handleOrderModeSwitches();
            break;
    }

    if( button_is_pressed(&SWT_PROG_PORT, SWT_PROG)) {
        changeMode();
		ui_update();
    }
}
