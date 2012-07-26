/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_pwrdwnHwSetup.c
 *
 *   @path  $(CSLPATH)\src\pwrdwn
 *
 *   @desc  File for functional layer of CSL API CSL_pwrdwnHwSetup ()
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
 *   @n@b CSL_pwrdwnHwSetup
 *
 *   @b Description
 *   @n It configures the  PWRDWN instance registers as per the values passed
 *      in the hardware setup structure.
 *
 *   @b Arguments
 *   @verbatim
            hPwrdwn         Handle to the pwrdwn instance

            setup           Pointer to hardware setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Hardware structure is not
 *                                                properly initialized
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_pwrdwnInit(), CSL_pwrdwnOpen() must be opened prior to this call
 *
 *   <b> Post Condition </b>
 *   @n  The specified instance will be setup according to value passed
 *
 *   @b Modifies
 *   @n Hardware registers for the specified instance
 * 
 *   @b Example:
     @verbatim
        CSL_PwrdwnObj pwrObj;
        CSL_PwrdwnHwSetup pwrSetup;
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
    
        // Close handle
        CSL_pwrdwnClose(hPwr);
    @endverbatim
 * ============================================================================  
 */
#pragma CODE_SECTION (CSL_pwrdwnHwSetup, ".text:csl_section:pwrdwn");
CSL_Status CSL_pwrdwnHwSetup (
    CSL_PwrdwnHandle    hPwrdwn,
    CSL_PwrdwnHwSetup   *setup
)
{
    /* This is a pointer to the registers of the instance of L2 PWRDWN
     *  referred to by this object
     */
    CSL_Status status = CSL_SOK;

    if (hPwrdwn == NULL) {
        return CSL_ESYS_BADHANDLE;
    }

    else if (setup == NULL) {
        return CSL_ESYS_INVPARAMS;
    }

    else {
            CSL_FINS(hPwrdwn->pdcRegs->PDCCMD, PDC_PDCCMD_MEGPD, setup->idlePwrdwn); 
    
            if (setup->manualPwrdwn) {
                hPwrdwn->l2pwrdwnRegs->L2PDWAKE[0] = 
                                                setup->manualPwrdwn->port0PageWake;
                hPwrdwn->l2pwrdwnRegs->L2PDWAKE[1] = 
                                                setup->manualPwrdwn->port1PageWake;
                hPwrdwn->l2pwrdwnRegs->L2PDSLEEP[0] = 
                                                setup->manualPwrdwn->port0PageSleep;
                hPwrdwn->l2pwrdwnRegs->L2PDSLEEP[1] = 
                                                setup->manualPwrdwn->port1PageSleep;
            }
    }
    return status;
}
