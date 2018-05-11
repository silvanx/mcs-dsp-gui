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

#include <math.h>

#include <c6x.h>

extern void intcVectorTable(void);  

#include "main.h"
#include "version.h"

#include "Device_lib.h"

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

	WRITE_REGISTER(0x318, 0x1);  // set AUX 1 as output

	MEA21_enableData();

	threshold = READ_REGISTER(0x1000);
	deadtime  = READ_REGISTER(0x1004);
	
	StimAmplitude = READ_REGISTER(0x1008);
	StimPeriod    = READ_REGISTER(0x100c);
	StimRepeats   = READ_REGISTER(0x1010);
	StimStepsize  = READ_REGISTER(0x1014);
	
//	WRITE_REGISTER(0x9200, 0x10000000; // Inititialze STG Memory, use only one segment
	WRITE_REGISTER(0x9200, 0x20000000); // Inititialze STG Memory, use 256 segments
#ifndef USE_SIMULATOR
	while (READ_REGISTER(0x9200) & 0x30000000); // wait for segment initialization to finish
#endif
	
	WRITE_REGISTER(0x0310, 0x0); // set AUX 1 to value 0
	WRITE_REGISTER(0x0310, 0x1); // set AUX 1 to value one

	SetSegment(0, 0); // select Segment 0 for DAC 1
	SetSegment(1, 0); // select Segment 0 for Sideband 1
	UploadSine(0, StimAmplitude, StimPeriod, StimRepeats, StimStepsize);
	SetSegment(0, 1); // select Segment 1 for DAC 1
	SetSegment(1, 1); // select Segment 0 for Sideband 1
	UploadSine(0, StimAmplitude/2, StimPeriod, StimRepeats, StimStepsize);
		
	WRITE_REGISTER(0x0310, 0x0); // set AUX 1 to value 0
	
	SetupTrigger();

	while(1)
	{
		WRITE_REGISTER(0x002C, 0x700 + 1*value);
		for (i = 0; i < 100000; i++);
		value = 1 - value; // switch on/off
	}
}

void UploadSine(int Channel, int Amplitude, int Period, int Repeats, int Stepsize)
{
	int yold = 0;
	int duration = 0;
	int datapoints = 0;
	volatile int i;
	int y;
	int vectors_used;
		
	vectors_used = 0;
	
	ClearChannel(Channel);
	for (i = 0; i < Period; i++)
	{
		y = Amplitude * sin((((double)i)/Period)*2*3.1415);
//		y = -(Amplitude *i)/Period;
		
		if (abs(y - yold) > Stepsize)
		{
			vectors_used += AddDataPoint(Channel, duration, yold+0x8000); 
			datapoints++;
			yold = y;
			duration = 1; // 20 us
		}
		else
		{
			duration++;
		}
	}
	vectors_used += AddDataPoint(Channel, duration, yold+0x8000);
	AddLoop(Channel, vectors_used, Repeats);
	
	// Create Sideband Information
	ClearChannel(Channel+1);
	vectors_used = 0;
	vectors_used += AddDataPoint(Channel+1, Period, 0x0019);
	AddLoop(Channel+1, vectors_used, Repeats);
//	AddDataPoint(Channel+1, 10, 0x0009); // keep Electrode connected to ground after stimulation
}

void AddLoop(int Channel, int Vectors, int Repeats)
{
	Uint32 ChannelReg;
	Uint32 LoopVector;

	ChannelReg = 0x9f20 + Channel*4;
	
	if (Repeats > 1)
	{
		LoopVector = 0x10000000 | (Repeats << 16) | Vectors;
		WRITE_REGISTER(ChannelReg, LoopVector);
	}
}

void SetSegment(int Channel, int Segment)
{
	Uint32 SegmentReg = 0x9200 + Channel*0x20;
	WRITE_REGISTER(SegmentReg, Segment);  // Any write to this register clears the Channeldata
}

void ClearChannel(int Channel)
{
	Uint32 ClearReg = 0x920c + Channel*0x20;
	WRITE_REGISTER(ClearReg, 0);  		// Any write to this register clears the Channeldata
}

int AddDataPoint(int Channel, int duration, int value)
{
	int vectors_used = 0;
	int	Vector;
	Uint32 ChannelReg = 0x9f20 + Channel*4;
	
	if (duration > 1000)
	{
		Vector = 0x04000000 | (((duration / 1000) - 1) << 16) | (value & 0xffff);	
		WRITE_REGISTER(ChannelReg, Vector);  // Write Datapoint to STG Memory
		duration %= 1000;
		vectors_used++;
	}
	
	if (duration > 0)
	{
		Vector = ((duration - 1) << 16) | (value & 0xffff);
		WRITE_REGISTER(ChannelReg, Vector);  // Write Datapoint to STG Memory
		vectors_used++;
	}

	return vectors_used;
}

void SetupTrigger()
{
	WRITE_REGISTER(0x0200, 0x1);  // Enable Trigger Packets
	WRITE_REGISTER(0x0204, 0x0);  // Setup Trigger
	WRITE_REGISTER(0x0208, 0x0);  // Setup Trigger

	WRITE_REGISTER(0x020c, 0x0);  // Setup Trigger
	WRITE_REGISTER(0x0210, 0x0);  // Setup Trigger

	WRITE_REGISTER(0x0218, 0x0);  // Setup Trigger
	WRITE_REGISTER(0x021c, 0x0);  // Setup Trigger
	WRITE_REGISTER(0x0220, 0x0);  // Setup Trigger
	WRITE_REGISTER(0x0224, 0x0);  // Setup Trigger
	WRITE_REGISTER(0x0228, 0x0);  // Setup Trigger
	WRITE_REGISTER(0x022c, 0x0);  // Setup Trigger

	WRITE_REGISTER(0x9190, 1); // Trigger 1 Repeat 
	WRITE_REGISTER(0x9194, 1); // Trigger 2 Repeat 
	WRITE_REGISTER(0x9198, 1); // Trigger 3 Repeat 

	WRITE_REGISTER(0x9104, 0x00020100); // DAC1 to Trigger1, DAC2 to Trigger2, DAC3 to Trigger3
	WRITE_REGISTER(0x9108, 0x00020100); // SBS1 to Trigger1, SBS2 to Trigger2, SBS3 to Trigger3
}

// Mask: Set to 1 for each bit which is to be modified
// Value: New Value for modified bits
void ModifyRegister(Uint32 reg, Uint32 Mask, Uint32 Value)
{
	Uint32 Temp;
	
	Temp = READ_REGISTER(reg);
	Temp &= ~Mask;
	Temp |= (Value & Mask);
	WRITE_REGISTER(reg, Temp);
}

