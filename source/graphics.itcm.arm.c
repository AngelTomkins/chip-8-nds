#include "graphics.h"

#include <nds.h>

#include "config.h"

#include "keypad.h"

u16* bgGfx;
int sub_bg_id;


void init_bgs() {
  /*
   * Graphics Init
   */
  videoSetMode(MODE_5_2D);
  videoSetModeSub(MODE_0_2D);
  vramSetBankA(VRAM_A_MAIN_BG);
  vramSetBankC(VRAM_C_SUB_BG);


  // Emulator Screen on top
  int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
  bgSetScale(bg3, 2<<5, 2<<5);

  bgGfx = bgGetGfxPtr(bg3);
  // Draw horizontal line to show the end of the emulated display
  for (u32 i = 0x1000; i < 0x1020; i++) {
    bgGfx[i] = (2 << 8 | 2);
  }

  // Set colour pallete for emulator screen
  BG_PALETTE[0] = color_presets[app_config.colour_scheme][0];
  BG_PALETTE[1] = color_presets[app_config.colour_scheme][1];
  BG_PALETTE[2] = color_presets[app_config.colour_scheme][2];

  // Setup keypad background
  int sub_bg_id = bgInitSub(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);

  decompress(keypadTiles, bgGetGfxPtr(sub_bg_id), LZ77Vram);
  decompress(keypadMap, bgGetMapPtr(sub_bg_id), LZ77Vram);
  decompress(keypadPal, BG_PALETTE_SUB, LZ77Vram);
}

int get_sub_id() {
  return sub_bg_id;
}

void update_bg(u8 display[256*32]) {
  DC_FlushRange(display, 256*32);
  dmaCopy(display, bgGfx, 256*32);
  bgUpdate();
}
