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

int initFromMailbox(int mailboxRegister, int defaultValue)
{
    int value = READ_REGISTER(MAILBOX_BASE + mailboxRegister);

    if (!value)
    {
        return defaultValue;
    }
    else
    {
        return value;
    }
}

void main()
{
	volatile int i;

	MEA21_init();

	WRITE_REGISTER(IFB_AUX_DIR, 0x3);  // set AUX 1 and 2 as output

	MEA21_enableData();

	threshold = initFromMailbox(MAILBOX_THRSHOLD, 0);
	deadtime  = initFromMailbox(MAILBOX_DEADTIME, 0);

	StimAmplitude = initFromMailbox(MAILBOX_AMPLITUDE, 100);
	StimDuration  = initFromMailbox(MAILBOX_DURATION, 5);
	StimRepeats   = initFromMailbox(MAILBOX_REPEATS, 1);
	StimStepsize  = initFromMailbox(MAILBOX_STEPSIZE, 1);
	
	InitializeStgMemory();
	
	WRITE_REGISTER(IFB_AUX_OUT, 0x0); // set AUX 1 to value 0
	WRITE_REGISTER(IFB_AUX_OUT, 0x1); // set AUX 1 to value one

    UploadBiphaseRect(0, 0, StimAmplitude, StimDuration, StimRepeats);

// other segments not implemented yet
//  UploadBiphaseRect(0, 1, StimAmplitude, StimPeriod, StimRepeats);
		
	WRITE_REGISTER(IFB_AUX_OUT, 0x0); // set AUX 1 to value 0
	
	SetupTrigger();

	WRITE_REGISTER(DIGITAL_MUX, 0x42000200);   // Sideband data 0 HS 1 bit 0  to Digital Out bit 0

	while(1);
}


