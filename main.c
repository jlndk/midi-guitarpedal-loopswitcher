#include <avr/io.h>
#include <util/delay.h>

#include "lib/definitions.h"
#include "lib/preset.h"
#include "lib/io.h"
#include "lib/switch.h"
#include "lib/ui.h"

void init() {
    DDRA = 0xff; //Set port as output
    DDRB = 0x00; //Set port as input
    DDRC = 0xff; //Set port as output
    DDRH = 0xff; //Set port as output
    DDRE = 0xff; //Set port as output
    DDRG = 0xff; //Set port as output
    DDRJ = 0xff; //Set port as output

    ui_init();
    initHardware();
}

void loop() {
    handleSwitches();
}

int main (void)
{
    init();

    while(1) {
        loop();
    }
}
