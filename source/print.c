#include "print.h"
#include <string.h>
#include "../include/tonccpy.h"
#include "font_letters.h"
/*
FontLetter letters[] = {
  {
    .width = 3,
    .data[0] = 0b01000000, 
    .data[1] = 0b10100000,
    .data[2] = 0b10100000,
    .data[3] = 0b11100000,
    .data[4] = 0b10100000,
  },
  {
    .width = 3,
    .data[0] = 0b11000000, 
    .data[1] = 0b10100000,
    .data[2] = 0b11000000, 
    .data[3] = 0b10100000,
    .data[4] = 0b11000000, 
  },
  {
    .width = 3,
    .data[0] = 0b01100000, 
    .data[1] = 0b10000000,
    .data[2] = 0b10000000, 
    .data[3] = 0b10000000,
    .data[4] = 0b01100000, 
  },
  {
    .width = 3,
    .data[0] = 0b11000000, 
    .data[1] = 0b10100000,
    .data[2] = 0b10100000, 
    .data[3] = 0b10100000,
    .data[4] = 0b11000000, 
  },
  {
    .width = 2,
    .data[0] = 0b11000000, 
    .data[1] = 0b10000000,
    .data[2] = 0b11000000, 
    .data[3] = 0b10000000, 
    .data[4] = 0b11000000,
  },
  {
    .width = 2,
    .data[0] = 0b11000000, 
    .data[1] = 0b10000000,
    .data[2] = 0b11000000, 
    .data[3] = 0b10000000, 
    .data[4] = 0b10000000,
  },
  {
    .width = 3,
    .data[0] = 0b01100000, 
    .data[1] = 0b10000000,
    .data[2] = 0b10000000, 
    .data[3] = 0b10100000, 
    .data[4] = 0b01100000,
  },
  {
    .width = 3,
    .data[0] = 0b10100000, 
    .data[1] = 0b10100000,
    .data[2] = 0b11100000, 
    .data[3] = 0b10100000, 
    .data[4] = 0b10100000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b01000000,
    .data[2] = 0b01000000, 
    .data[3] = 0b01000000, 
    .data[4] = 0b11100000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b01000000,
    .data[2] = 0b01000000, 
    .data[3] = 0b01000000, 
    .data[4] = 0b10000000,
  },
  {
    .width = 3,
    .data[0] = 0b10100000, 
    .data[1] = 0b10100000,
    .data[2] = 0b11000000, 
    .data[3] = 0b10100000, 
    .data[4] = 0b10100000,
  },
  {
    .width = 3,
    .data[0] = 0b10000000, 
    .data[1] = 0b10000000,
    .data[2] = 0b10000000, 
    .data[3] = 0b10000000, 
    .data[4] = 0b11100000,
  },
  {
    .width = 4,
    .data[0] = 0b10010000, 
    .data[1] = 0b11110000,
    .data[2] = 0b10010000, 
    .data[3] = 0b10010000, 
    .data[4] = 0b10010000,
  },
  {
    .width = 4,
    .data[0] = 0b10010000, 
    .data[1] = 0b11010000,
    .data[2] = 0b10110000, 
    .data[3] = 0b10010000, 
    .data[4] = 0b10010000,
  },
  {
    .width = 3,
    .data[0] = 0b01000000, 
    .data[1] = 0b10100000,
    .data[2] = 0b10100000, 
    .data[3] = 0b10100000, 
    .data[4] = 0b01000000,
  },
  {
    .width = 3,
    .data[0] = 0b11000000, 
    .data[1] = 0b10100000,
    .data[2] = 0b11000000, 
    .data[3] = 0b10000000, 
    .data[4] = 0b10000000,
  },
  {
    .width = 3,
    .data[0] = 0b01000000, 
    .data[1] = 0b10100000,
    .data[2] = 0b10100000, 
    .data[3] = 0b01000000, 
    .data[4] = 0b00100000,
  },
  {
    .width = 3,
    .data[0] = 0b11000000, 
    .data[1] = 0b10100000,
    .data[2] = 0b11000000, 
    .data[3] = 0b10100000, 
    .data[4] = 0b10100000,
  },
  {
    .width = 3,
    .data[0] = 0b01100000, 
    .data[1] = 0b10000000,
    .data[2] = 0b01000000, 
    .data[3] = 0b00100000, 
    .data[4] = 0b11000000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b01000000,
    .data[2] = 0b01000000, 
    .data[3] = 0b01000000, 
    .data[4] = 0b01000000,
  },
  {
    .width = 3,
    .data[0] = 0b10100000, 
    .data[1] = 0b10100000,
    .data[2] = 0b10100000, 
    .data[3] = 0b10100000, 
    .data[4] = 0b11100000,
  },
  {
    .width = 3,
    .data[0] = 0b10100000, 
    .data[1] = 0b10100000,
    .data[2] = 0b10100000, 
    .data[3] = 0b11100000, 
    .data[4] = 0b01000000,
  },
  {
    .width = 4,
    .data[0] = 0b10010000, 
    .data[1] = 0b10010000,
    .data[2] = 0b10010000, 
    .data[3] = 0b11110000, 
    .data[4] = 0b10010000,
  },
  {
    .width = 3,
    .data[0] = 0b10100000, 
    .data[1] = 0b10100000,
    .data[2] = 0b01000000, 
    .data[3] = 0b10100000, 
    .data[4] = 0b10100000,
  },
  {
    .width = 3,
    .data[0] = 0b10100000, 
    .data[1] = 0b10100000,
    .data[2] = 0b01000000, 
    .data[3] = 0b01000000, 
    .data[4] = 0b01000000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b00100000,
    .data[2] = 0b01000000, 
    .data[3] = 0b10000000, 
    .data[4] = 0b11100000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b10100000,
    .data[2] = 0b10100000,
    .data[3] = 0b10100000,
    .data[4] = 0b11100000,
  },
  {
    .width = 1,
    .data[0] = 0b10000000, 
    .data[1] = 0b10000000,
    .data[2] = 0b10000000,
    .data[3] = 0b10000000,
    .data[4] = 0b10000000,
  },
  {
    .width = 3,
    .data[0] = 0b11000000, 
    .data[1] = 0b00100000,
    .data[2] = 0b01000000,
    .data[3] = 0b10000000,
    .data[4] = 0b11100000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b00100000,
    .data[2] = 0b11100000,
    .data[3] = 0b00100000,
    .data[4] = 0b11100000,
  },
  {
    .width = 3,
    .data[0] = 0b10100000, 
    .data[1] = 0b10100000,
    .data[2] = 0b11100000,
    .data[3] = 0b00100000,
    .data[4] = 0b00100000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b10000000,
    .data[2] = 0b11100000,
    .data[3] = 0b00100000,
    .data[4] = 0b11100000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b10000000,
    .data[2] = 0b11100000,
    .data[3] = 0b10100000,
    .data[4] = 0b11100000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b00100000,
    .data[2] = 0b00100000,
    .data[3] = 0b00100000,
    .data[4] = 0b00100000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b10100000,
    .data[2] = 0b11100000,
    .data[3] = 0b10100000,
    .data[4] = 0b11100000,
  },
  {
    .width = 3,
    .data[0] = 0b11100000, 
    .data[1] = 0b10100000,
    .data[2] = 0b11100000,
    .data[3] = 0b00100000,
    .data[4] = 0b00100000,
  },
  {
    .width = 1,
    .data[0] = 0b00000000, 
    .data[1] = 0b00000000,
    .data[2] = 0b00000000,
    .data[3] = 0b00000000,
    .data[4] = 0b10000000,
  },
  {
    .width = 1,
    .data[0] = 0b10000000, 
    .data[1] = 0b10000000,
    .data[2] = 0b10000000,
    .data[3] = 0b00000000,
    .data[4] = 0b10000000,
  },
  {
    .width = 5,
    .data[0] = 0b01010000, 
    .data[1] = 0b10101000,
    .data[2] = 0b01110000,
    .data[3] = 0b10101000,
    .data[4] = 0b01010000,
  },
  {
    .width = 1,
    .data[0] = 0b00000000, 
    .data[1] = 0b10000000,
    .data[2] = 0b00000000,
    .data[3] = 0b10000000,
    .data[4] = 0b00000000,
  },
  {
    .width = 3,
    .data[0] = 0b00000000,
    .data[1] = 0b00000000,
    .data[2] = 0b00000000,
    .data[3] = 0b00000000,
    .data[4] = 0b00000000,
  },
};
*/

