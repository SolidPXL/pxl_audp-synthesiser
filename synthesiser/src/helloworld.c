/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "oscilators/generators.h"
#include "globals.h"
#include "synth_lib.h"
#include "audio.h"
#include "effects/sound_effects.h"
#include "sleep.h"
#include <stdlib.h>
#include <xtime_l.h>
#include "xgpio.h"
#include "xscugic.h"
#include "xil_exception.h"

#define GPIO_DEVICE_ID			XPAR_AXI_GPIO_1_DEVICE_ID
#define INTR_ID					XPAR_FABRIC_AXI_GPIO_1_IP2INTC_IRPT_INTR
#define BTN_CHANNEL				1

#define GPIO_LEDS_DEVICE_ID     XPAR_AXI_GPIO_2_DEVICE_ID
#define LED_MASK                0x01
#define LED_CHANNEL				1

static XGpio    Gpio;   // GPIO driver instance
static XGpio 	Leds;	// LED driver instance
static XScuGic  Intc;   // Interrupt controller instance


volatile uint32_t active_fx = 0;


uint32_t g_sample_index = 0;
int32_t g_sound_buffer[MAINBUFFER_SIZE] = {0};
uint8_t g_keys_pressed[7]; //Allow a maximum of 7 notes to be played simultaneously

int32_t convert(uint32_t val) {
    return (int32_t)(val ^ 0x80000000); // flips the MSB
}


void ButtonISR(void *InstancePtr)
{
    XGpio_InterruptClear(&Gpio, 1);
    uint32_t btns = XGpio_DiscreteRead(&Gpio, BTN_CHANNEL) & 0xF;
    // For each button pressed, toggle the corresponding effect bit
    for (int i = 0; i < 4; i++) {
        uint32_t mask = (1u << i);
        if (btns & mask) {
            active_fx ^= mask;
        }
    }
}

int SetupInterruptSystem(XScuGic *IntcInstancePtr, XGpio *GpioInstancePtr)
{
    int status;
    XScuGic_Config *gic_cfg;

    // Look up the GIC configuration
    gic_cfg = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
    if (!gic_cfg) return XST_FAILURE;

    // Initialize the GIC driver
    status = XScuGic_CfgInitialize(IntcInstancePtr, gic_cfg, gic_cfg->CpuBaseAddress);
    if (status != XST_SUCCESS) return status;

    // Connect our ButtonISR to the GPIO interrupt ID
    status = XScuGic_Connect(IntcInstancePtr,
                             INTR_ID,
                             (Xil_ExceptionHandler)ButtonISR,
                             (void *)GpioInstancePtr);
    if (status != XST_SUCCESS) return status;

    // Enable the interrupt at the GIC
    XScuGic_Enable(IntcInstancePtr, INTR_ID);

    // Initialize the exception table and register the GIC handler
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
                                 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
                                 IntcInstancePtr);
    Xil_ExceptionEnable();

    // Initialize the GPIO driver
    status = XGpio_Initialize(GpioInstancePtr, GPIO_DEVICE_ID);
    if (status != XST_SUCCESS) return status;

    // Set channel directions: channel 1 = inputs, channel 2 = outputs
    XGpio_SetDataDirection(GpioInstancePtr, BTN_CHANNEL, 0xF);   // 4-bit input
    XGpio_SetDataDirection(GpioInstancePtr, LED_CHANNEL, 0x0);   // 4-bit output

    // Enable GPIO interrupts on channel 1 (buttons)
    XGpio_InterruptEnable(GpioInstancePtr, 1);
    XGpio_InterruptGlobalEnable(GpioInstancePtr);

    return XST_SUCCESS;
}

