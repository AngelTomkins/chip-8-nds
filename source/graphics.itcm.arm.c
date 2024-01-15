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

  bgGfx = bgGetGfxPtr(bg3);
  memset(&bgGfx[0x4000], (3 << 8 | 3),  256*2);


  BG_PALETTE[0] = app_config.fg_colour;
  BG_PALETTE[1] = app_config.bg_colour;
  BG_PALETTE[2] = app_config.flair_colour;

  int bgSub = bgInitSub(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);

  decompress(keypadTiles, bgGetGfxPtr(bgSub), LZ77Vram);
  decompress(keypadMap, bgGetMapPtr(bgSub), LZ77Vram);
  decompress(keypadPal, BG_PALETTE_SUB, LZ77Vram);
}

void update_bg(u32 display[2][32]) {
    // Render to BG
      for (int large_x = 0; large_x < 256; large_x++) {
        for (int large_y = 0; large_y < 128; large_y++) {
          int small_x = large_x * 64 / 256;
          int small_y = large_y * 32 / 128;

          bgGfx[large_x/2 + large_y * 128 /*+ 4096*/] =
            (((display[small_x/32][small_y] & (1 << (small_x % 32))) > 0) << 8) 
              | ((display[small_x/32][small_y] & (1 << (small_x % 32))) > 0);
        }
      }
      bgUpdate();
}
