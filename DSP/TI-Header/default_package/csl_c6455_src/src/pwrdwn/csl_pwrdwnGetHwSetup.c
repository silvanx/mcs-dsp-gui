/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_pwrdwnGetHwSetup.c
 *
 *   @path  $(CSLPATH)\src\pwrdwn
 *
 *   @desc  File for functional layer of CSL API CSL_pwrdwnGetHwSetup ()
 *
 */
 
/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 * =============================================================================
 */
 
#include <csl_pwrdwn.h>

/** ===========================================================================
 *   @n@b CSL_pwrdwnGetHwSetup
 *
 *   @b Description
 *   @n It retrives the hardware setup parameters
 *
 *   @b Arguments
 *   @verbatim
         hPwr        Handle to the PWRDWN instance

         hwSetup     Pointer to hardware setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup retrived
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @b CSL_pwrdwnInit(), CSL_pwrdwnOpen() must be opened prior to this call.
 *
 *   <b> Post Condition </b>
 *   @n  The hardware set up structure will be populated with values from
 *       the registers
 *
 *   @b Modifies
 *   @n None
 *   
 *   @b Example
     @verbatim
       CSL_PwrdwnObj pwrObj;
       CSL_PwrdwnHwSetup pwrSetup, querySetup;
       CSL_PwrdwnHandle hPwr;
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
    
       // Query Setup
       CSL_pwrdwnGetHwSetup(hPwr,&querySetup);
    
       // Close handle
       CSL_pwrdwnClose(hPwr);

     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_pwrdwnGetHwSetup, ".text:csl_section:pwrdwn");
CSL_Status CSL_pwrdwnGetHwSetup (
    CSL_PwrdwnHandle  hPwrdwn,
    CSL_PwrdwnHwSetup *setup
)
{
    CSL_Status status = CSL_SOK;
    
    /* This is a pointer to the registers of the instance of L2 PWRDWN
     * referred to by this object
     */
    
    if (hPwrdwn == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }

    else if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    } 
    
    else {
        setup->idlePwrdwn = (Bool)CSL_FEXT(hPwrdwn->pdcRegs->PDCCMD, \
                                       PDC_PDCCMD_MEGPD);      
        if (setup->manualPwrdwn) {
            setup->manualPwrdwn->port0PageWake = 
                              CSL_FEXTR(hPwrdwn->l2pwrdwnRegs->L2PDWAKE[0], 2, 0);
            setup->manualPwrdwn->port1PageWake = 
                              CSL_FEXTR(hPwrdwn->l2pwrdwnRegs->L2PDWAKE[1], 2, 0);
            setup->manualPwrdwn->port0PageSleep = 
                              CSL_FEXTR(hPwrdwn->l2pwrdwnRegs->L2PDSLEEP[0], 2, 0);
            setup->manualPwrdwn->port1PageSleep = 
                              CSL_FEXTR(hPwrdwn->l2pwrdwnRegs->L2PDSLEEP[1], 2, 0);
        }
    }    
    return status;
}

