#ifndef CONFIG_H
#define CONFIG_H

#include <nds.h>

#define DEFAULT_FG_COLOUR RGB15(6,6,6)
#define DEFAULT_BG_COLOUR RGB15(31,16,24)
#define DEFAULT_FLAIR_COLOUR RGB15(24,24,24)

#define DEFAULT_EMULATION_SPEED 7

typedef struct {
  int fg_colour;
  int bg_colour;
  int flair_colour;

  int emulation_speed; // number of instructions per frame
} AppConfig;

extern AppConfig app_config;

void init_config();



#endif
