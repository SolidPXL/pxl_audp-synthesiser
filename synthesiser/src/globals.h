#ifndef GLOBALS_H
#define GLOBALS_H

#define MAINBUFFER_SIZE 2048
#define BUFFER_TIME_MS 500//One full buffer corresponds to how many milliseconds
#define SAMPLE_INTERVAL_US (BUFFER_TIME_MS*1000)/MAINBUFFER_SIZE//Calculated value based on size and time

struct generic_pipeline_node{
	void* config;
	void (*fnptr)(void*);
};

#endif