int main()
{
    init_platform();
	//Configure the IIC data structure
	IicConfig(XPAR_XIICPS_0_DEVICE_ID);

	//Configure the Audio Codec's PLL
	AudioPllConfig();

	//Configure the Line in and Line out ports.
	//Call LineInLineOutConfig() for a configuration that
	//enables the HP jack too.
	AudioConfigureJacks();
	LineinLineoutConfig();

	int status;
	    status = XGpio_Initialize(&Leds, GPIO_LEDS_DEVICE_ID);
	    if (status != XST_SUCCESS)  return XST_FAILURE;
	    XGpio_SetDataDirection(&Leds,
	                           LED_CHANNEL,
	                           ~LED_MASK);

		 // Hook up interrupts and GPIO
		status = SetupInterruptSystem(&Intc, &Gpio);
			if (status != XST_SUCCESS) {
				xil_printf("Interrupt setup failed %d\r\n", status);
		        return XST_FAILURE;
		    }

    print("Synthesiser\n\r");
    xil_printf("MAINBUFFER_SIZE: %d\n",MAINBUFFER_SIZE);
    xil_printf("BUFFER_TIME_MS: %d\n",BUFFER_TIME_MS);
    xil_printf("SAMPLE_INTERVAL_US: %d\n",SAMPLE_INTERVAL_US);
    xil_printf("SAMPLE_RATE_HZ: %d\n",SAMPLE_RATE_HZ);

    XTime time;
    XTime_GetTime(&time);
    srand(time);

    //Configure nodes, for each node create a generic_pipeline_node
//    struct sine_generator_config osc1_config = {
//    	.freq = note_to_freq_lut(A2),
//		.amp = 5000000,
//		.phasebuffer = {
//				.phase = 0,
//				.phase_inc = 0
//		}
//    };
//    struct generic_pipeline_node osc1_node = {
//    		.config = (void*)(&osc1_config),
//			.fnptr = sine_generator
//    };
//
//    struct saw_generator_config osc2_config = {
//		.freq = note_to_freq_lut(A2),
//		.amp = 5000000,
//		.phasebuffer = {
//				.phase = 0,
//				.phase_inc = 0
//		}
//	};
//	struct generic_pipeline_node osc2_node = {
//			.config = (void*)(&osc2_config),
//			.fnptr = saw_generator
//	};
//
//
//	struct square_generator_config osc3_config = {
//		.freq = note_to_freq_lut(A2),
//		.amp = 5000000,
//		.phasebuffer = {
//				.phase = 0,
//				.phase_inc = 0
//		}
//	};
//	struct generic_pipeline_node osc3_node = {
//			.config = (void*)(&osc3_config),
//			.fnptr = square_generator
//	};
//
//
//	struct triangle_generator_config osc4_config = {
//		.freq = note_to_freq_lut(A4),
//		.amp = 5000000,
//		.phasebuffer = {
//				.phase = 0,
//				.phase_inc = 0
//		}
//	};
//	struct generic_pipeline_node osc4_node = {
//			.config = (void*)(&osc4_config),
//			.fnptr = triangle_generator
//	};

	struct supersine_generator_config osc5_config = {
		.freq = note_to_freq_lut(A3),
		.amp = 7000000,
		.phasebuffers = NULL,
		.voices = 5,
		.voice_width = 8.0f
	};
	osc5_config.phasebuffers = (OscState*)malloc(osc5_config.voices*sizeof(OscState));
	for(int i=0;i<osc5_config.voices;i++){
		//read random noise
		uint32_t audin = Xil_In32(I2S_DATA_RX_L_REG);
		uint32_t random = rand();
		osc5_config.phasebuffers[i].phase = ((float)audin+random)/0xFFFFFFFF;
		osc5_config.phasebuffers[i].phase_inc = 0;
	}

	struct generic_pipeline_node osc5_node = {
			.config = (void*)(&osc5_config),
			.fnptr = supersine_generator
	};

	//===========================
    //			EFFECTS
	//===========================

    struct distortion_config dist_config = {
            .gain      = 5.0f,
            .threshold = 0.3f
    };
    struct generic_pipeline_node distortion_node = {
            .config = (void*)&dist_config,
            .fnptr  = distortion
    };

    struct delay_config delay_config = {
        .delay_samples = SAMPLE_RATE_HZ / 4,  // 250 ms delay
        .feedback      = 0.5f
    };
    struct generic_pipeline_node delay_node = {
        .config = (void*)&delay_config,
        .fnptr  = delay_effect
    };

    struct generic_pipeline_node fx_lp_node = {
		.config = NULL,
		.fnptr  = filterlp
	};

    struct gating_fx_config gate_config = {
		.delay_ms = 400
	};
	struct generic_pipeline_node gating_node = {
		.config = (void*)&gate_config,
		.fnptr  = fx_gate
	};



    //Synth pipeline
    struct generic_pipeline_node pipeline[5] ;  //Register the nodes here
    pipeline[0]	=	osc5_node;

    //const char *pipeline_names[] = { "Oscillator", "Distortion", "Delay", "Lowpass" };





    uint32_t k=0;

    while(1){
    	//  mirror buttons to LEDs
    	XGpio_DiscreteWrite(&Leds, LED_CHANNEL, active_fx);

     	if(k>= 0xFFFFFFFF){
    		k=0;
    	}
    	int note = k/500;
    	osc5_config.freq = note_to_freq_lut(note);

    	//zero buffer
    	for(int i=0;i<MAINBUFFER_SIZE;i++){
    		g_sound_buffer[i] = 0;
		}
		
    	//Build pipeline for this buffer: oscillator + any active effects
        int idx = 1;
        if (active_fx & 0x1) pipeline[idx++] = distortion_node;
        if (active_fx & 0x2) pipeline[idx++] = delay_node;
        if (active_fx & 0x4) pipeline[idx++] = gating_node;
        if (active_fx & 0x8) pipeline[idx++] = fx_lp_node;
        int pipeline_size = idx;

     	//Process pipeline
    	for(int i=0;i<pipeline_size;i++){
    		pipeline[i].fnptr(pipeline[i].config);
    	}

    	//Output result
    	for(int i=0;i<MAINBUFFER_SIZE;i++){
    		int32_t output = convert(g_sound_buffer[i]);
    		Xil_Out32(I2S_DATA_TX_L_REG, output);
    		Xil_Out32(I2S_DATA_TX_R_REG, output);
    		usleep_A9(SAMPLE_INTERVAL_US);
    	}

    	k++;

    }
    cleanup_platform();
    return 0;

}
