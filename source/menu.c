#include <nds.h>
#include <filesystem.h>
#include <dirent.h>
#include <fat.h>

#include "menu.h"
#include "config.h"
#include "print.h"
#include "roms.h"
#include "unistd.h"
#include "cpu.h"

extern u32 instructions_per_frame;

ConfigMenu config_menu;
int print_bg_id;
int keyboard_bg_id;

int selection = 0;

static void print_menu(int selection);
static int mutate_config(int selection, int keys);
static int print_help();
static int print_roms_menu();
static int fill_rom_entries(char* cwd, char* rom_entries, DIR* dirp);

static void show_console() {
  bgShow(print_bg_id);
  bgHide(keyboard_bg_id);
}
static void hide_console() {
  bgHide(print_bg_id);
  bgShow(keyboard_bg_id);
}

void init_config_console(int bg_id, int keyboard_id) {
  print_bg_id = bg_id;
  keyboard_bg_id = keyboard_id;
  hide_console();
}

#define MAX(a,b) (a>b) * a + (a<=b) * b
#define MIN(a,b) (a>b) * b + (a<=b) * a

#define NUM_SELECTIONS 4

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

    if (mutate_config(selection, keys)) {
      goto exit_menu;
    }

    swiWaitForVBlank();
  };
exit_menu:

  hide_console();
}

static void print_menu(int selection) {
  print_clear(bgGetGfxPtr(print_bg_id));

  char buffer[64] = {'\0'};


  print_to_bg(
      bgGetGfxPtr(print_bg_id),
      "Config Page\n"
      "Press Select For Help",
      5,
      PrintTextCentre
      );

  sprintf(
      buffer,
      "%sChoose Custom Rom%s",
      selection == 0 ? "* " : "",
      selection == 0 ? " *" : ""
      );

  print_to_bg(
      bgGetGfxPtr(print_bg_id),
      buffer,
      26,
      PrintTextCentre
      );

  sprintf(
      buffer,
      "%sInstructions Per Frame: %u%s",
      selection == 1 ? "* " : "",
      ipf_presets[app_config.emulation_speed],
      selection == 1 ? " *" : ""
      );

  print_to_bg(
      bgGetGfxPtr(print_bg_id),
      buffer,
      36,
      PrintTextCentre
      );


  sprintf(
      buffer,
      "%sColour Scheme: %s%s",
      selection == 2 ? "* " : "",
      color_presets_names[app_config.colour_scheme],
      selection == 2 ? " *" : ""
      );

  print_to_bg(
      bgGetGfxPtr(print_bg_id),
      buffer,
      46,
      PrintTextCentre
      );

  sprintf(
      buffer,
      "%sVBlank on Draw: %s%s",
      selection == 3 ? "* " : "",
      app_config.vblank_on_draw ? "true" : "false",
      selection == 3 ? " *" : ""
      );

  print_to_bg(
      bgGetGfxPtr(print_bg_id),
      buffer,
      56,
      PrintTextCentre
      );
}

