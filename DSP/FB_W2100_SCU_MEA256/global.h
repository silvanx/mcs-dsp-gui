#ifndef GLOBAL_H_
#define GLOBAL_H_

// #define USE_SIMULATOR
#define USE_MAILBOX_IRQ

#include <csl.h>

#include "Device_config.h"
#include "Stimulation.h"

#define I2C_BUFFER_SIZE 512

#define MONITOR_ARRAY   		64


#define STIMULUS_VECTOR_SIZE 	10
#define SENDDATA_PER_FRAME 		64

#define DOWNSAMPLE         	1
#define FRAMES_PER_LOOP    	1

extern int threshold;
extern int deadtime;

extern int StimAmplitude;
extern int StimDuration;
extern int StimRepeats;
extern int StimStepsize;

extern Uint32 StimulusEnable[HS1_CHANNELS / ELECTRODES_PER_REGISTER];
extern Uint32 elec_config[HS1_CHANNELS / ELECTRODES_PER_REGISTER];
extern Uint32 DAC_select[HS1_CHANNELS / (ELECTRODES_PER_REGISTER/2)];

#endif /*GLOBAL_H_*/
