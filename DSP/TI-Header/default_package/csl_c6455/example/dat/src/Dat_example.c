/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  DAT_example.c
 *
 *   @path  $(CSLPATH)\example\dat\src
 *
 *   @desc  Example of DAT
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *
 *  1D transfer mode:
 *          - Opens the dat module.
 *          - Copies a linear block of data from src to dst.  
 *          - Waits for a previous transfer to complete.
 *          - Does the data comparision to ensure the copied data is proper or 
 *            not and 
 *          - Fills a linear block of memory with the specified fillVal
 *            using EDMA.
 *          - Does the data comparision to ensure the filled data is proper or 
 *            not and 
 *          - Displays the message based on previous step
 *
 *  2D transfer mode:
 *          - Opens the dat module.
 *          - Initializes the source and destination buffer with data
 *          - Performs a 2-dimensional data copy (2D2D) using EDMA
 *          - Waits for a previous transfer to complete.
 *          - Does the data comparision to ensure the copied data is proper or 
 *            not and
 *          - Performs a 2-dimensional data copy (2D1D) using EDMA
 *          - Waits for a previous transfer to complete.
 *          - Does the data comparision to ensure the copied data is proper or 
 *            not and
 *          - Displays the message based on previous step
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Dat_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* ============================================================================
 *  Revision History
 *  ===============
 *  16-Dec-2005 ds  Updated documentation 
 * ============================================================================
 */
 
#include <stdio.h>
#include <csl_dat.h>

/*  Global Setup, Data */
#define DAT_CSL_EXA_OK    1 
#define NUMBER_OF_ROW     8 
#define NUM_OF_BYTES      256
#define ARRAY_INDEX       16 
#define FILL_VALUE        0x55555555
#define LINE_PITCH        20

/* Function forwards */
Int dat_1dXfer(void);
Int dat_2dXfer(void);

/* global buffers used during transfer */ 
Uint8 src[NUM_OF_BYTES];
Uint8 dst[NUM_OF_BYTES];
Uint8 dst1d[NUM_OF_BYTES];
Uint8 src1d[NUM_OF_BYTES];
Uint8 src2d[NUMBER_OF_ROW][LINE_PITCH];
Uint8 dst2d[NUMBER_OF_ROW][LINE_PITCH];

/* Variable to verify example status */
Int pass = 1;

/*
 *  ============================================================================
 *   @func   main
 *
 *   @desc
 *      main function to call dat function
 *  ============================================================================
*/
void main(void)
{
    if (dat_1dXfer() && pass) {
        printf("<< EXAMPLE PASSED >>: Dat 1D DAT Example Passed \n");
    
    }
    else {
        printf("<< EXAMPLE FAILED >>: Dat 1D DAT Example Failed \n");
        
    }
    
    if (dat_2dXfer() && pass) {
        printf("<< EXAMPLE PASSED >>: Dat 2D DAT Example Passed \n");
    
    }
    else {
        printf("<< EXAMPLE FAILED >>: Dat 2D DAT Example Failed \n");

    }
}

/*
 * =============================================================================
 *   @func  dat_1dXfer
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      The example function shows the usage of dat CSL APIs. This function  
 *      demonstrates the usage of CSL APIs in configuring the dat 1D transfer 
 *      mode.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */

Int dat_1dXfer(void)
{          
    Int         loopIdx;   
    Int         id;
    Uint32      fillVal;
    DAT_Setup   datSetup;

    /* dat setup */
    datSetup.qchNum = CSL_DAT_QCHA_0;
    datSetup.regionNum = CSL_DAT_REGION_GLOBAL ;
    datSetup.tccNum = 1;
    datSetup.paramNum = 0 ;
    datSetup.priority = CSL_DAT_PRI_0;
    
    /* Initialize the memory  */
    for (loopIdx = 0; loopIdx < NUM_OF_BYTES; loopIdx++){
        src[loopIdx] = loopIdx;
        dst[loopIdx] = 0xff;
    }
    
    /* opening the dat module */    
    DAT_open (&datSetup);
    
    /* Copies a linear block of data from Src to Dst */ 
    id = DAT_copy (&src, &dst, NUM_OF_BYTES);
    
    /* Waits for a previous transfer to complete */
    DAT_wait(id);
    
    /* Verify received data */
    for (loopIdx = 0; loopIdx < NUM_OF_BYTES; loopIdx++) {
        if (dst[loopIdx] != loopIdx) {
            printf("Linear block of data transfer from src to dst is failed\n");
            pass = 0;
        }
    }
    
    fillVal = FILL_VALUE;
    
    /* Fills a linear block of memory with the specified fillVal
        using EDMA */
    DAT_fill (&dst, NUM_OF_BYTES, &fillVal);
    DAT_wait (id);
    
    /* Verify fill data */
    for (loopIdx = 0; loopIdx < NUM_OF_BYTES; loopIdx++) {
        if (dst[loopIdx] != ((Uint8)fillVal)) {
            printf("Filling linear block of memory with the specified ");
            printf("fillVal is failed\n");
            pass = 0;
        }
    }
  
    return DAT_CSL_EXA_OK;
}

