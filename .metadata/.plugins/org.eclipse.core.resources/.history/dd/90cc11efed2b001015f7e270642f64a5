#include "generators.h"


void sine_generator(void* config){
	struct sine_generator_config parsed_config = *((struct sine_generator_config*)(config));
	static OscState phasebuffer = { 0.0f,0.0f};

	//Set the right increment
	phasebuffer.phase_inc = parsed_config.freq/SAMPLE_RATE_HZ;


	for (int i = 0; i < MAINBUFFER_SIZE; i++) {
	  g_sound_buffer[i] = sinf(2*M_PI * phasebuffer.phase) * parsed_config.amp;
	  phasebuffer.phase += phasebuffer.phase_inc;
	  if (phasebuffer.phase >= 1.0f) phasebuffer.phase -= 1.0f;
	  g_sample_index++;
	}

}

