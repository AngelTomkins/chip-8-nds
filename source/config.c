#include "config.h"
AppConfig app_config;


void init_config() {
  app_config.fg_colour = DEFAULT_FG_COLOUR;
  app_config.bg_colour = DEFAULT_BG_COLOUR;
  app_config.flair_colour = DEFAULT_FLAIR_COLOUR;
  app_config.emulation_speed = DEFAULT_EMULATION_SPEED;
}

