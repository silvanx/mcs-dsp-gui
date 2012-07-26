/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_pwrdwnHwControl.c
 *
 *   @path  $(CSLPATH)\src\pwrdwn
 *
 *   @desc  File for functional layer of CSL API CSL_pwrdwnHwControl ()
 *
 */
 
/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 * =============================================================================
 */
 
#include <csl_pwrdwn.h>
#include <csl_pwrdwnAux.h>

/** ===========================================================================
 *   @n@b CSL_pwrdwnHwControl
 *
 *   @b Description
 *   @n This function performs various control operations on the PWRDWN
 *      instance based on the command passed.
 *
 *   @b Arguments
 *   @verbatim
            hPwrdwn Handle to the PWRDWN instance

            cmd     Operation to be performed on the PWRDWN

            cmdArg  Arguement specific to the command
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Command execution successful.
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVCMD    - Invalid command
 *   @li                    CSL_ESYS_INVPARAMS - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   CSL_pwrdwnInit(), CSL_pwrdwnOpen() must be opened prior to this call
 *
 *   <b> Post Condition </b>
 *   @n  Registers of the PWRDWN instance are configured according to the 
 *       command and the command arguments. The command determines which  
 *       registers are modified.
 *
 *   @b Modifies
 *   @n Registers determined by the command
 *
 *   @b Example:
     @verbatim
        CSL_PwrdwnObj pwrObj;
        CSL_PwrdwnHwSetup pwrSetup;
        CSL_PwrdwnHandle hPwr;
        CSL_PwrdwnPortData pageSleep;

        // Init Module
        ...
        if (CSL_pwrdwnInit(NULL) != CSL_SOK)
            exit;
        // Opening a handle for the Module  
        hPwr = CSL_pwrdwnOpen (&pwrObj, CSL_PWRDWN, NULL, NULL);
    
        // Setup the arguments for the Setup structure
        ...
    
        // Setup
        CSL_pwrdwnHwSetup(hPwr,&pwrSetup);
    
        // Hw Control
        pageSleep.portNum = 0x1;
        pageSleep.data = 0x0;
        CSL_pwrdwnHwControl(hPwr,CSL_PWRDWN_CMD_PAGE0_SLEEP,&pageSleep);
    
        // Close handle
        CSL_pwrdwnClose(hPwr);
     @endverbtim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_pwrdwnHwControl, ".text:csl_section:pwrdwn");
CSL_Status CSL_pwrdwnHwControl (
    CSL_PwrdwnHandle        hPwrdwn,
    CSL_PwrdwnHwControlCmd  cmd,
    void                    *arg
)
{
    CSL_Status status = CSL_SOK;
    
    if (hPwrdwn == NULL) {
        return CSL_ESYS_BADHANDLE;
    }
    
    else if ((arg == NULL)  && ((cmd >= 0) && \
                    (cmd <= CSL_PWRDWN_CMD_PAGE1_WAKE))) {
        return CSL_ESYS_INVPARAMS;
    } 

    else {
        switch (cmd) {
            case CSL_PWRDWN_CMD_PAGE0_SLEEP:
                status = CSL_pwrdwnPage0Sleep(hPwrdwn, (CSL_PwrdwnPortData *)arg);
                break;

            case CSL_PWRDWN_CMD_PAGE1_SLEEP:
                status = CSL_pwrdwnPage1Sleep(hPwrdwn, (CSL_PwrdwnPortData *)arg);
                break;

            case CSL_PWRDWN_CMD_PAGE0_WAKE:
                status = CSL_pwrdwnPage0Wake(hPwrdwn, (CSL_PwrdwnPortData *)arg);
                break;

            case CSL_PWRDWN_CMD_PAGE1_WAKE:
                status = CSL_pwrdwnPage1Wake(hPwrdwn, (CSL_PwrdwnPortData *)arg);
                break;
        
            default:
                status = CSL_ESYS_INVCMD ;
                break;
        }
    }
    return status;
}
