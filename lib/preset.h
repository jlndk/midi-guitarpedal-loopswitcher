int current_preset = 0;

int is_programming = 0;

int presets[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
};

int states[4] = {0,0,0,0};

void setPreset(int preset) {
    current_preset = preset;
    for(int i = 0; i < 4; i++) {
        states[i] = presets[preset][i];
    }
}

void toggleProgrammingMode() {
    is_programming = !is_programming;

    if(is_programming) {
        PORTD |= (1 << PROGRAMMER_LED);
    }
    else {
        PORTD &= ~(1 << PROGRAMMER_LED);
    }
}

void modifyPreset(int loop) {
    presets[current_preset][loop] = !presets[current_preset][loop];
    setPreset(current_preset);
}