/*
 * =============================================================================
 *   @func  dat_2dXfer
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      The example function shows the usage of dat CSL APIs.This examples  
 *      performs  2D data transfers iteratively using DAT module.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
Int dat_2dXfer (void) 
{          
    Int         loopIdx,inLoopIdx; 
    Int         id = 0;
    DAT_Setup   datSetup;
    Uint8       srcVal = 4;

    /* dat setup */
    datSetup.qchNum = CSL_DAT_QCHA_0;
    datSetup.regionNum = CSL_DAT_REGION_GLOBAL ;
    datSetup.tccNum = 1;
    datSetup.paramNum = 0 ;
    datSetup.priority = CSL_DAT_PRI_0;
    
    /* opening the dat module */        
    DAT_open (&datSetup);   
    
    /* Initialize the source memory  */
    for (loopIdx = 0; loopIdx < NUMBER_OF_ROW; loopIdx++) {
        for (inLoopIdx = 0; inLoopIdx < ARRAY_INDEX ; inLoopIdx++)
        src2d[loopIdx][inLoopIdx] = loopIdx*0x10 + inLoopIdx;
        src2d[loopIdx][ARRAY_INDEX ] = srcVal;
        src2d[loopIdx][ARRAY_INDEX + 1 ] = srcVal;
        src2d[loopIdx][ARRAY_INDEX + 2 ] = srcVal;
        src2d[loopIdx][ARRAY_INDEX + 3 ] = srcVal;
    }   
    
    /* Initialize the destination memory  */
    for (loopIdx = 0; loopIdx < NUMBER_OF_ROW; loopIdx++) {
        for (inLoopIdx = 0; inLoopIdx < LINE_PITCH; inLoopIdx++)
            dst2d[loopIdx][inLoopIdx] = 0;
    }
    
    /* Performs a 2-dimensional(2D2D) data copy using EDMA */
    DAT_copy2d (DAT_2D2D, src2d, dst2d, ARRAY_INDEX , \
                NUMBER_OF_ROW, LINE_PITCH);
    
    /* Waits for a previous transfer to complete */
    DAT_wait(id);
    
    /* Verify received data  */
    for (loopIdx = 0; loopIdx < NUMBER_OF_ROW; loopIdx++) {
        for (inLoopIdx = 0; inLoopIdx < ARRAY_INDEX ; inLoopIdx++)
            if (src2d[loopIdx][inLoopIdx] != (loopIdx*0x10 + inLoopIdx)) {
                printf("2-dimensional(2D2D) data copy using EDMA is failed\n");
                pass = 0;
            }
    }
        
    for (loopIdx = 0; loopIdx < NUMBER_OF_ROW*ARRAY_INDEX ; loopIdx++)
        dst1d[loopIdx] = 0;

    /* Performs a 2-dimensional data copy (2D1D) using EDMA */
    DAT_copy2d (DAT_2D1D, src2d, dst1d, ARRAY_INDEX , \
                NUMBER_OF_ROW, LINE_PITCH);
    
    /* Waits for a previous transfer to complete */
    DAT_wait(id);
    
    /* Verify received data  */
    for (loopIdx = 0; loopIdx < NUMBER_OF_ROW*ARRAY_INDEX ; loopIdx++)
        if (dst1d[loopIdx] != loopIdx) {
            printf("2-dimensional(2D1D) data copy using EDMA is failed\n");
            pass = 0;   
        }
        
    /* Initialize the source memory for 1D */
    for (loopIdx = 0; loopIdx < NUMBER_OF_ROW*ARRAY_INDEX ; loopIdx++)
        src1d[loopIdx] = loopIdx;   
    
    /* Initialize the destination memory for 2D */
    for (loopIdx = 0; loopIdx < NUMBER_OF_ROW; loopIdx++) {
        for (inLoopIdx = 0; inLoopIdx < LINE_PITCH; inLoopIdx++)
            dst2d[loopIdx][inLoopIdx] = 0;
    }
    
    /* Performs a 2-dimensional data copy (1D2D) using EDMA */
    DAT_copy2d (DAT_1D2D, src1d, dst2d, ARRAY_INDEX , NUMBER_OF_ROW, LINE_PITCH);   
    
    /* Waits for a previous transfer to complete */
    DAT_wait (id);
    
    /* verify write */
    for (loopIdx = 0; loopIdx < NUMBER_OF_ROW; loopIdx++) {
        for (inLoopIdx = 0; inLoopIdx < ARRAY_INDEX ; inLoopIdx++)
            if (dst2d[loopIdx][inLoopIdx] != (0x10*loopIdx + inLoopIdx)) {
                printf("2-dimensional(1D2D) data copy using EDMA is failed\n");
                pass = 0;
            }
    }
    
    return DAT_CSL_EXA_OK;   
}   

