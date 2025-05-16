#ifndef GENERATORS_H
#define GENERATORS_H
#include "../globals.h"
#include <stdint.h>
#include <arm_math.h>

extern uint32_t g_sample_index;
extern int32_t g_sound_buffer[MAINBUFFER_SIZE];

struct Osc_State{
  float phase;        // [0,1) wrap-around
  float phase_inc;    // = freq / sample_rate
};
typedef struct Osc_State OscState;



//Generators
struct sine_generator_config{
	float freq;
	uint32_t amp;
	OscState phasebuffer;
};
void sine_generator(void* config);

struct saw_generator_config{
	float freq;
	uint32_t amp;
	OscState phasebuffer;
};
void saw_generator(void* config);

struct square_generator_config{
	float freq;
	uint32_t amp;
	OscState phasebuffer;
};
void square_generator(void* config);

struct triangle_generator_config{
	float freq;
	uint32_t amp;
	OscState phasebuffer;
};
void triangle_generator(void* config);

struct supersaw_generator_config{
	float freq;
	float amp;
	OscState* phasebuffers;
	uint8_t voices;
	float voice_width;
};
void supersaw_generator(void* config);

//functions
int32_t isquare_func(float phase, float amp);
float fsquare_func(float phase);
int32_t isawd_func(float phase, float amp);
float fsawd_func(float phase);
int32_t isawa_func(float phase, float amp);
float fsawa_func(float phase);
int32_t itriangle_func(float phase, float amp);
float ftriangle_func(float phase);



#endif
