/* ============================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/* ============================================================================
 *  @file Bwmngmt_example.c
 *
 *  @path $(CSLPATH)\example\bwmngmt\src
 *   
 *  @desc Example for BWMNGMT CSL
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This example, 
 *        1. Initializes and opens the CSL BWMNGMT module instance.
 *        2. Sets up the hardware to default values and mapPriority,
 *           ControlBlocks i.e., CSL_bwmngmtHwSetup() is called for 
 *           module configuration.
 *        3. Read back the hardware setup parameters 
 *        4. Does the comparision of configured setup parameters and red 
 *           hardware setup parameters  
 *        5. Displays the messages based on step 4
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Bwmngmt_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  23-sept-2005   PSK File Created
 *
 *  16-Dec-2005    ds  Updated documentation
 * =============================================================================
 */

#include <csl_bwmngmt.h>
#include <soc.h>
#include <stdio.h>

/* Forward declarations */
void bwmngmt_example (void);
CSL_Status bwmngmtHwSetupVerify(CSL_BwmngmtHwSetup*, CSL_BwmngmtHwSetup*);

/* Handle for the BWMNGMT instance */
CSL_BwmngmtHandle    hBwmngmt;

/* Global variable used to log the error */
Uint32 bwmngmtExampleFailed = 0;

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
    bwmngmt_example();

    return;
}

/*
 * =============================================================================
 *   @func   bwmngmt_example
 *
 *   @desc
 *      This function invokes example that prove functionalites of hardware
 *      setup function with different value for the setup parameters.
 *      The CSL API to retrive hardware setup parameters is also verified
 *      
 *   @arg
 *      None
 *      
 *   @expected result
 *      If the example passes, it displays the message "PASSED"
 *      If the example fails, it displays the messae "FAILED" 
 *
 *   @eg
 *      bwmngmt_example();
 * =============================================================================
*/
void bwmngmt_example (
    void
)
{
    CSL_BwmngmtObj        bwmngmtObj;
    CSL_Status            status;
    
    CSL_BwmngmtHwSetup    hwSetupRead;
    CSL_BwmngmtHwSetup    hwSetup = CSL_BWMNGMT_HWSETUP_DEFAULTS;

    /* Clear local data structures */
    memset(&bwmngmtObj, 0, sizeof(CSL_BwmngmtObj));
    memset(&hwSetupRead, 0, sizeof(CSL_BwmngmtHwSetup));
    
    /* Setup parameters for Bwmngmt */
    hwSetupRead.control = (CSL_BwmngmtControlBlocks)2;
    hwSetup.mapPriority = (CSL_BwmngmtPriority)0x0;
    
    /* Initialize BWMNGMT module */
    status = CSL_bwmngmtInit(NULL);
    if (status != CSL_SOK) {
        printf("BWMNGMT: Initialization... Failed.\n");
        bwmngmtExampleFailed++;
        return;
    }

    /* open the module */
    hBwmngmt = CSL_bwmngmtOpen(&bwmngmtObj, CSL_BWMNGMT, NULL, &status);
    if (status != CSL_SOK || hBwmngmt == NULL) {
        printf ("BWMNGMT: Opening instance... Failed.\n");
        bwmngmtExampleFailed++;
        return;
    }

    /* hardware setup */
    status = CSL_bwmngmtHwSetup(hBwmngmt, &hwSetup);
    if (status != CSL_SOK) {
        printf ("BWMNGMT: HW Setup... Failed.\n");
        bwmngmtExampleFailed++;
        return;
    }

    /* Read back and verify setup */
    status = CSL_bwmngmtGetHwSetup(hBwmngmt, &hwSetupRead);
    if (status != CSL_SOK) {
        printf ("BWMNGMT: Get HW Setup... Failed.\n");
        bwmngmtExampleFailed++;
        return;
    }
    
    /* Verify the setup parameter with red parameters */
    status = bwmngmtHwSetupVerify(&hwSetup, &hwSetupRead);
    if (status != CSL_SOK) {
        printf ("BWMNGMT: Example FAILED.\n");
        return;
    }
    else {
        printf ("BWMNGMT: Example PASSED.\n");
    }

    return;
}


/*
 * =============================================================================
 *   @func   bwmngmtHwSetupVerify
 *
 *   @desc
 *      This function compares the hw setup that was configured and that was
 *      returned by CSL_bwmngmtGetHwSetup() of BWMNGMT.
 *
 *   @arg    Pointer to the original configuration
 *           Pointer to the configuration that was returned by 
 *           bwmngmtGetHwSetup()
 *
 *   @eg
 *      CSL_BwmngmtHwSetup hwSetup;
 *      CSL_BwmngmtHwSetup hwSetupRead;
 *
 *      ...... ;
 *
 *      bwmngmtHwSetupVerify (hwSetup, hwSetupRead);
 * =============================================================================
 */
CSL_Status bwmngmtHwSetupVerify (
    CSL_BwmngmtHwSetup *hwSetup, 
    CSL_BwmngmtHwSetup *hwSetupRead
)
{
    CSL_Status status = CSL_SOK;

    /* Compare each and every filed of hw setup structure and 
     * print the read values.
     */

    /* Cpu Priority value */
    if (hwSetup->cpuPriority != hwSetupRead->cpuPriority) {
        bwmngmtExampleFailed++;
    }
    
    /* Cpu Maxwait value */
    if (hwSetup->cpuMaxwait != hwSetupRead->cpuMaxwait) {
        bwmngmtExampleFailed++;
    }
    
    /* Internal DMA max wait value */
    if (hwSetup->idmaMaxwait != hwSetupRead->idmaMaxwait) {
        bwmngmtExampleFailed++;
    }
    
    /* Slave Port Max Wait value */
    if (hwSetup->slapMaxwait != hwSetupRead->slapMaxwait) {
        bwmngmtExampleFailed++;
    }
    
    /* Master Port Priority value */
    if (hwSetup->mapPriority != hwSetupRead->mapPriority) { 
       bwmngmtExampleFailed++;
    }
   
    /* User Coherance Max Wait value */
    if (hwSetup->ucMaxwait != hwSetupRead->ucMaxwait) {
       bwmngmtExampleFailed++;
    }
   
    if (bwmngmtExampleFailed > 0) {
        status = CSL_ESYS_FAIL;
    }

    return status;
}
