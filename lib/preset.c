#include <avr/io.h>
#include "definitions.h"
#include "io.h"

//Struct for each pedal's path (I/O state of relays)
typedef struct Path Path;
struct Path {
	char first : 2;
	char second : 2;
};

//Struct for each pedal contains path and IO state
typedef struct Pedal Pedal;
struct Pedal {
	Path path;
	unsigned char name;
	unsigned int state : 2;
};

typedef struct Preset Preset;
struct Preset {
	int order[PEDAL_COUNT];
	int states[PEDAL_COUNT];
};

//List of pedal configurations.
Pedal pedals[PEDAL_COUNT];

Preset presets[PEDAL_COUNT];

char grp_pins[5][3] =
{
	{ GRP_IN_MASTER , GRP_IN_AB , GRP_IN_CD },
	{ GRP_A_MASTER , GRP_A_OB , GRP_A_CD },
	{ GRP_B_MASTER , GRP_B_AO , GRP_B_CD },
	{ GRP_C_MASTER , GRP_C_AB , GRP_C_OD },
	{ GRP_D_MASTER , GRP_D_AB , GRP_D_CO }
};

volatile unsigned char *grp_ports[5][3] =
{
	{ &GRP_IN_MASTER_PORT , &GRP_IN_AB_PORT , &GRP_IN_CD_PORT },
	{ &GRP_A_MASTER_PORT , &GRP_A_OB_PORT , &GRP_A_CD_PORT },
	{ &GRP_B_MASTER_PORT , &GRP_B_AO_PORT , &GRP_B_CD_PORT },
	{ &GRP_C_MASTER_PORT , &GRP_C_AB_PORT , &GRP_C_OD_PORT },
	{ &GRP_D_MASTER_PORT , &GRP_D_AB_PORT , &GRP_D_CO_PORT }
};

//Index of the current preset in the presets array
int current_preset = 0;

// The current device mode.
// 0 = Playback Mode
// 1 = Toggle Mode
// 2 = Order Mode
int mode = 0;

int selected_pedal = 0;

void updateGroup(int grp_pos, Path path) {
    //Write to pins according to status byte
    pin_set(path.first, grp_pins[grp_pos][0], grp_ports[grp_pos][0]);
    pin_set(path.second, grp_pins[grp_pos][1], grp_ports[grp_pos][1]);
    pin_set(path.second, grp_pins[grp_pos][2], grp_ports[grp_pos][2]);
}

void updateOrder() {
    Preset preset = presets[current_preset];

    int prevPedal = 0;

    //Update all groups except the last one
    for (int i = 0; i < PEDAL_COUNT; i++)
	{
        int pedal = preset.order[i];

        updateGroup(prevPedal, pedals[pedal].path);

        prevPedal = pedal + 1;
	}

    //Update output group manually
    int lastPedal = preset.order[ PEDAL_COUNT - 1 ];
    updateGroup(lastPedal + 1, pedals[lastPedal].path);
}

void updateStates() {
    //Get current preset
    Preset preset = presets[current_preset];

    //Reflect internal state of the loop to the hardware
    pin_set(preset.states[0], OUT_A, &OUT_A_PORT);
    pin_set(preset.states[1], OUT_B, &OUT_B_PORT);
    pin_set(preset.states[2], OUT_C, &OUT_C_PORT);
    pin_set(preset.states[3], OUT_D, &OUT_D_PORT);
}

void reflectPresetToHardware() {
    updateStates();
    updateOrder();
}

void setPreset(int preset) {
    current_preset = preset;
    reflectPresetToHardware();
}

void swapPedalsInPreset(int x, int y) {
    int tmpx = presets[current_preset].order[x];
    int tmpy = presets[current_preset].order[y];
    presets[current_preset].order[x] = tmpy;
    presets[current_preset].order[y] = tmpx;
}

void movePedalInPreset (int dir)
{
    int swap_pedal = 0;

    if(dir > 0) {
        swap_pedal = selected_pedal + 1;
    }
    else {
        swap_pedal = selected_pedal - 1;
    }

    //Prevent underflow/overflow
    if(swap_pedal < 0 || swap_pedal == PEDAL_COUNT) {
        return;
    }

    swapPedalsInPreset(selected_pedal, swap_pedal);

    //Update the variable to the new location of the already selected pedal
    selected_pedal = swap_pedal;

    reflectPresetToHardware();
}

void changeSelectedPedal(int dir)
{
    if(dir)
    {
        selected_pedal++;
    }
    else
    {
        selected_pedal--;
    }

    if(selected_pedal > PEDAL_COUNT - 1)
    {
        selected_pedal = PEDAL_COUNT - 1;
    }
    else if(selected_pedal < 0)
    {
        selected_pedal = 0;
    }
}

void togglePedalInPreset(int loop) {
    presets[current_preset].states[loop] = !presets[current_preset].states[loop];
    setPreset(current_preset);
}

/**
 * Change color of RGB-LED to match mode
 * Red = playback
 * Blue = selection
 * Green = order
 */
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

    //Always reset editing parameters when modes are changed
    selected_pedal = 0;

	updateModeLed();
}

int getMode() {
    return mode;
}

void initPresets() {
    for (int i = 0; i < PEDAL_COUNT; i++) {
        Preset preset = {
            .order = {0,1,2,3},
            .states = {0,0,0,0}
        };

        presets[i] = preset;
    }
}

//Defaulting to ABCD, bypass all
void initPedals()
{
	pedals[0].name = 'A', pedals[0].path.first = 0, pedals[0].path.second = 0, pedals[0].state = 0;
	pedals[1].name = 'B', pedals[1].path.first = 0, pedals[1].path.second = 1, pedals[1].state = 0;
	pedals[2].name = 'C', pedals[2].path.first = 1, pedals[2].path.second = 0, pedals[2].state = 0;
	pedals[3].name = 'D', pedals[3].path.first = 1, pedals[3].path.second = 1, pedals[3].state = 0;
}

void initHardware()
{
    initPedals();
    initPresets();
    updateModeLed();
    reflectPresetToHardware();
}
