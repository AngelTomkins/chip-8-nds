#include "app.h"

#include <nds.h>
#include <fat.h>
#include <filesystem.h>
#include <stdlib.h>
#include "config.h"
#include "graphics.h"
#include "profiling.h"
#include "roms.h"
#include "cpu.h"
#include "menu.h"


Cpu* cpu_p;
touchPosition touchXY;
DTCM_BSS u32 instructions_per_frame;
bool emulation_paused;

int sound;

static const u8 KEYBOARD_LAYOUT[16] = {
  0x1, 0x2, 0x3, 0xC,
  0x4, 0x5, 0x6, 0xD,
  0x7, 0x8, 0x9, 0xE,
  0xA, 0x0, 0xB, 0xF
};


static void init(char* rom);
static void loop();
static void update_keys();


void Vblank() {
}

void app_run(char* rom) {
  init(rom);
  cpu_reset();
  loop();
}

static void init(char* rom) {
  soundEnable();
  sound = soundPlayPSG(DutyCycle_50, 1000, 127, 64);
  soundPause(sound);

  if (!nitroFSInit(NULL)) {
    consoleDemoInit();
    printf("didn't init");
    while (1) { swiWaitForVBlank(); }
  }
  fatInitDefault();

  BgIds* bg_ids = init_bgs();
  init_config_console(bg_ids->sub[2], bg_ids->sub[0]);

  cpu_p = cpu_init();
  if (rom != NULL) {
    load_rom(rom);
  } else {
    open_menu();
  }

  irqSet(IRQ_VBLANK, Vblank);
}

static void loop() {
  while (1) {
    update_keys();
    if (keysDown() & KEY_START) {
      soundPause(sound);
      open_menu();
      continue;
    }

    profiling_framerate_push(instructions_per_frame);
    instructions_per_frame = 0;
    cpu_p->sound_timer -= cpu_p->sound_timer ? 1 : 0;
    cpu_p->delay_timer -= cpu_p->delay_timer ? 1 : 0;
    if (cpu_p->sound_timer != 0) {
      soundResume(sound);
    } else {
      soundPause(sound);
    }

    for (int i = 0; i < ipf_presets[app_config.emulation_speed]; i++) {
      cpu_next_instruction();
      instructions_per_frame += 1;
    }

    swiWaitForVBlank();
  }
}

static void update_keys() {
    scanKeys();
    if (keysHeld() & KEY_TOUCH) {
      touchRead(&touchXY);
      if (touchXY.px >= 192) {
        return;
      }
      int index = (touchXY.px / 48) | (touchXY.py / 48) << 2;
      cpu_p->key_down = KEYBOARD_LAYOUT[index];
    } else {
      cpu_p->key_old = cpu_p->key_down;
      cpu_p->key_down = 0x10;
    }
}

