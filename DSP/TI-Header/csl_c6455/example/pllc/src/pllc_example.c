/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *   @file  Pllc_example.c
 *
 *  @path $(CSLPATH)\example\pllc\src
 *
 *   @desc  Example of PLLC module CSL
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n The example shows PLLC module CSL usage
 *      1. Initalize the PLLC hardware setup data structure with default values
 *      2. Intialize PLLC module
 *      3. Set new values for divider 4
 *      4. Set the value using hardware control command
 *      5. Close the module
 *  ============================================================================
 *
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used.
 *         Refer CCS manual for setup configuration.
 *      2. Load required GEL file depending on the board used.
 *      3. Launch CCS window.
 *      4. Open project pllc_example.pjt.
 *      5. Build the project and load the .out file of the project.
 *
 *   @endverbatim
 *
 *
 *  ============================================================================
 */

/*  ============================================================================
 *  Revision History
 *  ===============
 *  22-Sep-2005 Tej File Modified.
 *  19-Dec-2005 SD  Modified according to the review comments 
 *  06-Feb-2006 SD  Modified according to the spec changes
 *
 *  ============================================================================
 */
#include <stdio.h>
#include <csl_pllc.h>

/* PLLC module handle structure */
CSL_PllcHandle           hPllc = NULL;

/* forward declarations*/
void pllc_csl_example (void);
void pllc_error_exit (void);
/*
 *  ============================================================================
 *  @func   main
 *
 *  @desc
 *     This is the main routine for the file.
 *
 *  @arg
 *      NONE
 *
 *  @return
 *      NONE
 *  ============================================================================
*/
void main (
    void
)
{
    /* Call the example routine */ 
    pllc_csl_example ();

}

