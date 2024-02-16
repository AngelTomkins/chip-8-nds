#include "menu.h"
#include "config.h"
#include "graphics.h"
#include <nds.h>
#include "../include/tonccpy.h"
#include "profiling.h"

ConfigMenu config_menu;

int selection = 0;

static void print_menu(int selection);
static void mutate_config(int selection, int keys);
static int print_help();

static void show_console() {
  bgShow(config_menu.console.bgId);
  bgHide(config_menu.keyboard_id);
}
static void hide_console() {
  bgShow(config_menu.keyboard_id);
  bgHide(config_menu.console.bgId);
}

void init_config_console(int sub_id) {
  toncset32(&config_menu, 0, sizeof(config_menu));
  config_menu.keyboard_id = 7;
  consoleInit(&config_menu.console, 1, BgType_Text4bpp, BgSize_T_256x256, 31, 3, false, true);
  consoleSelect(&config_menu.console);
  consoleClear();
  bgHide(config_menu.console.bgId);
}

#define MAX(a,b) (a>b) * a + (a<=b) * b
#define MIN(a,b) (a>b) * b + (a<=b) * a

#define NUM_SELECTIONS 3

void open_menu() {
  show_console();
  while (1) {
    print_menu(selection);

    scanKeys();
    int keys = keysDown();
    if (keys & KEY_START) {
      goto exit_menu;
    }

    if (keys & KEY_SELECT) {
      if (print_help() == 1) {
        goto exit_menu;
      }
    }

    if (keys & KEY_UP) {
      selection = (selection - 1);
      if (selection < 0) {
        selection = NUM_SELECTIONS - 1;
      }
      continue;
    } else if (keys & KEY_DOWN) {
      selection = (selection + 1) % NUM_SELECTIONS;
      continue;
    }

    mutate_config(selection, keys);

    swiWaitForVBlank();
  };
exit_menu:

  hide_console();
}

static void print_menu(int selection) {
  consoleSelect(&config_menu.console);
  consoleClear();
  //Header
  printf(
      "\x1b[0;8HConfig Page %d/1"
      "\x1b[1;5HPress Select For Help"
      "\x1b[20;4HIPF: %lu"
      "\x1b[21;4HCreated by Angel Tomkins"
      "\x1b[22;10Hgithub.com/"
      "\x1b[23;4Hangeltomkins/chip-8-nds/",
      1, profiling_framerate_get_average()
      );

  printf(
      "\x1b[4;0H%sInstructions Per Frame: %lu%s",
      selection == 0 ? "* " : "  ",
      ipf_presets[app_config.emulation_speed],
      selection == 0 ? " *" : ""
      );

  printf(
      "\x1b[6;0H%sColour Scheme: %s%s",
      selection == 1 ? "* " : "  ",
      color_presets_names[app_config.colour_scheme],
      selection == 1 ? " *" : ""
      );

  printf(
      "\x1b[8;0H%sVBlank on Draw: %s%s",
      selection == 2 ? "* " : "  ",
      app_config.vblank_on_draw ? "true" : "false",
      selection == 2 ? " *" : ""
      );
}

static void mutate_config(int selection, int keys) {
  switch (selection) {
    case 0:
      app_config.emulation_speed += ((keys & KEY_RIGHT) > 0) - ((keys & KEY_LEFT) > 0);
      app_config.emulation_speed = MIN((NUM_IPF_PRESETS-1), app_config.emulation_speed);
      app_config.emulation_speed = MAX(0, app_config.emulation_speed);
      break;
    case 1:
      app_config.colour_scheme += ((keys & KEY_RIGHT) > 0) - ((keys & KEY_LEFT) > 0);
      app_config.colour_scheme = MIN((NUM_COLOUR_PRESETS-1), app_config.colour_scheme);
      app_config.colour_scheme = MAX(0, app_config.colour_scheme);

      BG_PALETTE[0] = color_presets[app_config.colour_scheme][0];
      BG_PALETTE[1] = color_presets[app_config.colour_scheme][1];
      BG_PALETTE[2] = color_presets[app_config.colour_scheme][2];
      break;
    case 2:
      app_config.vblank_on_draw ^= ((keys & KEY_RIGHT) > 0) | ((keys & KEY_LEFT) > 0);
      break;

    default:
      break;
  }
}

static int print_help() {
  consoleClear();
  printf(
      "\x1b[0;9H- Help  Page -"
      "\x1b[1;5HPress Select to Return"
      "\x1b[4;11HLeft/Right"
      "\x1b[5;6HModify Config Value"
      "\x1b[7;12HUp/Down"
      "\x1b[8;4HNavigate Config Options"
      "\x1b[10;11HR/L Bumper"
      "\x1b[11;5HNavigate Config Pages"
      "\x1b[13;13HStart"
      "\x1b[14;8HResume Emulation"

      "\x1b[21;4HCreated by Angel Tomkins"
      "\x1b[22;10Hgithub.com/"
      "\x1b[23;4Hangeltomkins/chip-8-nds/"
      );


  while (1) {
    scanKeys();
    int keys = keysDown();
    if (keys & KEY_SELECT) {
      return 0;
    }
    if (keys & KEY_START) {
      return 1;
    }
  }
}
