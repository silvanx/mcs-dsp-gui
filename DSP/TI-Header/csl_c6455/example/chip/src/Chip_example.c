/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** ===========================================================================
 *   @file  Chip_example.c
 *
 *   @path  $(CSLPATH)\example\chip\src
 *
 *   @desc  Example of CHIP
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n The example shows how to use CHIP CSL for following operation
 *      1. Reads the value from the chip register
 *      2. Writes the value to the chip register
 *
 *  =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Chip_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* ============================================================================
 *  Revision History
 *  ===============
 *  26-Jul-2005 ds  File created
 *
 *  16-Dec-2005 ds  Updated documentation 
 * ============================================================================
 */
 
#include <csl_chip.h>
#include <soc.h>
#include <stdio.h>

/* Forward declaration */
void chip_example (void);

/* Globals variable */
Uint16   chipExampleFail = 0;

/*
 * =============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine for the file.
 *
 * =============================================================================
 */
void main (void)
{
    
    /* Invoke example */
    chip_example ();
    
    if (chipExampleFail > 0) {
        printf ("Example Failed:Chip write/read Reg Failed\n");
        return;
    }
    else 
        printf ("Example Passed:Chip write/read Reg Passed\n");
    
    printf("==============================================================\n");
    
    return;
}

/*
 * =============================================================================
 *   @func  chip_example
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This example shows how chip csl can be utilized to read and write chip
        registers 
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void chip_example (void)
{
    Uint32      val;
    Uint32      prevValue;
    
    printf ("Running CHIP module CSL example\n\n");
    
    /* write value into CSL_CHIP_ISR register */
    val = 0x00008000;
    CSL_chipWriteReg(CSL_CHIP_ISR , val);
    
    /* write one more value into CSL_CHIP_ISR register and get the old value */
    val = 0x00001000;
    prevValue = CSL_chipWriteReg(CSL_CHIP_ISR , val);
    
    /* Check the previously written value  */
    if (prevValue == 0x00008000)
        printf("Chip write reg passed\n");
    else {
        printf("Chip write reg failed\n");
        chipExampleFail++;
        return;
    }
    
    /* read the value from CSL_CHIP_ISR */
    prevValue = CSL_chipReadReg(CSL_CHIP_ISR);
    
    /* Check the previously written value  */  
    if (prevValue == 0x00009000)
        printf("Chip read reg passed\n");         
    else {
        printf("Chip read reg failed \n");
        chipExampleFail++;
        return;
    }
     
    return;
}
