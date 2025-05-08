#ifndef GENERATORS_H
#define GENERATORS_H
#include "../globals.h"
#include <stdint.h>
#include <arm_math.h>

extern uint32_t g_sample_index;
extern int32_t g_sound_buffer[MAINBUFFER_SIZE];

typedef struct {
  float phase;        // [0,1) wrap-around
  float phase_inc;    // = freq / sample_rate
} OscState;


//Generators
struct sine_generator_config{
	float freq;
	uint32_t amp;
};
void sine_generator(void* config);



#endif
