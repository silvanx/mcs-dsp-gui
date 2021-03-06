#include <csl_types.h>

#include "global.h"

#define MEA21_REGISTER(reg)          (*(volatile Uint32 *)(0xa0000000+reg))                   
#define READ_REGISTER(reg)           MEA21_REGISTER(reg)
#define WRITE_REGISTER(reg, value)   {MEA21_REGISTER(reg) = value; (*(volatile Uint32 *)(0x70000000)) = 0; (*(volatile Uint32 *)(0x70000000));}


#ifdef INCLUDE_HS1_DATA
#define HS1_CHANNELS    120
#define HS1_DATA_WORDS  (HS1_CHANNELS+2)
#define HS1_DATA_ENABLE 0x0200
#else
#define HS1_CHANNELS    0
#define HS1_DATA_WORDS  0
#define HS1_DATA_ENABLE 0
#endif

#ifdef INCLUDE_HS2_DATA
#define HS2_CHANNELS    120
#define HS2_DATA_WORDS  (HS2_CHANNELS+2)
#define HS2_DATA_ENABLE 0x0400
#else
#define HS2_CHANNELS    0
#define HS2_DATA_WORDS  0
#define HS2_DATA_ENABLE 0
#endif

#ifdef INCLUDE_IF_DATA
#define IF_CHANNELS     8
#define IF_DATA_WORDS   (IF_CHANNELS+1)
#define IF_DATA_ENABLE  0x0800
#else
#define IF_CHANNELS     0
#define IF_DATA_WORDS   0
#define IF_DATA_ENABLE  0
#endif

#ifdef INCLUDE_HS1_FILTER_DATA
#define HF1_CHANNELS    120
#define HF1_DATA_WORDS  (HF1_CHANNELS+2)
#define HF1_DATA_ENABLE 0x4000
#else
#define HF1_CHANNELS    0
#define HF1_DATA_WORDS  0
#define HF1_DATA_ENABLE 0
#endif

#ifdef INCLUDE_HS2_FILTER_DATA
#define HF2_CHANNELS    120
#define HF2_DATA_WORDS  (HF2_CHANNELS+2)
#define HF2_DATA_ENABLE 0x8000
#else
#define HF2_CHANNELS    0
#define HF2_DATA_WORDS  0
#define HF2_DATA_ENABLE 0
#endif

#ifdef INCLUDE_DIGITAL_DATA
#define DIGITAL_CHANNELS    31
#define DIGITAL_DATA_WORDS  (DIGITAL_CHANNELS+1)
#define DIGITAL_DATA_ENABLE 0x1000
#else
#define DIGITAL_CHANNELS    0
#define DIGITAL_DATA_WORDS  0
#define DIGITAL_DATA_ENABLE 0
#endif

#ifdef INCLUDE_TIMESTAMP_DATA
#define TIMESTAMP_CHANNELS    2
#define TIMESTAMP_DATA_WORDS  (TIMESTAMP_CHANNELS+1)
#define TIMESTAMP_DATA_ENABLE 0x2000
#else
#define TIMESTAMP_CHANNELS    0
#define TIMESTAMP_DATA_WORDS  0
#define TIMESTAMP_DATA_ENABLE 0
#endif


#define HS1_DATA_OFFSET     	(1)
#define HS2_DATA_OFFSET     	(HS1_DATA_OFFSET       + HS1_DATA_WORDS)
#define IF_DATA_OFFSET      	(HS2_DATA_OFFSET       + HS2_DATA_WORDS)
#define HF1_DATA_OFFSET			(IF_DATA_OFFSET        + IF_DATA_WORDS)
#define HF2_DATA_OFFSET			(HF1_DATA_OFFSET       + HF1_DATA_WORDS)
#define DIGITAL_DATA_OFFSET  	(HF2_DATA_OFFSET       + HF2_DATA_WORDS)
#define TIMESTAMP_DATA_OFFSET 	(DIGITAL_DATA_OFFSET   + DIGITAL_DATA_WORDS)

#define CHANNELS_PER_FRAME	 (HS1_DATA_WORDS+HS2_DATA_WORDS+IF_DATA_WORDS+HF1_DATA_WORDS+HF2_DATA_WORDS+DIGITAL_DATA_WORDS+TIMESTAMP_DATA_WORDS)
#define DSPINDATACTRL_VALUE	 (0x0100| HS1_DATA_ENABLE | HS2_DATA_ENABLE | IF_DATA_ENABLE | DIGITAL_DATA_ENABLE | TIMESTAMP_DATA_ENABLE | HF1_DATA_ENABLE | HF2_DATA_ENABLE )   // Enable IRQ and selected data streams

extern Uint32 MeaData[CHANNELS_PER_FRAME*FRAMES_PER_LOOP];
extern Uint32 MonitorData[MONITOR_ARRAY];

#define DSP_INDATA_CTRL   0x0400
#define DSP_OUTDATA_CTRL  0x0404
#define DSP_OUTDATA_THR   0x0414
#define FEEDBACK_REGISTER 0x0780
#define MAILBOX_CTRL      0x0424


void MEA21_init();

void SetMonitorSize(int datapoints);

