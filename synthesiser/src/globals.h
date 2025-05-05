#ifndef GLOBALS_H
#define GLOBALS_H

#define MAINBUFFER_SIZE 256
#define BUFFER_TIME_MS 50//One full buffer corresponds to how many milliseconds
#define SAMPLE_INTERVAL_US (BUFFER_TIME_MS*1000)/MAINBUFFER_SIZE//Calculated value based on size and time
#if SAMPLE_INTERVAL_US!=1000000
#define SAMPLE_RATE_HZ (1000000 / SAMPLE_INTERVAL_US) //Calculated value how many samples in 1 second
#else
#define SAMPLE_RATE_HZ 1
#endif

struct generic_pipeline_node{
	void* config;
	void (*fnptr)(void*);
};

#endif
