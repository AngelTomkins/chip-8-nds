#ifndef LETTERS_H
#define LETTERS_H

#include <nds.h>


typedef struct __attribute__((__packed__)){
  u8 width;
  u8 data[6];
} FontLetter;

typedef struct __attribute__((__packed__)){
  FontLetter letters[95];
} FontAscii; // 658 bytes


extern FontAscii font_ascii_Nx6;

#endif
