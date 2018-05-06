
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
 * Moves the currently selected pedal according to the given direction.
 *
 * @param dir: The direction of the movement.
 *             0: Back (Left)
 *             1: Forward (Right)
 */
void movePedalInPreset(int dir);

/**
 * Change which pedal is selected according to the given direction.
 *
 * @param dir: The direction of the movement.
 *             0: Back (Left)
 *             1: Forward (Right)
 */
void changeSelectedPedal(int dir);

/**
 * Activates/deactivates a given loop in the currently active preset
 *
 * @param loop: The index of the loop in the states array which should be
 *              toggled
 */
void togglePedalInPreset(int loop);
