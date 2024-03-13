#include "graphics.h"

#include <nds.h>
#include "../include/tonccpy.h"

#include "config.h"
#include "keypad.h"

u16* bgGfx;

BgIds bg_ids;

BgIds* init_bgs() {
  videoSetMode(MODE_5_2D);
  videoSetModeSub(MODE_5_2D);
  vramSetBankA(VRAM_A_MAIN_BG);
  vramSetBankC(VRAM_C_SUB_BG);

  // Emulator Screen on top
  bg_ids.main[3] = bgInit(3, BgType_Bmp8, BgSize_B8_128x128, 0, 0);
  bgSetScale(bg_ids.main[3], 2<<5, 2<<5);

  bgGfx = bgGetGfxPtr(bg_ids.main[3]);
  // Draw horizontal line to show the end of the emulated display
  for (u32 i = 0x800; i < 0x820; i++) {
    bgGfx[i] = (2 << 8 | 2);
  }

  // Set colour pallete for emulator screen
  BG_PALETTE[0] = color_presets[app_config.colour_scheme][0];
  BG_PALETTE[1] = color_presets[app_config.colour_scheme][1];
  BG_PALETTE[2] = color_presets[app_config.colour_scheme][2];

  // Setup keypad background
  bg_ids.sub[0] = bgInitSub(0, BgType_Text8bpp, BgSize_T_256x256, 7, 0);
  bg_ids.sub[2] = bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 3, 0);
  bgHide(bg_ids.sub[2]);
  toncset16(bgGetGfxPtr(bg_ids.sub[2]), 253<<8|253, 256*256/2);

  dmaCopy(keypadTiles, bgGetGfxPtr(bg_ids.sub[0]), keypadTilesLen);
  dmaCopy(keypadMap, bgGetMapPtr(bg_ids.sub[0]), keypadMapLen);
  dmaCopy(keypadPal, BG_PALETTE_SUB, keypadPalLen);

  BG_PALETTE_SUB[253] = RGB15(0,0,0);
  BG_PALETTE_SUB[254] = RGB15(31,31,31);

  return &bg_ids;
}

void ITCM_CODE ARM_CODE update_bg(u8 display[64*32]) {
  asm_update_bg(display, bgGfx);
}
