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
#define LOWPASS_LENGTH 4
#define BANDPASS_LENGTH 7
#define POWER_SEGMENT_LENGTH 50

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


void filter(double *b, double *a, int filterLength, double *xPrevious, double *yPrevious, double xCurrent)
{
	int i;
	if (filterLength <= 0)
		return;

	double b_acc = b[0] * xCurrent;
	double a_acc = 0;

	for (i = 1; i < filterLength; i++)
	{
		b_acc += b[i] * xPrevious[i - 1];
		a_acc += a[i] * yPrevious[i - 1];
	}

	double yCurrent = b_acc - a_acc;

	for (i = filterLength - 1; i > 0; i--)
	{
		xPrevious[i] = xPrevious[i - 1];
		yPrevious[i] = yPrevious[i - 1];
	}
	yPrevious[0] = yCurrent;
	xPrevious[0] = xCurrent;
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
            // update_waveform = 1;
        }
        break;

    case MAILBOX_REPEATS:
        if (StimRepeats != reg_value)
        {
            StimRepeats   = reg_value;
            // update_waveform = 1;
        }
        break;

    case MAILBOX_STEPSIZE:
        if (StimStepsize != reg_value)
        {
            StimStepsize  = reg_value;
            // update_waveform = 1;
        }
        break;

    case MAILBOX_PROPORTIONAL_GAIN:
        StimProportionalGain = reg_value;
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
	// Define sampling frequency and period
	const float f_s = 20000;
	const float T_s = 1 / f_s;

	// Define controller call period (23.08ms)
	const float T_controller = 0.02308;

	// Calculate T_controller to T_s ratio to know every how many calls of interrupt 6 we need to call the controller
	const int ratio_T_controller_T_s = T_controller * f_s;  //5 * 18 / 1000 * f_s;

	// Define SetPoint being the target beta ARV 
    const float SetPoint = threshold;                     //set SetPoint randomly to be 5mV ie 5000uV

    // Define array that remembers previous inputs and outputs for the sake of filtering
    static double xPrevious1[LOWPASS_LENGTH];
    static double yPrevious1[LOWPASS_LENGTH];
    static double xPrevious2[LOWPASS_LENGTH];
    static double yPrevious2[LOWPASS_LENGTH];
    static double xPrevious3[BANDPASS_LENGTH];
    static double yPrevious3[BANDPASS_LENGTH];
    static double unfiltered_beta_history[POWER_SEGMENT_LENGTH];
    static double filtered_beta_history[POWER_SEGMENT_LENGTH];
    
    static int history_index = 0;
    
    // Define a variable that is true just the first run
    static int first_run = 1; 

    // Define the upper and lower bounds for the controller output (i.e. DBS amplitude)
    const float MaxValue = StimAmplitude / 1000;                     //in uA
    const float MinValue = 0;                       //in uA

    // Define the step between pulses amplitude
    const float delta_DBS_amp = ( MaxValue - MinValue ) / 15;

    // Define vector to store the amplitude of the stimulation pulses
    static float pulse[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Define dummy variable
    static int c = 0;
    static int i = 0;

    // Multiply pulse vector by delta_DBS_amp to get the vector assoicated with the amplitude of the stimulation pulses
    if (first_run)
    {

        // These should be zero anyway, since the arrays are declared static but better safe than sorry
        for (i = 0; i < LOWPASS_LENGTH; i++) {
            yPrevious1[i] = 0;
            xPrevious1[i] = 0;
			yPrevious2[i] = 0;
			xPrevious2[i] = 0;
        }
		for (i = 0; i < BANDPASS_LENGTH; i++) {
			yPrevious3[i] = 0;
			xPrevious3[i] = 0;
		}
		for (i=0; i < POWER_SEGMENT_LENGTH; i++) {
		    filtered_beta_history[i] = 0;
		    unfiltered_beta_history[i] = 0;
		}


        // Not anymore the first run (thus, this if statement will be run only in the first call of interrupt6 function)
        first_run = 0;
	}

    // Define current error
    static float error = 0;

    // Define the applied bounded controller output value (i.e. applied pulse amplitude)
    static float OutputValue = 0;

    // Set increment initially to 0
    static float increment = 0.0;

    // Define index of stimulation pulse to be applied
    static int stim_index = 0;

    // Define difference between the amplitude of the required stimulation pulse and the one to be applied
    static float pulse_amp_diff = 0;

    // Define state value
    static double state_value = 0;
    static double xCurrent = 0;
    static double yCurrent1 = 0;
	static double decimated1 = 0;
	static double yCurrent2 = 0;
	static double decimated2 = 0;
	static double yCurrent3 = 0;
	static double filtered_state_value = 0;
	static int decimationCounter1 = 0;
	static int decimationCounter2 = 0;

	int power_estimate_length;
	double inf_norm;
	double beta_power;
	double total_power;
	static double relative_beta_power = 0;
    static float stimulation_output;
	
    
	// Define counter for function run
	static int timestamp = 0; // exists only in this function but is created only once on the first function call (i.e. static)
	static double timestamp_global;
	static int segment = 0;
	static int crossing_detected = 0;
	
	static int stg_electrode = 0;

	static int seg = 0;

	CSL_Edma3ccRegsOvly edma3ccRegs = (CSL_Edma3ccRegsOvly)CSL_EDMA3CC_0_REGS;
	
	// search start of data segments
	Int32  HS_data_header[NUM_SEGMENTS];
    // command information decoding
    // bits 31:28 Data Source/Group
    // bits 27:21 reserved for future use
    // bit 20:19 data format '00': 2x16 bit, '01': 1x32 bit, '10': 64 bit in 2 DWords
    // bit 18 '0': Analog data, '1': Digital data / don't alow data manipulation (no filter, no sign/unsign change)
    // bit 17 last Frame/Segment of sweep
    // bit 16 first Frame/Segment of sweep
#ifdef _W2100
    // bits 15:8 segment number / sub group
    // bits 7:0 length of this packet excluding token counter/CRC
#else
    // bits 15:9 segment number / sub group
    // bits 8:0 length of this packet excluding token counter/CRC
#endif

    // Data Source/Group decoding:
    // 0: Header
#ifdef _W2100
    // 1: Receiver 0 Data (up to 32 segments, each segment has up to 255 32-bit words)
    // 2: Receiver 1 Data (up to 32 segments, each segment has up to 255 32-bit words)
    // 3: IFB Analog Data
    // 4: DSP Data (up to 128 segments, each segment has up to 256 32-bit words)
    // 7: Digital Data
#else
    // 1,2,3,4: Extender Unit 0 Data (up to 4*16 segments, each segment has up to 511 32-bit words)
    // 5,6,7,8: Extender Unit 1 Data (up to 4*16 segments, each segment has up to 511 32-bit words)
    // 9: IFB Analog Data
    // A: Analog data
    // B: DAC data
    // C: DSP Data (up to 128 segments, each segment has up to 256 32-bit words)
    // D: Digital Data
#endif
    // E: reserved
    // F: Fooder/Tail

	Int32* restrict HS_Data_p[NUM_SEGMENTS];
	Int32* restrict IF_Data_p  = 0;
	int index = 0;
	for(i = 0;i < NUM_SEGMENTS;i++)
	{
		HS_data_header[i] = MeaData[index];
		HS_Data_p[i] = (Int32 *)&MeaData[index + 1];
#ifdef _W2100
		if ((HS_data_header[i] & 0xF0000000) == 0x30000000) // IF Analog
#else
		if ((HS_data_header[i]& 0xF0000000) == 0x90000000) // IF Analog
#endif
		{
			IF_Data_p =  (Int32 *)&MeaData[index + 1];
		}
        // debug
		// MonitorData[i] = MeaData[index];

#ifdef _W2100
		index += (HS_data_header[i] & 0xFF) + 1;
#else
		index += (HS_data_header[i] & 0x1FF) + 1;
#endif
	}

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
	///// WRITE_REGISTER(IFB_AUX_OUT, aux_value); // set  AUX 1 to value one

#ifndef _W2100
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
    // Calculate current beta ARV (differential recording)
    // xCurrent = abs(HS_Data_p[0][2] - HS_Data_p[0][0]); // NB: In uV
	// Calculate current beta ARV (single electrode for testing with signal generator)
	xCurrent = 0.25 * (HS_Data_p[0][0] + HS_Data_p[0][1] + HS_Data_p[0][2] + HS_Data_p[0][3]);
    
	// Hardcoded filter parameters
	// First downsampling (Butterworth, lowpass, cutoff 0.1 (normalized))
	double a1[LOWPASS_LENGTH] = { 1, -2.37409474370935, 1.92935566909122, -0.532075368312092 };
	double b1[LOWPASS_LENGTH] = { 0.00289819463372137, 0.00869458390116412, 0.00869458390116412, 0.00289819463372137 };
	int decimationFactor1 = 10;

	// Second downsampling (Butterworth, lowpass, cutoff 0.25 (normalized))
	double a2[LOWPASS_LENGTH] = { 1, -1.45902906222806, 0.910369000290069, -0.197825187264319 };
	double b2[LOWPASS_LENGTH] = { 0.0316893438497110, 0.0950680315491330, 0.0950680315491330, 0.0316893438497110 };
	int decimationFactor2 = 4;

	// Beta extraction (Butterworth, bandpass, 13-30 Hz, assuming 500 Hz sampling frequency)
	double a3[BANDPASS_LENGTH] = { 1, -5.40212898354275, 12.3252130462259, -15.1987442456715, 10.6838109529814, -4.05972313481503, 0.651760197122122 };
	double b3[BANDPASS_LENGTH] = { 0.000995173561555180, 0, -0.00298552068466554, 0, 0.00298552068466554, 0, -0.000995173561555180 };

	filter(b1, a1, LOWPASS_LENGTH, xPrevious1, yPrevious1, xCurrent);
	yCurrent1 = yPrevious1[0];
	if (decimationCounter1 % decimationFactor1 == 0)
	{
		decimated1 = yCurrent1;
		filter(b2, a2, LOWPASS_LENGTH, xPrevious2, yPrevious2, decimated1);
		yCurrent2 = yPrevious2[0];
		if (decimationCounter2 % decimationFactor2 == 0)
		{
		    decimated2 = yCurrent2;
			filter(b3, a3, BANDPASS_LENGTH, xPrevious3, yPrevious3, decimated2);
			yCurrent3 = yPrevious3[0];

			unfiltered_beta_history[history_index] = decimated2;
			filtered_beta_history[history_index] = yCurrent3;
			history_index = (history_index + 1) % POWER_SEGMENT_LENGTH;
		}
		decimationCounter2++;
	}
	decimationCounter1++;

    filtered_state_value = abs(yPrevious3[0]);

    inf_norm = 0;
	beta_power = 0;
	total_power = 0;
	power_estimate_length = POWER_SEGMENT_LENGTH;

	for (i = 0; i < POWER_SEGMENT_LENGTH; i++)
	{
		if (abs(filtered_beta_history[i]) > inf_norm)
		    inf_norm = abs(filtered_beta_history[i]);

		beta_power += (1.0 / power_estimate_length) * filtered_beta_history[i] * filtered_beta_history[i];
		total_power += (1.0 / power_estimate_length) * unfiltered_beta_history[i] * unfiltered_beta_history[i];
	}

	relative_beta_power = 1000.0 * beta_power / total_power;

	double magnitude = relative_beta_power;

	// If we're about to update the controller but we're currently stimulating, delay the controller update by 400 us
    // if (timestamp == ratio_T_controller_T_s - 1  && (HS_Data_p[1][0] & 1) * 1000) {
    //         timestamp = ratio_T_controller_T_s - (int) (0.0004 * f_s);
    // }

    // Increment timestamp each function call and call controller when T_controller elapsed i.e. when timestamp ==	ratio_T_controller_T_s
    if (++timestamp ==	ratio_T_controller_T_s)
    {
        for (c = 0; c < 16; c++)
        {
            pulse[c] = c * delta_DBS_amp;
        }
        // set AUX output to 1
        //aux_value |= 1;
	    //WRITE_REGISTER(IFB_AUX_OUT, aux_value); 
        
        // reset timestamp counter
        timestamp=0;
        
        // Relate the pulse index to the memory segment index assoicated with it 
        if (StimProportionalGain > 0)
        {
            if (threshold > 0)
            {
                error = (magnitude - threshold) / threshold;
            }
            else
            {
                error = magnitude;
            }
            stimulation_output = (StimProportionalGain / 1000) * error;

            if (stimulation_output > MaxValue)
            {
                OutputValue = MaxValue;
            }
            else if (stimulation_output < MinValue)
            {
                OutputValue = MinValue;
            }
            else
            {
                OutputValue = stimulation_output;
            }

            stim_index = 0;
            pulse_amp_diff = abs(pulse[0] - OutputValue);
            for (c = 1; c < 16; c++)
            {
                if (abs(pulse[c] - OutputValue) < pulse_amp_diff)
                {
                    stim_index = c;
                    pulse_amp_diff = abs(pulse[c] - OutputValue);
                }
            }
            seg = stim_index;

        }
        else
        {
            if (magnitude > threshold){
                seg = 15;
            }
            else {
                seg = 0;
            }
        }
        

        // Set AUX 1 output value to zero
        //aux_value &= 0;
	    //WRITE_REGISTER(IFB_AUX_OUT, aux_value);
     }

    if (seg == 0) {
        // Turn off stimulation if stim_index = 0
        WRITE_REGISTER(0x9A80, 0);
    }
    else {
        // Update stimulation pulse
        WRITE_REGISTER(0x9A80, 0x1000 * seg +  0x100); // Trigger Channel 1
    }

MonitorData[0] = threshold;
MonitorData[1] = yCurrent1;
MonitorData[2] = decimated1;
MonitorData[3] = yCurrent2;
MonitorData[4] = decimated2;
MonitorData[5] = yCurrent3;
MonitorData[6] = filtered_state_value;
MonitorData[7] = magnitude;
MonitorData[8] = beta_power;
MonitorData[9] = total_power;
MonitorData[10] = relative_beta_power;
MonitorData[11] = seg;
MonitorData[12] = MaxValue;
MonitorData[13] = StimProportionalGain;
MonitorData[14] = OutputValue;
MonitorData[15] = stimulation_output;
MonitorData[16] = delta_DBS_amp;
MonitorData[17] = pulse[0];
MonitorData[18] = pulse[5];
MonitorData[19] = pulse[10];
MonitorData[20] = pulse[15];
MonitorData[21] = pulse[15];

/*
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
*/

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

	//int f = HS_Data_p[0][0] > 0;
	//WRITE_REGISTER(0x0480, f); // Feedback
/*
	MonitorData[0] = (timestamp >> 4) & 0xFF;
	MonitorData[1] = HS_Data_p[0][4] + 80;
	MonitorData[2] = (IF_Data_p[0][0] - 1190000) >> 15;
	//MonitorData[3] = HS_Data_p[0][6] + 30;
	MonitorData[4] = HS_Data_p[0][0] >> 10;
	MonitorData[5] = HS_Data_p[0][8] + 30;
	MonitorData[6] = HS_Data_p[0][9] + 30;
*/
	for(i = 0; i < 64; i++)
	{
		//MonitorData[i] = HS_Data_p[0][i];
	}
	for(i = 32; i < 64; i++)
	{
		//MonitorData[i] = IF_Data_p[0][i];
	}

    CSL_FINST(edma3ccRegs->ESRH, EDMA3CC_ESRH_E53, SET);    // Manual Trigger Event 53

	aux_value &= ~1;
	////// WRITE_REGISTER(IFB_AUX_OUT, aux_value); // set AUX 1 to value zero
}


