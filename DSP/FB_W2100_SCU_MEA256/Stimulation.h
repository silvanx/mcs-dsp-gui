/*
 * Stimulation.h
 *
 *  Created on: 14.05.2018
 *      Author: jesinger
 */

#ifndef STIMULATION_H_
#define STIMULATION_H_

#define REGISTER_OFFSET 1
#define MEMPOINT_OFFSET (8 * REGISTER_OFFSET)

#define TIGGER_PER_HS           18
#define ELECTRODES_PER_REGISTER 32

#define TRIGGER_CTRL_HS1       0x0100
#define TRIGGER_SET_EVENT_HS1  0x0110
#define TRIGGER_ID_HS1         0x0140

#define STG_ELECTRODE_MODE   0x9c70       // 0x9120 on MEA2100
#define STG_ELECTRODE_ENABLE 0x9ca0       // 0x9158 on MEA2100
#define STG_ELECTRODE_MUX    0x9cd0       // 0x9160 on MEA2100
#define STG_TRIGGER_CONFIG   0x9600
#define STG_TRIGGER_REPEAT   0x9700       // 0x9190 on MEA2100

#define STG_MEMPOINT_CC_BASE 0x9200
#define STG_MEMPOINT_WP_BASE 0x9203   // write to this address clears the stg data
#define STG_DATA_MEMORY      0x9f80

void InitializeStgMemory();

void UploadBiphaseRect(int channel, int segment, int amplitude, int duration, int repeats);
void UploadSine(int channel, int segment, int amplitude, int period, int repeats, int threshold);

void SetSegment(int channel, int segment);
void ClearChannel(int channel, int segment);

void SetupTrigger();

void AddLoop(int channel, int vectors, int repeats);
int AddDataPoint(int channel, int duration, int value);

#endif /* STIMULATION_H_ */
