#include "app.h"

#include <filesystem.h>
#include <stdlib.h>
#include "config.h"
#include "graphics.h"
#include "roms.h"
#include "cpu.h"


DTCM_BSS Cpu* cpu_p;
DTCM_BSS touchPosition touchXY;

DTCM_BSS int sound;

DTCM_DATA static const u8 KEYBOARD_LAYOUT[16] = {
  0x1, 0x2, 0x3, 0xC,
  0x4, 0x5, 0x6, 0xD,
  0x7, 0x8, 0x9, 0xE,
  0xA, 0x0, 0xB, 0xF
};


static void init(char* rom);
static void loop();
static ARM_CODE void update_keys();

void Vblank() {
    cpu_p->sound_timer -= cpu_p->sound_timer ? 1 : 0;
    cpu_p->delay_timer -= cpu_p->delay_timer ? 1 : 0;
    if (cpu_p->sound_timer != 0) {
      soundResume(sound);
    } else {
      soundPause(sound);
    }
}

void app_run(char* rom) {
  init(rom);
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

  init_config();
  init_bgs();
  cpu_p = cpu_init();
  load_rom(rom, cpu_p->ram);

  irqSet(IRQ_VBLANK, Vblank);
}

static void loop() {
  while (1) {
    for (int i = 0; i < app_config.emulation_speed; i++) {
      cpu_next_instruction();
      update_keys();
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

