#include "global.h"

int threshold;
int deadtime;

int StimAmplitude;
int StimDuration;
int StimRepeats;
int StimStepsize;

Uint32 StimulusEnable[HS1_CHANNELS / ELECTRODES_PER_REGISTER];
Uint32 elec_config[HS1_CHANNELS / ELECTRODES_PER_REGISTER];
Uint32 DAC_select[HS1_CHANNELS / (ELECTRODES_PER_REGISTER/2)];
