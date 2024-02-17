#include "cpu.h"
#include <filesystem.h>
#include <stdlib.h>
#include "config.h"
#include "graphics.h"

#include "../include/tonccpy.h"

#define VF_REGISTER 1

DTCM_DATA Cpu cpu = {
  .pc = 0x200,
  .index = 0,
  .registers_vx = {0},
  .delay_timer = 0,
  .sound_timer = 0,
  .key_down = 0,
  .key_old = 0,
  .stack = {0},
  .sp = 0,
};

DTCM_BSS u8 instruction_first;
DTCM_BSS u8 instruction_second;

__attribute__((aligned(32))) u8 display[64*32] = {0};

// Returns an initialized cpu instance
Cpu* cpu_init() {
  cpu.ram = (u8*)calloc(4096, sizeof(u8));
  sassert(cpu.ram != NULL, "Could not allocate ram");

  FILE *f = fopen("nitro:/internal/character_data.bin", "rb");
  fread(cpu.ram, 1, 80, f);
  fclose(f);

  return &cpu;
}


void cpu_next_instruction() {
  instruction_first = cpu.ram[cpu.pc];
  instruction_second = cpu.ram[cpu.pc + 1];
  cpu.pc += 2;

  switch (instruction_first >> 4) {
    case 0x0: 
      switch (instruction_second) {
        case 0xE0:
          ins_00E0();
          break;
        case 0xEE:
          ins_00EE();
          break;
        default:
          break;
      }
      break;

    case 0x1:
      ins_1NNN();
      break;

    case 0x2:
      ins_2NNN();
      break;

    case 0x3:
      ins_3XNN();
      break;
      
    case 0x4:
      ins_4XNN();
      break;

    case 0x5:
      switch (instruction_second & 0xF) {
        case 0x0:
          ins_5XY0();
          break;
        default:
          break;
      }
      break;

    case 0x6:
      ins_6XNN();
      break;

    case 0x7:
      ins_7XNN();
      break;

    case 0x8:
      switch (instruction_second & 0xF) {
        case 0x0:
          ins_8XY0();
          break;
        case 0x1:
          ins_8XY1();
          break;
        case 0x2:
          ins_8XY2();
          break;
        case 0x3:
          ins_8XY3();
          break;
        case 0x4:
          ins_8XY4();
          break;
        case 0x5:
          ins_8XY5();
          break;
        case 0x6:
          ins_8XY6();
          break;
        case 0x7:
          ins_8XY7();
          break;
        case 0xE:
          ins_8XYE();
          break;
        default:
          break;
      }
      break;

    case 0x9:
      switch (instruction_second & 0xF) {
        case 0x0:
          ins_9XY0();
          break;
        default:
          break;
      }
      break;

    case 0xA:
      ins_ANNN();
      break;

    case 0xB:
      ins_BNNN();
      break;

    case 0xC:
      ins_CXNN();
      break;

    case 0xD:
      ins_DXYN();
      break;

    case 0xE:
      switch (instruction_second & 0xFF) {
        case 0x9E:
          ins_EX9E();
          break;
        case 0xA1:
          ins_EXA1();
          break;
        default:
          break;
      }
      break;

    case 0xF: 
      switch (instruction_second & 0xFF) {
        case 0x07:
          ins_FX07();
          break;
        case 0x0A:
          ins_FX0A();
          break;
        case 0x15:
          ins_FX15();
          break;
        case 0x18:
          ins_FX18();
          break;
        case 0x1E:
          ins_FX1E();
          break;
        case 0x29:
          ins_FX29();
          break;
        case 0x33:
          ins_FX33();
          break;
        case 0x55:
          ins_FX55();
          break;
        case 0x65:
          ins_FX65();
          break;
        default:
          break;
      }
      break;

    default:
      break;
  }

}

static u16 get_nnn() {
  return (instruction_first & 0xF) << 8 | instruction_second;
}

static u8 get_reg_x() {
  return instruction_first & 0xF;
}
static u8 get_reg_y() {
  return instruction_second >> 4;
}

void ins_00E0() {
  toncset32(display, 0, sizeof(display));
  update_bg(display);
}

void ins_00EE() {
  cpu.pc = cpu.stack[cpu.sp];
  cpu.sp -= 1;
}

void ins_1NNN() {
  cpu.pc = get_nnn();
}

void ins_2NNN() {
  cpu.sp += 1;
  cpu.stack[cpu.sp] = cpu.pc;
  cpu.pc = get_nnn();
}

void ins_3XNN() {
  if (cpu.registers_vx[get_reg_x()] == (instruction_second)) {
    cpu.pc += 2;
  }
}

void ins_4XNN() {
  if (cpu.registers_vx[get_reg_x()] != (instruction_second)) {
    cpu.pc += 2;
  }
}

void ins_5XY0() {
  if (cpu.registers_vx[get_reg_x()] == cpu.registers_vx[get_reg_y()]) {
    cpu.pc += 2;
  }
}

void ins_6XNN() {
  cpu.registers_vx[get_reg_x()] = instruction_second;
}

void ins_7XNN() {
  cpu.registers_vx[get_reg_x()] += instruction_second;
}

void ins_8XY0() {
  cpu.registers_vx[get_reg_x()] = cpu.registers_vx[get_reg_y()];
}

