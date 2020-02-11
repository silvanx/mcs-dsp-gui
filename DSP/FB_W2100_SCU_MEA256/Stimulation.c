/*
 * Stimulation.c
 *
 *  Created on: 14.05.2018
 *      Author: jesinger
 */

#include "Device_lib.h"

#include "Stimulation.h"

#include <math.h>

void UploadBiphaseRect(int channel, int segment, int amplitude, int duration, int repeats)
{
    int vectors_used;

    vectors_used = 0;
    ClearChannel(channel, segment);
    vectors_used += AddDataPoint(channel, duration, 0x8000 + amplitude);
    vectors_used += AddDataPoint(channel, duration, 0x8000 - amplitude);
    AddLoop(channel, vectors_used, repeats);

    vectors_used = 0;
    ClearChannel(channel+1, segment);
    vectors_used += AddDataPoint(channel+1, duration, 0x0119); // bit 1,3,4 and 8
    vectors_used += AddDataPoint(channel+1, duration, 0x0019); // bit 1,3,4
    AddLoop(channel+1, vectors_used, repeats);
}

void UploadSine(int channel, int segment, int amplitude, int period, int repeats, int stepsize)
{
    int yold = 0;
    int duration = 0;
    int datapoints = 0;
    volatile int i;
    int y;
    int vectors_used;

    vectors_used = 0;

    ClearChannel(channel, segment);
    for (i = 0; i < period; i++)
    {
        y = amplitude * sin((((double)i)/period)*2*3.1415);
//      y = -(Amplitude *i)/Period;

        if (abs(y - yold) > stepsize)
        {
            vectors_used += AddDataPoint(channel, duration, yold+0x8000);
            datapoints++;
            yold = y;
            duration = 1; // 20 us
        }
        else
        {
            duration++;
        }
    }
    vectors_used += AddDataPoint(channel, duration, yold+0x8000);
    AddLoop(channel, vectors_used, repeats);

    // Create Sideband Information
    ClearChannel(channel+1, segment);
    vectors_used = 0;
    vectors_used += AddDataPoint(channel+1, period, 0x0019);
    AddLoop(channel+1, vectors_used, repeats);
//  AddDataPoint(Channel+1, 10, 0x0009); // keep Electrode connected to ground after stimulation
}

void AddLoop(int channel, int vectors, int repeats)
{
    Uint32 ChannelReg = STG_DATA_MEMORY + channel * REGISTER_OFFSET;
    Uint32 LoopVector;

    if (repeats > 1)
    {
        LoopVector = 0x10000000 | (repeats << 16) | vectors;
        WRITE_REGISTER(ChannelReg, LoopVector);
    }
}

void SetSegment(int channel, int segment)
{
    Uint32 SegmentReg = STG_MEMPOINT_CC_BASE + (channel * MEMPOINT_OFFSET);
    WRITE_REGISTER(SegmentReg, segment);
}

void ClearChannel(int channel, int segment)
{
    Uint32 ClearReg = STG_MEMPOINT_WP_BASE + (channel * MEMPOINT_OFFSET);
//  SetSegment(channel, segment);
    WRITE_REGISTER(ClearReg, 0);        // Any write to this register clears the channeldata
}

int AddDataPoint(int channel, int duration, int value)
{
    int vectors_used = 0;
    int Vector;
    Uint32 ChannelReg = STG_DATA_MEMORY + channel * REGISTER_OFFSET;

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
    int i;

    WRITE_REGISTER(TRIGGER_CTRL_HS1, 0x1);  // Enable Trigger Packets

    for (i = 0; i < TIGGER_PER_HS; i++)
    {
        WRITE_REGISTER(TRIGGER_ID_HS1+i, 0x0);    // Setup Trigger
        WRITE_REGISTER(STG_TRIGGER_CONFIG+i, (4 << 1) | 1);
        WRITE_REGISTER(STG_TRIGGER_REPEAT+i, 1);  // Trigger Repeat: only once
    }

//    WRITE_REGISTER(0x9104, 0x00020100); // DAC1 to Trigger1, DAC2 to Trigger2, DAC3 to Trigger3
//    WRITE_REGISTER(0x9108, 0x00020100); // SBS1 to Trigger1, SBS2 to Trigger2, SBS3 to Trigger3
}
