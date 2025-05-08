#ifndef GLOBALS_H
#define GLOBALS_H

#define MAINBUFFER_SIZE 256
#define BUFFER_TIME_MS 3//One full buffer corresponds to how many milliseconds
#define SAMPLE_INTERVAL_US (BUFFER_TIME_MS*1000)/MAINBUFFER_SIZE//Calculated value based on size and time
#define SAMPLE_RATE_HZ ((MAINBUFFER_SIZE * 1000) / BUFFER_TIME_MS)

struct generic_pipeline_node{
	void* config;
	void (*fnptr)(void*);
};

#endif
