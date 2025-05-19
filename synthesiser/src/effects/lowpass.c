/*
 * lowpass.c
 *
 *  Created on: 14 mei 2025
 *      Author: 12300752
 */

#include "sound_effects.h"

void lowpass(void* config) {
    struct lowpass_config* cfg = (struct lowpass_config*)config;
    float32_t alpha = cfg->alpha;
    for (int i = 0; i < MAINBUFFER_SIZE; i++) {
        float32_t in = (float32_t)g_sound_buffer[i] / (float32_t)INT32_MAX;
        cfg->prev    = cfg->prev + alpha * (in - cfg->prev);
        g_sound_buffer[i] = (int32_t)(cfg->prev * (float32_t)INT32_MAX);
    }
}

