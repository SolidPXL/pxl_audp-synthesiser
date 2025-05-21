#ifndef SOUND_EFFECTS_H
#define SOUND_EFFECTS_H

#include "../globals.h"
#include <stdint.h>
#include <arm_math.h>

extern uint32_t g_sample_index;
extern int32_t g_sound_buffer[MAINBUFFER_SIZE];

//Volume FX
 struct distortion_config{
    float32_t gain;
    float32_t threshold;
} ;
void distortion(void *config);

//Delays, echos and reverb
struct delay_config {
    uint32_t delay_samples;
    float32_t feedback;
} ;
void delay_effect(void *config);

struct lowpass_config{
    float32_t alpha;
    float32_t prev;
} ;
void lowpass(void *config);



//Filters
void filterlp(void *config);


//Envelopes and LFOS

//For performance, keep the delay in multiples of 2 ms
struct gating_fx_config{
    uint32_t delay_ms;
} ;
void fx_gate(void *config);

#endif // SOUND_EFFECTS_H
