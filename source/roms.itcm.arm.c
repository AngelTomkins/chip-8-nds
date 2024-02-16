#include "roms.h"
#include <filesystem.h>


void load_rom(char* path, u8* cpu_ram) {
    chdir("nitro:/roms/");
    FILE *f = fopen(path, "rb");
    if ( f == NULL) {
      consoleDemoInit();
      printf("Couldn't open %s", path);
      while (1) { swiWaitForVBlank(); }
    }

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (fileSize > 0xC8F) {
      consoleDemoInit();
      printf("Rom too big: %lu\nin %s", fileSize, path);
      while (1) { swiWaitForVBlank(); }
    }

    fread(&cpu_ram[0x200], sizeof(u8), fileSize, f);

    fclose(f);
}
