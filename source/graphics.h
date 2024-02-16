#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <nds.h>

void init_bgs();
void update_bg(u8 display[256*32]);
int get_sub_id();

#endif