void ins_8XY1() {
  cpu.registers_vx[get_reg_x()] |= cpu.registers_vx[get_reg_y()];
}

void ins_8XY2() {
  cpu.registers_vx[get_reg_x()] &= cpu.registers_vx[get_reg_y()];
}

void ins_8XY3() {
  cpu.registers_vx[get_reg_x()] ^= cpu.registers_vx[get_reg_y()];
}

void ins_8XY4() {
  u32 temp = cpu.registers_vx[get_reg_x()] + cpu.registers_vx[get_reg_y()];
  cpu.registers_vx[get_reg_x()] = temp;

  cpu.registers_vx[0xF] = temp >> 8;
}

void ins_8XY5() {
  register u32 underflow = cpu.registers_vx[get_reg_x()] < cpu.registers_vx[get_reg_y()];
  cpu.registers_vx[get_reg_x()] -= cpu.registers_vx[get_reg_y()];
  cpu.registers_vx[0xF] = !underflow;
}

void ins_8XY6() {
  u8 lsb = cpu.registers_vx[get_reg_x()] & 0x01;
  cpu.registers_vx[get_reg_x()] = cpu.registers_vx[get_reg_y()] >> 1;
  cpu.registers_vx[0xF] = lsb;
}

void ins_8XY7() {
  register u32 underflow = cpu.registers_vx[get_reg_y()] < cpu.registers_vx[get_reg_x()];
  cpu.registers_vx[get_reg_x()] = cpu.registers_vx[get_reg_y()] - cpu.registers_vx[get_reg_x()];
  cpu.registers_vx[0xF] = !underflow;
}

void ins_8XYE() {
  u32 temp = cpu.registers_vx[get_reg_x()];
  temp <<= 1;

  cpu.registers_vx[get_reg_x()] = temp;
  cpu.registers_vx[0xF] = temp >> 8;
}

void ins_9XY0() {
  if (cpu.registers_vx[get_reg_x()] != cpu.registers_vx[get_reg_y()]) {
    cpu.pc += 2;
  }
}
void ins_ANNN() {
  cpu.index = get_nnn();
}
void ins_BNNN() {
  cpu.pc = (get_nnn()) + cpu.registers_vx[0];
}
void ins_CXNN() {
  cpu.registers_vx[get_reg_x()] = rand() % (instruction_second);
}

void ins_DXYN() {
  u8 flag_changed = 0;

  const u8 x_val = cpu.registers_vx[get_reg_x()] % 64;
  const u8 y_val = cpu.registers_vx[get_reg_y()] % 32;

  for (u32 i = 0; i < (instruction_second & 0xF); i++) {
    const u8 y_pos = y_val + i;
    if (y_pos >= 32) {
      return;
    }

    u8 display_byte = cpu.ram[cpu.index + i];

    for (u32 j = 0; j < 8; j++) {
      const u8 x_pos = x_val + j;
      if (x_pos >= 64) {
        break;
      }

      flag_changed |= ( display[x_pos + y_pos*64] != ((display_byte & (0x80 >> j)) != 0) );

      display[x_pos + y_pos*64] ^= (display_byte & (0x80 >> j)) != 0;
    }
  }
  cpu.registers_vx[0xF] = flag_changed;

  update_bg(display);
  if (app_config.vblank_on_draw) {
    swiWaitForVBlank();
  }
}

void ins_EX9E() {
  if (cpu.key_down == cpu.registers_vx[get_reg_x()] && (!(cpu.key_down & 0x10)) ) {
    cpu.pc += 2;
  }
}

void ins_EXA1() {
  if (cpu.key_down != cpu.registers_vx[get_reg_x()]) {
    cpu.pc += 2;
  }
}

void ins_FX07() {
  cpu.registers_vx[get_reg_x()] = cpu.delay_timer;
}

void ins_FX0A() {
  if (cpu.key_down & 0x10 && cpu.key_old & 0xF) {
    cpu.registers_vx[get_reg_x()] = cpu.key_old;
  } else {
    cpu.pc -= 2;
  }
}

void ins_FX15() {
  cpu.delay_timer = cpu.registers_vx[get_reg_x()];
}

void ins_FX18() {
  cpu.sound_timer = cpu.registers_vx[get_reg_x()];
}

void ins_FX1E() {
  cpu.index += cpu.registers_vx[get_reg_x()];
}

void ins_FX29() {
  cpu.index = cpu.registers_vx[get_reg_x()] * 5;
}

void ins_FX33() {
  register u8 x = cpu.registers_vx[get_reg_x()];
  cpu.ram[cpu.index] = x / 100;
  x %= 100;
  
  cpu.ram[cpu.index + 1] = x / 10;

  x %= 10;
  cpu.ram[cpu.index + 2] = x;
}

void ins_FX55() {
  for (int i = 0; i <= (get_reg_x()); i++) {
    cpu.ram[cpu.index + i] = cpu.registers_vx[i];
  }
  cpu.index += (get_reg_x()) + 1;
}

void ins_FX65() {
  for (int i = 0; i <= (get_reg_x()); i++) {
    cpu.registers_vx[i] = cpu.ram[cpu.index + i];
  }
  cpu.index += cpu.registers_vx[get_reg_x()] + 1;
}