static int mutate_config(int selection, int keys) {
  switch (selection) {
    case 0:
      if (keys & (KEY_A | KEY_RIGHT | KEY_LEFT)) {
        return print_roms_menu();
      }
      break;
    case 1:
      app_config.emulation_speed += ((keys & KEY_RIGHT) > 0) - ((keys & KEY_LEFT) > 0);
      app_config.emulation_speed = MIN((NUM_IPF_PRESETS-1), app_config.emulation_speed);
      app_config.emulation_speed = MAX(0, app_config.emulation_speed);
      break;
    case 2:
      app_config.colour_scheme += ((keys & KEY_RIGHT) > 0) - ((keys & KEY_LEFT) > 0);
      app_config.colour_scheme = MIN((NUM_COLOUR_PRESETS-1), app_config.colour_scheme);
      app_config.colour_scheme = MAX(0, app_config.colour_scheme);

      BG_PALETTE[0] = color_presets[app_config.colour_scheme][0];
      BG_PALETTE[1] = color_presets[app_config.colour_scheme][1];
      BG_PALETTE[2] = color_presets[app_config.colour_scheme][2];
      break;
    case 3:
      app_config.vblank_on_draw ^= ((keys & KEY_RIGHT) > 0) | ((keys & KEY_LEFT) > 0);
      break;

    default:
      break;
  }
  return 0;
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


char _rom_entries[256 * 64] = {0};
char* rom_entries = &_rom_entries[0];
int rom_selection = 0;
int num_entries;

static int print_roms_menu() {
  int on_emulator = 0;
  if (isDSiMode()) {
    on_emulator = chdir("sd:/");
  } else {
    on_emulator = chdir("fat:/");
  }
  if (on_emulator) {
    chdir("nitro:/roms/");
  }

  char cwd[256];

  DIR* dirp = opendir(".");
  if (dirp == NULL) {
    printf("Error dirp == null");
  }

  
  rom_entries = &_rom_entries[0];
  rom_selection = 0;
  num_entries = fill_rom_entries(cwd, rom_entries, dirp);


  closedir(dirp);

  while (1) {
    scanKeys();
    int keys = keysDown();

    // Exit Menu
    if (keys & (KEY_START | KEY_SELECT)) {
      closedir(dirp);
      return 0;
    }
    
    if (keys & KEY_DOWN) { // Scroll Down
      rom_selection += 1;
      if (rom_selection > num_entries-1) {
        rom_selection = num_entries;
      }
    } else if (keys & KEY_UP) { // Scroll Up
      rom_selection = rom_selection - 1;
      if (rom_selection < 0) {
        rom_selection = 0;
      }
    }

    if (keys & (KEY_A | KEY_RIGHT | KEY_LEFT)) {
      if (strchr(rom_entries + 64*rom_selection, '/')) { // If selection is a directory
        chdir(rom_entries + 64*rom_selection);
        closedir(dirp);
        dirp = opendir(".");
        rom_selection = 0;
        num_entries = fill_rom_entries(cwd, rom_entries, dirp);
      } else { // If selection is a file (rom)
        char buffer[256];
        sprintf(buffer, "%.64s/%.64s", cwd, rom_entries + 64*rom_selection);
        load_rom(buffer);
        cpu_reset();
        closedir(dirp);
        return 1;
      }
    }

    print_clear(bgGetGfxPtr(print_bg_id));
    print_to_bg(
        bgGetGfxPtr(print_bg_id),
        "- Choose Rom -\n"
        "Press Select to Return\n\n",
        5,
        PrintTextCentre
        );


    char buffer[256];
    sprintf(buffer, "Current Dir: %.64s", cwd);

    print_to_bg(
        bgGetGfxPtr(print_bg_id),
        buffer,
        26,
        PrintTextCentre
        );

    int q = 0;

    for (int i = (rom_selection - 8) > 0 ? rom_selection - 8 : 0;
        i < (rom_selection - 8) ? rom_selection + 8 : 16
        && i < num_entries+1;
        i += 1) {
      sprintf(buffer, " %c %s", (rom_selection == i) ? '*' : ' ', rom_entries + 64*i);
      print_to_bg(
          bgGetGfxPtr(print_bg_id),
          buffer,
          34 + q * 8,
          PrintTextLeft
          );
      q += 1;
    }

    swiWaitForVBlank();
  }
}

static int fill_rom_entries(char* cwd, char* rom_entries, DIR* dirp) {
  char *cwd_p = getcwd(NULL, 0);
  sprintf(cwd, "%.255s", cwd_p);
  rewinddir(dirp);

  int num_elements = 0;
  while (1) {
    struct dirent *cur = readdir(dirp);

    if (cur == NULL) {
      break;
    }
    if (strlen(cur->d_name) == 0) {
      break;
    }
    num_elements += 1;
  }
  rewinddir(dirp);

  int num_valid_elements = 0;
  sprintf(rom_entries, "%.63s", cwd[0] == 'n' ? (isDSiMode() ? "sd:/" : "fat:/") : "nitro:/");

  for (int i = 1; i < num_elements+1; i++) {
    struct dirent *cur = readdir(dirp);

    if (cur == NULL) {
      break;
    }
    if (strlen(cur->d_name) == 0) {
      break;
    }

    if (cur->d_type == DT_DIR) {
      num_valid_elements += 1;
      sprintf(rom_entries+ 64*i, "%.62s/", cur->d_name);
    } else if (
        cur->d_name[strlen(cur->d_name) - 1] == '8' &&
        cur->d_name[strlen(cur->d_name) - 2] == 'h' &&
        cur->d_name[strlen(cur->d_name) - 3] == 'c' &&
        cur->d_name[strlen(cur->d_name) - 4] == '.'
    ) {
      num_valid_elements += 1;
      sprintf(rom_entries+ 64*i, "%.63s", cur->d_name);
    }
  }
  return num_valid_elements;
}
