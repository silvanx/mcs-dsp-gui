#include "global.h"

Int32 adc_intern[HS1_CHANNELS + IF_CHANNELS];
#pragma DATA_ALIGN(adc_intern, 8);


int threshold;
int deadtime;

Uint32 StimulusEnable[2];
Uint32 DAC_select[4];
Uint32 elec_config[4];
