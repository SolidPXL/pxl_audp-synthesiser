#include "generators.h"



int32_t isquare_func(float phase, float amp){
	float val = (phase < 0.5f ? 1.0f : -1.0f) * amp;
	return (int32_t)(val);
}

float fsquare_func(float phase) {
    return phase < 0.5f ? 1.0f : -1.0f;
}

int32_t isawd_func(float phase, float amp){
	float val = (2.0f * (phase - 0.5f)) * amp;  // range: [-1, 1)
	return (int32_t)(val * 2147483647.0f);
}

float fsawd_func(float phase){
	return -phase;
}

int32_t isawa_func(float phase, float amp){
	float val = (2.0f * (-phase - 0.5f)) * amp;  // range: [-1, 1)
	return (int32_t)(val * 2147483647.0f);
}

float fsawa_func(float phase){
	return phase;
}


int32_t itriangle_func(float phase, float amp){
	//Not implemented
	return 0;
}

float ftriangle_func(float phase){
	float val = 0;
	if(phase<0){
		val = (2.0f*fabsf(phase+0.5f)-1.0f);
	} else {
		val = (-2.0f*fabsf(phase-0.5f)+1.0f);
	}
	return val;
//	return phase<0 ? (2.0f*abs(phase+0.5f)-1.0f) : (-2.0f*abs(phase-0.5f)+1.0f);
}
