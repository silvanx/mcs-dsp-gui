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

int num_tr_cross[HS1_CHANNELS/2];
int last_tr_cross[HS1_CHANNELS/2];

Uint32 reg_written;
Uint32 reg_value;

#define DATA_HEADER_SIZE 1

void toggleLED()
{
    static int led = 0;
    CSL_GpioRegsOvly gpioRegs = (CSL_GpioRegsOvly)CSL_GPIO_0_REGS;

    CSL_FINS(gpioRegs->OUT_DATA, GPIO_OUT_DATA_OUT2, led); // LED
    led = 1 - led;
}

// Mailbox write interrupt
// use "#define USE_MAILBOX_IRQ" in global.h to enable this interrupt
interrupt void interrupt8(void)
{
	reg_written = READ_REGISTER(0x428);
	reg_value   = READ_REGISTER(0x1000 + reg_written);

	threshold = READ_REGISTER(0x1000);
	deadtime  = READ_REGISTER(0x1004);

	// a write to a mailbox register occurred
}


// DMA finished Interrupt
interrupt void interrupt6(void)
{
	static int timestamp = 0; // exists only in this function but is created only once on the first function call (i.e. static)
	static int segment = 0;
	
	int i;
	CSL_Edma3ccRegsOvly edma3ccRegs = (CSL_Edma3ccRegsOvly)CSL_EDMA3CC_0_REGS;
	
	Int32* restrict adc_i_p = &adc_intern[0]; // we create here a pointer for compiler optimization reasons
	Int32* restrict HS1_Data_p = (Int32 *)&MeaData[DATA_HEADER_SIZE];
//	Int32* restrict IF_Data_p  = (Int32 *)&MeaData[DATA_HEADER_SIZE+HS1_CHANNELS+DATA_HEADER_SIZE];

	// Prepare DMA for next data transfer DO NOT CHANGE THE FOLLOWING LINE
	CSL_FINST(edma3ccRegs->ICRH, EDMA3CC_ICRH_I52, CLEAR);	// Clear pending interrupt for event 52
    // 
    
	// Write to AUX register to see how long interrupt takes (set output to high, at the end set output to low)
	WRITE_REGISTER(0x0310, 0x1); // set AUX 1 to value one

#if 1
	// inititial setup      
    if (timestamp == 0) {
    	
    	timestamp = 0;
    	for (i = 0; i < HS1_CHANNELS/2; i++)
		{
			num_tr_cross[i]=0;
			last_tr_cross[i]=-deadtime;
		}
    	
    } 



    
    // collect data
    else if (timestamp < 5000)
    {
		for (i = 0; i < HS1_CHANNELS/2; i++)
		{
			*adc_i_p++ = *HS1_Data_p++;
		}
	
		for (i = 0; i < HS1_CHANNELS/2; i++)
		{
			if(adc_intern[i] < threshold && ((timestamp-last_tr_cross[i]) > deadtime) )
			{
				num_tr_cross[i]++;
				last_tr_cross[i] = timestamp;	
			}
		}
    }
	// analyze, might take longer
    else if (timestamp == 5000) 
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
    		if (num_tr_cross[i] > 0) 
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

		WRITE_REGISTER(TRIGGER_ID_HS1,        segment << 16);  // select segment for trigger 1
		WRITE_REGISTER(TRIGGER_SET_EVENT_HS1, 0x00010001);     // Start Trigger 1
		segment = 1 - segment; // alternate between segment 0 and 1
       	
    	// analyze data
    	// configure stim signal
    }

    // Wait for stimulation to finish
    else if (timestamp < 100000) 
    {    	
    	// analyze data
    	// configure stim signal
    }
    else
    {
    	// write result to mailbox

    	
//    	timestamp = -1;
    }
 
    if (timestamp == 0) 
    {
		WRITE_REGISTER(0x002C, 0x404); //switch on HS2 LED
    }
	else if (timestamp == 50000) 
	{
		WRITE_REGISTER(0x002C, 0x400); //switch off HS2 LED
    }
#endif
 
    
    //MonitorData[0] = timestamp;
    if ((int)MeaData[1 + 0] > (int)threshold)
    {
    	MonitorData[0] = MeaData[DATA_HEADER_SIZE + 0];
        WRITE_REGISTER(FEEDBACK_REGISTER, 1);
    }
    else
    {
        MonitorData[0] = 0; //timestamp;
        WRITE_REGISTER(FEEDBACK_REGISTER, 0);
    }
    MonitorData[1] = MeaData[DATA_HEADER_SIZE + 0];
    CSL_FINST(edma3ccRegs->ESRH, EDMA3CC_ESRH_E53, SET);  // Trigger DMA event 53
    	
	
	/*for (i = 0; i < HS2_CHANNELS; i++)
	{
		*adc_i_p++ = *HS2_Data_p++;
	}
	*/
	/*for (i = 0; i < IF_CHANNELS; i++)
	{
		*adc_i_p++ = *IF_Data_p++;
	}*/

   
	WRITE_REGISTER(0x0310, 0x0); // set AUX 1 to value zero

   
    // loop through electrode
        // check for threshold crossing if passed deadtime (compare to timestamp that indicates last detected spike)
        // if yes then add 1 to rate counter and save timestamp
        
        // check static counter if 1 second in samples reached
        
        // decide which electrodes to stimulate
        
        // write stimulation to DACs
        
        
        // MONITOR EXECUTION TIME WITH DIGITAL PULSE`

    timestamp++;
	if (timestamp == 50000)
	{
	    timestamp = 0;
	    toggleLED();
	}
}


