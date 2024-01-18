#include "graphics.h"

#include <nds.h>

#include "config.h"
//extern AppConfig app_config;

#include "keypad.h"

u16* bgGfx;


void init_bgs() {
  /*
   * Graphics Init
   */
  videoSetMode(MODE_5_2D);
  videoSetModeSub(MODE_0_2D);
  vramSetBankA(VRAM_A_MAIN_BG);
  vramSetBankC(VRAM_C_SUB_BG);


  int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
  bgSetScale(bg3, 2<<5, 2<<5);

  bgGfx = bgGetGfxPtr(bg3);
  // Draw horizontal line to show the end of the emulated display
  for (u32 i = 0x1000; i < 0x1020; i++) {
    bgGfx[i] = (3 << 8 | 3);
  }
  //memset(&bgGfx[0x1000], (3 << 8 | 3),  64);

  BG_PALETTE[0] = app_config.fg_colour;
  BG_PALETTE[1] = app_config.bg_colour;
  BG_PALETTE[2] = app_config.flair_colour;

  int bgSub = bgInitSub(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);

  decompress(keypadTiles, bgGetGfxPtr(bgSub), LZ77Vram);
  decompress(keypadMap, bgGetMapPtr(bgSub), LZ77Vram);
  decompress(keypadPal, BG_PALETTE_SUB, LZ77Vram);
}

void update_bg(u8 display[256*32]) {
  DC_FlushRange(display, 256*32);
  dmaCopy(display, bgGfx, 256*32);
  bgUpdate();
}