FontLetter get_letter_from_char(char letter);
int get_number_pixels(char* string);
int get_offset(PrintTextAlignment alignment, char* string);

void print_clear(u16* gfx) {
  toncset16(gfx, 253<<8|253, 256*192/2);
}

void print_to_bg(u16* gfx, char* string, int v_offset, PrintTextAlignment alignment) {
  v_offset *= 256;
  int gfx_offset = get_offset(alignment, string);


  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == '\n') {
      v_offset += 256 * 8;
      gfx_offset = get_offset(alignment, &string[i+1]);
      continue;
    }

    if (gfx_offset >= 252) {
      v_offset += 256 * 8;
      gfx_offset = get_offset(alignment, &string[i+1]);
    }

    
    u8 index = (string[i]-32);
    u8 width = font_ascii_Nx6.letters[index].width;

    for (int x = 0; x < 6; x++) {
      u8 data = font_ascii_Nx6.letters[index].data[x];
      for (int j = 0; j < width; j++) {
        ((u8*)gfx)[gfx_offset + v_offset + (j + x*256)] = ((data >> (7-j)) & 1) ? 254 : 253;
      }
    }
    gfx_offset += width + 1;
  }

}

int get_number_pixels(char* string) {
  int pixels = 0;
  while (*string != '\n' && *string != '\0') {
    u8 index = *(string++) - 32;
    pixels += 1 + (font_ascii_Nx6.letters[index].width);
  }
  return pixels;
}

int get_offset(PrintTextAlignment alignment, char* string) {
  switch (alignment) {
    default:
    case PrintTextLeft:
      return 0;
    case PrintTextCentre:
      return (256 - get_number_pixels(string)) / 2;
    case PrintTextRight:
      return 256 - get_number_pixels(string);
  }
}
