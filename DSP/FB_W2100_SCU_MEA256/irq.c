#include <csl.h>
#include <cslr_tmr.h>
#include <cslr_gpio.h>
#include <cslr_chip.h>
#include <cslr_edma3cc.h>
#include <soc.h>
#include <c6x.h>

#include "main.h"
#include "irq.h"
#include "Device_lib.h"
#include "Common/MCS_USB_commands.h"

int num_tr_cross[HS1_CHANNELS/2];
int last_tr_cross[HS1_CHANNELS/2];

Uint32 aux_value = 0;

#define DATA_HEADER_SIZE 1

void toggleLED()
{
    static int led = 0;
    CSL_GpioRegsOvly gpioRegs = (CSL_GpioRegsOvly)CSL_GPIO_0_REGS;

    CSL_FINS(gpioRegs->OUT_DATA, GPIO_OUT_DATA_OUT2, led); // LED
    led = 1 - led;
}


void W2100Usb(Uint32 direction, Uint32 request, Uint32 value, Uint32 index, Uint32 data, Uint32 length)
{
	Uint32 setup0 = direction + (request << 8) + (value << 16);
	Uint32 setup1 = index + (length << 16);
	WRITE_REGISTER(0x0c10, setup0);
	WRITE_REGISTER(0x0c11, setup1);
	WRITE_REGISTER(0x0c12, data);
	WRITE_REGISTER(0x0c13, 0);
	Uint32 ready = 0;
	Uint32 repeat = 50000; // 2.5s
	while (!ready && repeat > 0)
	{
		repeat--;
		ready = READ_REGISTER(0x0c13);
	}
}

// Mailbox write interrupt
// use "#define USE_MAILBOX_IRQ" in global.h to enable this interrupt
interrupt void interrupt8(void)
{
    int update_waveform = 0;
    Uint32 reg_written;
    Uint32 reg_value;

    // a write to a mailbox register occurred
	reg_written = READ_REGISTER(MAILBOX_LASTWRITTEN);
	reg_value   = READ_REGISTER(MAILBOX_BASE + reg_written);

	switch(reg_written)
	{
	case MAILBOX_THRSHOLD:
	    threshold = reg_value;
	    break;

	case MAILBOX_DEADTIME:
	    deadtime = reg_value;
	    break;

    case MAILBOX_AMPLITUDE:
        if (StimAmplitude != reg_value)
        {
            StimAmplitude = reg_value;
            update_waveform = 1;
        }
        break;

    case MAILBOX_DURATION:
        if (StimDuration != reg_value)
        {
            StimDuration    = reg_value;
            update_waveform = 1;
        }
        break;

    case MAILBOX_REPEATS:
        if (StimRepeats != reg_value)
        {
            StimRepeats   = reg_value;
            update_waveform = 1;
        }
        break;

    case MAILBOX_STEPSIZE:
        if (StimStepsize != reg_value)
        {
            StimStepsize  = reg_value;
            update_waveform = 1;
        }
        break;
	}

	if (update_waveform)
	{
	    UploadBiphaseRect(0, 0, StimAmplitude, StimDuration, StimRepeats);
	}
}


