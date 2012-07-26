/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/* ============================================================================
 *   @file  pwrdwnExample.c
 *
 *   @path $(CSLPATH)\example\pwrdwn\src
 *
 *   @desc  Example for pwrdwn module
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *      This function invokes example that prove functionalites of power down 
 *      controller
 *   @n This example, 
 *        1. Initializes and opens the CSL PWRDWN module instance.
 *        2. Sets up the hardware to setup parameters i.e.,  
 *           CSL_pwrdwnHwSetup() is called for module configuration.
 *        3. Puts page0 a port1 into sleep 
 *        4. Gets the page0 status
 *        5. Wakes up the pageo of port1
 *        6. Gets the page0 status
 *        7. Compare the wakeup and sleep page0 status
 *        8. Displays the messages based on step 7
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Pwrdwn_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  28-Jul-2005 PSK  File Created
 *  16-Dec-2005 ds   Updated documentation
 * =============================================================================
 */

#include <csl_pwrdwn.h>
#include <soc.h>
#include <stdio.h>

void pwrdwn_example(void);

Uint32 demoFail = 0;

/*
 * =============================================================================
 *  @func   main
 *
 *  @desc
 *     This is the main routine for the file.
 *
 *  @expected result
 *      If the example passes, it displays the message "PASSED"
 *      If the example fails, it displays the messae "FAILED" 
 *
 * =============================================================================
*/
void main(void)
{
    
    printf("PWRDWN EXAMPLE DEMO\n");
    
    /* Invoke example */
    pwrdwn_example();
    
    if (demoFail > 0) {
        printf("\nPWRDWN:  example Demo... FAILED.\n");
    }
    else {
        printf("\nPWRDWN: example Demo... PASSED\n");
    }

    return;
}

/*
 * =============================================================================
 *   @func   pwrdwn_example
 *
 *   @desc
 *      This function invokes example that prove functionalites of power down 
 *      controller. This example puts a page on a specific port into sleep 
 *      and verifies the status for that page by calling the CSL API to 
 *      retrieve the status parameters.
 *            
 *   @arg
 *      None
 *  
 *   @eg
 *      pwrdwn_example();
 * =============================================================================
*/
void pwrdwn_example (void)
{
    CSL_PwrdwnContext   pContext;
    CSL_PwrdwnObj       pwrdwnObj;
    CSL_PwrdwnHandle    hPwrdwn;
    CSL_Status          status;
    CSL_PwrdwnHwSetup   hwSetup;
    CSL_PwrdwnPortData  pageSleep, response, response1;
    
    CSL_PwrdwnL2Manual  manualPwrdwn;

    manualPwrdwn.port0PageWake  = 0x0;
    manualPwrdwn.port1PageWake  = 0x0;
    manualPwrdwn.port0PageSleep = 0x0;
    manualPwrdwn.port1PageSleep = 0x0;
    
    hwSetup.idlePwrdwn = (Bool)0x0;
    hwSetup.manualPwrdwn = &manualPwrdwn;
    
    /* Initialize the module */
    if (CSL_pwrdwnInit(&pContext) != CSL_SOK) {
        printf("PWRDWN: Initialization...  FAILED\n");
        demoFail++;
    }
    
    /* Clear the local data structures */
    memset(&pwrdwnObj, 0, sizeof(CSL_PwrdwnObj));

    /* Open the module */
    hPwrdwn = CSL_pwrdwnOpen (&pwrdwnObj, (CSL_InstNum)CSL_PWRDWN, NULL, 
                             &status);
    if ((hPwrdwn == NULL) || (status != CSL_SOK)) {
        printf("PWRDWN: Error in opening the instance ...\n");
        demoFail++;
    }
    
    /* Do hardware setup */
    if (CSL_pwrdwnHwSetup(hPwrdwn, &hwSetup) != CSL_SOK) {
        printf("PWRDWN: CSL_pwrdwnHwSetup ... FAILED\n");
        demoFail++;
    }
    
    /* select port number and page which should be put into sleep */
    pageSleep.portNum = (Bool)0x1;
    pageSleep.data = 0x1;
                                                             
    /* Put the selected page into sleep */
    if (CSL_pwrdwnHwControl(hPwrdwn, CSL_PWRDWN_CMD_PAGE0_SLEEP, &pageSleep) \
                                                                 != CSL_SOK) {
        printf("PWRDWN: CSL_pwrdwnHwControl              ... FAILED\n");
        demoFail++; 
    }
        
    
    response.portNum = (Bool)1;
        
    /* Get the status of the page */    
    if (CSL_pwrdwnGetHwStatus (hPwrdwn, CSL_PWRDWN_QUERY_PAGE0_STATUS, 
                                            &response) != CSL_SOK) {
        printf ("PWRDWN: CSL_pwrdwnGetHwStatus              ... FAILED\n");
        demoFail++; 
    }
    
    /* Check for the correct status of the page */
    if ((response.data & 0x1) == 0x1) {
        printf("Status example PASSED\n");
    }
    
    /* Wake up the page */
    if (CSL_pwrdwnHwControl(hPwrdwn, CSL_PWRDWN_CMD_PAGE0_WAKE, &pageSleep)\
                                                      != CSL_SOK) {
        printf("PWRDWN: CSL_pwrdwnHwControlCmd           ... FAILED\n");
        demoFail++; 
    }
        
    if (CSL_pwrdwnGetHwStatus (hPwrdwn, CSL_PWRDWN_QUERY_PAGE0_STATUS,\
                                                  &response1) != CSL_SOK) {
        printf ("PWRDWN: CSL_pwrdwnGetHwStatus            ... FAILED\n");
        demoFail++; 
    }

    if (response.data != response1.data) {
        printf("PWRDWN: functionality example PASSED");    
    }
    else {  
        printf("PWRDWN: functionality example FAILED");
        demoFail++;
    }

    return;
}
