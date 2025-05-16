#include "generators.h"
#define CFG ((struct supersaw_generator_config*)config)

void supersaw_generator(void* config){

	struct supersaw_generator_config parsed_config = *((struct supersaw_generator_config*)(config));

	//Set the right increment

	for(int i=0;i<CFG->voices;i++){
		float frac = (CFG->voices == 1) ? 0.0f : (float)i / (CFG->voices - 1);
		float offset = (frac - 0.5f) * CFG->voice_width;
		float voice_freq = CFG->freq + offset;
		CFG->phasebuffers[i].phase_inc = voice_freq / SAMPLE_RATE_HZ;
	}


	for (int i = 0; i < MAINBUFFER_SIZE; i++) {
		for(int j=0;j<CFG->voices;j++){
			g_sound_buffer[i] += (int32_t)(ftriangle_func(CFG->phasebuffers[j].phase) * (parsed_config.amp/CFG->voices));
			CFG->phasebuffers[j].phase += CFG->phasebuffers[j].phase_inc;
			if (CFG->phasebuffers[j].phase >= 1.0f) CFG->phasebuffers[j].phase -= 1.0f;
		}
	  g_sample_index++;
	}

}
