#include "sound_effects.h"

void distortion(void* config) {
    struct distortion_config* cfg = (struct distortion_config*)config;
    float32_t gain      = cfg->gain;
    float32_t threshold = cfg->threshold;

    for (int i = 0; i < MAINBUFFER_SIZE; i++) {
        float32_t in = (float32_t)g_sound_buffer[i] / (float32_t)INT32_MAX;
        in *= gain;
        // hard clip
        if (in > threshold)      in = threshold;
        else if (in < -threshold) in = -threshold;
        g_sound_buffer[i] = (int32_t)(in * (float32_t)INT32_MAX);
    }
}
