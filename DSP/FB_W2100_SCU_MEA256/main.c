#include <stdio.h>
#include <string.h>

#include <cslr_pllc.h>
#include <cslr_gpio.h>
#include <cslr_emifa.h>
#include <cslr_ddr2.h>
#include <cslr_dev.h>
#include <cslr_intc.h>
#include <cslr_chip.h>
#include <cslr_edma3cc.h>
#include <soc.h>

#include <c6x.h>

#include "main.h"
#include "version.h"

#include "Device_lib.h"

#include "Stimulation.h"

char dsp_version[] = "(>)"SW_STRING"(<)";


void main()
{
	static int value = 0;
	volatile int i;

	int StimAmplitude;
	int StimPeriod;
	int StimRepeats;
	int StimStepsize;

	MEA21_init();

	WRITE_REGISTER(IFB_AUX_DIR, 0x1);  // set AUX 1 as output

	MEA21_enableData();

	threshold = READ_REGISTER(0x1000);
	deadtime  = READ_REGISTER(0x1004);
	
	StimAmplitude = READ_REGISTER(0x1008);
	StimPeriod    = READ_REGISTER(0x100c);
	StimRepeats   = READ_REGISTER(0x1010);
	StimStepsize  = READ_REGISTER(0x1014);
	
	InitializeStgMemory();
	
	WRITE_REGISTER(IFB_AUX_OUT, 0x0); // set AUX 1 to value 0
	WRITE_REGISTER(IFB_AUX_OUT, 0x1); // set AUX 1 to value one

    UploadBiphaseRect(0, 0, 100, 5, StimRepeats);
//	UploadBiphaseRect(0, 0, StimAmplitude, StimPeriod, StimRepeats);
//	UploadSine(0, StimAmplitude, StimPeriod, StimRepeats, StimStepsize);

// other segments not implemented yet
//  UploadBiphaseRect(0, 1, StimAmplitude, StimPeriod, StimRepeats);
//	UploadSine(0, StimAmplitude/2, StimPeriod, StimRepeats, StimStepsize);
		
	WRITE_REGISTER(IFB_AUX_OUT, 0x0); // set AUX 1 to value 0
	
	SetupTrigger();

	while(1);
}


