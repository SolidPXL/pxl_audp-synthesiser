#include "sound_effects.h"
#define CFG ((struct gating_fx_config*)config)

void fx_gate(void *config){
	static uint8_t is_gated = 0;
	static uint32_t elapsed_ms = 0;

	if(elapsed_ms>=CFG->delay_ms){
		is_gated = !is_gated;
		elapsed_ms = 0;
	}

	if(is_gated){
		for(int i=0;i<MAINBUFFER_SIZE;i++){
			g_sound_buffer[i]=0;
		}

	}

	elapsed_ms++;
}
