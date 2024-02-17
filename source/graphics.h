#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <nds.h>

typedef struct {
  int main[4];
  int sub[4];
} BgIds;


extern void asm_update_bg(u8 dtcm_bg[64*32], u16* bgGfx);

BgIds* init_bgs();
void update_bg(u8 display[64*32]);
int get_sub_id();

#endif
