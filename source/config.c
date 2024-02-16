#include "config.h"
AppConfig app_config;

/*
#define DEFAULT_FG_COLOUR RGB15(6,6,6)
#define DEFAULT_BG_COLOUR RGB15(31,16,24)
#define DEFAULT_FLAIR_COLOUR RGB15(31,16,24)
*/

const u32 ipf_presets[NUM_IPF_PRESETS] = { 7, 15, 20, 30, 100, 200, 500, 700, 1000, 9999};

const u32 color_presets[NUM_COLOUR_PRESETS][3] = {
  {
    RGB15(6,6,6), RGB15(31,16,24), RGB15(0,0,0)
  },
  {
    RGB15(0,0,0), RGB15(31,31,31), RGB15(15,15,15)
  },
  {
    RGB15(31,31,31), RGB15(0,0,0), RGB15(15,15,15)
  },
  {
    RGB15(29,16,17), RGB15(31,29,28), RGB15(24,11,19)
  },
  {
    RGB15(31,31,31), RGB15(31, 17, 21), RGB15(28,14,25)
  },
};
const char* color_presets_names[NUM_COLOUR_PRESETS] = {
  "Dark Pastel",
  "Monochrome 1",
  "Monochrome 2",
  "Cake",
  "Sapphic",
};

void init_config() {
  app_config.colour_scheme = 0;
  app_config.emulation_speed = 0;
  app_config.vblank_on_draw = 0;
}