// DMA finished Interrupt
interrupt void interrupt6(void)
{
	static int timestamp = 0; // exists only in this function but is created only once on the first function call (i.e. static)
	static int segment = 0;
	static int crossing_detected = 0;
	
	static int stg_electrode = 0;

	static int seg = 0;

	int i;
	CSL_Edma3ccRegsOvly edma3ccRegs = (CSL_Edma3ccRegsOvly)CSL_EDMA3CC_0_REGS;
	
	Int32* restrict HS1_Data_p = (Int32 *)&MeaData[DATA_HEADER_SIZE];
	Int32* restrict IF_Data_p  = (Int32 *)&MeaData[DATA_HEADER_SIZE+HS1_CHANNELS+DATA_HEADER_SIZE];

	// Prepare DMA for next data transfer DO NOT CHANGE THE FOLLOWING LINE
	CSL_FINST(edma3ccRegs->ICRH, EDMA3CC_ICRH_I52, CLEAR);	// Clear pending interrupt for event 52
    // 
    
	// Write to AUX register to see how long interrupt takes (set output to high, at the end set output to low)

	//if (timestamp == 9999)
	{
		aux_value |= 1;
	}
	//else
	{
	//	aux_value &= ~1;
	}
	WRITE_REGISTER(IFB_AUX_OUT, aux_value); // set  AUX 1 to value one

#if 0
	// Monitor Analog in
    if (IF_Data_p[0] > threshold)
    {
        aux_value |= 2;
        WRITE_REGISTER(0x002C, 0x404); //switch on HS2 LED

        if (crossing_detected == 0)
        {
            crossing_detected = 1;
            WRITE_REGISTER(TRIGGER_ID_HS1,        segment << 16);  // select segment for trigger 1
            WRITE_REGISTER(TRIGGER_SET_EVENT_HS1, 0x01);     // Start Trigger 1
        }
    }
    else
    {
        crossing_detected = 0;
        aux_value &= ~2;
        WRITE_REGISTER(0x002C, 0x400); //switch on HS2 LED
    }

    // once per second
    if (timestamp == 49999)
    {    	
    	int enable;
    	int mux;
    	int config;
    	int iMeanActivity = 0;
    	for (i = 0; i < HS1_CHANNELS; i++)
    	{
    		iMeanActivity = iMeanActivity + num_tr_cross[i];
    	}
    	iMeanActivity = iMeanActivity /(HS1_CHANNELS);

    	for (i = 0; i < HS1_CHANNELS / ELECTRODES_PER_REGISTER; i++)
    	{
    	    StimulusEnable[i] = 0;
            elec_config[i] = 0;
    	}

        for (i = 0; i < HS1_CHANNELS / (ELECTRODES_PER_REGISTER/2); i++)
        {
            DAC_select[i] = 0;
        }

        for (i = 0; i < HS1_CHANNELS; i++)
    	{
    		// if (num_tr_cross[i] <= iMeanActivity) {
    		// if (num_tr_cross[i] > 0)
            if (i == stg_electrode)
			{
    			enable = 1;
    			mux = 1; // Stimulation Source is DAC 1
    			config = 0; // Use Sidestream 1 for Stimulation Switch
    		}
    		else
    		{
    			enable = 0;
    			mux = 0; // Keep MUX at ground
    			config = 1; // Keep Switches static, manual mode
    		}
    		
    		// 1 bit per channel
    		StimulusEnable[i/ELECTRODES_PER_REGISTER] |= (enable << (i % ELECTRODES_PER_REGISTER));
            elec_config[i/ELECTRODES_PER_REGISTER]    |= (config << (i % ELECTRODES_PER_REGISTER));

            // 2 bit per channel
            DAC_select[i/(ELECTRODES_PER_REGISTER/2)] |= (mux << 2 * (i % (ELECTRODES_PER_REGISTER/2)));
       	}
       	
       	for (i = 0; i < HS1_CHANNELS / ELECTRODES_PER_REGISTER; i++)
       	{
       		WRITE_REGISTER(STG_ELECTRODE_ENABLE + i*REGISTER_OFFSET, StimulusEnable[i]); // Enable Stimulation on STG
//			WRITE_REGISTER(0x8140+i*REGISTER_OFFSET, StimulusEnable[i]); // Enable hard blanking for Stimulation Electrodes
            WRITE_REGISTER(STG_ELECTRODE_MODE + (i*REGISTER_OFFSET), elec_config[i]); // Configure Stimulation Electrodes to Listen to Sideband 1
       	}

       	for (i = 0; i < HS1_CHANNELS / (ELECTRODES_PER_REGISTER/2); i++)
       	{
       		WRITE_REGISTER(STG_ELECTRODE_MUX + (i*REGISTER_OFFSET), DAC_select[i]);  // Select DAC 1 for Stimulation Electrodes
       	}

//		WRITE_REGISTER(TRIGGER_ID_HS1,        segment << 16);  // select segment for trigger 1
//		WRITE_REGISTER(TRIGGER_SET_EVENT_HS1, 0x01);     // Start Trigger 1
//		segment = 1 - segment; // alternate between segment 0 and 1
       	
    	// analyze data
    	// configure stim signal
    }


	if (++timestamp == 50000)
	{
	    timestamp = 0;
	    toggleLED();

	    if (stg_electrode < 256)
	    {
	        stg_electrode++;
        }
	    else
	    {
	        stg_electrode = 0;
	    }

	}
#else
#if 1
#define PERIOD 200
	int nextsegment[16] =
	{
			0, 1, 2, 3,
			2, 1, 0, 2,
			4, 8, 7, 6,
			5, 4, 3, 2,
	};
	static int j = 0;
	if (timestamp == PERIOD - 50)
	{
		WRITE_REGISTER(0x9A80, 0x1000 * nextsegment[j] +  0x100); // Trigger Channel 1
		j++;
	}

	if (timestamp > 0 && timestamp < PERIOD * 16 - 100)
	{
		if (timestamp % PERIOD == 0)
		{
			WRITE_REGISTER(0x9A80, 0x1000 * nextsegment[j] +  0x100); // Trigger Channel 1
			j++;
		}
	}

	if (timestamp == PERIOD * 16 + 50)
	{
		WRITE_REGISTER(0x9A80, 0); // Stop Trigger
	}
	++timestamp;
#else
	if (timestamp == 5000)
	{
	    //WRITE_REGISTER(0x0480, 0); // Feedback
	}
	aux_value &= ~2;
	MonitorData[3] = 0;
	if (++timestamp == 20000)
	{
		timestamp = 0;
	    toggleLED();

	    //WRITE_REGISTER(0x0480, 1); // Feedback
	    seg++;
	    if (seg >= 16)
	    {
	    	seg = 0;
	    }
	    WRITE_REGISTER(0x9A80, 0x1000 * seg +  0x100); // Trigger Channel 1
	    aux_value |= 2;
	    MonitorData[3] = 5;
	}
#endif
#endif

	//int f = HS1_Data_p[0] > 0;
	//WRITE_REGISTER(0x0480, f); // Feedback

	MonitorData[0] = (timestamp >> 4) & 0xFF;
	MonitorData[1] = HS1_Data_p[4] + 80;
	MonitorData[2] = (IF_Data_p[0] - 1190000) >> 15;
	//MonitorData[3] = HS1_Data_p[6] + 30;
	MonitorData[4] = HS1_Data_p[0] >> 10;
	MonitorData[5] = HS1_Data_p[8] + 30;
	MonitorData[6] = HS1_Data_p[9] + 30;

	for(i = 0; i < 64; i++)
	{
		//MonitorData[i] = HS1_Data_p[i];
	}
	for(i = 32; i < 64; i++)
	{
		//MonitorData[i] = IF_Data_p[i];
	}

    CSL_FINST(edma3ccRegs->ESRH, EDMA3CC_ESRH_E53, SET);    // Manual Trigger Event 53

	aux_value &= ~1;
	WRITE_REGISTER(IFB_AUX_OUT, aux_value); // set AUX 1 to value zero
}