/*
 *  ============================================================================
 *  @func   pllc_csl_example
 *
 *  @desc
 *      1. Initalize the PLLC hardware setup data structure with default values
 *      2. Intialize PLLC module
 *      3. Set new values for divider 4
 *      4. Set the value using hardware control command
 *      5. Close the module
 *
 *  @arg
 *      NONE
 *
 *  @return
 *      NONE
 *  ============================================================================
*/
void pllc_csl_example (
    void
)
{
    CSL_PllcObj              pllcObj;
    CSL_Status               status;
    CSL_PllcHwSetup          hwSetup;
    CSL_PllcHwSetup          hwSetupRead;
    CSL_PllcDivideControl    arg;
    CSL_PllcDivRatio         arg1;
    CSL_BitMask32            response;   
    CSL_BitMask32            argPllCtrl;    

    /* Initialize the PLLC CSL module */
    status = CSL_pllcInit(NULL);

    if (status != CSL_SOK) {
        printf ("PLLC: Initialization... Failed.\n");
        printf ("\tReason: CSL_pllcInit failed. [status = 0x%x].\n", status);
        return;
    }

    /* Clear local data structures */
    memset(&pllcObj, 0, sizeof(CSL_PllcObj));

    /* Open the PLLC CSL module */
    hPllc = CSL_pllcOpen (&pllcObj, CSL_PLLC_1, NULL, &status);

    if ((hPllc == NULL) || (status != CSL_SOK)) {
        printf ("PLLC: Open... Failed.\n");
        printf ("\tReason: Error opening the instance. [status = 0x%x, "\
                "hPllc = 0x%x].\n", status, hPllc);
        return;
    }

    /* Setup PLLC hardware parameters */
    hwSetup.divEnable  = (CSL_BitMask32) CSL_PLLC_DIVEN_PLLDIV4 | CSL_PLLC_DIVEN_PREDIV |
                            CSL_PLLC_DIVEN_PLLDIV5;

    hwSetup.preDiv     = (Uint32)        0x00000002;
    hwSetup.pllM       = (Uint32)        0x000000015;
    hwSetup.pllDiv4    = (Uint32)        0x00000002;
    hwSetup.pllDiv5    = (Uint32)        0x00000002;

    status = CSL_pllcHwSetup (hPllc, &hwSetup);

    if (status != CSL_SOK) {
        printf ("PLLC: HwSetup... Failed.\n");
        printf ("\tReason: Error setting up the hardware."\
                " [status = 0x%x, hPllc = 0x%x].\n", status, hPllc);
        pllc_error_exit ();
        return;
    }

    /* Read back */

    status = CSL_pllcGetHwSetup (hPllc, &hwSetupRead);

    if (status != CSL_SOK) {
        printf ("PLLC: Hardware setup parameters reading... Failed.\n");
        printf ("\tReason: Error setting in hardware validation."\
                " [status = 0x%x, hPllc = 0x%x].\n", status, hPllc);
        pllc_error_exit ();

    }

    /* Change divider settings for PLLDIV4 */

    /* Wait if another GO operation is currently in progress.*/
    do {
        CSL_pllcGetHwStatus (hPllc, CSL_PLLC_QUERY_STATUS, &response);
    } while (response & CSL_PLLC_STATUS_GO);

    /* Command to enable PLLDIV4 */
    arg.divNum = CSL_PLLC_DIVSEL_PLLDIV4;
    arg.divCtrl = CSL_PLLC_PLLDIV_ENABLE;

    status = CSL_pllcHwControl (hPllc, CSL_PLLC_CMD_PLLDIV_CONTROL,
                                   &arg);
    if (status != CSL_SOK) {
        printf ("PLLC: HwControl for PLL Divider Control... Failed.\n");
        printf ("\tReason: Error in Divider Control."\
                " [status = 0x%x, hPllc = 0x%x].\n", status, hPllc);
        pllc_error_exit ();
        return;
    }

    /* Command to change PLLDIV4 Divider Ratio */
    arg1.divNum = CSL_PLLC_DIVSEL_PLLDIV4;    
    arg1.divRatio = 0x00000004;

    status = CSL_pllcHwControl (hPllc, CSL_PLLC_CMD_SET_PLLRATIO,
                                   &arg1);

    if ((status != CSL_SOK) || (status == CSL_ESYS_INVPARAMS))
    {
        printf ("PLLC: HwControl for PLL Divider Ratio Set Command "\
                "Control... Failed.\n");
        printf ("\tReason: Error in Control for Divider Ratio Set Command."\
                " [status = 0x%x, hPllc = 0x%x].\n", status, hPllc);
        pllc_error_exit ();
        return;
    }

    /* Set GOSET bit to change/set the dividers */
    argPllCtrl = 0x010000;   /* value to set the GOSET bit */ 
    status = CSL_pllcHwControl (hPllc, CSL_PLLC_CMD_PLLCONTROL,
                                   &argPllCtrl);
    if (status != CSL_SOK) {
        printf ("PLLC: HwControl for PLL command control... Failed.\n");
        printf ("\tReason: Error in PLL Command Control."\
                " [status = 0x%x, hPllc = 0x%x].\n", status, hPllc);
        pllc_error_exit ();
        return;
    }

    /* Poll for divide-ratio change and clock alignment to complete */
    do {
        CSL_pllcGetHwStatus (hPllc, CSL_PLLC_QUERY_STATUS, &response);
    } while (response & CSL_PLLC_STATUS_GO);

    /* Close the module */
    status = CSL_pllcClose (hPllc);
    if (status != CSL_SOK) {
        printf ("PLLC: Close the instance ... Failed\n");
    }

    printf("PLLC example complete \n");

    return;
}

/*
 *  ============================================================================
 *  @func   pllc_error_exit
 *
 *  @desc
 *     This calls the module close function in case of error
 *
 *  @arg
 *      NONE
 *
 *  @return
 *      NONE
 *  ============================================================================
 */
void pllc_error_exit (
    void
)
{
    CSL_Status               status;

    /* Closes the module */
    status = CSL_pllcClose (hPllc);
    if (status != CSL_SOK) {
        printf ("PLLC: Close Pllc instance... Failed\n");
    }
}
