#ifndef CPU_H
#define CPU_H

#include <nds.h>

typedef void (*FunctionPointer)();

/****************/
/* Instructions */
/****************/
void ins_00E0();
void ins_00EE();
void ins_1NNN();
void ins_2NNN();
void ins_3XNN();
void ins_4XNN();
void ins_5XY0();
void ins_6XNN();
void ins_7XNN();
void ins_8XY0();
void ins_8XY1();
void ins_8XY2();
void ins_8XY3();
void ins_8XY4();
void ins_8XY5();
void ins_8XY6();
void ins_8XY7();
void ins_8XYE();
void ins_9XY0();
void ins_ANNN();
void ins_BNNN();
void ins_CXNN();
void ins_DXYN();
void ins_EX9E();
void ins_EXA1();
void ins_FX07();
void ins_FX0A();
void ins_FX15();
void ins_FX18();
void ins_FX1E();
void ins_FX29();
void ins_FX33();
void ins_FX55();
void ins_FX65();


typedef struct {
  u16 pc;
  u16 index;

  u8 registers_vx[16];

  u8 delay_timer;
  u8 sound_timer;

  u8 key_down;
  u8 key_old;

  u16 stack[24]; // Stack size is not strictly defined in spec
  u8 sp;


  u32 display[2][32];
  bool display_updated;

  //u8* ram; // 4096 bytes on heap 
  u8 ram[4096]; // 4096 bytes on stack
} Cpu;

// Returns an initialized cpu instance
Cpu* cpu_init();

void cpu_next_instruction();


#endif
