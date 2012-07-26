/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** ===========================================================================
 *   @file  Tsc_example.c
 *
 *   @path  $(CSLPATH)\example\tsc\src
 *
 *   @desc  Example of TSC CSL
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n The example shows how to use the TSC.
 *       1. Enables the counter.
 *       2. Waits for some time. 
 *       3. Reads the timer counter value
 *       4. Waits for some time. 
 *       5. Reads the timer counter value
 *       6. Compares the counter values to ensure the counter is incremented
 *       7. Displays the messages based on step 6
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Tsc_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* ============================================================================
 *  Revision History
 *  ===============
 *  27-Jul-2005 ds created
 *  14-Nov-2005 ds modified  - Removed Ctimer related APIs and Added TSC APIs
 *  16-Dec-2005 ds Updated documentation
 * ============================================================================
 */

#include <stdio.h>
#include <csl_tsc.h>

/* Macro that gives 1 CLK delay cycles */
#define WAIT_FOR_1_CLK  do {                               \
                            volatile int delayCnt = 1;      \
                            while(delayCnt > 0) --delayCnt; \
                           }while (0)       
                           
/* Forward declaration */
void tsc_example (void);

/* Globals */
Uint32      exampleFailed = 0;

/*
 * ============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine for the file.  
 *    
 * ============================================================================
 */
void main(void)
{   
    
    /* Invoke example */
    tsc_example ();
    
    if (exampleFailed > 0) {
        printf ("Time Stamp Counter Example Failed[Example Failed: %d]\n", \
                exampleFailed);
    }
    else {
        printf ("Time Stamp Counter Example Passed\n");
    }
   
    printf("==============================================================\n");
}

/*
 * =============================================================================
 *   @func  tsc_example
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *     It implements following steps
 *          1. Enables the counter.
 *          2. Waits for some time. 
 *          3. Reads the timer counter value
 *          4. Waits for some time. 
 *          5. Reads the timer counter value
 *          6. Compares the counter values to ensure the counter is incremented
 *          7. Print the result
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void tsc_example (void)
{
    CSL_Uint64          counterVal;
        
    printf("Running TSC CSL example\n");

    printf("Enable the Time Stamp Counter\n");
    
    /* Enable the TSC */
    CSL_tscEnable();
      
    /* Give small delay */
    WAIT_FOR_1_CLK;
    
    /* Read the counter value */  
    counterVal = CSL_tscRead();
   
    /* Give small delay */
    WAIT_FOR_1_CLK;
    
    /* Read the counter value */
    counterVal = CSL_tscRead();
    
    /* Verify the counter value incremented or not */
    if(counterVal > 0) {
        printf("Increment in the time stamp counter value\n");
        printf ("counterVal = 0x%lX\n", counterVal);
    }
    else {
        printf("Not increment in the  time stamp counter value\n");
        printf ("counterVal = 0x%lX\n", counterVal);
        exampleFailed++;
        return;
    }
    
    return;
}
