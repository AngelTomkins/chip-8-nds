#include "roms.h"
#include <filesystem.h>
#include "cpu.h"

extern Cpu cpu;

void load_rom(char* path) {
    FILE *f = fopen(path, "rb");
    if ( f == NULL) {
      consoleDemoInit();
      printf("Couldn't open %s", path);
      while (1) { swiWaitForVBlank(); }
    }

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (fileSize > 0xe00) {
      consoleDemoInit();
      printf("Rom too big: %lu\nin %s", fileSize, path);
      while (1) { swiWaitForVBlank(); }
    }

    if(fread(&cpu.ram[0x200], sizeof(u8), fileSize, f) != fileSize) {
      consoleDemoInit();
      printf("There was an error reading the file:\n%s", path);
      while (1) { swiWaitForVBlank(); }
    }
    fclose(f);
}
void load_rom2(char* path) {
  return;
}
