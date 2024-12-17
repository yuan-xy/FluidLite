#include <stdio.h>
#include <fluidlite.h>
#include "fluid_sfont.h"

int main(int argc, char** argv)
{
	fluid_settings_t* settings = NULL;
	fluid_synth_t* synth = NULL;
	fluid_sfont_t* sfont = NULL;
	int err = 0, sfid = -1;

	if (argc != 2) {
		fprintf(stderr, "Usage: instruments [soundfont]\n");
		return 1;
	}

	settings = new_fluid_settings();
	synth = new_fluid_synth(settings);
	sfid = fluid_synth_sfload(synth, argv[1], 1);
	if (sfid == -1) {
		fprintf(stderr, "Failed to load the SoundFont\n");
		err = 4;
		goto cleanup;
	}

    /* Enumeration of banks and programs */
    sfont = fluid_synth_get_sfont_by_id(synth, sfid);
    if (sfont != NULL) {
        fluid_preset_t struct_preset;
		fluid_preset_t *preset = &struct_preset;
        fluid_sfont_iteration_start(sfont);
        while (fluid_sfont_iteration_next(sfont, preset) != 0) {
            int bank = fluid_preset_get_banknum(preset);
            int prog = fluid_preset_get_num(preset);
            const char* name = fluid_preset_get_name(preset);
			printf("bank: %d prog: %d name: %s\n", bank, prog, name);
		}
	}

 cleanup:
	if (synth) {
		delete_fluid_synth(synth);
	}
	if (settings) {
		delete_fluid_settings(settings);
	}
	return err;
}