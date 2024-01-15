#include "app.h"

#include <filesystem.h>

#define DEFAULT_ROM "nitro:/roms/Pong (1 player).ch8"

int main(int argc, char* argv[]) {

  char* rom;
  if (argc > 1) {
    rom = argv[1];
  } else {
    rom = DEFAULT_ROM;
  }


  app_run(rom);
  return 0;
}
