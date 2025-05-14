#include "sound_effects.h"

static float32_t* delay_buffer = NULL;
static uint32_t buffer_length = 0;
static uint32_t buffer_index  = 0;

void delay_effect(void* config) {
    struct delay_config* cfg = (struct delay_config*)config;
    if (buffer_length != cfg->delay_samples) {
        free(delay_buffer);
        buffer_length  = cfg->delay_samples;
        delay_buffer   = (float32_t*)malloc(buffer_length * sizeof(float32_t));
        for (uint32_t i = 0; i < buffer_length; i++) {
            delay_buffer[i] = 0.0f;
        }
        buffer_index = 0;
    }

    for (int i = 0; i < MAINBUFFER_SIZE; i++) {
        float32_t in      = (float32_t)g_sound_buffer[i] / (float32_t)INT32_MAX;
        float32_t delayed = delay_buffer[buffer_index];
        float32_t out     = in + delayed * cfg->feedback;
        delay_buffer[buffer_index] = in + delayed * cfg->feedback;
        buffer_index = (buffer_index + 1) % buffer_length;
        g_sound_buffer[i] = (int32_t)(out * (float32_t)INT32_MAX);
    }
}
