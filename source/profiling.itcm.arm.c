#include "profiling.h"

DTCM_DATA FramerateStats framerate_stats = {0};

void profiling_framerate_push(u32 instructions_per_frame) {
  for (int i = (NUM_PREVIOUS_FRAMES - 1); i > 0; i--) {
    framerate_stats.num_instructions_per_frame[i] = framerate_stats.num_instructions_per_frame[i-1];
  }
  framerate_stats.num_instructions_per_frame[0] = instructions_per_frame;
}

u32 profiling_framerate_get_average() {
  u32 sum = 0;
  for (int i = 0; i < NUM_PREVIOUS_FRAMES; i++) {
    sum += framerate_stats.num_instructions_per_frame[i];
  }
  return sum / NUM_PREVIOUS_FRAMES;
}


u16 timer_start(int timer_id, ClockDivider divider) {
  TIMER_CR(timer_id) = 0;
  TIMER_DATA(0) = 0;
  TIMER_CR(timer_id) = divider | TIMER_ENABLE;
  return TIMER_DATA(0);
}

u16 timer_get(int timer_id) {
  return TIMER_DATA(timer_id);
}
