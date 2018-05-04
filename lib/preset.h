int current_preset = 0;

int mode = 0;

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

void modifyPreset(int loop) {
    presets[current_preset][loop] = !presets[current_preset][loop];
    setPreset(current_preset);
}

//Change color of RGB-LED to match mode
//Red = playback
//Blue = selection
//Green = order
void updateModeLed ()
{
    MODE_LED_RED_PORT &= ~(1 << MODE_LED_RED);
    MODE_LED_GREEN_PORT &= ~(1 << MODE_LED_GREEN);
    MODE_LED_BLUE_PORT &= ~(1 << MODE_LED_BLUE);

	switch (mode)
	{
		case 0:
			MODE_LED_RED_PORT |= (1 << MODE_LED_RED);
			break;
		case 1:
			MODE_LED_BLUE_PORT |= (1 << MODE_LED_BLUE);
			break;
		case 2:
			MODE_LED_GREEN_PORT |= (1 << MODE_LED_GREEN);
			break;
	}
}

//Iterate mode + 1 and update LED
void changeMode() {
	mode++;
    if (mode > 2)
	{
		mode = 0;
    }
	updateModeLed();
}
