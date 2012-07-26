/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** ============================================================================
 *
 *   @file  Idma_example.c
 *
 *   @path  $(CSLPATH)\example\idma\src
 *
 *   @desc  Example of IDMA CSL
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n The example shows how to use the idma for data transfer from one memory 
 *      area to another memory area
 *      This example demonstrates the following operations.
 *       - Initializes IDMA channel 1
 *       - Sets channel 1 to have priority 7 and interrupt event generation on 
 *       - Initializes IDMA channel 0
 *       - Sets channel 0 to have interrupt event generation on 
 *       - Clears dst1 array 
 *       - Perform copy of data from src to dst1
 *       - Waits until copying is completed  
 *       - Compars the source and destination buffers
 *       - Fill the dst1 array with the value "0xAAAABABA"
 *       - Copies dst1 data into dst0.  
 *       - Gets IDMA1 status is active after the submission for the transfer
 *       - Does the data comparision to ensure the copied data is proper or 
 *         not and 
 *       - Displays the result based on previous step
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Idma_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* ============================================================================
 *  Revision History
 *  ===============
 *  27-Jul-2005 ds     File Created
 *
 *  16-Dec-2005 ds     Updated documentation 
 * ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <csl_idma.h>


/* Align various arrays to a double word address, in internal L2 */
#pragma DATA_SECTION(src,   "ISRAM");
#pragma DATA_SECTION(dst0,  "ISRAM1");
#pragma DATA_SECTION(dst1,  "ISRAM1");
#pragma DATA_ALIGN(src,      8);
#pragma DATA_ALIGN(dst0,     8);
#pragma DATA_ALIGN(dst1,     8);

/*  Static 80 byte array of data in "src"  */
Uint32 src[20] =
{
    0xDEADBEEF, 0xFADEBABE, 0x5AA51C3A, 0xD4536BA3,
    0x5E69BA23, 0x4884A01F, 0x9265ACDA, 0xFFFF0123,
    0xBEADDABE, 0x234A76B2, 0x9675ABCD, 0xABCDEF12,
    0xEEEECDEA, 0x01234567, 0x00000000, 0xFEEDFADE,
    0x0A1B2C3D, 0x4E5F6B7C, 0x5AA5ECCE, 0xFABEFACE
};

/*  Static 80 byte array of data in "dst0"  */
Uint32 dst0[0x200] =
{
    0x00010203, 0x04050607, 0x08090A0B, 0x10111213,
    0x14151617, 0x18191A1B, 0x1C1D1E1F, 0x20212123,
    0x24252627, 0x28292A2B, 0x2C2D2E2F, 0x30313233,
    0x34353637, 0x38393A3B, 0x3C3D3E3F, 0x40414243,
    0x44454647, 0x48494A4B, 0x4C4D4E4F, 0x50515253
};

/* Forward declaration */
void idma_example (void);

/*  Array in which results will be copied over */
Uint32      dst1[0x200];

/* Global variable to check fail status of example */
Uint32      idmaExampleFailed = 0;


void main(void)
{
    /* Invoke a example */
    idma_example ();
    
    if (idmaExampleFailed > 0) {
        printf ("<<Example Failed>>: example failed. [Examples failed: %d]\n", \
                                                           idmaExampleFailed);
    }
    else {
        printf ("<<Example Passed>>: Idma example passed.\n");
    }
    
    printf("===============================================================\n");
    
    return;
}

/*
 * =============================================================================
 *   @func  idma_example
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This example shows how idma csl performs the data transfer between 
 *      source and destination buffers
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void idma_example (void)
{
    Uint32        cnt0;
    Uint32        cnt1;
    Uint32        stat;
    Uint32        count;

    /* Initialize IDMA Channel 1                               
     * Set Chan 1 to have Priority 7 and Interrupt Event Gen On 
     */
    cnt1 = IDMA1_init(IDMA_PRI_7, IDMA_INT_EN);

    printf("Runnning IDMA Example \n");
                            
    if (cnt1 != 0xF0000000){
        printf("Set the channel 1 to have priority 7 and interrupt event ");
        printf("generation enable failed.\n");
        idmaExampleFailed++;
        return;
    }
    else {
        printf("Set the channel 1 to have priority 7 and interrupt event ");
        printf("generation enable passed.\n");
        printf("Channel 0 initialization passed.\n");
    }

    /* Initialize IDMA channel 0                
     * Set channel 0 to have interrupt event generation ON 
     */
    cnt0 = IDMA0_init(IDMA_INT_EN);

    if (cnt0 != 0x10000000){
        printf("Set the channel 0 to have interrupt event generation ");
        printf("enable failed.\n");
        idmaExampleFailed++;
        return;
    }
    else {
        printf("Set the channel 0 to have interrupt event generation ");
        printf("enable passed.\n");
    }

    /* Clear dst1 array */
    memset(dst1, 0, sizeof(dst1));

    /* Copy src to dst1 - 80 bytes - 20 words */
    IDMA1_copy(src, dst1, 80);

    /* Wait until copying is completed */
    IDMA1_wait();

    /* Comparing the source and destination buffers */
    if (memcmp(src, dst1, sizeof(src))) {
        printf("IDMA: data copy from source to destination using idma is ");
        printf("failed\n");
        idmaExampleFailed++;
        return;
    }
    else {
        for(count = 0; count < 20; count++)
             printf("value of src[%d]: 0x%x,value of dst[%d]: 0x%x\n", \
                          count, src[count], count, dst1[count]);
        printf("IDMA: data copy from source to destination using idma is ");
        printf("passed\n");
    }
    
    printf("===============================================================\n");
    
    /*
     * The following shows fill capability of Channel   
     * 1. First fill the dst1 array with the value "0xAAAABABA".     
     * 2. Now copy dst1 into dst0.                                   
     *                                                               
     * This is an example of a backward transfer where address of    
     * "dst0" is less than "dst1".                                   
     */

    printf("Data fill example\n");
    
    IDMA1_fill(dst1, 0x800, 0xAAAABABA);
    
    /* This simulator requires IDMA1_wait between all transfers for  
     * the transfers to work correctly.                              
     */   
    IDMA1_wait();
    
    for(count = 0; count < 20; count++)
        printf("value of dst[%d]: 0x%x\n",count,dst1[count]);
       
    
    /* Perform the transfer from "dst1" to "dst0". Recall that    
     * "dst1" was just filled with a constant pattern 0xAAAABABA.   
     * Also verify that getStatus function is working by checking if
     * IDMA1 status is ACTV after the submission for the transfer   
     */
    IDMA1_copy(dst1, dst0, 0x800);
    stat = IDMA1_getStatus();
    if(stat != 1) {
        printf("IDMA channel 1 not in the active status.\n");
        idmaExampleFailed++;
        return;
    }
    else {
        printf("IDMA channel 1 in the active status.\n");
    }
    
    /* IDMA1_wait() waits until all previous transfers for IDMA Channel 1
     * have been completed
     */
    IDMA1_wait();
        
    if (memcmp(dst0, dst1, sizeof(dst0))) {
        printf("IDMA: data fill failed.\n");
        idmaExampleFailed++;
        return;
    }
    else {
        printf("IDAM: data fill passed.\n");
    }

    return;
}
