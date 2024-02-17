#ifndef PROFILING_H
#define PROFILING_H
#include <nds.h>

#define NUM_PREVIOUS_FRAMES 30

typedef struct __attribute__((__packed__)) {
  u16 num_instructions_per_frame[NUM_PREVIOUS_FRAMES];
} FramerateStats;

void profiling_framerate_init();
void profiling_framerate_push(u32 instructions_per_frame);
u32 profiling_framerate_get_average();

u16 timer_start(int timer_id, ClockDivider divider);
u16 timer_get(int timer_id);

#endif
