#ifndef CONFIG_H
#define CONFIG_H

#include <nds.h>

#define NUM_COLOUR_PRESETS 5
#define NUM_IPF_PRESETS 10

extern const u16 ipf_presets[NUM_IPF_PRESETS];
extern const u16 color_presets[NUM_COLOUR_PRESETS][3];
extern const char* color_presets_names[NUM_COLOUR_PRESETS];

typedef struct {
  int colour_scheme;
  int emulation_speed; // number of instructions per frame
  int vblank_on_draw;
} AppConfig;

extern AppConfig app_config;


#endif
