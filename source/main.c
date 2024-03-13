#include "app.h"

#include <filesystem.h>

int main(int argc, char* argv[]) {

  char* rom;
  if (argc > 1) {
    rom = argv[1];
  } else {
    rom = NULL;
  }

  app_run(rom);
  return 0;
}
