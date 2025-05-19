#include "sound_effects.h"

//Keep in mind, these taps were computed on a buffer time of 2 ms, buffer size of 96 and samplerate of 48000Hz
//https://fiiir.com/
#define FILTER_TAP_NUM 39  // Number of coefficients (N)
static const float fir_taps[] = {
    -0.0006340646f,
    -0.0004215772f,
    -0.0001370670f,
     0.0003752429f,
     0.0012896313f,
     0.0027803639f,
     0.0050014815f,
     0.0080669426f,
     0.0120332201f,
     0.0168862919f,
     0.0225345889f,
     0.0288089174f,
     0.0354697054f,
     0.0422211998f,
     0.0487315382f,
     0.0546570133f,
     0.0596683926f,
     0.0634769125f,
     0.0658575531f,
     0.0666674268f,
     0.0658575531f,
     0.0634769125f,
     0.0596683926f,
     0.0546570133f,
     0.0487315382f,
     0.0422211998f,
     0.0354697054f,
     0.0288089174f,
     0.0225345889f,
     0.0168862919f,
     0.0120332201f,
     0.0080669426f,
     0.0050014815f,
     0.0027803639f,
     0.0012896313f,
     0.0003752429f,
    -0.0001370670f,
    -0.0004215772f,
    -0.0006340646f
};

void filterlp(void *config){

	// Static state holds past input samples between blocks
	static float history[FILTER_TAP_NUM] = {0};

	// Temp buffer to store the output
	float output[MAINBUFFER_SIZE];

	for (int i = 0; i < MAINBUFFER_SIZE; i++) {
		// Shift history buffer
		for (int j = FILTER_TAP_NUM - 1; j > 0; j--) {
			history[j] = history[j - 1];
		}
		history[0] = g_sound_buffer[i];

		// Convolve input with coefficients
		float acc = 0;
		for (int j = 0; j < FILTER_TAP_NUM; j++) {
			acc += fir_taps[j] * history[j];
		}

		output[i] = acc;
	}

	// Copy back into the global audio buffer
	for (int i = 0; i < MAINBUFFER_SIZE; i++) {
		g_sound_buffer[i] = output[i];
	}



}


