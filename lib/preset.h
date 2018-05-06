
/**
 * Initializes and prepares relays and other hardware
 */
void initHardware ();

/**
 * Returns the current device mode.
 *
 * 0 = Playback Mode
 * 1 = Toggle Mode
 * 2 = Order Mode
 */
int getMode();

/**
 * Iterates though the diffrent device modes.
 */
void changeMode();

/**
 * Selects a preset (on the given index) to become the new active preset
 *
 * @param preset: The index of the preset in the presets array which should
 *                become active
 */
void setPreset(int preset);

/**
 * Activates/deactivates a given loop in the currently active preset
 *
 * @param loop: The index of the loop in the states array which should be
 *              toggled
 */
void togglePedalInPreset(int loop);
