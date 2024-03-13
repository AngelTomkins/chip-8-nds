#ifndef PRINT_H
#define PRINT_H

#include <nds.h>


typedef enum {
  PrintTextLeft,
  PrintTextRight,
  PrintTextCentre,
} PrintTextAlignment;

void print_to_bg(u16* gfx, char* string, int v_offset, PrintTextAlignment alignment);
void print_clear(u16* gfx);

#endif

