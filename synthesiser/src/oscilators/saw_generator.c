#include "generators.h"
#define CFG ((struct saw_generator_config*)config)

void saw_generator(void* config){

	struct saw_generator_config parsed_config = *((struct saw_generator_config*)(config));

	//Set the right increment
	CFG->phasebuffer.phase_inc = parsed_config.freq/SAMPLE_RATE_HZ;


	for (int i = 0; i < MAINBUFFER_SIZE; i++) {
	  g_sound_buffer[i] += (int32_t)(fsawd_func(CFG->phasebuffer.phase) * parsed_config.amp);
	  CFG->phasebuffer.phase += CFG->phasebuffer.phase_inc;
	  if (CFG->phasebuffer.phase >= 1.0f) CFG->phasebuffer.phase -= 1.0f;
	  g_sample_index++;
	}

}

